
#include "misc/include.hpp"
#include "misc/xor/xor.hpp"
#include "misc/sha/sha.hpp"

#define KERNEL_SHARED_MEMORY_ADDRESS				0x7ffe0000
#define KERNEL_SYSTEM_TIME							*(unsigned __int64*)(KERNEL_SHARED_MEMORY_ADDRESS + 0x14)
#define KERNEL_SYSTEM_ROOT_PATH						((wchar_t*)(KERNEL_SHARED_MEMORY_ADDRESS + 0x30))
#define KERNEL_DEBUGGER_INFORMATION					*(unsigned __int8*)(KERNEL_SHARED_MEMORY_ADDRESS + 0x2d4)

#define NTDLL_MODULE_FILE_PATH						XOR(L":\\windows\\system32\\ntdll.dll")
#define WIN_32_U_MODULE_FILE_PATH					XOR(L":\\windows\\system32\\win32u.dll")
#define KERNEL_32_MODULE_FILE_PATH					XOR(L":\\windows\\system32\\kernel32.dll")
#define USER_32_MODULE_FILE_PATH					XOR(L":\\windows\\system32\\user32.dll")

#define CURRENT_PROCESS_HANDLE						(void*)-1
#define CURRENT_THREAD_HANDLE						(void*)-2

#define THREAD_CREATE_FLAGS_BYPASS_DEBUGGER			0x00000004
#define THREAD_CREATE_FLAGS_BYPASS_PROCESS_FREEZE	0x00000040

#define OBJ_CASE_INSENSITIVE						0x00000040

#define ZERO_MEMORY(address, size)	for (unsigned __int64 x = 0; x < size; ++x) *(unsigned __int8*)(address + x) = 0;

namespace sdk
{
	inline unsigned __int64 current_process_load_kernel_system_time = 0;

	inline unsigned __int64 internal_send_error_report_callback = 0;
	inline unsigned __int64 external_send_error_report_callback = 0;

	extern auto get_process_enviroment_block() -> _PEB*;

	struct __multibyte_string;
	struct __unicode_string;

	extern auto get_module_address(sdk::__unicode_string file_path_or_name) -> unsigned __int64;
	extern auto get_module_address_ex(void* process_handle, sdk::__unicode_string file_path_or_name) -> unsigned __int64;
	extern auto get_module_file_path(unsigned __int64 address) -> wchar_t*;
	extern auto get_module_file_path_ex(void* process_handle, unsigned __int64 address) -> wchar_t*;
	extern auto get_module_size(unsigned __int64 address) -> unsigned __int64;
	extern auto get_module_size_ex(void* process_handle, unsigned __int64 address) -> unsigned __int64;
	extern auto get_module_export_address(unsigned __int64 address, char* name) -> unsigned __int64;
	extern auto get_module_export_address_ex(void* process_handle, unsigned __int64 address, char* name) -> unsigned __int64;

	extern auto nt_query_system_information(unsigned __int32 klass, void* information, unsigned __int32 size, unsigned __int32* requested_size = nullptr) -> __int32;

	extern auto nt_open_process(void** handle, unsigned __int32 access, unsigned __int64 identifier, bool force_elevation = true) -> __int32;
	extern auto nt_query_information_process(void* handle, unsigned __int32 klass, void* information, unsigned __int32 size, unsigned __int32* requested_size = nullptr) -> __int32;	
	extern auto nt_set_information_process(void* handle, unsigned __int32 klass, void* information, unsigned __int32 size) -> __int32;
	extern auto nt_open_process_token(void* handle, unsigned __int32 access, void** token_handle) -> __int32;
	extern auto nt_terminate_process(void* handle, __int32 exit_code) -> __int32;

