
#include "../features.hpp"

auto client::features::visual::chams::run(client::mapper::__minecraft& minecraft) -> void
{
	if (!client::features::visual::chams::enabled)
		return;

	auto timer = minecraft.get_timer();
	auto timer_partial_ticks = timer.get_partial_ticks();

	auto world = minecraft.get_world();
	auto world_players = world.get_players();

	auto local_player = minecraft.get_local_player();
	auto local_player_view_position = local_player.get_view_position(timer_partial_ticks);

	auto render_manager = minecraft.get_render_manager();

	for (auto& player : world_players)
	{
		if (client::mapper::jni->IsSameObject(local_player.object, player.object))
			continue;

		auto player_health = player.get_health();

		if (player_health <= 0.f)
			continue;

		if (!client::features::visual::chams::draw_invisible_players && player.get_flag(5))
			continue;

		auto player_view_position = player.get_view_position(timer_partial_ticks);

		auto local_player_view_position_distance_to_player_view_position = local_player_view_position.get_distance_to_vec3(player_view_position);

		if (local_player_view_position_distance_to_player_view_position > 255.)
			continue;

		static auto module_export_address_0 = sdk::get_module_export_address(sdk::get_module_address(XOR(L"opengl32.dll")), XOR("glPolygonOffset"));
		static auto module_export_address_1 = sdk::get_module_export_address(sdk::get_module_address(XOR(L"opengl32.dll")), XOR("glColor4f"));

		glEnable(0x8037);

		((void(__stdcall*)(float, float))module_export_address_0)(1.f, -1000000.f);

		if (client::features::visual::chams::custom_color)
		{
			glDisable(GL_TEXTURE_2D);
			
			((void(__stdcall*)(float, float, float, float))module_export_address_1)(
				(float)client::features::visual::chams::color.x,
				(float)client::features::visual::chams::color.y,
				(float)client::features::visual::chams::color.z,
				(float)client::features::visual::chams::color.w
			);
		}

		render_manager.render_player(player, timer_partial_ticks);

		if (client::features::visual::chams::custom_color)
			glEnable(GL_TEXTURE_2D);

		((void(__stdcall*)(float, float))module_export_address_0)(1.f, 1000000.f);

		glDisable(0x8037);
	}
}