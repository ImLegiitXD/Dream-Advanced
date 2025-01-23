
#include "../security.h"

#pragma comment(linker, "/INCLUDE:_tls_used")
#pragma comment(linker, "/INCLUDE:_tls_callback")

#pragma const_seg(".CRT$XLY")

extern "C" const auto _tls_callback = (unsigned __int64)client::security::callbacks::thread_notification;

#pragma const_seg()

auto client::security::callbacks::thread_notification(unsigned __int64 module_address, unsigned __int32 calling_reason, unsigned __int64 reserved) -> void
{
	if (RegisterClassExW == nullptr)
		return;

	if (sdk::current_process_load_kernel_system_time == 0)
	{
		sdk::current_process_load_kernel_system_time = KERNEL_SYSTEM_TIME;

		return;
	}

	if (sdk::current_process_load_kernel_system_time == 0 || KERNEL_SYSTEM_TIME == 0 || sdk::__timer(sdk::current_process_load_kernel_system_time, KERNEL_SYSTEM_TIME).has_elapsed(2500.))
		CHECK_CURRENT_PROCESS_THREADS_3_REPORT_EXIT_RETURN((void)nullptr);
}

auto client::security::callbacks::module_notification(unsigned __int32 calling_reason, _LDR_DLL_NOTIFICATION_DATA* ldnd, unsigned __int64 context) -> void
{
	if (sdk::current_process_load_kernel_system_time == 0 || KERNEL_SYSTEM_TIME == 0 || sdk::__timer(sdk::current_process_load_kernel_system_time, KERNEL_SYSTEM_TIME).has_elapsed(2500.))
		CHECK_CURRENT_PROCESS_THREADS_3_REPORT_EXIT_RETURN((void)nullptr);

	client::security::callbacks::module_file_paths.push_back(ldnd->Loaded.FullDllName->Buffer);
}