	extern auto nt_query_virtual_memory(void* process_handle, void* address, unsigned __int32 klass, void* information, unsigned __int64 size, unsigned __int64* requested_size = nullptr) -> __int32;
	extern auto nt_allocate_virtual_memory(void* process_handle, void** address, unsigned __int64* size, unsigned __int32 type, unsigned __int32 protection) -> __int32;	
	extern auto nt_free_virtual_memory(void* process_handle, void** address, unsigned __int64* size, unsigned __int32 type) -> __int32;
	extern auto nt_protect_virtual_memory(void* process_handle, void* address, unsigned __int64* size, unsigned __int32 new_protection, unsigned __int32* old_protection) -> __int32;	
	extern auto nt_read_virtual_memory(void* process_handle, void* target_address, void* source_address, unsigned __int64 size, unsigned __int64* requested_size = nullptr) -> __int32;
	extern auto nt_write_virtual_memory(void* process_handle, void* target_address, void* source_address, unsigned __int64 size, unsigned __int64* requested_size = nullptr) -> __int32;

	extern auto nt_open_thread(void** handle, unsigned __int32 access, unsigned __int64 identifier) -> __int32;
	extern auto nt_create_thread_ex(void** handle, unsigned __int32 access, void* process_handle, void* address, void* parameters, unsigned __int32 flags) -> __int32;	
	extern auto nt_query_information_thread(void* handle, unsigned __int32 klass, void* information, unsigned __int32 size, unsigned __int32* requested_size = nullptr) -> __int32;
	extern auto nt_set_information_thread(void* handle, unsigned __int32 klass, void* information, unsigned __int32 size) -> __int32;
	extern auto nt_resume_thread(void* handle, unsigned __int32* suspend_count) -> __int32;	
	extern auto nt_terminate_thread(void* handle, __int32 exit_code) -> __int32;

	extern auto nt_open_file(void** handle, unsigned __int32 access, void* object_attributes, unsigned __int32 share_access) -> __int32;
	extern auto nt_query_volume_file_information(void* handle, void* information, unsigned __int32 size, unsigned __int32 klass) -> __int32;

	extern auto nt_create_section(void** handle, unsigned __int32 access, void* size, unsigned __int32 protection, unsigned __int32 attributes, void* file_handle) -> __int32;	
	extern auto nt_map_view_of_section(void* handle, void* process_handle, void** address, unsigned __int64* size, unsigned __int32 protection) -> __int32;	
	extern auto nt_unmap_view_of_section(void* handle, void* address) -> __int32;

	extern auto nt_set_timer_resolution(unsigned __int32 new_resolution, unsigned __int8 set, unsigned __int32* old_resolution) -> __int32;
	extern auto nt_delay_execution(__int32 milliseconds) -> __int32;

	extern auto nt_adjust_privileges_token(void* handle, void* privileges, unsigned __int32 size) -> __int32;
	extern auto nt_duplicate_object(void* source_process_handle, void* source_handle, void* target_process_handle, void** target_handle, unsigned __int32 access, unsigned __int32 flags) -> __int32;
	extern auto nt_close(void* handle) -> __int32;

	extern auto ldr_register_dll_notification(void* function, void** cookie) -> __int32;
	extern auto ldr_unregister_dll_notification(void* cookie) -> __int32;
	extern auto ldr_load_dll(void* file_name, unsigned __int64* address) -> __int32;

	extern auto nt_user_get_async_key_state(__int32 key_code) -> __int16;

	extern auto nt_user_find_window_ex(void* klass, void* title) -> void*;
	extern auto nt_user_query_window(void* handle, unsigned __int32 klass) -> unsigned __int32;
	extern auto nt_user_build_hwnd_list(unsigned __int32 count, void** list, unsigned __int32* requested_count = nullptr) -> __int32;
	extern auto nt_user_get_class_name(void* handle, _UNICODE_STRING* class_name) -> __int32;
	extern auto nt_user_internal_get_window_text(void* handle, wchar_t* text, __int32 text_length) -> __int32;

	extern auto nt_user_enum_display_devices(void* display_device) -> __int32;

