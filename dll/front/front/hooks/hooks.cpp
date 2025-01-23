
#include "hooks.hpp"

auto client::hooks::initialize() -> __int32
{
	auto us_0 = _UNICODE_STRING(10, 12, XOR(L"LWJGL")), us_1 = _UNICODE_STRING();

	auto window = sdk::nt_user_find_window_ex(&us_0, &us_1);

	//if (window == nullptr)
	//	REPORT_EXIT_RETURN(1);

	if (ImGui::CreateContext() == nullptr)
		REPORT_EXIT_RETURN(1);

	if (!ImGui_ImplWin32_Init(window))
		REPORT_EXIT_RETURN(1);

	if (!ImGui_ImplOpenGL3_Init())
		REPORT_EXIT_RETURN(1);

	auto& io = ImGui::GetIO();

	io.IniFilename = nullptr;
	io.LogFilename = nullptr;
	io.FontDefault = io.Fonts->AddFontFromMemoryCompressedTTF(ImGui::Fonts::VerdanaData, ImGui::Fonts::VerdanaSize, 20.f);
	io.MouseDrawCursor = false;

	if (MH_Initialize() != 0)
		REPORT_EXIT_RETURN(1);

	auto lwjgl_64_module_address = sdk::get_module_address(XOR(L"lwjgl64.dll"));

	if (lwjgl_64_module_address == 0)
		REPORT_EXIT_RETURN(1);

	auto lwjgl_64_module_export_address_0 = sdk::get_module_export_address(lwjgl_64_module_address, XOR("Java_org_lwjgl_WindowsSysImplementation_nGetTime"));

	if (lwjgl_64_module_export_address_0 == 0)
		REPORT_EXIT_RETURN(1);

	if (MH_CreateHook((void*)lwjgl_64_module_export_address_0, client::hooks::get_time, &client::hooks::original_get_time) != 0 || client::hooks::original_get_time == nullptr)
		REPORT_EXIT_RETURN(1);

	auto lwjgl_64_module_export_address_1 = sdk::get_module_export_address(lwjgl_64_module_address, XOR("Java_org_lwjgl_opengl_GL11_nglClear"));

	if (lwjgl_64_module_export_address_1 == 0)
		REPORT_EXIT_RETURN(1);

	if (MH_CreateHook((void*)lwjgl_64_module_export_address_1, client::hooks::clear, &client::hooks::original_clear) != 0 || client::hooks::original_clear == nullptr)
		REPORT_EXIT_RETURN(1);

	auto lwjgl_64_module_export_address_2 = sdk::get_module_export_address(lwjgl_64_module_address, XOR("Java_org_lwjgl_opengl_GL11_nglRotatef"));

	if (lwjgl_64_module_export_address_2 == 0)
		REPORT_EXIT_RETURN(1);

	if (MH_CreateHook((void*)lwjgl_64_module_export_address_2, client::hooks::rotate, &client::hooks::original_rotate) != 0 || client::hooks::original_rotate == nullptr)
		REPORT_EXIT_RETURN(1);

	auto java_module_address = sdk::get_module_address(XOR(L"java.dll"));

	if (java_module_address == 0)
		REPORT_EXIT_RETURN(1);

	auto java_module_export_address = sdk::get_module_export_address(java_module_address, XOR("Java_java_lang_StrictMath_atan2"));

	if (java_module_export_address == 0)
		REPORT_EXIT_RETURN(1);

	if (MH_CreateHook((void*)java_module_export_address, client::hooks::atan_2, &client::hooks::original_atan_2) != 0 || client::hooks::original_atan_2 == nullptr)
		REPORT_EXIT_RETURN(1);

	auto opengl_32_module_address = sdk::get_module_address(XOR(L"opengl32.dll"));

	if (opengl_32_module_address == 0)
		REPORT_EXIT_RETURN(1);

	auto opengl_32_module_export_address = sdk::get_module_export_address(opengl_32_module_address, XOR("wglSwapBuffers"));

	if (opengl_32_module_export_address == 0)
		REPORT_EXIT_RETURN(1);

	if (MH_CreateHook((void*)opengl_32_module_export_address, client::hooks::swap_buffers, &client::hooks::original_swap_buffers) != 0 || client::hooks::original_swap_buffers == nullptr)
		REPORT_EXIT_RETURN(1);

	auto ws_2_32_module_address = sdk::get_module_address(XOR(L"ws2_32.dll"));

	if (ws_2_32_module_address == 0)
		REPORT_EXIT_RETURN(1);

	auto ws_2_32_module_export_address_0 = client::hooks::send_function = sdk::get_module_export_address(ws_2_32_module_address, XOR("WSASend"));

	if (ws_2_32_module_export_address_0 == 0)
		REPORT_EXIT_RETURN(1);

	if (MH_CreateHook((void*)ws_2_32_module_export_address_0, client::hooks::send, &client::hooks::original_send) != 0 || client::hooks::original_send == nullptr)
		REPORT_EXIT_RETURN(1);

	auto ws_2_32_module_export_address_1 = sdk::get_module_export_address(ws_2_32_module_address, XOR("WSARecv"));

	if (ws_2_32_module_export_address_1 == 0)
		REPORT_EXIT_RETURN(1);

	if (MH_CreateHook((void*)ws_2_32_module_export_address_1, client::hooks::recv, &client::hooks::original_recv) != 0 || client::hooks::original_recv == nullptr)
		REPORT_EXIT_RETURN(1);

	if (MH_EnableHook(MH_ALL_HOOKS) != 0)
		REPORT_EXIT_RETURN(1);

	return 0;
}

auto client::hooks::uninitialize() -> __int32
{
	if (MH_DisableHook(MH_ALL_HOOKS) != 0)
		REPORT_EXIT_RETURN(1);

	if (MH_Uninitialize() != 0)
		REPORT_EXIT_RETURN(1);

	client::hooks::release_buffered_packets(client::hooks::send_function);

	if (client::mapper::uninitialize() != 0)
		REPORT_EXIT_RETURN(1);

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	return 0;
}