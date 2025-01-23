
#include "../mapper/mapper.hpp"

#define IS_THREAD_TAMPERED_REPORT_EXIT_RETURN(thread_handle, message, value)	\
{{	\
	if (thread_handle == nullptr)	\
		EXTRA_REPORT_EXIT_RETURN(message, value);	\
	\
	if (auto tbi = _THREAD_BASIC_INFORMATION(); sdk::nt_query_information_thread(thread_handle, 0, &tbi, sizeof(_THREAD_BASIC_INFORMATION)) != 0 || tbi.ExitStatus != STILL_ACTIVE)	\
		EXTRA_REPORT_EXIT_RETURN(message, value);	\
	\
	if (unsigned __int32 thread_suspend_count = 0; sdk::nt_resume_thread(thread_handle, &thread_suspend_count) != 0 || thread_suspend_count != 0)	\
		EXTRA_REPORT_EXIT_RETURN(message, value);	\
}}

#define CHECK_CURRENT_PROCESS_THREADS_0_REPORT_EXIT_RETURN(value)	\
{{	\
	IS_THREAD_TAMPERED_REPORT_EXIT_RETURN(client::security::scrt_thread_handle, sdk::__multibyte_string(XOR("scrt_thread_handle")), value);	\
	IS_THREAD_TAMPERED_REPORT_EXIT_RETURN(client::security::main_thread_handle, sdk::__multibyte_string(XOR("main_thread_handle")), value);	\
	\
	if (client::security::scrt_thread_last_updated_kernel_system_time == 0 || KERNEL_SYSTEM_TIME == 0 || sdk::__timer(client::security::scrt_thread_last_updated_kernel_system_time, KERNEL_SYSTEM_TIME).has_elapsed(2500.))	\
		EXTRA_REPORT_EXIT_RETURN(sdk::__multibyte_string(XOR("scrt_thread_last_updated_kernel_system_time")), value);	\
	\
	if (client::security::main_thread_last_updated_kernel_system_time == 0 || KERNEL_SYSTEM_TIME == 0 || sdk::__timer(client::security::main_thread_last_updated_kernel_system_time, KERNEL_SYSTEM_TIME).has_elapsed(2500.))	\
		EXTRA_REPORT_EXIT_RETURN(sdk::__multibyte_string(XOR("main_thread_last_updated_kernel_system_time")), value);	\
	\
	client::security::scrt_thread_last_updated_kernel_system_time = KERNEL_SYSTEM_TIME;	\
}}

#define CHECK_CURRENT_PROCESS_THREADS_1_REPORT_EXIT_RETURN(value)	\
{{	\
	IS_THREAD_TAMPERED_REPORT_EXIT_RETURN(client::security::scrt_thread_handle, sdk::__multibyte_string(XOR("scrt_thread_handle")), value);	\
	IS_THREAD_TAMPERED_REPORT_EXIT_RETURN(client::security::main_thread_handle, sdk::__multibyte_string(XOR("main_thread_handle")), value);	\
	IS_THREAD_TAMPERED_REPORT_EXIT_RETURN(client::security::core_thread_handle, sdk::__multibyte_string(XOR("core_thread_handle")), value);	\
	\
	if (client::security::scrt_thread_last_updated_kernel_system_time == 0 || KERNEL_SYSTEM_TIME == 0 || sdk::__timer(client::security::scrt_thread_last_updated_kernel_system_time, KERNEL_SYSTEM_TIME).has_elapsed(2500.))	\
		EXTRA_REPORT_EXIT_RETURN(sdk::__multibyte_string(XOR("scrt_thread_last_updated_kernel_system_time")), value);	\
	\
	if (client::security::main_thread_last_updated_kernel_system_time == 0 || KERNEL_SYSTEM_TIME == 0 || sdk::__timer(client::security::main_thread_last_updated_kernel_system_time, KERNEL_SYSTEM_TIME).has_elapsed(2500.))	\
		EXTRA_REPORT_EXIT_RETURN(sdk::__multibyte_string(XOR("main_thread_last_updated_kernel_system_time")), value);	\
	\
	if (client::security::core_thread_last_updated_kernel_system_time == 0 || KERNEL_SYSTEM_TIME == 0 || sdk::__timer(client::security::core_thread_last_updated_kernel_system_time, KERNEL_SYSTEM_TIME).has_elapsed(2500.))	\
		EXTRA_REPORT_EXIT_RETURN(sdk::__multibyte_string(XOR("core_thread_last_updated_kernel_system_time")), value);	\
	\
	client::security::main_thread_last_updated_kernel_system_time = KERNEL_SYSTEM_TIME;	\
}}