	extern auto allocate_memory(unsigned __int64 size) -> unsigned __int64;
	extern auto get_allocation_size(unsigned __int64 address) -> unsigned __int64;
	extern auto free_memory(unsigned __int64 address) -> void;
	extern auto copy_memory(unsigned __int64 target_address, unsigned __int64 source_address, unsigned __int64 size) -> void;
	extern auto count_memory_matches(unsigned __int64 address, unsigned __int64 size, unsigned __int8 value) -> unsigned __int64;
	extern auto compare_memory(unsigned __int64 address_0, unsigned __int64 address_1, unsigned __int64 size) -> unsigned __int64;

	extern auto get_multibyte_string_length(char* string) -> unsigned __int64;
	extern auto get_unicode_string_length(wchar_t* string) -> unsigned __int64;
	extern auto multibyte_string_equals_multibyte_string(char* string_0, char* string_1, bool is_case_sensitive) -> bool;
	extern auto multibyte_string_equals_unicode_string(char* multibyte_string, wchar_t* unicode_string, bool is_case_sensitive) -> bool;
	extern auto unicode_string_equals_unicode_string(wchar_t* string_0, wchar_t* string_1, bool is_case_sensitive) -> bool;
	extern auto concatenate_multibyte_string(char* string_0, char* string_1) -> void;
	extern auto concatenate_unicode_string(wchar_t* string_0, wchar_t* string_1) -> void;
	extern auto multibyte_to_unicode(char* multibyte_string, wchar_t* unicode_string) -> void;
	extern auto unicode_to_multibyte(wchar_t* unicode_string, char* multibyte_string) -> void;
	extern auto left_find_multibyte_sub_string(char* string, char* sub_string, bool is_case_sensitive, unsigned __int64 ignore_count) -> unsigned __int64;
	extern auto left_find_unicode_sub_string(wchar_t* string, wchar_t* sub_string, bool is_case_sensitive, unsigned __int64 ignore_count) -> unsigned __int64;
	extern auto right_find_multibyte_sub_string(char* string, char* sub_string, bool is_case_sensitive, unsigned __int64 ignore_count) -> unsigned __int64;
	extern auto right_find_unicode_sub_string(wchar_t* string, wchar_t* sub_string, bool is_case_sensitive, unsigned __int64 ignore_count) -> unsigned __int64;
	extern auto make_multibyte_string_uppercase(char* string) -> void;
	extern auto make_unicode_string_uppercase(wchar_t* string) -> void;
	extern auto make_multibyte_string_lowercase(char* string) -> void;
	extern auto make_unicode_string_lowercase(wchar_t* string) -> void;

	struct __multibyte_string
	{
		inline static unsigned __int64 size = 0x200;

		__multibyte_string(unsigned __int64 length = sdk::__multibyte_string::size);
		__multibyte_string(char* string);
		__multibyte_string(char* string, unsigned __int64 forced_length);
		__multibyte_string(const sdk::__multibyte_string& string);
		~__multibyte_string();

		sdk::__multibyte_string& operator=(const sdk::__multibyte_string& string)
		{
			this->set(string.multibyte_string);

			return *this;
		}

		char* multibyte_string = nullptr;
		wchar_t* unicode_string = nullptr;

		static auto is_valid(sdk::__multibyte_string string) -> bool;

		auto set(char* string) -> void;
		auto get_multibyte_string() -> char*;
		auto get_unicode_string() -> wchar_t*;
		auto get_size() -> unsigned __int64;
		auto get_length() -> unsigned __int64;
		auto left_find(char* sub_string, bool is_case_sensitive = true, unsigned __int64 ignore_count = 0) -> unsigned __int64;
		auto right_find(char* sub_string, bool is_case_sensitive = true, unsigned __int64 ignore_count = 0) -> unsigned __int64;
		auto to_upper() -> void;
		auto to_lower() -> void;
		auto left_pop() -> void;
		auto right_pop() -> void;
		auto left_trim() -> void;
		auto right_trim() -> void;
		auto left_right_trim() -> void;
		auto concatenate(char* string) -> void;
		auto concatenate(char* string_0, char* string_1) -> void;
		auto concatenate(char* string_0, char* string_1, char* string_2) -> void;
		auto equals(char* string, bool is_case_sensitive = true) -> bool;
	};

