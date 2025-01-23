
#include "../features.hpp"

auto client::features::combat::backtrack::run(client::mapper::__minecraft& minecraft, bool draw_bounds) -> void
{
	if (!client::features::combat::backtrack::enabled)
		return;

	if (minecraft.get_current_screen().object != nullptr)
		return;

	auto timer_partial_ticks = minecraft.get_timer().get_partial_ticks();

	auto local_player = minecraft.get_local_player();
	auto local_player_view_position = local_player.get_view_position(timer_partial_ticks);
	auto local_player_look_position = local_player.get_look_position(timer_partial_ticks);

	if (client::mapper::version != client::mapper::supported_versions::MINECRAFT_17)
		local_player_view_position.y += 1.62;

	auto local_player_view_vector = client::mapper::__vec3(
		local_player_view_position.x + local_player_look_position.x * (client::features::combat::reach::enabled ? client::features::combat::reach::distance : 3.),
		local_player_view_position.y + local_player_look_position.y * (client::features::combat::reach::enabled ? client::features::combat::reach::distance : 3.),
		local_player_view_position.z + local_player_look_position.z * (client::features::combat::reach::enabled ? client::features::combat::reach::distance : 3.)
	);

	struct __player_tick_data
	{
		unsigned __int64 kernel_system_time = 0;
		client::mapper::__vec3 view_position;
		std::pair<client::mapper::__vec3, client::mapper::__vec3> bounding_box_bounds;
		bool draw = false;
	};

	struct __player_data
	{
		sdk::__multibyte_string name;
		__player_tick_data player_tick_data[20];
	};

	static auto players_data = std::vector<__player_data>();

	/*
	if (draw_bounds)
	{
		auto local_player_view_position = minecraft.get_local_player().get_view_position(minecraft.get_timer().get_partial_ticks());

		for (auto& player_data : players_data)
		{
			for (unsigned __int64 x = 0; x < 20; ++x)
			{
				if (player_data.player_tick_data[x].draw)
				{
					if (local_player_view_position.get_distance_to_vec3(player_data.player_tick_data[x].view_position) > 255.)
						continue;

					client::features::visual::render_3d_bounding_box(
						{ player_data.player_tick_data[x].view_position.x - local_player_view_position.x, player_data.player_tick_data[x].view_position.y - local_player_view_position.y, player_data.player_tick_data[x].view_position.z - local_player_view_position.z },
						client::features::visual::player_esp_3d::color,
						client::features::visual::player_esp_3d::draw_health,
						0.f,
						client::features::visual::player_esp_3d::draw_hurt_time,
						0
					);
				}
			}
		}

		return;
	}

	for (auto& player_data : players_data)
	{
		for (unsigned __int64 x = 0; x < 20; ++x)
			player_data.player_tick_data[x].draw = false;
	}
	*/

	for (auto& player : minecraft.get_world().get_players())
	{
		if (client::mapper::jni->IsSameObject(local_player.object, player.object))
			continue;

		auto player_name = player.get_name();

		auto player_found = false;

		for (auto& player_data : players_data)
		{
			if (player_name.equals(player_data.name.get_multibyte_string()))
			{
				player_found = true;

				sdk::copy_memory((unsigned __int64)&player_data.player_tick_data[1], (unsigned __int64)&player_data.player_tick_data[0], sizeof(__player_tick_data) * 19);

				player_data.player_tick_data[0].kernel_system_time = KERNEL_SYSTEM_TIME;
				player_data.player_tick_data[0].view_position = player.get_view_position(timer_partial_ticks);
				player_data.player_tick_data[0].bounding_box_bounds = player.get_bounding_box().get_bounds();

				for (unsigned __int64 x = 0; x < 20; ++x)
				{
					if (sdk::__timer(player_data.player_tick_data[x].kernel_system_time, KERNEL_SYSTEM_TIME).has_elapsed(client::features::combat::backtrack::delay))
						continue;

					auto player_bounding_box = player.get_bounding_box();

					auto player_bounding_box_bounds = player_bounding_box.get_bounds();

					auto player_position = player.get_position();

					player_bounding_box_bounds.first.x = player_position.x - .4;
					player_bounding_box_bounds.first.y = player_position.x - .1;
					player_bounding_box_bounds.first.z = player_position.x - .4;
					player_bounding_box_bounds.second.x = player_position.x + .4;
					player_bounding_box_bounds.second.y = player_position.x + 1.9;
					player_bounding_box_bounds.second.z = player_position.x + .4;

					player_bounding_box.set_bounds(player_data.player_tick_data[x].bounding_box_bounds);

					auto player_bounding_box_interception = player_bounding_box.calculate_interception(local_player_view_position, local_player_view_vector);

					player_bounding_box.set_bounds(player_bounding_box_bounds);

					if (player_bounding_box_interception.object == nullptr)
						continue;

					player_bounding_box.set_bounds(player_data.player_tick_data[x].bounding_box_bounds);

					player_data.player_tick_data[x].draw = true;

					break;
				}
			}
		}

		if (!player_found)
			players_data.push_back({ player_name, { KERNEL_SYSTEM_TIME, player.get_view_position(timer_partial_ticks), player.get_bounding_box().get_bounds() }});
	}
}