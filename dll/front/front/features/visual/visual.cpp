
#include "../features.hpp"

auto client::features::visual::world_to_screen(client::mapper::__vec3 data, bool can_reverse, bool ignore_z) -> client::mapper::__vec2
{
	auto multiply_matrix = [&](client::mapper::__vec4 vec4, double matrix[16]) -> client::mapper::__vec4
	{
		return client::mapper::__vec4(
			vec4.x * matrix[0] + vec4.y * matrix[4] + vec4.z * matrix[8] + vec4.w * matrix[12],
			vec4.x * matrix[1] + vec4.y * matrix[5] + vec4.z * matrix[9] + vec4.w * matrix[13],
			vec4.x * matrix[2] + vec4.y * matrix[6] + vec4.z * matrix[10] + vec4.w * matrix[14],
			vec4.x * matrix[3] + vec4.y * matrix[7] + vec4.z * matrix[11] + vec4.w * matrix[15]
		);
	};

	auto clipped_space_position = multiply_matrix(multiply_matrix({ data.x, data.y, data.z, 1.f }, client::features::visual::model_view_matrix), client::features::visual::projection_matrix);

	if (clipped_space_position.w < -.52 && !can_reverse)
		return client::mapper::__vec2(FLT_MAX, FLT_MAX);

	auto space_position = client::mapper::__vec3(clipped_space_position.x / clipped_space_position.w, clipped_space_position.y / clipped_space_position.w, clipped_space_position.z / clipped_space_position.w);

	if ((space_position.z < -1.f || space_position.z > 1.f) && !can_reverse && !ignore_z)
		return client::mapper::__vec2(FLT_MAX, FLT_MAX);

	if (can_reverse && (clipped_space_position.w < 0. && can_reverse))
	{
		return client::mapper::__vec2(
			(float)(client::features::visual::view_port[2] - (((space_position.x + 1.f) / 2.f) * client::features::visual::view_port[2])),
			(float)(client::features::visual::view_port[3] - (((1.f - space_position.y) / 2.f) * client::features::visual::view_port[3]))
		);
	}
	else
		return client::mapper::__vec2((float)(((space_position.x + 1.f) / 2.f) * client::features::visual::view_port[2]), (float)(((1.f - space_position.y) / 2.f) * client::features::visual::view_port[3]));
}

