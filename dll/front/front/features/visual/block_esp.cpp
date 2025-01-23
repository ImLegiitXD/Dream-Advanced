
#include "../features.hpp"

auto client::features::visual::block_esp::run(client::mapper::__minecraft& minecraft) -> void
{
	if (!client::features::visual::block_esp::enabled)
		return;

	auto timer = minecraft.get_timer();
	auto timer_partial_ticks = timer.get_partial_ticks();

	auto world = minecraft.get_world();

	auto local_player = minecraft.get_local_player();
	auto local_player_view_position = local_player.get_view_position(timer_partial_ticks);

	auto fixed_local_player_view_position = client::mapper::__vec3
	{
		(double)(__int64)floor(local_player_view_position.x),
		(double)(__int64)local_player_view_position.y,
		(double)(__int64)floor(local_player_view_position.z)
	};

	static struct render_block
	{
		__int32 id = 0;
		client::mapper::__vec3 position;
		client::mapper::__vec4 color;
	};

	static std::vector<render_block> render_blocks;

	if (static sdk::__timer timer; timer.has_elapsed(5000., true))
	{
		render_blocks.clear();

		static auto rad = 25.;

		for (double pos_x = fixed_local_player_view_position.x - rad - 1.; pos_x <= fixed_local_player_view_position.x + rad; pos_x++)
		for (double pos_y = fixed_local_player_view_position.y - rad - 1.; pos_y <= fixed_local_player_view_position.y + 5.; pos_y++)
		for (double pos_z = fixed_local_player_view_position.z - rad - 1.; pos_z <= fixed_local_player_view_position.z + rad; pos_z++)
		{
			auto id = world.get_block_id(pos_x, pos_y, pos_z);

			client::mapper::__vec4 fill_color, outline_color;

			if (client::features::visual::block_esp::draw_diamond && id == 56)
				fill_color = { .1, .7, 1., .5 }; else
			if (client::features::visual::block_esp::draw_emerald && id == 129)
				fill_color = { .2, .7, .2, .5 }; else
			if (client::features::visual::block_esp::draw_iron && id == 15)
				fill_color = { .7, .4, .2, .5 }; else
			if (client::features::visual::block_esp::draw_gold && id == 14)
				fill_color = { .7, .6, .2, .5 }; else
			if (client::features::visual::block_esp::draw_lapis && id == 21)
				fill_color = { .2, .2, .9, .5 }; else
			if (client::features::visual::block_esp::draw_coal && id == 16)
				fill_color = { .1, .1, .1, .5 }; else
			if (client::features::visual::block_esp::draw_redstone && (id == 73 || id == 74))
				fill_color = { .7, .1, .1, .5 }; else
			if (client::features::visual::block_esp::draw_chests && id == 54)
				fill_color = { .4, .23, .125, .5 }; else
				continue;

			render_blocks.push_back(
				render_block{ id, { pos_x, pos_y, pos_z }, fill_color });
		}
	}

	for (auto& render_block : render_blocks)
	{
		auto id = world.get_block_id(render_block.position.x, render_block.position.y, render_block.position.z);

		if (render_block.id != id)
			continue;

		render_block.color.w = .5 - .5 * (min(local_player_view_position.get_distance_to_vec3({ render_block.position.x, render_block.position.y, render_block.position.z }), 25.) / 25.);

		auto real = client::mapper::__vec3({ render_block.position.x - local_player_view_position.x, render_block.position.y - local_player_view_position.y, render_block.position.z - local_player_view_position.z });

		auto min_x = real.x;
		auto min_y = real.y;
		auto min_z = real.z;

		auto max_x = real.x + 1.;
		auto max_y = real.y + 1.;
		auto max_z = real.z + 1.;

		auto bottom_0 = client::features::visual::world_to_screen({ min_x, min_y, min_z });

		if (bottom_0.x == FLT_MAX || bottom_0.y == FLT_MAX)
			continue;

		auto bottom_1 = client::features::visual::world_to_screen({ max_x, min_y, min_z });

		if (bottom_1.x == FLT_MAX || bottom_1.y == FLT_MAX)
			continue;

		auto bottom_2 = client::features::visual::world_to_screen({ max_x, min_y, max_z });

		if (bottom_2.x == FLT_MAX || bottom_2.y == FLT_MAX)
			continue;

		auto bottom_3 = client::features::visual::world_to_screen({ min_x, min_y, max_z });

		if (bottom_3.x == FLT_MAX || bottom_3.y == FLT_MAX)
			continue;

		auto top_0 = client::features::visual::world_to_screen({ min_x, max_y, min_z });

		if (top_0.x == FLT_MAX || top_0.y == FLT_MAX)
			continue;

		auto top_1 = client::features::visual::world_to_screen({ max_x, max_y, min_z });

		if (top_1.x == FLT_MAX || top_1.y == FLT_MAX)
			continue;

		auto top_2 = client::features::visual::world_to_screen({ max_x, max_y, max_z });

		if (top_2.x == FLT_MAX || top_2.y == FLT_MAX)
			continue;

		auto top_3 = client::features::visual::world_to_screen({ min_x, max_y, max_z });

		if (top_3.x == FLT_MAX || top_3.y == FLT_MAX)
			continue;

		ImGui::GetForegroundDrawList()->AddQuadFilled(
			{ bottom_0.x, bottom_0.y }, { bottom_1.x, bottom_1.y }, { bottom_2.x, bottom_2.y }, { bottom_3.x, bottom_3.y }, ImGui::ColorConvertFloat4ToU32({ (float)render_block.color.x, (float)render_block.color.y, (float)render_block.color.z, (float)render_block.color.w }));
		ImGui::GetForegroundDrawList()->AddQuadFilled(
			{ top_0.x, top_0.y }, { top_1.x, top_1.y }, { top_2.x, top_2.y }, { top_3.x, top_3.y }, ImGui::ColorConvertFloat4ToU32({ (float)render_block.color.x, (float)render_block.color.y, (float)render_block.color.z, (float)render_block.color.w }));

		ImGui::GetForegroundDrawList()->AddQuadFilled(
			{ bottom_0.x, bottom_0.y }, { top_0.x, top_0.y }, { top_1.x, top_1.y }, { bottom_1.x, bottom_1.y }, ImGui::ColorConvertFloat4ToU32({ (float)render_block.color.x, (float)render_block.color.y, (float)render_block.color.z, (float)render_block.color.w }));
		ImGui::GetForegroundDrawList()->AddQuadFilled(
			{ bottom_1.x, bottom_1.y }, { top_1.x, top_1.y }, { top_2.x, top_2.y }, { bottom_2.x, bottom_2.y }, ImGui::ColorConvertFloat4ToU32({ (float)render_block.color.x, (float)render_block.color.y, (float)render_block.color.z, (float)render_block.color.w }));
		ImGui::GetForegroundDrawList()->AddQuadFilled(
			{ bottom_2.x, bottom_2.y }, { top_2.x, top_2.y }, { top_3.x, top_3.y }, { bottom_3.x, bottom_3.y }, ImGui::ColorConvertFloat4ToU32({ (float)render_block.color.x, (float)render_block.color.y, (float)render_block.color.z, (float)render_block.color.w }));
		ImGui::GetForegroundDrawList()->AddQuadFilled(
			{ bottom_3.x, bottom_3.y }, { top_3.x, top_3.y }, { top_0.x, top_0.y }, { bottom_0.x, bottom_0.y }, ImGui::ColorConvertFloat4ToU32({ (float)render_block.color.x, (float)render_block.color.y, (float)render_block.color.z, (float)render_block.color.w }));
	}
}