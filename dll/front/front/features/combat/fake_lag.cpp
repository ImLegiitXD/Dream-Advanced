
#include "../features.hpp"

auto client::features::combat::fake_lag::run(client::mapper::__minecraft& minecraft, bool draw_bounds) -> void
{
	auto update_timer_release_buffered_packets = [&]() -> void
	{
		client::features::combat::fake_lag::timer.update();

		return ((void(__cdecl*)(unsigned __int64))client::features::combat::fake_lag::release_buffered_packets_function)(0);
	};

	if (!client::features::combat::fake_lag::enabled)
		return update_timer_release_buffered_packets();

	if (minecraft.get_current_screen().object != nullptr)
		return update_timer_release_buffered_packets();

	struct __bounding_box
	{
		client::mapper::__vec3 view_position;
		double alpha = 0.;
		sdk::__timer timer;
	};

	static auto last_sent_bounding_box = __bounding_box();

	auto timer_partial_ticks = minecraft.get_timer().get_partial_ticks();

	auto local_player = minecraft.get_local_player();
	auto local_player_view_position = local_player.get_view_position(timer_partial_ticks);

	if (client::features::combat::fake_lag::draw_last_sent_position && draw_bounds)
	{
		if (last_sent_bounding_box.alpha > 0.)
		{
			client::features::visual::render_3d_bounding_box(
			{
				last_sent_bounding_box.view_position.x - local_player_view_position.x,
				last_sent_bounding_box.view_position.y - local_player_view_position.y - (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17 ? 1.62 : 0.),
				last_sent_bounding_box.view_position.z - local_player_view_position.z
			},
			{
				(float)client::features::combat::fake_lag::color.x,
				(float)client::features::combat::fake_lag::color.y,
				(float)client::features::combat::fake_lag::color.z,
				(float)client::features::combat::fake_lag::color.w * last_sent_bounding_box.alpha
			},
			false, 0.f, false, 0);

			last_sent_bounding_box.alpha -= last_sent_bounding_box.timer.get_elapsed_milliseconds() / client::features::combat::fake_lag::delay;
		}

		return;
	}

	auto update_last_sent_bounding_box_update_timer_release_buffered_packets = [&](double alpha) -> void
	{
		last_sent_bounding_box.view_position = local_player_view_position;
		last_sent_bounding_box.alpha = alpha;

		last_sent_bounding_box.timer.update();

		return update_timer_release_buffered_packets();
	};

	if (client::features::combat::fake_lag::clicking_only && (sdk::nt_user_get_async_key_state(VK_LBUTTON) & 0x8000) == 0)
		return update_last_sent_bounding_box_update_timer_release_buffered_packets(0.);

	if (client::features::combat::fake_lag::weapons_only)
	{
		auto local_player_held_item_stack = local_player.get_held_item_stack();

		if (local_player_held_item_stack.object == nullptr)
			return update_last_sent_bounding_box_update_timer_release_buffered_packets(0.);

		auto local_player_held_item = local_player_held_item_stack.get_item();

		if (local_player_held_item.object == nullptr)
			return update_last_sent_bounding_box_update_timer_release_buffered_packets(0.);

		if (!((client::features::combat::weapons::sword && local_player_held_item.is_sword()) || (client::features::combat::weapons::axe && local_player_held_item.is_axe()) ||
			(client::features::combat::weapons::pickaxe && local_player_held_item.is_pickaxe()) || (client::features::combat::weapons::shovel && local_player_held_item.is_shovel())))
			return update_last_sent_bounding_box_update_timer_release_buffered_packets(0.);
	}

	auto closest_local_player_view_position_distance_to_player_view_position = DBL_MAX, closest_last_sent_bounding_box_view_position_distance_to_player_view_position = DBL_MAX;

	for (auto& player : minecraft.get_world().get_players())
	{
		if (client::mapper::jni->IsSameObject(local_player.object, player.object))
			continue;

		auto player_view_position = player.get_view_position(timer_partial_ticks);

		auto local_player_view_position_distance_to_player_view_position = local_player_view_position.get_distance_to_vec3(player_view_position);

		if (local_player_view_position_distance_to_player_view_position < closest_local_player_view_position_distance_to_player_view_position)
			closest_local_player_view_position_distance_to_player_view_position = local_player_view_position_distance_to_player_view_position;

		auto last_sent_bounding_box_view_position_distance_to_player_view_position = last_sent_bounding_box.view_position.get_distance_to_vec3(player_view_position);

		if (last_sent_bounding_box_view_position_distance_to_player_view_position < closest_last_sent_bounding_box_view_position_distance_to_player_view_position)
			closest_last_sent_bounding_box_view_position_distance_to_player_view_position = last_sent_bounding_box_view_position_distance_to_player_view_position;
	}

	static auto was_in_range = false;

	auto is_in_range = closest_local_player_view_position_distance_to_player_view_position < client::features::combat::fake_lag::distance;

	auto temporal_was_in_range = was_in_range;

	was_in_range = is_in_range;

	if (!is_in_range)
		return update_last_sent_bounding_box_update_timer_release_buffered_packets(0.);

	else if (!temporal_was_in_range)
		return update_last_sent_bounding_box_update_timer_release_buffered_packets(1.);

	if (client::features::combat::fake_lag::release_when_distancing && closest_local_player_view_position_distance_to_player_view_position > closest_last_sent_bounding_box_view_position_distance_to_player_view_position)
		return update_last_sent_bounding_box_update_timer_release_buffered_packets(1.);

	if (client::features::combat::fake_lag::timer.has_elapsed(client::features::combat::fake_lag::delay, true))
		return update_last_sent_bounding_box_update_timer_release_buffered_packets(1.);

	if (client::features::combat::fake_lag::release_when_attacked && !local_player.is_vulnerable())
		return update_last_sent_bounding_box_update_timer_release_buffered_packets(1.);

	if (client::features::combat::fake_lag::release_when_attacking && (sdk::nt_user_get_async_key_state(VK_LBUTTON) & 0x8000) != 0)
	{
		if (auto pointed_entity = minecraft.get_pointed_entity(); pointed_entity.object != nullptr && pointed_entity.is_vulnerable())
			return update_last_sent_bounding_box_update_timer_release_buffered_packets(1.);
	}
}