auto client::features::visual::render_2d_bounding_box(
	client::mapper::__vec3 vec3, client::mapper::__vec4 outline_color, client::mapper::__vec4 line_color, client::mapper::__vec4 fill_color, bool draw_corners, bool draw_health, float health, bool draw_hurt_time, __int32 hurt_time) -> void
{
	auto min_x = vec3.x - .35, min_y = vec3.y, min_z = vec3.z - .35, max_x = vec3.x + .35, max_y = vec3.y + 1.85, max_z = vec3.z + .35;

	client::mapper::__vec3 bounding_box[] =
	{
		{ min_x, min_y, min_z },
		{ min_x, max_y, min_z },
		{ max_x, max_y, min_z },
		{ max_x, min_y, min_z },
		{ max_x, max_y, max_z },
		{ min_x, max_y, max_z },
		{ min_x, min_y, max_z },
		{ max_x, min_y, max_z }
	};

	auto bounding_box_screen_position = client::mapper::__vec4(DBL_MAX, DBL_MAX, DBL_MIN, DBL_MIN);

	for (auto x = 0; x < 8; ++x)
	{
		auto screen_position = client::features::visual::world_to_screen({ bounding_box[x].x, bounding_box[x].y, bounding_box[x].z });

		if (screen_position.x == FLT_MAX || screen_position.y == FLT_MAX)
			return;

		bounding_box_screen_position.x = min(screen_position.x, bounding_box_screen_position.x);
		bounding_box_screen_position.y = min(screen_position.y, bounding_box_screen_position.y);
		bounding_box_screen_position.z = max(screen_position.x, bounding_box_screen_position.z);
		bounding_box_screen_position.w = max(screen_position.y, bounding_box_screen_position.w);
	}

	if (bounding_box_screen_position.x == DBL_MAX || bounding_box_screen_position.y == DBL_MAX || bounding_box_screen_position.z == DBL_MIN || bounding_box_screen_position.w == DBL_MIN)
		return;

	if (draw_corners)
	{
		ImGui::GetForegroundDrawList()->AddLine(
			{ (float)bounding_box_screen_position.x, (float)bounding_box_screen_position.y },
			{ (float)bounding_box_screen_position.x, (float)bounding_box_screen_position.y + ((float)bounding_box_screen_position.w - (float)bounding_box_screen_position.y) * .33f },
			ImGui::ColorConvertFloat4ToU32({ (float)outline_color.x, (float)outline_color.y, (float)outline_color.z, (float)outline_color.w }),
			3.f
		);

		ImGui::GetForegroundDrawList()->AddLine(
			{ (float)bounding_box_screen_position.x, (float)bounding_box_screen_position.y },
			{ (float)bounding_box_screen_position.x + ((float)bounding_box_screen_position.z - (float)bounding_box_screen_position.x) * .33f, (float)bounding_box_screen_position.y },
			ImGui::ColorConvertFloat4ToU32({ (float)outline_color.x, (float)outline_color.y, (float)outline_color.z, (float)outline_color.w }),
			3.f
		);

		ImGui::GetForegroundDrawList()->AddLine(
			{ (float)bounding_box_screen_position.x, (float)bounding_box_screen_position.y },
			{ (float)bounding_box_screen_position.x, (float)bounding_box_screen_position.y + ((float)bounding_box_screen_position.w - (float)bounding_box_screen_position.y) * .33f },
			ImGui::ColorConvertFloat4ToU32({ (float)line_color.x, (float)line_color.y, (float)line_color.z, (float)line_color.w })
		);

		ImGui::GetForegroundDrawList()->AddLine(
			{ (float)bounding_box_screen_position.x, (float)bounding_box_screen_position.y },
			{ (float)bounding_box_screen_position.x + ((float)bounding_box_screen_position.z - (float)bounding_box_screen_position.x) * .33f, (float)bounding_box_screen_position.y },
			ImGui::ColorConvertFloat4ToU32({ (float)line_color.x, (float)line_color.y, (float)line_color.z, (float)line_color.w })
		);

		ImGui::GetForegroundDrawList()->AddLine(
			{ (float)bounding_box_screen_position.x, (float)bounding_box_screen_position.w },
			{ (float)bounding_box_screen_position.x, (float)bounding_box_screen_position.w - ((float)bounding_box_screen_position.w - (float)bounding_box_screen_position.y) * .33f },
			ImGui::ColorConvertFloat4ToU32({ (float)outline_color.x, (float)outline_color.y, (float)outline_color.z, (float)outline_color.w }),
			3.f
		);

		ImGui::GetForegroundDrawList()->AddLine(
			{ (float)bounding_box_screen_position.x, (float)bounding_box_screen_position.w },
			{ (float)bounding_box_screen_position.x + ((float)bounding_box_screen_position.z - (float)bounding_box_screen_position.x) * .33f, (float)bounding_box_screen_position.w },
			ImGui::ColorConvertFloat4ToU32({ (float)outline_color.x, (float)outline_color.y, (float)outline_color.z, (float)outline_color.w }),
			3.f
		);

		ImGui::GetForegroundDrawList()->AddLine(
			{ (float)bounding_box_screen_position.x, (float)bounding_box_screen_position.w },
			{ (float)bounding_box_screen_position.x, (float)bounding_box_screen_position.w - ((float)bounding_box_screen_position.w - (float)bounding_box_screen_position.y) * .33f },
			ImGui::ColorConvertFloat4ToU32({ (float)line_color.x, (float)line_color.y, (float)line_color.z, (float)line_color.w })
		);

		ImGui::GetForegroundDrawList()->AddLine(
			{ (float)bounding_box_screen_position.x, (float)bounding_box_screen_position.w },
			{ (float)bounding_box_screen_position.x + ((float)bounding_box_screen_position.z - (float)bounding_box_screen_position.x) * .33f, (float)bounding_box_screen_position.w },
			ImGui::ColorConvertFloat4ToU32({ (float)line_color.x, (float)line_color.y, (float)line_color.z, (float)line_color.w })
		);

		ImGui::GetForegroundDrawList()->AddLine(
			{ (float)bounding_box_screen_position.z, (float)bounding_box_screen_position.y },
			{ (float)bounding_box_screen_position.z, (float)bounding_box_screen_position.y + ((float)bounding_box_screen_position.w - (float)bounding_box_screen_position.y) * .33f },
			ImGui::ColorConvertFloat4ToU32({ (float)outline_color.x, (float)outline_color.y, (float)outline_color.z, (float)outline_color.w }),
			3.f
		);

		ImGui::GetForegroundDrawList()->AddLine(
			{ (float)bounding_box_screen_position.z, (float)bounding_box_screen_position.y },
			{ (float)bounding_box_screen_position.z - ((float)bounding_box_screen_position.z - (float)bounding_box_screen_position.x) * .33f, (float)bounding_box_screen_position.y },
			ImGui::ColorConvertFloat4ToU32({ (float)outline_color.x, (float)outline_color.y, (float)outline_color.z, (float)outline_color.w }),
			3.f
		);

		ImGui::GetForegroundDrawList()->AddLine(
			{ (float)bounding_box_screen_position.z, (float)bounding_box_screen_position.y },
			{ (float)bounding_box_screen_position.z, (float)bounding_box_screen_position.y + ((float)bounding_box_screen_position.w - (float)bounding_box_screen_position.y) * .33f },
			ImGui::ColorConvertFloat4ToU32({ (float)line_color.x, (float)line_color.y, (float)line_color.z, (float)line_color.w })
		);

		ImGui::GetForegroundDrawList()->AddLine(
			{ (float)bounding_box_screen_position.z, (float)bounding_box_screen_position.y },
			{ (float)bounding_box_screen_position.z - ((float)bounding_box_screen_position.z - (float)bounding_box_screen_position.x) * .33f, (float)bounding_box_screen_position.y },
			ImGui::ColorConvertFloat4ToU32({ (float)line_color.x, (float)line_color.y, (float)line_color.z, (float)line_color.w })
		);

		ImGui::GetForegroundDrawList()->AddLine(
			{ (float)bounding_box_screen_position.z, (float)bounding_box_screen_position.w },
			{ (float)bounding_box_screen_position.z, (float)bounding_box_screen_position.w - ((float)bounding_box_screen_position.w - (float)bounding_box_screen_position.y) * .33f },
			ImGui::ColorConvertFloat4ToU32({ (float)outline_color.x, (float)outline_color.y, (float)outline_color.z, (float)outline_color.w }),
			3.f
		);

		ImGui::GetForegroundDrawList()->AddLine(
			{ (float)bounding_box_screen_position.z, (float)bounding_box_screen_position.w },
			{ (float)bounding_box_screen_position.z - ((float)bounding_box_screen_position.z - (float)bounding_box_screen_position.x) * .33f, (float)bounding_box_screen_position.w },
			ImGui::ColorConvertFloat4ToU32({ (float)outline_color.x, (float)outline_color.y, (float)outline_color.z, (float)outline_color.w }),
			3.f
		);

		ImGui::GetForegroundDrawList()->AddLine(
			{ (float)bounding_box_screen_position.z, (float)bounding_box_screen_position.w },
			{ (float)bounding_box_screen_position.z, (float)bounding_box_screen_position.w - ((float)bounding_box_screen_position.w - (float)bounding_box_screen_position.y) * .33f },
			ImGui::ColorConvertFloat4ToU32({ (float)line_color.x, (float)line_color.y, (float)line_color.z, (float)line_color.w })
		);

		ImGui::GetForegroundDrawList()->AddLine(
			{ (float)bounding_box_screen_position.z, (float)bounding_box_screen_position.w },
			{ (float)bounding_box_screen_position.z - ((float)bounding_box_screen_position.z - (float)bounding_box_screen_position.x) * .33f, (float)bounding_box_screen_position.w },
			ImGui::ColorConvertFloat4ToU32({ (float)line_color.x, (float)line_color.y, (float)line_color.z, (float)line_color.w })
		);
	}
	else
	{
		ImGui::GetForegroundDrawList()->AddRect(
			{ (float)bounding_box_screen_position.x - 1.f, (float)bounding_box_screen_position.y - 1.f },
			{ (float)bounding_box_screen_position.z + 1.f, (float)bounding_box_screen_position.w + 1.f },
			ImGui::ColorConvertFloat4ToU32({ (float)outline_color.x, (float)outline_color.y, (float)outline_color.z, (float)outline_color.w })
		);

		ImGui::GetForegroundDrawList()->AddRect(
			{ (float)bounding_box_screen_position.x, (float)bounding_box_screen_position.y },
			{ (float)bounding_box_screen_position.z, (float)bounding_box_screen_position.w },
			ImGui::ColorConvertFloat4ToU32({ (float)line_color.x, (float)line_color.y, (float)line_color.z, (float)line_color.w })
		);

		ImGui::GetForegroundDrawList()->AddRect(
			{ (float)bounding_box_screen_position.x + 1.f, (float)bounding_box_screen_position.y + 1.f },
			{ (float)bounding_box_screen_position.z - 1.f, (float)bounding_box_screen_position.w - 1.f },
			ImGui::ColorConvertFloat4ToU32({ (float)outline_color.x, (float)outline_color.y, (float)outline_color.z, (float)outline_color.w })
		);
	}

	ImGui::GetForegroundDrawList()->AddRectFilled(
		{ (float)bounding_box_screen_position.x + 1.f, (float)bounding_box_screen_position.y + 1.f },
		{ (float)bounding_box_screen_position.z - 1.f, (float)bounding_box_screen_position.w - 1.f },
		ImGui::ColorConvertFloat4ToU32({ (float)fill_color.x, (float)fill_color.y, (float)fill_color.z, (float)fill_color.w })
	);

	if (draw_health)
	{
		ImGui::GetForegroundDrawList()->AddRect(
			{ (float)bounding_box_screen_position.x - 6.f, (float)bounding_box_screen_position.y - 1.f },
			{ (float)bounding_box_screen_position.x - 3.f, (float)bounding_box_screen_position.w + 1.f },
			ImGui::ColorConvertFloat4ToU32({ .1f, .1f, .1f, 1.f })
		);

		ImGui::GetForegroundDrawList()->AddRectFilled(
			{ (float)bounding_box_screen_position.x - 6.f, (float)bounding_box_screen_position.y - 1.f },
			{ (float)bounding_box_screen_position.x - 3.f, (float)bounding_box_screen_position.w + 1.f },
			ImGui::ColorConvertFloat4ToU32({ .1f, .1f, .1f, 1.f })
		);

		ImGui::GetForegroundDrawList()->AddRectFilled(
			{ (float)bounding_box_screen_position.x - 5.f, (float)bounding_box_screen_position.w - (((float)bounding_box_screen_position.w - (float)bounding_box_screen_position.y) * (health / 20.f)) },
			{ (float)bounding_box_screen_position.x - 4.f, (float)bounding_box_screen_position.w },
			ImGui::ColorConvertFloat4ToU32({ (20.f - health) / 20.f, (health < 5.f ? 5.f : health) / 20.f, .35f, 1.f })
		);
	}

	if (draw_hurt_time)
	{
		ImGui::GetForegroundDrawList()->AddRectFilled(
			{ (float)bounding_box_screen_position.x + 1.f, (float)bounding_box_screen_position.y + 1.f },
			{ (float)bounding_box_screen_position.z - 1.f, (float)bounding_box_screen_position.w - 1.f },
			ImGui::ColorConvertFloat4ToU32({ .8f, .35f, .35f, (float)fill_color.w * (float)hurt_time / 10.f * .5f })
		);
	}
}

