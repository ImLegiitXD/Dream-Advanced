
#include "security.hpp"

namespace client::security
{
	inline void* scrt_thread_handle = nullptr;
	inline void* main_thread_handle = nullptr;
	inline void* core_thread_handle = nullptr;
	inline void* menu_thread_handle = nullptr;
	inline void* auth_thread_handle = nullptr;
	inline void* exit_thread_handle = nullptr;
	inline auto scrt_thread_last_updated_kernel_system_time = KERNEL_SYSTEM_TIME;
	inline auto main_thread_last_updated_kernel_system_time = KERNEL_SYSTEM_TIME;
	inline auto core_thread_last_updated_kernel_system_time = KERNEL_SYSTEM_TIME;
}

namespace client::security::callbacks
{
	extern auto thread_notification(unsigned __int64 module_address, unsigned __int32 calling_reason, unsigned __int64 reserved) -> void;

	inline void* module_entry_point_callback_cookie = nullptr;
	inline auto module_file_paths = std::vector<sdk::__unicode_string>();

	extern auto module_notification(unsigned __int32 calling_reason, _LDR_DLL_NOTIFICATION_DATA* ldnd, unsigned __int64 context) -> void;
}

namespace client::security::checks
{
	inline unsigned __int64 is_virtual_computer_checks_count = 0;

	extern auto is_virtual_computer(unsigned __int64 fixed_value, unsigned __int64* value) -> unsigned __int64;

	inline unsigned __int64 is_debugger_present_checks_count = 0;

	extern auto is_debugger_present(unsigned __int64 fixed_value, unsigned __int64* value) -> unsigned __int64;

	inline unsigned __int64 is_process_tampered_checks_count = 0;

	extern auto	is_process_tampered(unsigned __int64 fixed_value, unsigned __int64* value) -> unsigned __int64;

	inline unsigned __int64 is_process_accessed_checks_count = 0;

	extern auto is_process_accessed(unsigned __int64 fixed_value, unsigned __int64* value) -> unsigned __int64;
}

namespace client::security::report
{
	extern auto create(sdk::__multibyte_string message) -> void;
}