#define CHECK_CURRENT_PROCESS_THREADS_2_REPORT_EXIT_RETURN(value)	\
{{	\
	IS_THREAD_TAMPERED_REPORT_EXIT_RETURN(client::security::scrt_thread_handle, sdk::__multibyte_string(XOR("scrt_thread_handle")), value);	\
	IS_THREAD_TAMPERED_REPORT_EXIT_RETURN(client::security::main_thread_handle, sdk::__multibyte_string(XOR("main_thread_handle")), value);	\
	IS_THREAD_TAMPERED_REPORT_EXIT_RETURN(client::security::core_thread_handle, sdk::__multibyte_string(XOR("core_thread_handle")), value);	\
	IS_THREAD_TAMPERED_REPORT_EXIT_RETURN(client::security::menu_thread_handle, sdk::__multibyte_string(XOR("menu_thread_handle")), value);	\
	IS_THREAD_TAMPERED_REPORT_EXIT_RETURN(client::security::auth_thread_handle, sdk::__multibyte_string(XOR("auth_thread_handle")), value);	\
	\
	if (client::security::scrt_thread_last_updated_kernel_system_time == 0 || KERNEL_SYSTEM_TIME == 0 || sdk::__timer(client::security::scrt_thread_last_updated_kernel_system_time, KERNEL_SYSTEM_TIME).has_elapsed(2500.))	\
		EXTRA_REPORT_EXIT_RETURN(sdk::__multibyte_string(XOR("scrt_thread_last_updated_kernel_system_time")), value);	\
	\
	if (client::security::main_thread_last_updated_kernel_system_time == 0 || KERNEL_SYSTEM_TIME == 0 || sdk::__timer(client::security::main_thread_last_updated_kernel_system_time, KERNEL_SYSTEM_TIME).has_elapsed(2500.))	\
		EXTRA_REPORT_EXIT_RETURN(sdk::__multibyte_string(XOR("main_thread_last_updated_kernel_system_time")), value);	\
	\
	if (client::security::core_thread_last_updated_kernel_system_time == 0 || KERNEL_SYSTEM_TIME == 0 || sdk::__timer(client::security::core_thread_last_updated_kernel_system_time, KERNEL_SYSTEM_TIME).has_elapsed(2500.))	\
		EXTRA_REPORT_EXIT_RETURN(sdk::__multibyte_string(XOR("core_thread_last_updated_kernel_system_time")), value);	\
	\
	client::security::core_thread_last_updated_kernel_system_time = KERNEL_SYSTEM_TIME;	\
}}

#define CHECK_CURRENT_PROCESS_THREADS_3_REPORT_EXIT_RETURN(value)	\
{{	\
	IS_THREAD_TAMPERED_REPORT_EXIT_RETURN(client::security::scrt_thread_handle, sdk::__multibyte_string(XOR("scrt_thread_handle")), value);	\
	IS_THREAD_TAMPERED_REPORT_EXIT_RETURN(client::security::main_thread_handle, sdk::__multibyte_string(XOR("main_thread_handle")), value);	\
	IS_THREAD_TAMPERED_REPORT_EXIT_RETURN(client::security::core_thread_handle, sdk::__multibyte_string(XOR("core_thread_handle")), value);	\
	IS_THREAD_TAMPERED_REPORT_EXIT_RETURN(client::security::menu_thread_handle, sdk::__multibyte_string(XOR("menu_thread_handle")), value);	\
	IS_THREAD_TAMPERED_REPORT_EXIT_RETURN(client::security::auth_thread_handle, sdk::__multibyte_string(XOR("auth_thread_handle")), value);	\
	\
	if (client::security::scrt_thread_last_updated_kernel_system_time == 0 || KERNEL_SYSTEM_TIME == 0 || sdk::__timer(client::security::scrt_thread_last_updated_kernel_system_time, KERNEL_SYSTEM_TIME).has_elapsed(2500.))	\
		EXTRA_REPORT_EXIT_RETURN(sdk::__multibyte_string(XOR("scrt_thread_last_updated_kernel_system_time")), value);	\
	\
	if (client::security::main_thread_last_updated_kernel_system_time == 0 || KERNEL_SYSTEM_TIME == 0 || sdk::__timer(client::security::main_thread_last_updated_kernel_system_time, KERNEL_SYSTEM_TIME).has_elapsed(2500.))	\
		EXTRA_REPORT_EXIT_RETURN(sdk::__multibyte_string(XOR("main_thread_last_updated_kernel_system_time")), value);	\
	\
	if (client::security::core_thread_last_updated_kernel_system_time == 0 || KERNEL_SYSTEM_TIME == 0 || sdk::__timer(client::security::core_thread_last_updated_kernel_system_time, KERNEL_SYSTEM_TIME).has_elapsed(2500.))	\
		EXTRA_REPORT_EXIT_RETURN(sdk::__multibyte_string(XOR("core_thread_last_updated_kernel_system_time")), value);	\
}}