auto client::features::visual::render_3d_bounding_box(client::mapper::__vec3 vec3, client::mapper::__vec4 color, bool draw_health, float health, bool draw_hurt_time, __int32 hurt_time) -> void
{
	auto min_x = vec3.x - .35, min_y = vec3.y, min_z = vec3.z - .35, max_x = vec3.x + .35, max_y = vec3.y + 1.85, max_z = vec3.z + .35;

	auto bottom_0 = client::features::visual::world_to_screen({ min_x, min_y, min_z });

	if (bottom_0.x == FLT_MAX || bottom_0.y == FLT_MAX)
		return;

	auto bottom_1 = client::features::visual::world_to_screen({ max_x, min_y, min_z });

	if (bottom_1.x == FLT_MAX || bottom_1.y == FLT_MAX)
		return;

	auto bottom_2 = client::features::visual::world_to_screen({ max_x, min_y, max_z });

	if (bottom_2.x == FLT_MAX || bottom_2.y == FLT_MAX)
		return;

	auto bottom_3 = client::features::visual::world_to_screen({ min_x, min_y, max_z });

	if (bottom_3.x == FLT_MAX || bottom_3.y == FLT_MAX)
		return;

	auto top_0 = client::features::visual::world_to_screen({ min_x, max_y, min_z });

	if (top_0.x == FLT_MAX || top_0.y == FLT_MAX)
		return;

	auto top_1 = client::features::visual::world_to_screen({ max_x, max_y, min_z });

	if (top_1.x == FLT_MAX || top_1.y == FLT_MAX)
		return;

	auto top_2 = client::features::visual::world_to_screen({ max_x, max_y, max_z });

	if (top_2.x == FLT_MAX || top_2.y == FLT_MAX)
		return;

	auto top_3 = client::features::visual::world_to_screen({ min_x, max_y, max_z });

	if (top_3.x == FLT_MAX || top_3.y == FLT_MAX)
		return;

	ImGui::GetForegroundDrawList()->AddQuadFilled({ bottom_0.x, bottom_0.y }, { bottom_1.x, bottom_1.y }, { bottom_2.x, bottom_2.y }, { bottom_3.x, bottom_3.y }, ImGui::ColorConvertFloat4ToU32({ (float)color.x, (float)color.y, (float)color.z, (float)color.w }));
	ImGui::GetForegroundDrawList()->AddQuadFilled({ top_0.x, top_0.y }, { top_1.x, top_1.y }, { top_2.x, top_2.y }, { top_3.x, top_3.y }, ImGui::ColorConvertFloat4ToU32({ (float)color.x, (float)color.y, (float)color.z, (float)color.w }));

	ImGui::GetForegroundDrawList()->AddQuadFilled({ bottom_0.x, bottom_0.y }, { top_0.x, top_0.y }, { top_1.x, top_1.y }, { bottom_1.x, bottom_1.y }, ImGui::ColorConvertFloat4ToU32({ (float)color.x, (float)color.y, (float)color.z, (float)color.w }));
	ImGui::GetForegroundDrawList()->AddQuadFilled({ bottom_1.x, bottom_1.y }, { top_1.x, top_1.y }, { top_2.x, top_2.y }, { bottom_2.x, bottom_2.y }, ImGui::ColorConvertFloat4ToU32({ (float)color.x, (float)color.y, (float)color.z, (float)color.w }));
	ImGui::GetForegroundDrawList()->AddQuadFilled({ bottom_2.x, bottom_2.y }, { top_2.x, top_2.y }, { top_3.x, top_3.y }, { bottom_3.x, bottom_3.y }, ImGui::ColorConvertFloat4ToU32({ (float)color.x, (float)color.y, (float)color.z, (float)color.w }));
	ImGui::GetForegroundDrawList()->AddQuadFilled({ bottom_3.x, bottom_3.y }, { top_3.x, top_3.y }, { top_0.x, top_0.y }, { bottom_0.x, bottom_0.y }, ImGui::ColorConvertFloat4ToU32({ (float)color.x, (float)color.y, (float)color.z, (float)color.w }));

	if (draw_health)
	{
		client::mapper::__vec3 bounding_box[] =
		{
			{ min_x, min_y, min_z },
			{ min_x, max_y, min_z },
			{ max_x, max_y, min_z },
			{ max_x, min_y, min_z },
			{ max_x, max_y, max_z },
			{ min_x, max_y, max_z },
			{ min_x, min_y, max_z },
			{ max_x, min_y, max_z }
		};

		auto bounding_box_screen_position = client::mapper::__vec4(DBL_MAX, DBL_MAX, DBL_MIN, DBL_MIN);

		for (auto x = 0; x < 8; ++x)
		{
			auto screen_position = client::features::visual::world_to_screen({ bounding_box[x].x, bounding_box[x].y, bounding_box[x].z });

			if (screen_position.x == FLT_MAX || screen_position.y == FLT_MAX)
				return;

			bounding_box_screen_position.x = min(screen_position.x, bounding_box_screen_position.x);
			bounding_box_screen_position.y = min(screen_position.y, bounding_box_screen_position.y);
			bounding_box_screen_position.z = max(screen_position.x, bounding_box_screen_position.z);
			bounding_box_screen_position.w = max(screen_position.y, bounding_box_screen_position.w);
		}

		if (bounding_box_screen_position.x == DBL_MAX || bounding_box_screen_position.y == DBL_MAX || bounding_box_screen_position.z == DBL_MIN || bounding_box_screen_position.w == DBL_MIN)
			return;
	
		ImGui::GetForegroundDrawList()->AddRect(
			{ (float)bounding_box_screen_position.x - 6.f, (float)bounding_box_screen_position.y - 1.f },
			{ (float)bounding_box_screen_position.x - 3.f, (float)bounding_box_screen_position.w + 1.f },
			ImGui::ColorConvertFloat4ToU32({ .1f, .1f, .1f, 1.f })
		);

		ImGui::GetForegroundDrawList()->AddRectFilled(
			{ (float)bounding_box_screen_position.x - 6.f, (float)bounding_box_screen_position.y - 1.f },
			{ (float)bounding_box_screen_position.x - 3.f, (float)bounding_box_screen_position.w + 1.f },
			ImGui::ColorConvertFloat4ToU32({ .1f, .1f, .1f, 1.f })
		);

		ImGui::GetForegroundDrawList()->AddRectFilled(
			{ (float)bounding_box_screen_position.x - 5.f, (float)bounding_box_screen_position.w - (((float)bounding_box_screen_position.w - (float)bounding_box_screen_position.y) * (health / 20.f)) },
			{ (float)bounding_box_screen_position.x - 4.f, (float)bounding_box_screen_position.w },
			ImGui::ColorConvertFloat4ToU32({ (20.f - health) / 20.f, (health < 5.f ? 5.f : health) / 20.f, .35f, 1.f })
		);
	}

	if (draw_hurt_time)
		client::features::visual::render_3d_bounding_box(vec3, { .8f, .35f, .35f, (float)color.w * (float)hurt_time / 10.f }, false, 0.f, false, 0);
}

