
#include "client.hpp"

auto client::initialize() -> __int32
{
	if (sdk::current_process_load_kernel_system_time == 0 || KERNEL_SYSTEM_TIME == 0 || sdk::__timer(sdk::current_process_load_kernel_system_time, KERNEL_SYSTEM_TIME).has_elapsed(2500.))
		REPORT_EXIT_RETURN(1);

	for (auto nt_delay_execution_result = 0; nt_delay_execution_result == 0 && KERNEL_SYSTEM_TIME != 0; nt_delay_execution_result = sdk::nt_delay_execution(1000))
	{
		if (auto pici = _PROCESS_INSTRUMENTATION_CALLBACK_INFORMATION(); sdk::nt_set_information_process(CURRENT_PROCESS_HANDLE, 0x28, &pici, sizeof(_PROCESS_INSTRUMENTATION_CALLBACK_INFORMATION)) != 0)
			REPORT_EXIT_RETURN(1);

		if (auto fixed_value = KERNEL_SYSTEM_TIME, value = client::security::checks::is_virtual_computer_checks_count = 0;
			fixed_value == 0 || client::security::checks::is_virtual_computer(fixed_value, &value) != sdk::current_process_load_kernel_system_time || fixed_value != value || client::security::checks::is_virtual_computer_checks_count != 1)
			REPORT_EXIT_RETURN(1);

		if (auto fixed_value = KERNEL_SYSTEM_TIME, value = client::security::checks::is_debugger_present_checks_count = 0;
			fixed_value == 0 || client::security::checks::is_debugger_present(fixed_value, &value) != sdk::current_process_load_kernel_system_time || fixed_value != value || client::security::checks::is_debugger_present_checks_count != 4)
			REPORT_EXIT_RETURN(1);

		if (auto fixed_value = KERNEL_SYSTEM_TIME, value = client::security::checks::is_process_tampered_checks_count = 0;
			fixed_value == 0 || client::security::checks::is_process_tampered(fixed_value, &value) != sdk::current_process_load_kernel_system_time || fixed_value != value || client::security::checks::is_process_tampered_checks_count == 0)
			REPORT_EXIT_RETURN(1);

		if (auto fixed_value = KERNEL_SYSTEM_TIME, value = client::security::checks::is_process_accessed_checks_count = 0;
			fixed_value == 0 || client::security::checks::is_process_accessed(fixed_value, &value) != sdk::current_process_load_kernel_system_time || fixed_value != value || client::security::checks::is_process_accessed_checks_count == 0)
			REPORT_EXIT_RETURN(1);

		static auto create_core_thread = []() -> __int32
		{
			if (sdk::nt_create_thread_ex(&client::security::core_thread_handle, THREAD_ALL_ACCESS, CURRENT_PROCESS_HANDLE, client::core::initialize, nullptr, THREAD_CREATE_FLAGS_BYPASS_DEBUGGER | THREAD_CREATE_FLAGS_BYPASS_PROCESS_FREEZE) != 0)
				REPORT_EXIT_RETURN(1);

			return 0;
		}();

		CHECK_CURRENT_PROCESS_THREADS_1_REPORT_EXIT_RETURN(1);
	}

	REPORT_EXIT_RETURN(1);
}