	struct __unicode_string
	{
		inline static unsigned __int64 size = 0x200;

		__unicode_string(unsigned __int64 length = sdk::__unicode_string::size);
		__unicode_string(wchar_t* string);
		__unicode_string(wchar_t* string, unsigned __int64 forced_length);
		__unicode_string(const sdk::__unicode_string& string);
		~__unicode_string();

		sdk::__unicode_string& operator=(const sdk::__unicode_string& string)
		{
			this->set(string.unicode_string);

			return *this;
		}

		wchar_t* unicode_string = nullptr;
		char* multibyte_string = nullptr;

		static auto is_valid(sdk::__unicode_string string) -> bool;

		auto set(wchar_t* string) -> void;
		auto get_unicode_string() -> wchar_t*;
		auto get_multibyte_string() -> char*;
		auto get_size() -> unsigned __int64;
		auto get_length() -> unsigned __int64;
		auto left_find(wchar_t* sub_string, bool is_case_sensitive = true, unsigned __int64 ignore_count = 0) -> unsigned __int64;
		auto right_find(wchar_t* sub_string, bool is_case_sensitive = true, unsigned __int64 ignore_count = 0) -> unsigned __int64;
		auto to_upper() -> void;
		auto to_lower() -> void;
		auto left_pop() -> void;
		auto right_pop() -> void;
		auto left_trim() -> void;
		auto right_trim() -> void;
		auto left_right_trim() -> void;
		auto concatenate(wchar_t* string) -> void;
		auto concatenate(wchar_t* string_0, wchar_t* string_1) -> void;
		auto concatenate(wchar_t* string_0, wchar_t* string_1, wchar_t* string_2) -> void;
		auto equals(wchar_t* string, bool is_case_sensitive = true) -> bool;
	};

	extern auto get_hardware_identifier() -> sdk::__multibyte_string;

	struct __absolute_jump
	{
		void* process_handle = nullptr;
		unsigned __int64 source_address = 0;
		unsigned __int64 target_address = 0;
		unsigned __int8 old_instructions[14] = {};

		auto create() -> bool;
		auto remove() -> bool;
	};

	struct __timer
	{
		__timer(unsigned __int64 old_kernel_system_time, unsigned __int64 new_kernel_system_time);
		__timer();
		~__timer();

		unsigned __int64 fist_kernel_system_time = false;
		unsigned __int64 old_kernel_system_time = 0;
		unsigned __int64 new_kernel_system_time = 0;
		double elapsed_milliseconds = 0.;

		auto update() -> void;
		auto has_elapsed(double milliseconds, bool fist_kernel_system_time_return_true = false, bool update_old_kernel_system_time = true) -> bool;
		auto get_elapsed_milliseconds() -> double;
	};

	extern auto generate_random_value(double minimum_value, double maximum_value) -> double;

	inline void* target_process_handle = nullptr;
}

#define EXIT_RETURN(value)	\
{{	\
	((__int32(_stdcall*)(void*, __int32))sdk::get_module_export_address(sdk::get_module_address(NTDLL_MODULE_FILE_PATH), XOR("NtTerminateProcess")))(sdk::target_process_handle, 0);	\
	\
	((__int32(_stdcall*)(void*, __int32))sdk::get_module_export_address(sdk::get_module_address(NTDLL_MODULE_FILE_PATH), XOR("NtTerminateProcess")))(CURRENT_PROCESS_HANDLE, 0);	\
	\
	ZERO_MEMORY(0, (unsigned __int64)-1);	\
	\
	return value;	\
}}

#define REPORT_EXIT_RETURN(value)	\
{{	\
	auto fixed_message = sdk::__multibyte_string(XOR("function: "));	\
	\
	fixed_message.concatenate(XOR(__FUNCTION__));	\
	\
	fixed_message.right_pop();	\
	\
	auto fixed_line = sdk::__multibyte_string();	\
	\
	snprintf(fixed_line.get_multibyte_string(), fixed_line.get_size(), XOR("%d"), __LINE__);	\
	\
	fixed_message.concatenate(XOR("\n"), XOR("line: "), fixed_line.get_multibyte_string());	\
	\
	fixed_message.to_lower();	\
	\
	((void(__cdecl*)(sdk::__multibyte_string))sdk::internal_send_error_report_callback)(fixed_message);	\
	\
	EXIT_RETURN(value);	\
}}