auto client::features::visual::render_nametag(sdk::__multibyte_string name, client::mapper::__vec3 vec3, client::mapper::__vec4 color, bool draw_health, float health, bool draw_distance, double distance, bool draw_hurt_time, __int32 hurt_time) -> void
{
	auto min_x = vec3.x - .35, min_y = vec3.y, min_z = vec3.z - .35, max_x = vec3.x + .35, max_y = vec3.y + 1.85, max_z = vec3.z + .35;

	client::mapper::__vec3 bounding_box[] =
	{
		{ min_x, min_y, min_z },
		{ min_x, max_y, min_z },
		{ max_x, max_y, min_z },
		{ max_x, min_y, min_z },
		{ max_x, max_y, max_z },
		{ min_x, max_y, max_z },
		{ min_x, min_y, max_z },
		{ max_x, min_y, max_z }
	};

	auto bounding_box_screen_position = client::mapper::__vec4(DBL_MAX, DBL_MAX, DBL_MIN, DBL_MIN);

	for (auto x = 0; x < 8; ++x)
	{
		auto screen_position = client::features::visual::world_to_screen({ bounding_box[x].x, bounding_box[x].y, bounding_box[x].z });

		if (screen_position.x == FLT_MAX || screen_position.y == FLT_MAX)
			continue;

		bounding_box_screen_position.x = min(screen_position.x, bounding_box_screen_position.x);
		bounding_box_screen_position.y = min(screen_position.y, bounding_box_screen_position.y);
		bounding_box_screen_position.z = max(screen_position.x, bounding_box_screen_position.z);
		bounding_box_screen_position.w = max(screen_position.y, bounding_box_screen_position.w);
	}

	if (bounding_box_screen_position.x == DBL_MAX || bounding_box_screen_position.y == DBL_MAX || bounding_box_screen_position.z == DBL_MIN || bounding_box_screen_position.w == DBL_MIN)
		return;

	auto screen_position = client::mapper::__vec2(bounding_box_screen_position.x + (bounding_box_screen_position.z - bounding_box_screen_position.x) * .5, bounding_box_screen_position.y);

	auto name_size = ImGui::CalcTextSize(name.get_multibyte_string());

	ImGui::GetForegroundDrawList()->AddRectFilled(
		{ screen_position.x - name_size.x * .5f - 4.f, screen_position.y - name_size.y - 7.f },
		{ screen_position.x + name_size.x * .5f + 4.f, screen_position.y - 5.f },
		ImGui::ColorConvertFloat4ToU32({ .1175f, .1175f, .1175f, .8f })
	);

	if (draw_hurt_time)
	{
		ImGui::GetForegroundDrawList()->AddRectFilled(
			{ screen_position.x - name_size.x * .5f - 4.f, screen_position.y - name_size.y - 7.f },
			{ screen_position.x + name_size.x * .5f + 4.f, screen_position.y - 5.f },
			ImGui::ColorConvertFloat4ToU32({ .8f, .35f, .35f, .5f * (float)hurt_time / 10.f })
		);
	}

	ImGui::GetForegroundDrawList()->AddText(
		{ (float)screen_position.x - name_size.x * .5f, (float)screen_position.y - name_size.y - 7.f },
		ImGui::ColorConvertFloat4ToU32(
			{
				(float)color.x,
				(float)color.y,
				(float)color.z,
				(float)color.w
			}),
		name.get_multibyte_string()
	);

	if (draw_health)
	{
		auto minimun_position = client::mapper::__vec2({ screen_position.x - name_size.x * .5f - 4.f, screen_position.y - 5.f });
		auto maximun_position = client::mapper::__vec2({ screen_position.x + name_size.x * .5f + 4.f, screen_position.y - 2.f });

		ImGui::GetForegroundDrawList()->AddRectFilled(
			{ minimun_position.x, minimun_position.y },
			{ maximun_position.x, maximun_position.y },
			ImGui::ColorConvertFloat4ToU32({ .1175f, .1175f, .1175f, .8f })
		);

		ImGui::GetForegroundDrawList()->AddRectFilled(
			{ minimun_position.x + 1.f, minimun_position.y + 1.f },
			{ minimun_position.x + (maximun_position.x - minimun_position.x) * health / 20.f - 1.f, maximun_position.y - 1.f },
			ImGui::ColorConvertFloat4ToU32({ (20.f - health) / 20.f, (health < 5.f ? 5.f : health) / 20.f, .35f, 1.f })
		);
	}

	if (draw_distance)
	{
		auto fixed_distance = sdk::__multibyte_string();

		snprintf(fixed_distance.get_multibyte_string(), fixed_distance.get_size(), XOR("%.2f"), distance);

		auto& io = ImGui::GetIO();

		auto fixed_distance_size = io.FontDefault->CalcTextSizeA(16.f, FLT_MAX, -1.f, fixed_distance.get_multibyte_string());;

		ImGui::GetForegroundDrawList()->AddRectFilled(
			{ (float)screen_position.x - fixed_distance_size.x * .5f - 4.f, (float)screen_position.y - fixed_distance_size.y - fixed_distance_size.y - 15.f },
			{ (float)screen_position.x + fixed_distance_size.x * .5f + 4.f, (float)screen_position.y - fixed_distance_size.y - 13.f },
			ImGui::ColorConvertFloat4ToU32({ .1175f, .1175f, .1175f, .8f })
		);

		ImGui::GetForegroundDrawList()->AddText(io.FontDefault, 16.f,
			{ (float)screen_position.x - fixed_distance_size.x * .5f, (float)screen_position.y - name_size.y - fixed_distance_size.y - 7.f },
			ImGui::ColorConvertFloat4ToU32({ (2.f - ((float)distance < 5. ? 5.f : (float)distance) / 20.f), ((float)distance < 5. ? 5.f : (float)distance) / 20.f, 0.f, (float)color.w }),
			fixed_distance.get_multibyte_string()
		);
	}
}

