
#include "core.hpp"

auto client::core::initialize() -> __int32
{
	if (sdk::ldr_register_dll_notification(client::security::callbacks::module_notification, &client::security::callbacks::module_entry_point_callback_cookie) != 0 || client::security::callbacks::module_entry_point_callback_cookie == nullptr)
		REPORT_EXIT_RETURN(1);

	if (sdk::nt_create_thread_ex(&client::security::menu_thread_handle, THREAD_ALL_ACCESS, CURRENT_PROCESS_HANDLE, client::core::menu::initialize, nullptr, THREAD_CREATE_FLAGS_BYPASS_DEBUGGER | THREAD_CREATE_FLAGS_BYPASS_PROCESS_FREEZE) != 0)
		REPORT_EXIT_RETURN(1);

	for (; !client::core::menu::initialized; sdk::nt_delay_execution(1));

	if (sdk::ldr_unregister_dll_notification(client::security::callbacks::module_entry_point_callback_cookie) != 0)
		REPORT_EXIT_RETURN(1);

	if (sdk::nt_create_thread_ex(&client::security::auth_thread_handle, THREAD_ALL_ACCESS, CURRENT_PROCESS_HANDLE, client::core::auth::initialize, nullptr, THREAD_CREATE_FLAGS_BYPASS_DEBUGGER | THREAD_CREATE_FLAGS_BYPASS_PROCESS_FREEZE) != 0)
		REPORT_EXIT_RETURN(1);

	for (; client::core::menu::target_process_identifier == 0; sdk::nt_delay_execution(1))
	{
		if (client::core::menu::uninitialized)
			EXIT_RETURN(0);

		CHECK_CURRENT_PROCESS_THREADS_2_REPORT_EXIT_RETURN(1);
	}

	if (sdk::nt_open_process(&sdk::target_process_handle, PROCESS_ALL_ACCESS, client::core::menu::target_process_identifier) != 0 || sdk::target_process_handle == nullptr)
		REPORT_EXIT_RETURN(1);

	auto remote_module_address = sdk::get_module_address_ex(sdk::target_process_handle, XOR(L"lwjgl64.dll"));

	if (remote_module_address == 0)
		REPORT_EXIT_RETURN(1);

	auto remote_module_export_address = sdk::get_module_export_address_ex(sdk::target_process_handle, remote_module_address, XOR("Java_org_lwjgl_opengl_GL11_nglPushMatrix"));

	if (remote_module_export_address == 0)
		REPORT_EXIT_RETURN(1);

	auto remote_mapped_received_module = client::mapper::__module(sdk::target_process_handle, client::core::auth::received_module, remote_module_export_address, (unsigned __int64)client::core::java_org_lwjgl_opengl_gl_11_ngl_push_matrix);

	if (!remote_mapped_received_module.create())
		REPORT_EXIT_RETURN(1);

	sdk::free_memory(client::core::auth::received_module);

	if (client::core::ipc::initialize(remote_mapped_received_module.address) != 0)
		REPORT_EXIT_RETURN(1);

	//auto hardware_identifier_setting_address = client::core::ipc::get_setting_address(XOR("client::hardware_identifier"));

	//if (hardware_identifier_setting_address == 0)
	//	REPORT_EXIT_RETURN(1);

	//sdk::copy_memory(hardware_identifier_setting_address, (unsigned __int64)sdk::get_hardware_identifier().get_multibyte_string(), 64);

	auto loader_process_identifier_setting_address = client::core::ipc::get_setting_address(XOR("client::hooks::loader_process_identifier"));

	if (loader_process_identifier_setting_address == 0)
		REPORT_EXIT_RETURN(1);

	auto pbi = _PROCESS_BASIC_INFORMATION();

	if (sdk::nt_query_information_process(CURRENT_PROCESS_HANDLE, 0, &pbi, sizeof(_PROCESS_BASIC_INFORMATION)) != 0 || pbi.UniqueProcessId == 0)
		REPORT_EXIT_RETURN(1);

	*(unsigned __int64*)loader_process_identifier_setting_address = pbi.UniqueProcessId;

	if (!remote_mapped_received_module.attach())
		REPORT_EXIT_RETURN(1);

	auto detach_remove_remote_mapped_received_module = true;

	for (client::core::menu::set_configuration(); !client::core::menu::uninitialized; sdk::nt_delay_execution(1))
	{
		if (auto pbi = _PROCESS_BASIC_INFORMATION(); sdk::nt_query_information_process(sdk::target_process_handle, 0, &pbi, sizeof(_PROCESS_BASIC_INFORMATION)) != 0 || pbi.ExitStatus != STILL_ACTIVE)
		{
			detach_remove_remote_mapped_received_module = false;

			break;
		}

		CHECK_CURRENT_PROCESS_THREADS_2_REPORT_EXIT_RETURN(1);
	}

	if (detach_remove_remote_mapped_received_module)
	{
		if (!remote_mapped_received_module.detach())
			REPORT_EXIT_RETURN(1);

		if (!remote_mapped_received_module.remove())
			REPORT_EXIT_RETURN(1);
	}

	if (sdk::nt_create_thread_ex(&client::security::exit_thread_handle, THREAD_ALL_ACCESS, CURRENT_PROCESS_HANDLE, client::core::exit::initialize, nullptr, THREAD_CREATE_FLAGS_BYPASS_DEBUGGER | THREAD_CREATE_FLAGS_BYPASS_PROCESS_FREEZE) != 0)
		REPORT_EXIT_RETURN(1);

	for (; !client::core::exit::uninitialized; sdk::nt_delay_execution(1))
		CHECK_CURRENT_PROCESS_THREADS_2_REPORT_EXIT_RETURN(1);

	EXIT_RETURN(0);
}

auto client::core::java_org_lwjgl_opengl_gl_11_ngl_push_matrix(void* jni, void* klass, unsigned __int64 function) -> void
{
	if (jni != nullptr && klass != nullptr && function != 0)
	{
		if (auto shellcode_function_address = (unsigned __int64)client::core::java_org_lwjgl_opengl_gl_11_ngl_push_matrix + 0x100 - sizeof(unsigned __int64), shellcode_function = *(unsigned __int64*)shellcode_function_address; shellcode_function != 0)
		{
			*(unsigned __int64*)shellcode_function_address = 0;

			((void(__cdecl*)())shellcode_function)();
		}
	}

	return ((void(__stdcall*)())function)();
}