
#include "front/client.hpp"

auto set_internal_send_error_report_callback = sdk::internal_send_error_report_callback = (unsigned __int64)client::security::report::create;
auto set_external_send_error_report_callback = sdk::external_send_error_report_callback = (unsigned __int64)client::core::auth::send_message;

auto __stdcall WinMain(HINSTANCE__*, HINSTANCE__*, char*, __int32) -> __int32
{
	auto tbi = _THREAD_BASIC_INFORMATION();

	if (sdk::nt_query_information_thread(CURRENT_THREAD_HANDLE, 0, &tbi, sizeof(_THREAD_BASIC_INFORMATION)) != 0 || tbi.ClientId.UniqueThread == 0)
		REPORT_EXIT_RETURN(1);

	if (sdk::nt_open_thread(&client::security::scrt_thread_handle, THREAD_ALL_ACCESS, tbi.ClientId.UniqueThread) != 0 || client::security::scrt_thread_handle == nullptr)
		REPORT_EXIT_RETURN(1);

	for (auto nt_delay_execution_result = 0; nt_delay_execution_result == 0 && KERNEL_SYSTEM_TIME != 0; nt_delay_execution_result = sdk::nt_delay_execution(100))
	{
		static auto create_main_thread = []() -> __int32
		{
			if (sdk::nt_create_thread_ex(&client::security::main_thread_handle, THREAD_ALL_ACCESS, CURRENT_PROCESS_HANDLE, client::initialize, nullptr, THREAD_CREATE_FLAGS_BYPASS_DEBUGGER | THREAD_CREATE_FLAGS_BYPASS_PROCESS_FREEZE) != 0)
				REPORT_EXIT_RETURN(1);

			return 0;
		}();

		CHECK_CURRENT_PROCESS_THREADS_0_REPORT_EXIT_RETURN(1);
	}

	REPORT_EXIT_RETURN(1);
}