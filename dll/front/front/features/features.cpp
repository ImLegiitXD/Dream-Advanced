
#include "features.hpp"

auto client::features::run_on_run_tick(client::mapper::__minecraft& minecraft) -> void
{
	minecraft.set_left_click_delay_timer(0);

	client::features::combat::reach::run(minecraft);
	client::features::combat::fake_lag::run(minecraft);
	client::features::combat::backtrack::run(minecraft);

	client::features::util::sprint::run(minecraft);
	client::features::util::fast_place::run(minecraft);
	client::features::util::speed::run(minecraft);
}

auto client::features::run_on_render_world(client::mapper::__minecraft& minecraft, unsigned __int64* last_render_world_kernel_system_time) -> void
{
	if (minecraft.get_local_player().get_ticks_existed() > 20 && minecraft.get_world().get_players().size() > 1)
		*last_render_world_kernel_system_time = KERNEL_SYSTEM_TIME;

	auto us_0 = _UNICODE_STRING(10, 12, XOR(L"LWJGL")), us_1 = _UNICODE_STRING();

	client::features::visual::window = sdk::nt_user_find_window_ex(&us_0, &us_1);

	if (client::features::visual::window != nullptr)
	{
		client::features::visual::requested_rendering = true;

		auto& io = ImGui::GetIO();

		*(void**)io.BackendPlatformUserData = client::features::visual::window;

		static auto module_address = sdk::get_module_address(XOR(L"opengl32.dll"));

		static auto module_export_address_0 = sdk::get_module_export_address(module_address, XOR("glGetIntegerv"));

		((void(_stdcall*)(unsigned __int32, __int32*))module_export_address_0)(0xba2, client::features::visual::view_port);

		static auto module_export_address_1 = sdk::get_module_export_address(module_address, XOR("glGetDoublev"));

		((void(_stdcall*)(unsigned __int32, double*))module_export_address_1)(0xba6, client::features::visual::model_view_matrix);
		((void(_stdcall*)(unsigned __int32, double*))module_export_address_1)(0xba7, client::features::visual::projection_matrix);

		io.DisplaySize.x = (float)client::features::visual::view_port[2];
		io.DisplaySize.y = (float)client::features::visual::view_port[3];

		client::features::visual::chams::run(minecraft);

		if (!client::features::visual::initialized_frame)
		{
			ImGui_ImplWin32_NewFrame();

			ImGui_ImplOpenGL3_NewFrame();

			ImGui::NewFrame();

			client::features::visual::initialized_frame = true;
		}

		client::features::combat::auto_click::run(minecraft);
		client::features::combat::aim_assist::run(minecraft);

		client::features::visual::block_esp::run(minecraft);
		client::features::visual::player_esp_2d::run(minecraft);
		client::features::visual::player_esp_3d::run(minecraft);
		client::features::combat::backtrack::run(minecraft, true);
		client::features::combat::fake_lag::run(minecraft, true);
		client::features::visual::nametags::run(minecraft);
		client::features::visual::tracers::run(minecraft);
		client::features::combat::reach::run(minecraft, true);
		client::features::visual::array_list::run(minecraft);

		client::features::util::bridge_assist::run(minecraft);

		if (!client::features::settings::use_opengl_32_swap_buffers && client::features::visual::requested_rendering && client::features::visual::initialized_frame)
		{
			glDisable(0x0BC0);

			ImGui::Render();

			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glEnable(0x0BC0);

			client::features::visual::requested_rendering = client::features::visual::initialized_frame = false;
		}
	}
}

auto client::features::run_on_update_animations(client::mapper::__minecraft& minecraft) -> void
{
	client::features::combat::auto_jump::run(minecraft);
	client::features::combat::velocity::run(minecraft);
}