#define EXTRA_REPORT_EXIT_RETURN(message, value)	\
{{	\
	auto fixed_message = sdk::__multibyte_string(XOR("function: "));	\
	\
	fixed_message.concatenate(XOR(__FUNCTION__));	\
	\
	fixed_message.right_pop();	\
	\
	auto fixed_line = sdk::__multibyte_string();	\
	\
	snprintf(fixed_line.get_multibyte_string(), fixed_line.get_size(), XOR("%d"), __LINE__);	\
	\
	fixed_message.concatenate(XOR("\n"), XOR("line: "), fixed_line.get_multibyte_string());	\
	\
	fixed_message.concatenate(XOR("\n"), XOR("message: "), message.get_multibyte_string());	\
	\
	fixed_message.to_lower();	\
	\
	((void(__cdecl*)(sdk::__multibyte_string))sdk::internal_send_error_report_callback)(fixed_message);	\
	\
	EXIT_RETURN(value);	\
}}

#define IS_NTDLL_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(function, value)	\
{{	\
	if (function == 0)	\
		REPORT_EXIT_RETURN(value);	\
	\
	if (*(unsigned __int8*)function != 0x4c || *(unsigned __int8*)(function + 0x1) != 0x8b || *(unsigned __int8*)(function + 0x2) != 0xd1)	\
		REPORT_EXIT_RETURN(value);	\
	\
	if (*(unsigned __int8*)(function + 0x3) != 0xb8 || *(unsigned __int32*)(function + 0x4) > 0x200)	\
		REPORT_EXIT_RETURN(value);	\
	\
	if (*(unsigned __int64*)(function + 0x8) != 0x017ffe03082504f6)	\
		REPORT_EXIT_RETURN(value);	\
	\
	if (*(unsigned __int8*)(function + 0x10) != 0x75 || *(unsigned __int8*)(function + 0x11) != 0x03)	\
		REPORT_EXIT_RETURN(value);	\
	\
	if (*(unsigned __int8*)(function + 0x12) != 0x0f || *(unsigned __int8*)(function + 0x13) != 0x05)	\
		REPORT_EXIT_RETURN(value);	\
	\
	if (*(unsigned __int8*)(function + 0x14) != 0xc3)	\
		REPORT_EXIT_RETURN(value);	\
}}

#define IS_WIN_32_U_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(function, value)	\
{{	\
	if (function == 0)	\
		REPORT_EXIT_RETURN(value);	\
	\
	if (*(unsigned __int8*)function != 0x4c || *(unsigned __int8*)(function + 0x1) != 0x8b || *(unsigned __int8*)(function + 0x2) != 0xd1)	\
		REPORT_EXIT_RETURN(value);	\
	\
	if (*(unsigned __int8*)(function + 0x3) != 0xb8 || *(unsigned __int32*)(function + 0x4) < 0x1000 || *(unsigned __int32*)(function + 0x4) > 0x1500)	\
		REPORT_EXIT_RETURN(value);	\
	\
	if (*(unsigned __int64*)(function + 0x8) != 0x017ffe03082504f6)	\
		REPORT_EXIT_RETURN(value);	\
	\
	if (*(unsigned __int8*)(function + 0x10) != 0x75 || *(unsigned __int8*)(function + 0x11) != 0x03)	\
		REPORT_EXIT_RETURN(value);	\
	\
	if (*(unsigned __int8*)(function + 0x12) != 0x0f || *(unsigned __int8*)(function + 0x13) != 0x05)	\
		REPORT_EXIT_RETURN(value);	\
	\
	if (*(unsigned __int8*)(function + 0x14) != 0xc3)	\
		REPORT_EXIT_RETURN(value);	\
}}