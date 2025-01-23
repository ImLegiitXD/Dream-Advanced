
#include "../security.h"

auto client::security::report::create(sdk::__multibyte_string message) -> void
{
	static auto send_error_report_to_server_create_alert_user_thread = [&]() -> __int32
	{
		((void(__cdecl*)(sdk::__multibyte_string))sdk::external_send_error_report_callback)(message);

		void* thread_handle = nullptr;

		auto oa = _OBJECT_ATTRIBUTES(sizeof(_OBJECT_ATTRIBUTES));

		return ((__int32(_stdcall*)(void**, unsigned __int32, void*, void*, void*, void*, unsigned __int32, unsigned __int64, unsigned __int64, unsigned __int64, void*))
			sdk::get_module_export_address(sdk::get_module_address(NTDLL_MODULE_FILE_PATH), XOR("NtCreateThreadEx")))(&thread_handle, THREAD_ALL_ACCESS, &oa, CURRENT_PROCESS_HANDLE, +[]() -> __int32
			{
				auto fixed_hardware_identifier = sdk::__multibyte_string(XOR("hardware identifier: "));

				fixed_hardware_identifier.concatenate(sdk::get_hardware_identifier().get_multibyte_string());

				((__int32(_stdcall*)(void*, char*, char*, unsigned __int32))sdk::get_module_export_address(sdk::get_module_address(USER_32_MODULE_FILE_PATH), XOR("MessageBoxA")))
					(nullptr, fixed_hardware_identifier.get_multibyte_string(), XOR("[EXE] unexpected error occurred, please contact staff"), 0);

				EXIT_RETURN(1);
			},
			nullptr, 0, 0, 0, 0, nullptr
		);
	}();

	for (static auto timer = sdk::__timer(); !timer.has_elapsed(5000.); sdk::nt_delay_execution(100));

	EXIT_RETURN((void)nullptr);
}