auto client::features::visual::render_tracer(client::mapper::__vec3 vec3, client::mapper::__vec4 color, bool draw_distance, double distance, bool draw_hurt_time, __int32 hurt_time) -> void
{
	auto screen_position = client::features::visual::world_to_screen(vec3, true);

	if (screen_position.x == FLT_MAX || screen_position.y == FLT_MAX)
		return;

	ImGui::GetForegroundDrawList()->AddLine(
		{ (float)client::features::visual::view_port[2] * .5f, (float)client::features::visual::view_port[3] * .5f },
		{ screen_position.x, screen_position.y },
		ImGui::ColorConvertFloat4ToU32({ (float)color.x, (float)color.y, (float)color.z, (float)color.w })
	);

	if (draw_distance)
	{
		ImGui::GetForegroundDrawList()->AddLine(
			{ (float)client::features::visual::view_port[2] * .5f, (float)client::features::visual::view_port[3] * .5f },
			{ screen_position.x, screen_position.y },
			ImGui::ColorConvertFloat4ToU32(
				{
					(2.f - ((float)distance < 5. ? 5.f : (float)distance) / 20.f),
					((float)distance < 5. ? 5.f : (float)distance) / 20.f,
					0.f,
					(float)color.w
				}),
			2.f
		);
	}

	if (draw_hurt_time)
	{
		ImGui::GetForegroundDrawList()->AddLine(
			{ (float)client::features::visual::view_port[2] * .5f, (float)client::features::visual::view_port[3] * .5f },
			{ screen_position.x, screen_position.y },
			ImGui::ColorConvertFloat4ToU32({ .8f, .35f, .35f, (float)color.w * (float)hurt_time / 10.f }),
			2.f
		);
	}
}