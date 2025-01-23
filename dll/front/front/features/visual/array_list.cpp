
#include "../features.hpp"

auto client::features::visual::array_list::run(client::mapper::__minecraft& minecraft) -> void
{
	if (!client::features::visual::array_list::enabled)
		return;

	static auto timer = sdk::__timer();

	auto elapsed_milliseconds = (float)timer.get_elapsed_milliseconds();

	auto smooth_value_change = [&](float& value, float speed) -> bool
	{
		if (value += (1.f - value) * speed * elapsed_milliseconds * .14285f; speed > 0.f ? value > 0.99f : value < 0.1f)
		{
			value = speed > 0.f ? 1.f : 0.f;

			return true;
		}

		return false;
	};

	__int32 window_view_port[4] = { 0, 0, 0, 0 };

	glGetIntegerv(GL_VIEWPORT, window_view_port);

	static auto array_list_animation_progress = 0.f;

	static auto animation_minimum_position = ImVec2(5.f, 5.f), animation_maximum_position = ImVec2((float)window_view_port[2] + 95.f, 5.f);

	animation_maximum_position.x = (float)window_view_port[2] + 95.f - array_list_animation_progress * 100.f;

	struct __feature_data
	{
		const char* name = nullptr;
		bool* is_enabled = nullptr;
		float animation_progress = 0.f;
	};

	static __feature_data feature_data_array[] =
	{
		{ "Aim Assist",			&client::features::combat::aim_assist::enabled,		0.f	},
		{ "Auto Click",			&client::features::combat::auto_click::enabled,		.1f	},
		{ "Reach",				&client::features::combat::reach::enabled,			.2f	},
		{ "Speed",				&client::features::util::speed::enabled,			.2f	},
		{ "Velocity",			&client::features::combat::velocity::enabled,		.4f	},
		{ "Fake Lag",			&client::features::combat::fake_lag::enabled,		.4f	},
		{ "Block Esp",			&client::features::visual::block_esp::enabled,		.7f	},
		{ "Nametags",			&client::features::visual::nametags::enabled,		.8f	},
		{ "Player Esp 2D",		&client::features::visual::player_esp_2d::enabled,	.9f	},
		{ "Player Esp 3D",		&client::features::visual::player_esp_3d::enabled,	.9f	},
		{ "Tracers",			&client::features::visual::tracers::enabled,		.1f	},
		{ "Chams",				&client::features::visual::chams::enabled,			.2f	},
		{ "Bridge Assist",		&client::features::util::bridge_assist::enabled,	.4f },
		{ "Fast Place",			&client::features::util::fast_place::enabled,		.5f	}
	};

	if (static auto is_feature_data_array_sorted = false; !is_feature_data_array_sorted)
	{
		for (unsigned __int64 x = 0; x < sizeof(feature_data_array) / sizeof(__feature_data) - 1; ++x)
		{
			for (unsigned __int64 y = 0; y < sizeof(feature_data_array) / sizeof(__feature_data) - 1; ++y)
			{
				if (ImGui::CalcTextSize(feature_data_array[y].name).x < ImGui::CalcTextSize(feature_data_array[y + 1].name).x)
				{
					auto current_feature_data = feature_data_array[y];

					feature_data_array[y] = feature_data_array[y + 1];

					feature_data_array[y + 1] = current_feature_data;
				}
			}
		}

		is_feature_data_array_sorted = true;
	}

	float animation_position_y_increment = 0.f;

	for (auto& current_feature_data : feature_data_array)
	{
		if (!(*current_feature_data.is_enabled))
			continue;

		auto current_feature_data_name_size = ImGui::CalcTextSize(current_feature_data.name);

		auto temporal_animation_minimum_position = ImVec2(animation_maximum_position.x - 4.f - current_feature_data_name_size.x - 4.f, animation_minimum_position.y + animation_position_y_increment);
		auto temporal_animation_maximum_position = ImVec2(animation_maximum_position.x, animation_maximum_position.y + animation_position_y_increment + 30.f);

		ImGui::GetBackgroundDrawList()->AddRectFilled(
			temporal_animation_minimum_position,
			temporal_animation_maximum_position,
			ImGui::ColorConvertFloat4ToU32({ .12f, .13f, .15f, .9f * array_list_animation_progress })
		);

		ImGui::GetBackgroundDrawList()->AddRectFilled(
			{ temporal_animation_minimum_position.x, temporal_animation_minimum_position.y + 30.f },
			{ temporal_animation_maximum_position.x, temporal_animation_minimum_position.y + 33.f },
			ImGui::ColorConvertFloat4ToU32({ .08f, .08f, .08f, .9f * array_list_animation_progress })
		);

		for (auto x = 0, y = 50; x < y; ++x)
		{
			auto fixed_add_line = [&](ImVec2 point_0, ImVec2 point_1, ImU32 color) -> void
			{
				point_0.x -= (float)y;
				point_1.x -= (float)y;

				if (point_0.x < temporal_animation_minimum_position.x)
					point_0.x = temporal_animation_minimum_position.x;

				if (point_0.x > temporal_animation_maximum_position.x)
					point_0.x = temporal_animation_maximum_position.x;

				if (point_1.x < temporal_animation_minimum_position.x)
					point_1.x = temporal_animation_minimum_position.x;

				if (point_1.x > temporal_animation_maximum_position.x)
					point_1.x = temporal_animation_maximum_position.x;

				ImGui::GetBackgroundDrawList()->AddLine(point_0, point_1, color);
			};

			fixed_add_line(
				{ temporal_animation_minimum_position.x + (temporal_animation_maximum_position.x + (float)y - temporal_animation_minimum_position.x) * current_feature_data.animation_progress + (float)x, temporal_animation_maximum_position.y },
				{ temporal_animation_minimum_position.x + (temporal_animation_maximum_position.x + (float)y - temporal_animation_minimum_position.x) * current_feature_data.animation_progress + (float)x + 1.f, temporal_animation_maximum_position.y },
				ImGui::ColorConvertFloat4ToU32({ 0.19, 0.26, 0.57, .9f * (float)x / (float)y * array_list_animation_progress })
			);

			fixed_add_line(
				{ temporal_animation_minimum_position.x + (temporal_animation_maximum_position.x + (float)y - temporal_animation_minimum_position.x) * current_feature_data.animation_progress + (float)x, temporal_animation_maximum_position.y + 1.f },
				{ temporal_animation_minimum_position.x + (temporal_animation_maximum_position.x + (float)y - temporal_animation_minimum_position.x) * current_feature_data.animation_progress + (float)x + 1.f, temporal_animation_maximum_position.y + 1.f },
				ImGui::ColorConvertFloat4ToU32({ 0.19, 0.26, 0.57, 1.8f * (float)x / (float)y * array_list_animation_progress })
			);

			fixed_add_line(
				{ temporal_animation_minimum_position.x + (temporal_animation_maximum_position.x + (float)y - temporal_animation_minimum_position.x) * current_feature_data.animation_progress + (float)x, temporal_animation_maximum_position.y + 2.f },
				{ temporal_animation_minimum_position.x + (temporal_animation_maximum_position.x + (float)y - temporal_animation_minimum_position.x) * current_feature_data.animation_progress + (float)x + 1.f, temporal_animation_maximum_position.y + 2.f },
				ImGui::ColorConvertFloat4ToU32({ 0.19, 0.26, 0.57, .9f * (float)x / (float)y * array_list_animation_progress })
			);
		}

		if (smooth_value_change(current_feature_data.animation_progress, .015f))
			current_feature_data.animation_progress = 0.f;

		ImGui::GetBackgroundDrawList()->AddText(
			{ temporal_animation_minimum_position.x + 4.f, temporal_animation_minimum_position.y + 15.f - current_feature_data_name_size.y / 2.f - 1.f },
			ImGui::ColorConvertFloat4ToU32({ .6f, .6f, .6f, .9f * array_list_animation_progress }),
			current_feature_data.name
		);

		animation_position_y_increment += 33.;
	}

	smooth_value_change(array_list_animation_progress, .05f);

	if (client::features::visual::array_list::draw_watermark)
	{
		static auto timer = sdk::__timer();

		auto elapsed_milliseconds = (float)timer.get_elapsed_milliseconds();

		auto smooth_value_change = [&](float& value, float speed) -> bool
			{
				if (value += (1.f - value) * speed * elapsed_milliseconds * .14285f; speed > 0.f ? value > 0.99f : value < 0.1f)
				{
					value = speed > 0.f ? 1.f : 0.f;

					return true;
				}

				return false;
			};

		static auto water_mark_animation_progress = 0.f;

		static auto animation_minimum_position = ImVec2(-95.f, 5.f), animation_maximum_position = ImVec2(animation_minimum_position.x, animation_minimum_position.y + 30.f);

		animation_minimum_position.x = -95.f + water_mark_animation_progress * 100.f;

		static auto client_text_size = ImGui::CalcTextSize(XOR("DREAM")), advanced_text_size = ImGui::CalcTextSize(XOR("ADVANCED"));

		animation_maximum_position.x = animation_minimum_position.x + (4.f + client_text_size.x + 4.f + advanced_text_size.x + 4.f) * water_mark_animation_progress;

		ImGui::GetBackgroundDrawList()->AddRectFilled(
			animation_minimum_position,
			animation_maximum_position,
			ImGui::ColorConvertFloat4ToU32({ .12f, .13f, .15f, .9f * water_mark_animation_progress })
		);

		ImGui::GetBackgroundDrawList()->AddRect(
			{ animation_minimum_position.x + 1.f, animation_minimum_position.y + 1.f },
			{ animation_maximum_position.x - 1.f, animation_maximum_position.y - 1.f },
			ImGui::ColorConvertFloat4ToU32({ 0.19, 0.26, 0.57, .9f * water_mark_animation_progress })
		);

		ImGui::GetBackgroundDrawList()->AddRectFilled(
			{ animation_minimum_position.x + 4.f - 1.f, animation_minimum_position.y + 3.f },
			{ animation_minimum_position.x + 4.f + 1.f + client_text_size.x, animation_maximum_position.y - 3.f },
			ImGui::ColorConvertFloat4ToU32({ .24f, .26f, .3f, .3f * water_mark_animation_progress })
		);

		ImGui::GetBackgroundDrawList()->AddText(
			{ animation_minimum_position.x + 4.f, animation_minimum_position.y + 15.f - client_text_size.y / 2.f - 1.f },
			ImGui::ColorConvertFloat4ToU32({ 0.19, 0.26, 0.57, .9f * water_mark_animation_progress }),
			XOR("DREAM")
		);

		ImGui::GetBackgroundDrawList()->AddText(
			{ animation_minimum_position.x + 4.f + client_text_size.x + 4.f, animation_minimum_position.y + 15.f - advanced_text_size.y / 2.f - 1.f },
			ImGui::ColorConvertFloat4ToU32({ .6f, .6f, .6f, .6f * water_mark_animation_progress }),
			XOR("ADVANCED")
		);

		ImGui::GetBackgroundDrawList()->AddRectFilled(
			{ animation_minimum_position.x, animation_maximum_position.y },
			{ animation_maximum_position.x, animation_maximum_position.y + 3.f },
			ImGui::ColorConvertFloat4ToU32({ .08f, .08f, .08f, .9 })
		);

		static auto pulse_animation_progress = 0.f;

		for (auto x = 0, y = 50; x < y; ++x)
		{
			auto fixed_add_line = [&](ImVec2 point_0, ImVec2 point_1, ImU32 color) -> void
				{
					point_0.x -= (float)y;
					point_1.x -= (float)y;

					if (point_0.x < animation_minimum_position.x)
						point_0.x = animation_minimum_position.x;

					if (point_0.x > animation_maximum_position.x)
						point_0.x = animation_maximum_position.x;

					if (point_1.x < animation_minimum_position.x)
						point_1.x = animation_minimum_position.x;

					if (point_1.x > animation_maximum_position.x)
						point_1.x = animation_maximum_position.x;

					ImGui::GetBackgroundDrawList()->AddLine(point_0, point_1, color);
				};

			fixed_add_line(
				{ animation_minimum_position.x + (animation_maximum_position.x + (float)y - animation_minimum_position.x) * pulse_animation_progress + (float)x, animation_maximum_position.y },
				{ animation_minimum_position.x + (animation_maximum_position.x + (float)y - animation_minimum_position.x) * pulse_animation_progress + (float)x + 1.f, animation_maximum_position.y },
				ImGui::ColorConvertFloat4ToU32({ 0.19, 0.26, 0.57, .9f * (float)x / (float)y * water_mark_animation_progress })
			);

			fixed_add_line(
				{ animation_minimum_position.x + (animation_maximum_position.x + (float)y - animation_minimum_position.x) * pulse_animation_progress + (float)x, animation_maximum_position.y + 1.f },
				{ animation_minimum_position.x + (animation_maximum_position.x + (float)y - animation_minimum_position.x) * pulse_animation_progress + (float)x + 1.f, animation_maximum_position.y + 1.f },
				ImGui::ColorConvertFloat4ToU32({ 0.19, 0.26, 0.57, 1.8f * (float)x / (float)y * water_mark_animation_progress })
			);

			fixed_add_line(
				{ animation_minimum_position.x + (animation_maximum_position.x + (float)y - animation_minimum_position.x) * pulse_animation_progress + (float)x, animation_maximum_position.y + 2.f },
				{ animation_minimum_position.x + (animation_maximum_position.x + (float)y - animation_minimum_position.x) * pulse_animation_progress + (float)x + 1.f, animation_maximum_position.y + 2.f },
				ImGui::ColorConvertFloat4ToU32({ 0.19, 0.26, 0.57, .9f * (float)x / (float)y * water_mark_animation_progress })
			);
		}

		if (smooth_value_change(pulse_animation_progress, .015f))
			pulse_animation_progress = 0.f;

		smooth_value_change(water_mark_animation_progress, .05f);
	}
}