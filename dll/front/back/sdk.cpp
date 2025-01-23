
#include "sdk.hpp"

auto sdk::get_process_enviroment_block() -> _PEB*
{
	return ((_TEB*)__readgsqword((unsigned __int32)(unsigned __int64)&(((_NT_TIB*)0)->Self)))->ProcessEnvironmentBlock;
}

auto sdk::get_module_address(sdk::__unicode_string file_path_or_name) -> unsigned __int64
{
	unsigned __int64 module_address = 0;

	if (!sdk::__unicode_string::is_valid(file_path_or_name))
		REPORT_EXIT_RETURN(0);

	auto process_enviroment_block = sdk::get_process_enviroment_block();

	for (auto modules_data = process_enviroment_block->Ldr->InMemoryOrderModuleList; modules_data.Flink != &process_enviroment_block->Ldr->InMemoryOrderModuleList; modules_data = *modules_data.Flink)
	{
		auto module_data = (_LDR_DATA_TABLE_ENTRY*)((unsigned __int64)modules_data.Flink - (unsigned __int64)(&((_LDR_DATA_TABLE_ENTRY*)0)->InMemoryOrderLinks));

		auto module_file_path = sdk::__unicode_string(module_data->FullDllName.Buffer);

		if (!sdk::__unicode_string::is_valid(module_file_path))
			REPORT_EXIT_RETURN(0);

		if (file_path_or_name.equals((file_path_or_name.get_unicode_string()[0] == L':' ? &module_file_path.get_unicode_string()[1] : &module_file_path.get_unicode_string()[module_file_path.right_find(XOR(L"\\")) + 1]), false))
		{
			if (module_address != 0)
				EXTRA_REPORT_EXIT_RETURN(module_file_path, 0);

			module_address = module_data->DllBase;
		}
	}

	return module_address;
}

auto sdk::get_module_address_ex(void* process_handle, sdk::__unicode_string file_path_or_name) -> unsigned __int64
{
	unsigned __int64 module_address = 0;

	if (process_handle == nullptr)
		REPORT_EXIT_RETURN(0);

	if (!sdk::__unicode_string::is_valid(file_path_or_name))
		REPORT_EXIT_RETURN(0);

	auto pbi = _PROCESS_BASIC_INFORMATION();

	if (sdk::nt_query_information_process(process_handle, 0, &pbi, sizeof(_PROCESS_BASIC_INFORMATION)) != 0 || pbi.PebBaseAddress == nullptr)
		REPORT_EXIT_RETURN(0);

	auto peb = _PEB();

	if (sdk::nt_read_virtual_memory(process_handle, pbi.PebBaseAddress, &peb, sizeof(_PEB)) != 0 || peb.Ldr == nullptr)
		REPORT_EXIT_RETURN(0);

	auto pld = _PEB_LDR_DATA();

	if (sdk::nt_read_virtual_memory(process_handle, peb.Ldr, &pld, sizeof(_PEB_LDR_DATA)) != 0 || pld.InMemoryOrderModuleList.Flink == nullptr)
		REPORT_EXIT_RETURN(0);

	for (auto modules_data = pld.InMemoryOrderModuleList; modules_data.Flink != &peb.Ldr->InMemoryOrderModuleList;)
	{
		auto ldte = _LDR_DATA_TABLE_ENTRY();

		if (sdk::nt_read_virtual_memory(process_handle, (void*)((unsigned __int64)modules_data.Flink - (unsigned __int64)(&((_LDR_DATA_TABLE_ENTRY*)0)->InMemoryOrderLinks)), &ldte, sizeof(_LDR_DATA_TABLE_ENTRY)) != 0)
			REPORT_EXIT_RETURN(0);

		auto module_file_path = sdk::__unicode_string((unsigned __int64)ldte.FullDllName.Length);

		if (sdk::nt_read_virtual_memory(process_handle, ldte.FullDllName.Buffer, module_file_path.get_unicode_string(), (unsigned __int64)ldte.FullDllName.Length) != 0)
			REPORT_EXIT_RETURN(0);

		if (!sdk::__unicode_string::is_valid(module_file_path))
			REPORT_EXIT_RETURN(0);

		if (file_path_or_name.equals((file_path_or_name.get_unicode_string()[0] == L':' ? &module_file_path.get_unicode_string()[1] : &module_file_path.get_unicode_string()[module_file_path.right_find(XOR(L"\\")) + 1]), false))
		{
			if (module_address != 0)
				EXTRA_REPORT_EXIT_RETURN(module_file_path, 0);

			module_address = ldte.DllBase;
		}

		if (sdk::nt_read_virtual_memory(process_handle, modules_data.Flink, &modules_data, sizeof(_LIST_ENTRY)) != 0 || modules_data.Flink == nullptr)
			REPORT_EXIT_RETURN(0);
	}

	return module_address;
}

auto sdk::get_module_file_path(unsigned __int64 address) -> wchar_t*
{
	wchar_t* module_file_path = nullptr;

	if (address == 0)
		REPORT_EXIT_RETURN(nullptr);

	auto process_enviroment_block = sdk::get_process_enviroment_block();

	for (auto modules_data = process_enviroment_block->Ldr->InMemoryOrderModuleList; modules_data.Flink != &process_enviroment_block->Ldr->InMemoryOrderModuleList; modules_data = *modules_data.Flink)
	{
		if (auto module_data = (_LDR_DATA_TABLE_ENTRY*)((unsigned __int64)modules_data.Flink - (unsigned __int64)(&((_LDR_DATA_TABLE_ENTRY*)0)->InMemoryOrderLinks)); module_data->DllBase == address)
		{
			if (module_file_path != nullptr)
				REPORT_EXIT_RETURN(nullptr);

			module_file_path = module_data->FullDllName.Buffer;
		}
	}

	return module_file_path;
}

auto sdk::get_module_file_path_ex(void* process_handle, unsigned __int64 address) -> wchar_t*
{
	wchar_t* module_file_path = nullptr;

	if (process_handle == nullptr || address == 0)
		REPORT_EXIT_RETURN(nullptr);

	return module_file_path;
}

auto sdk::get_module_size(unsigned __int64 address) -> unsigned __int64
{
	unsigned __int64 module_size = 0;

	if (address == 0)
		REPORT_EXIT_RETURN(0);

	for (auto mbi = _MEMORY_BASIC_INFORMATION((void*)address); sdk::nt_query_virtual_memory(CURRENT_PROCESS_HANDLE, mbi.BaseAddress, 0, &mbi, sizeof(_MEMORY_BASIC_INFORMATION)) == 0; *(unsigned __int64*)&mbi.BaseAddress += mbi.RegionSize)
	{
		if ((unsigned __int64)mbi.AllocationBase != address)
			break;

		module_size += mbi.RegionSize;
	}

	return module_size;
}

auto sdk::get_module_size_ex(void* process_handle, unsigned __int64 address) -> unsigned __int64
{
	unsigned __int64 module_size = 0;

	if (process_handle == nullptr || address == 0)
		REPORT_EXIT_RETURN(0);

	for (auto mbi = _MEMORY_BASIC_INFORMATION((void*)address); sdk::nt_query_virtual_memory(process_handle, mbi.BaseAddress, 0, &mbi, sizeof(_MEMORY_BASIC_INFORMATION)) == 0; *(unsigned __int64*)&mbi.BaseAddress += mbi.RegionSize)
	{
		if ((unsigned __int64)mbi.AllocationBase != address)
			break;

		module_size += mbi.RegionSize;
	}

	return module_size;
}

auto sdk::get_module_export_address(unsigned __int64 address, char* name) -> unsigned __int64
{
	unsigned __int64 module_export_address = 0;

	if (address == 0 || name == nullptr)
		return 0;

	auto module_nt_headers = (_IMAGE_NT_HEADERS64*)(address + (unsigned __int64)((_IMAGE_DOS_HEADER*)address)->e_lfanew);

	auto module_export_directory = (_IMAGE_EXPORT_DIRECTORY*)(address + (unsigned __int64)module_nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

	auto module_export_directory_functions = (unsigned __int32*)(address + (unsigned __int64)module_export_directory->AddressOfFunctions);
	auto module_export_directory_names = (unsigned __int32*)(address + (unsigned __int64)module_export_directory->AddressOfNames);
	auto module_export_directory_ordinals = (unsigned __int16*)(address + (unsigned __int64)module_export_directory->AddressOfNameOrdinals);

	auto module_export_directory_size = module_nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size;

	for (unsigned __int32 x = 0; x < module_export_directory->NumberOfNames; ++x)
	{
		auto module_export_name = sdk::__multibyte_string((char*)(address + module_export_directory_names[x]));

		if (!sdk::__multibyte_string::is_valid(module_export_name))
			REPORT_EXIT_RETURN(0);

		if (!module_export_name.equals(name))
			continue;

		if (module_export_address != 0)
			REPORT_EXIT_RETURN(0);

		auto temporal_module_export_address = address + module_export_directory_functions[module_export_directory_ordinals[x]];

		if (temporal_module_export_address > (unsigned __int64)module_export_directory && temporal_module_export_address < (unsigned __int64)module_export_directory + (unsigned __int64)module_export_directory_size)
		{
			auto forwarded_module_export_name = sdk::__multibyte_string((char*)temporal_module_export_address);

			if (!sdk::__multibyte_string::is_valid(forwarded_module_export_name))
				REPORT_EXIT_RETURN(0);

			auto separator_position = forwarded_module_export_name.left_find(XOR("."));

			auto module_name = sdk::__multibyte_string((char*)temporal_module_export_address, separator_position);

			module_name.concatenate(XOR(".dll"));

			auto export_name = sdk::__multibyte_string((char*)(temporal_module_export_address + separator_position + 1));

			module_export_address = sdk::get_module_export_address(sdk::get_module_address(module_name.get_unicode_string()), export_name.get_multibyte_string());
		}

		else
		{
			module_export_address = temporal_module_export_address;

			break;
		}
	}

	return module_export_address;
}

auto sdk::get_module_export_address_ex(void* process_handle, unsigned __int64 address, char* name) -> unsigned __int64
{
	unsigned __int64 module_export_address = 0;

	if (address == 0 || name == nullptr)
		return 0;

	unsigned __int64 remote_module = 0, remote_module_size = sdk::get_module_size_ex(process_handle, address);

	if (sdk::nt_allocate_virtual_memory(CURRENT_PROCESS_HANDLE, (void**)&remote_module, &remote_module_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE) != 0 || remote_module == 0)
		REPORT_EXIT_RETURN(0);

	if (sdk::nt_read_virtual_memory(process_handle, (void*)address, (void*)remote_module, remote_module_size) != 0)
		REPORT_EXIT_RETURN(0);

	auto module_nt_headers = (_IMAGE_NT_HEADERS64*)(remote_module + (unsigned __int64)((_IMAGE_DOS_HEADER*)remote_module)->e_lfanew);

	auto module_export_directory = (_IMAGE_EXPORT_DIRECTORY*)(remote_module + (unsigned __int64)module_nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

	auto module_export_directory_functions = (unsigned __int32*)(remote_module + (unsigned __int64)module_export_directory->AddressOfFunctions);
	auto module_export_directory_names = (unsigned __int32*)(remote_module + (unsigned __int64)module_export_directory->AddressOfNames);
	auto module_export_directory_ordinals = (unsigned __int16*)(remote_module + (unsigned __int64)module_export_directory->AddressOfNameOrdinals);

	auto module_export_directory_size = module_nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size;

	for (unsigned __int32 x = 0; x < module_export_directory->NumberOfNames; ++x)
	{
		auto module_export_name = sdk::__multibyte_string((char*)(remote_module + module_export_directory_names[x]));

		if (!sdk::__multibyte_string::is_valid(module_export_name))
			REPORT_EXIT_RETURN(0);

		if (!module_export_name.equals(name))
			continue;

		if (module_export_address != 0)
			REPORT_EXIT_RETURN(0);

		if (auto temporal_module_export_address = remote_module + module_export_directory_functions[module_export_directory_ordinals[x]]; 
			temporal_module_export_address > (unsigned __int64)module_export_directory && temporal_module_export_address < (unsigned __int64)module_export_directory + (unsigned __int64)module_export_directory_size)
		{
			auto forwarded_module_export_name = sdk::__multibyte_string((char*)temporal_module_export_address);

			if (!sdk::__multibyte_string::is_valid(forwarded_module_export_name))
				REPORT_EXIT_RETURN(0);

			auto separator_position = forwarded_module_export_name.left_find(XOR("."));

			auto module_name = sdk::__multibyte_string((char*)temporal_module_export_address, separator_position);

			module_name.concatenate(XOR(".dll"));

			auto export_name = sdk::__multibyte_string((char*)temporal_module_export_address + separator_position + 1);

			module_export_address = sdk::get_module_export_address_ex(process_handle, sdk::get_module_address_ex(process_handle, module_name.get_unicode_string()), export_name.get_multibyte_string());
		}

		else
		{
			module_export_address = address + module_export_directory_functions[module_export_directory_ordinals[x]];

			break;
		}
	}

	if (sdk::nt_free_virtual_memory(CURRENT_PROCESS_HANDLE, (void**)&remote_module, &remote_module_size, MEM_RELEASE) != 0)
		REPORT_EXIT_RETURN(0);

	return module_export_address;
}

auto sdk::nt_query_system_information(unsigned __int32 klass, void* information, unsigned __int32 size, unsigned __int32* requested_size) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(NTDLL_MODULE_FILE_PATH), XOR("NtQuerySystemInformation"));

	IS_NTDLL_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, 1);

	auto nt_query_system_information_result = ((__int32(_stdcall*)(unsigned __int32, void*, unsigned __int32, unsigned __int32*))module_export_address)(klass, information, size, requested_size);

	if (klass == 0x23)
	{
		if (auto skdi = (_SYSTEM_KERNEL_DEBUGGER_INFORMATION*)information; skdi->DebuggerEnabled == 0)
			skdi->DebuggerEnabled = ((KERNEL_DEBUGGER_INFORMATION & 0x1) != 0 || (KERNEL_DEBUGGER_INFORMATION & 0x2) != 0);
	}

	return nt_query_system_information_result;
}

auto sdk::nt_open_process(void** handle, unsigned __int32 access, unsigned __int64 identifier, bool force_elevation) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(NTDLL_MODULE_FILE_PATH), XOR("NtOpenProcess"));

	IS_NTDLL_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, 1);

	if (force_elevation)
	{
		if (void* temporal_process_handle = nullptr; sdk::nt_open_process(&temporal_process_handle, PROCESS_QUERY_LIMITED_INFORMATION, identifier, false) == 0 && temporal_process_handle != nullptr)
		{
			void* elevated_process_handle = nullptr;

			sdk::nt_duplicate_object(CURRENT_PROCESS_HANDLE, temporal_process_handle, CURRENT_PROCESS_HANDLE, &elevated_process_handle, PROCESS_ALL_ACCESS, 0);

			if (sdk::nt_close(temporal_process_handle) != 0)
				REPORT_EXIT_RETURN(1);

			if (elevated_process_handle != nullptr)
			{
				*handle = elevated_process_handle;

				return 0;
			}
		}
	}

	auto oa = _OBJECT_ATTRIBUTES(sizeof(_OBJECT_ATTRIBUTES));

	auto ci = _CLIENT_IDENTIFIER(identifier, 0);

	return ((__int32(_stdcall*)(void**, unsigned __int32, void*, void*))module_export_address)(handle, access, &oa, &ci);
}

auto sdk::nt_query_information_process(void* handle, unsigned __int32 klass, void* information, unsigned __int32 size, unsigned __int32* requested_size) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(NTDLL_MODULE_FILE_PATH), XOR("NtQueryInformationProcess"));

	IS_NTDLL_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, 1);

	return ((__int32(_stdcall*)(void*, unsigned __int32, void*, unsigned __int32, unsigned __int32*))module_export_address)(handle, klass, information, size, requested_size);
}

auto sdk::nt_set_information_process(void* handle, unsigned __int32 klass, void* information, unsigned __int32 size) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(NTDLL_MODULE_FILE_PATH), XOR("NtSetInformationProcess"));

	IS_NTDLL_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, 1);

	return ((__int32(_stdcall*)(void*, unsigned __int32, void*, unsigned __int32))module_export_address)(handle, klass, information, size);
}

auto sdk::nt_open_process_token(void* handle, unsigned __int32 access, void** token_handle) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(NTDLL_MODULE_FILE_PATH), XOR("NtOpenProcessToken"));

	IS_NTDLL_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, 1);

	return ((__int32(_stdcall*)(void*, unsigned __int32, void**))module_export_address)(handle, access, token_handle);
}

auto sdk::nt_terminate_process(void* handle, __int32 exit_code) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(NTDLL_MODULE_FILE_PATH), XOR("NtTerminateProcess"));

	IS_NTDLL_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, 1);

	return ((__int32(_stdcall*)(void*, __int32))module_export_address)(handle, exit_code);
}

auto sdk::nt_query_virtual_memory(void* process_handle, void* address, unsigned __int32 klass, void* information, unsigned __int64 size, unsigned __int64* requested_size) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(NTDLL_MODULE_FILE_PATH), XOR("NtQueryVirtualMemory"));

	IS_NTDLL_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, 1);

	return ((__int32(_stdcall*)(void*, void*, unsigned __int32, void*, unsigned __int64, unsigned __int64*))module_export_address)(process_handle, address, klass, information, size, requested_size);
}

auto sdk::nt_allocate_virtual_memory(void* process_handle, void** address, unsigned __int64* size, unsigned __int32 type, unsigned __int32 protection) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(NTDLL_MODULE_FILE_PATH), XOR("NtAllocateVirtualMemory"));

	IS_NTDLL_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, 1);

	return ((__int32(_stdcall*)(void*, void**, unsigned __int32*, unsigned __int64*, unsigned __int32, unsigned __int32))module_export_address)(process_handle, address, nullptr, size, type, protection);
}

auto sdk::nt_free_virtual_memory(void* process_handle, void** address, unsigned __int64* size, unsigned __int32 type) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(NTDLL_MODULE_FILE_PATH), XOR("NtFreeVirtualMemory"));

	IS_NTDLL_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, 1);

	return ((__int32(_stdcall*)(void*, void**, unsigned __int64*, unsigned __int32))module_export_address)(process_handle, address, size, type);
}

auto sdk::nt_protect_virtual_memory(void* process_handle, void* address, unsigned __int64* size, unsigned __int32 new_protection, unsigned __int32* old_protection) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(NTDLL_MODULE_FILE_PATH), XOR("NtProtectVirtualMemory"));

	IS_NTDLL_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, 1);

	return ((__int32(_stdcall*)(void*, void**, unsigned __int64*, unsigned __int32, unsigned __int32*))module_export_address)(process_handle, &address, size, new_protection, old_protection);
}

auto sdk::nt_read_virtual_memory(void* process_handle, void* target_address, void* source_address, unsigned __int64 size, unsigned __int64* requested_size) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(NTDLL_MODULE_FILE_PATH), XOR("NtReadVirtualMemory"));

	IS_NTDLL_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, 1);

	return ((__int32(_stdcall*)(void*, void*, void*, unsigned __int64, unsigned __int64*))module_export_address)(process_handle, target_address, source_address, size, requested_size);
}

auto sdk::nt_write_virtual_memory(void* process_handle, void* target_address, void* source_address, unsigned __int64 size, unsigned __int64* requested_size) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(NTDLL_MODULE_FILE_PATH), XOR("NtWriteVirtualMemory"));

	IS_NTDLL_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, 1);

	return ((__int32(_stdcall*)(void*, void*, void*, unsigned __int64, unsigned __int64*))module_export_address)(process_handle, target_address, source_address, size, requested_size);
}

auto sdk::nt_open_thread(void** handle, unsigned __int32 access, unsigned __int64 identifier) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(NTDLL_MODULE_FILE_PATH), XOR("NtOpenThread"));

	IS_NTDLL_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, 1);

	auto oa = _OBJECT_ATTRIBUTES(sizeof(_OBJECT_ATTRIBUTES));

	auto ci = _CLIENT_IDENTIFIER(0, identifier);

	return ((__int32(_stdcall*)(void**, unsigned __int32, void*, void*))module_export_address)(handle, access, &oa, &ci);
}

auto sdk::nt_create_thread_ex(void** handle, unsigned __int32 access, void* process_handle, void* address, void* parameters, unsigned __int32 flags) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(NTDLL_MODULE_FILE_PATH), XOR("NtCreateThreadEx"));

	IS_NTDLL_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, 1);

	auto oa = _OBJECT_ATTRIBUTES(sizeof(_OBJECT_ATTRIBUTES));

	return ((__int32(_stdcall*)(void**, unsigned __int32, void*, void*, void*, void*, unsigned __int32, unsigned __int64, unsigned __int64, unsigned __int64, void*))
		module_export_address)(handle, access, &oa, process_handle, address, parameters, flags, 0, 0, 0, nullptr);
}

auto sdk::nt_query_information_thread(void* handle, unsigned __int32 klass, void* information, unsigned __int32 size, unsigned __int32* requested_size) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(NTDLL_MODULE_FILE_PATH), XOR("NtQueryInformationThread"));

	IS_NTDLL_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, 1);

	return ((__int32(_stdcall*)(void*, unsigned __int32, void*, unsigned __int32, unsigned __int32*))module_export_address)(handle, klass, information, size, requested_size);
}

auto sdk::nt_set_information_thread(void* handle, unsigned __int32 klass, void* information, unsigned __int32 size) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(NTDLL_MODULE_FILE_PATH), XOR("NtSetInformationThread"));

	IS_NTDLL_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, 1);

	return ((__int32(_stdcall*)(void*, unsigned __int32, void*, unsigned __int32))module_export_address)(handle, klass, information, size);
}

auto sdk::nt_resume_thread(void* handle, unsigned __int32* suspend_count) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(NTDLL_MODULE_FILE_PATH), XOR("NtResumeThread"));

	IS_NTDLL_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, 1);

	return ((__int32(_stdcall*)(void*, unsigned __int32*))module_export_address)(handle, suspend_count);
}

auto sdk::nt_terminate_thread(void* handle, __int32 exit_code) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(NTDLL_MODULE_FILE_PATH), XOR("NtTerminateThread"));

	IS_NTDLL_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, 1);

	return ((__int32(_stdcall*)(void*, __int32))module_export_address)(handle, exit_code);
}

auto sdk::nt_open_file(void** handle, unsigned __int32 access, void* object_attributes, unsigned __int32 share_access) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(NTDLL_MODULE_FILE_PATH), XOR("NtOpenFile"));

	IS_NTDLL_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, 1);

	auto isb = _IO_STATUS_BLOCK();

	return ((__int32(_stdcall*)(void**, unsigned __int32, void*, void*, unsigned __int32, unsigned __int32))module_export_address)(handle, access, object_attributes, &isb, share_access, 0);
}

auto sdk::nt_query_volume_file_information(void* handle, void* information, unsigned __int32 size, unsigned __int32 klass) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(NTDLL_MODULE_FILE_PATH), XOR("NtQueryVolumeInformationFile"));

	IS_NTDLL_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, 1);

	auto is_file_handle_nullptr = handle == nullptr;

	if (is_file_handle_nullptr)
	{
		auto fixed_module_file_path = sdk::__unicode_string(XOR(L"\\??\\"));

		fixed_module_file_path.concatenate(sdk::__unicode_string(KERNEL_SYSTEM_ROOT_PATH, 1).get_unicode_string(), NTDLL_MODULE_FILE_PATH);

		auto us = _UNICODE_STRING((unsigned __int16)(fixed_module_file_path.get_length() * 2), (unsigned __int16)(fixed_module_file_path.get_length() * 2 + 2), fixed_module_file_path.get_unicode_string());

		auto oa = _OBJECT_ATTRIBUTES(sizeof(_OBJECT_ATTRIBUTES), 0, &us, OBJ_CASE_INSENSITIVE);

		if (sdk::nt_open_file(&handle, FILE_READ_DATA, &oa, FILE_SHARE_READ) != 0)
			REPORT_EXIT_RETURN(1);
	}

	auto isb = _IO_STATUS_BLOCK();

	auto nt_query_volume_file_information_result = ((__int32(_stdcall*)(void*, void*, void*, unsigned __int32, unsigned __int32))module_export_address)(handle, &isb, information, size, klass);

	if (is_file_handle_nullptr)
	{
		if (sdk::nt_close(handle) != 0)
			REPORT_EXIT_RETURN(1);
	}

	return nt_query_volume_file_information_result;
}

auto sdk::nt_create_section(void** handle, unsigned __int32 access, void* size, unsigned __int32 protection, unsigned __int32 attributes, void* file_handle) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(NTDLL_MODULE_FILE_PATH), XOR("NtCreateSection"));

	IS_NTDLL_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, 1);

	auto oa = _OBJECT_ATTRIBUTES(sizeof(_OBJECT_ATTRIBUTES));

	return ((__int32(_stdcall*)(void**, unsigned __int32, void*, void*, unsigned __int32, unsigned __int32, void*))module_export_address)(handle, access, &oa, size, protection, attributes, file_handle);
}

auto sdk::nt_map_view_of_section(void* handle, void* process_handle, void** address, unsigned __int64* size, unsigned __int32 protection) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(NTDLL_MODULE_FILE_PATH), XOR("NtMapViewOfSection"));

	IS_NTDLL_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, 1);

	return ((__int32(_stdcall*)(void*, void*, void**, unsigned __int32*, unsigned __int64, void*, unsigned __int64*, unsigned __int32, unsigned __int32, unsigned __int32))
		module_export_address)(handle, process_handle, address, nullptr, 0, nullptr, size, 2, 0, protection);
}

auto sdk::nt_unmap_view_of_section(void* handle, void* address) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(NTDLL_MODULE_FILE_PATH), XOR("NtUnmapViewOfSection"));

	IS_NTDLL_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, 1);

	return ((__int32(_stdcall*)(void*, void*))module_export_address)(handle, address);
}

auto sdk::nt_set_timer_resolution(unsigned __int32 new_resolution, unsigned __int8 set, unsigned __int32* old_resolution) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(NTDLL_MODULE_FILE_PATH), XOR("NtSetTimerResolution"));

	IS_NTDLL_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, 1);

	return ((__int32(_stdcall*)(unsigned __int32, unsigned __int8, unsigned __int32*))module_export_address)(new_resolution, set, old_resolution);
}

auto sdk::nt_delay_execution(__int32 milliseconds) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(NTDLL_MODULE_FILE_PATH), XOR("NtDelayExecution"));

	IS_NTDLL_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, 1);

	static auto set_timer_resolution = []() -> __int32
	{
		if (unsigned __int32 old_timer_resolution = 0; sdk::nt_set_timer_resolution(0, 1, &old_timer_resolution) != 0)
			REPORT_EXIT_RETURN(1);

		return 0;
	}();

	auto li = _LARGE_INTEGER();

	li.QuadPart = (__int64)-(milliseconds * 10000);

	return ((__int32(_stdcall*)(unsigned __int8, void*))module_export_address)(0, &li);
}

auto sdk::nt_adjust_privileges_token(void* handle, void* privileges, unsigned __int32 size) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(NTDLL_MODULE_FILE_PATH), XOR("NtAdjustPrivilegesToken"));

	IS_NTDLL_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, 1);

	return ((__int32(_stdcall*)(void*, unsigned __int8, void*, unsigned __int32, void*, unsigned __int32*))module_export_address)(handle, 0, privileges, size, nullptr, nullptr);
}

auto sdk::nt_duplicate_object(void* source_process_handle, void* source_handle, void* target_process_handle, void** target_handle, unsigned __int32 access, unsigned __int32 flags) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(NTDLL_MODULE_FILE_PATH), XOR("NtDuplicateObject"));

	IS_NTDLL_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, 1);

	return ((__int32(_stdcall*)(void*, void*, void*, void**, unsigned __int32, unsigned __int32, unsigned __int32))module_export_address)(source_process_handle, source_handle, target_process_handle, target_handle, access, 0, flags);
}

auto sdk::nt_close(void* handle) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(NTDLL_MODULE_FILE_PATH), XOR("NtClose"));

	IS_NTDLL_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, 1);

	return ((__int32(_stdcall*)(void*))module_export_address)(handle);
}

auto sdk::ldr_register_dll_notification(void* function, void** cookie) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(NTDLL_MODULE_FILE_PATH), XOR("LdrRegisterDllNotification"));

	return ((__int32(_stdcall*)(unsigned __int32, void*, void*, void**))module_export_address)(0, function, nullptr, cookie);
}

auto sdk::ldr_unregister_dll_notification(void* cookie) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(NTDLL_MODULE_FILE_PATH), XOR("LdrUnregisterDllNotification"));

	return ((__int32(_stdcall*)(void*))module_export_address)(cookie);
}

auto sdk::ldr_load_dll(void* file_name, unsigned __int64* address) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(NTDLL_MODULE_FILE_PATH), XOR("LdrLoadDll"));

	return ((__int32(_stdcall*)(wchar_t*, unsigned __int32, void*, unsigned __int64*))module_export_address)(nullptr, 0, file_name, address);
}

auto sdk::nt_user_get_async_key_state(__int32 key_code) -> __int16
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(WIN_32_U_MODULE_FILE_PATH), XOR("NtUserGetAsyncKeyState"));

	IS_WIN_32_U_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, 0);

	return ((__int16(_stdcall*)(__int32))module_export_address)(key_code);
}

auto sdk::nt_user_find_window_ex(void* klass, void* title) -> void*
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(WIN_32_U_MODULE_FILE_PATH), XOR("NtUserFindWindowEx"));

	IS_WIN_32_U_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, nullptr);

	return ((void*(_stdcall*)(void*, void*, void*, void*, unsigned __int32))module_export_address)(nullptr, nullptr, klass, title, 0);
}

auto sdk::nt_user_query_window(void* handle, unsigned __int32 klass) -> unsigned __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(WIN_32_U_MODULE_FILE_PATH), XOR("NtUserQueryWindow"));

	IS_WIN_32_U_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, 1);

	return ((unsigned __int32(_stdcall*)(void*, unsigned __int32))module_export_address)(handle, klass);
}

auto sdk::nt_user_build_hwnd_list(unsigned __int32 count, void** list, unsigned __int32* requested_count) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(WIN_32_U_MODULE_FILE_PATH), XOR("NtUserBuildHwndList"));

	IS_WIN_32_U_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, 1);

	return ((__int32(_stdcall*)(void*, void*, unsigned __int8, unsigned __int32, unsigned __int32, unsigned __int32, void**, unsigned __int32*))module_export_address)(nullptr, nullptr, 0, 0, 0, count, list, requested_count);
}

auto sdk::nt_user_get_class_name(void* handle, _UNICODE_STRING* class_name) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(WIN_32_U_MODULE_FILE_PATH), XOR("NtUserGetClassName"));

	IS_WIN_32_U_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, 1);

	return ((__int32(_stdcall*)(void*, unsigned __int8, _UNICODE_STRING*))module_export_address)(handle, 1, class_name);
}

auto sdk::nt_user_internal_get_window_text(void* handle, wchar_t* text, __int32 text_length) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(WIN_32_U_MODULE_FILE_PATH), XOR("NtUserInternalGetWindowText"));

	IS_WIN_32_U_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, 1);

	return ((__int32(_stdcall*)(void*, wchar_t*, __int32))module_export_address)(handle, text, text_length);
}

auto sdk::nt_user_enum_display_devices(void* display_device) -> __int32
{
	static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(WIN_32_U_MODULE_FILE_PATH), XOR("NtUserEnumDisplayDevices"));

	IS_WIN_32_U_NT_EXPORTED_FUNCTION_TAMPERED_REPORT_EXIT_RETURN(module_export_address, 1);

	return ((__int32(_stdcall*)(void*, unsigned __int32, void*, unsigned __int32))module_export_address)(nullptr, 0, display_device, 0);
}

auto sdk::allocate_memory(unsigned __int64 size) -> unsigned __int64
{
	unsigned __int64 allocation_address = 0;

	for (; allocation_address == 0; allocation_address = (unsigned __int64)::malloc(size));

	ZERO_MEMORY(allocation_address, size);

	return allocation_address;
}

auto sdk::get_allocation_size(unsigned __int64 address) -> unsigned __int64
{
	return ::_msize((void*)address);
}

auto sdk::free_memory(unsigned __int64 address) -> void
{
	ZERO_MEMORY(address, sdk::get_allocation_size(address));

	return ::free((void*)address);
}

auto sdk::copy_memory(unsigned __int64 target_address, unsigned __int64 source_address, unsigned __int64 size) -> void
{
	::memcpy((void*)target_address, (void*)source_address, size);
}

auto sdk::count_memory_matches(unsigned __int64 address, unsigned __int64 size, unsigned __int8 value) -> unsigned __int64
{
	unsigned __int64 memory_matches = 0;

	for (auto temporal_address = address; temporal_address < address + size; ++temporal_address)
	{
		if (*(unsigned __int8*)temporal_address == value)
			++memory_matches;
	}

	return memory_matches;
}

auto sdk::compare_memory(unsigned __int64 address_0, unsigned __int64 address_1, unsigned __int64 size) -> unsigned __int64
{
	unsigned __int64 memory_matches = 0;

	for (unsigned __int64 x = 0; x < size; ++x)
	{
		if (*(unsigned __int8*)(address_0 + x) == *(unsigned __int8*)(address_1 + x))
			++memory_matches;
	}

	return memory_matches;
}

auto sdk::get_multibyte_string_length(char* string) -> unsigned __int64
{
	unsigned __int64 string_length = 0;

	if (string == nullptr)
		return 0;

	for (; string[string_length] != 0; ++string_length);

	return string_length;
}

auto sdk::get_unicode_string_length(wchar_t* string) -> unsigned __int64
{
	unsigned __int64 string_length = 0;

	if (string == nullptr)
		return 0;

	for (; string[string_length] != 0; ++string_length);

	return string_length;
}

auto sdk::multibyte_string_equals_multibyte_string(char* string_0, char* string_1, bool is_case_sensitive) -> bool
{
	if (string_0 == nullptr || string_1 == nullptr)
		return false;

	auto string_0_length = sdk::get_multibyte_string_length(string_0);

	if (sdk::get_multibyte_string_length(string_1) != string_0_length)
		return false;

	for (unsigned __int64 x = 0; x < string_0_length; ++x)
	{
		if ((is_case_sensitive ? string_0[x] != string_1[x] : toupper(string_0[x]) != toupper(string_1[x])))
			return false;
	}

	return true;
}

auto sdk::multibyte_string_equals_unicode_string(char* multibyte_string, wchar_t* unicode_string, bool is_case_sensitive) -> bool
{
	if (multibyte_string == nullptr || unicode_string == nullptr)
		return false;

	auto multibyte_string_length = sdk::get_multibyte_string_length(multibyte_string);

	if (sdk::get_unicode_string_length(unicode_string) != multibyte_string_length)
		return false;

	for (unsigned __int64 x = 0; x < multibyte_string_length; ++x)
	{
		if ((is_case_sensitive ? multibyte_string[x] != unicode_string[x] : toupper(multibyte_string[x]) != (__int32)towupper(unicode_string[x])))
			return false;
	}

	return true;
}

auto sdk::unicode_string_equals_unicode_string(wchar_t* string_0, wchar_t* string_1, bool is_case_sensitive) -> bool
{
	if (string_0 == nullptr || string_1 == nullptr)
		return false;

	auto string_0_length = sdk::get_unicode_string_length(string_0);

	if (sdk::get_unicode_string_length(string_1) != string_0_length)
		return false;

	for (unsigned __int64 x = 0; x < string_0_length; ++x)
	{
		if ((is_case_sensitive ? string_0[x] != string_1[x] : towupper(string_0[x]) != towupper(string_1[x])))
			return false;
	}

	return true;
}

auto sdk::concatenate_multibyte_string(char* string_0, char* string_1) -> void
{
	if (string_0 == nullptr || string_1 == nullptr)
		return;

	for (unsigned __int64 x = 0, string_0_length = sdk::get_multibyte_string_length(string_0), string_1_length = sdk::get_multibyte_string_length(string_1); x < string_1_length; ++x)
		string_0[string_0_length + x] = string_1[x];
}

auto sdk::concatenate_unicode_string(wchar_t* string_0, wchar_t* string_1) -> void
{
	if (string_0 == nullptr || string_1 == nullptr)
		return;

	for (unsigned __int64 x = 0, string_0_length = sdk::get_unicode_string_length(string_0), string_1_length = sdk::get_unicode_string_length(string_1); x < string_1_length; ++x)
		string_0[string_0_length + x] = string_1[x];
}

auto sdk::multibyte_to_unicode(char* multibyte_string, wchar_t* unicode_string) -> void
{
	if (multibyte_string == nullptr || unicode_string == nullptr)
		return;

	for (unsigned __int64 x = 0, multibyte_string_length = sdk::get_multibyte_string_length(multibyte_string); x < multibyte_string_length; ++x)
		unicode_string[x] = (wchar_t)multibyte_string[x];
}

auto sdk::unicode_to_multibyte(wchar_t* unicode_string, char* multibyte_string) -> void
{
	if (unicode_string == nullptr || multibyte_string == nullptr)
		return;

	for (unsigned __int64 x = 0, unicode_string_length = sdk::get_unicode_string_length(unicode_string); x < unicode_string_length; ++x)
		multibyte_string[x] = (char)unicode_string[x];
}

auto sdk::left_find_multibyte_sub_string(char* string, char* sub_string, bool is_case_sensitive, unsigned __int64 ignore_count) -> unsigned __int64
{
	if (string == nullptr || sub_string == nullptr)
		return (unsigned __int64)-1;

	auto string_length = sdk::get_multibyte_string_length(string), sub_string_length = sdk::get_multibyte_string_length(sub_string);

	if (string_length < sub_string_length)
		return (unsigned __int64)-1;

	for (unsigned __int64 x = 0, memory_matches = 0; x < string_length - sub_string_length + 1; ++x)
	{
		for (unsigned __int64 y = 0; y < sub_string_length; ++y)
		{
			if ((is_case_sensitive ? string[x + y] != sub_string[y] : toupper(string[x + y]) != toupper(sub_string[y])))
				break;

			if (y == sub_string_length - 1 && ++memory_matches > ignore_count)
				return x;
		}
	}

	return (unsigned __int64)-1;
}

auto sdk::left_find_unicode_sub_string(wchar_t* string, wchar_t* sub_string, bool is_case_sensitive, unsigned __int64 ignore_count) -> unsigned __int64
{
	if (string == nullptr || sub_string == nullptr)
		return (unsigned __int64)-1;

	auto string_length = sdk::get_unicode_string_length(string), sub_string_length = sdk::get_unicode_string_length(sub_string);

	if (string_length < sub_string_length)
		return (unsigned __int64)-1;

	for (unsigned __int64 x = 0, memory_matches = 0; x < string_length - sub_string_length + 1; ++x)
	{
		for (unsigned __int64 y = 0; y < sub_string_length; ++y)
		{
			if ((is_case_sensitive ? string[x + y] != sub_string[y] : towupper(string[x + y]) != towupper(sub_string[y])))
				break;

			if (y == sub_string_length - 1 && ++memory_matches > ignore_count)
				return x;
		}
	}

	return (unsigned __int64)-1;
}

auto sdk::right_find_multibyte_sub_string(char* string, char* sub_string, bool is_case_sensitive, unsigned __int64 ignore_count) -> unsigned __int64
{
	if (string == nullptr || sub_string == nullptr)
		return (unsigned __int64)-1;

	auto string_length = sdk::get_multibyte_string_length(string), sub_string_length = sdk::get_multibyte_string_length(sub_string);

	if (string_length < sub_string_length)
		return (unsigned __int64)-1;

	for (unsigned __int64 x = string_length - sub_string_length, memory_matches = 0; x > 0; --x)
	{
		for (unsigned __int64 y = 0; y < sub_string_length; ++y)
		{
			if ((is_case_sensitive ? string[x + y] != sub_string[y] : toupper(string[x + y]) != toupper(sub_string[y])))
				break;

			if (y == sub_string_length - 1 && ++memory_matches > ignore_count)
				return x;
		}
	}

	return (unsigned __int64)-1;
}

auto sdk::right_find_unicode_sub_string(wchar_t* string, wchar_t* sub_string, bool is_case_sensitive, unsigned __int64 ignore_count) -> unsigned __int64
{
	if (string == nullptr || sub_string == nullptr)
		return (unsigned __int64)-1;

	auto string_length = sdk::get_unicode_string_length(string), sub_string_length = sdk::get_unicode_string_length(sub_string);

	if (string_length < sub_string_length)
		return (unsigned __int64)-1;

	for (unsigned __int64 x = string_length - sub_string_length, memory_matches = 0; x > 0; --x)
	{
		for (unsigned __int64 y = 0; y < sub_string_length; ++y)
		{
			if ((is_case_sensitive ? string[x + y] != sub_string[y] : towupper(string[x + y]) != towupper(sub_string[y])))
				break;

			if (y == sub_string_length - 1 && ++memory_matches > ignore_count)
				return x;
		}
	}

	return (unsigned __int64)-1;
}

auto sdk::make_multibyte_string_uppercase(char* string) -> void
{
	for (unsigned __int64 x = 0, string_length = sdk::get_multibyte_string_length(string); x < string_length; ++x)
		string[x] = toupper(string[x]);
}

auto sdk::make_unicode_string_uppercase(wchar_t* string) -> void
{
	for (unsigned __int64 x = 0, string_length = sdk::get_unicode_string_length(string); x < string_length; ++x)
		string[x] = towupper(string[x]);
}

auto sdk::make_multibyte_string_lowercase(char* string) -> void
{
	for (unsigned __int64 x = 0, string_length = sdk::get_multibyte_string_length(string); x < string_length; ++x)
		string[x] = tolower(string[x]);
}

auto sdk::make_unicode_string_lowercase(wchar_t* string) -> void
{
	for (unsigned __int64 x = 0, string_length = sdk::get_unicode_string_length(string); x < string_length; ++x)
		string[x] = towlower(string[x]);
}

sdk::__multibyte_string::__multibyte_string(unsigned __int64 length)
{
	this->multibyte_string = (char*)sdk::allocate_memory(length + 1);
}

sdk::__multibyte_string::__multibyte_string(char* string)
{
	if (string != nullptr)
	{
		auto string_length = sdk::get_multibyte_string_length(string);

		sdk::copy_memory((unsigned __int64)(this->multibyte_string = (char*)sdk::allocate_memory(string_length + 1)), (unsigned __int64)string, string_length);
	}

	else
		this->multibyte_string = (char*)sdk::allocate_memory(sdk::__multibyte_string::size + 1);
}

sdk::__multibyte_string::__multibyte_string(char* string, unsigned __int64 forced_length)
{
	if (string != nullptr)
	{
		auto string_length = sdk::get_multibyte_string_length(string);

		if (string_length > forced_length)
			string_length = forced_length;

		sdk::copy_memory((unsigned __int64)(this->multibyte_string = (char*)sdk::allocate_memory(string_length + 1)), (unsigned __int64)string, string_length);
	}
	
	else
		this->multibyte_string = (char*)sdk::allocate_memory(sdk::__multibyte_string::size + 1);
}

sdk::__multibyte_string::__multibyte_string(const sdk::__multibyte_string& string)
{
	if (string.multibyte_string != nullptr)
	{
		auto string_length = sdk::get_multibyte_string_length(string.multibyte_string);

		sdk::copy_memory((unsigned __int64)(this->multibyte_string = (char*)sdk::allocate_memory(string_length + 1)), (unsigned __int64)string.multibyte_string, string_length);
	}

	else
		this->multibyte_string = (char*)sdk::allocate_memory(sdk::__multibyte_string::size + 1);
}

sdk::__multibyte_string::~__multibyte_string()
{
	if (this->multibyte_string != nullptr)
		sdk::free_memory((unsigned __int64)this->multibyte_string);

	if (this->unicode_string != nullptr)
		sdk::free_memory((unsigned __int64)this->unicode_string);
}

auto sdk::__multibyte_string::is_valid(sdk::__multibyte_string string) -> bool
{
	return &string != nullptr && string.multibyte_string != nullptr && string.multibyte_string[0] != 0;
}

auto sdk::__multibyte_string::set(char* string) -> void
{
	if (string == nullptr)
		return;

	sdk::free_memory((unsigned __int64)this->multibyte_string);

	auto string_length = sdk::get_multibyte_string_length(string);

	return sdk::copy_memory((unsigned __int64)(this->multibyte_string = (char*)sdk::allocate_memory(string_length + 1)), (unsigned __int64)string, string_length);
}

auto sdk::__multibyte_string::get_multibyte_string() -> char*
{
	return this->multibyte_string;
}

auto sdk::__multibyte_string::get_unicode_string() -> wchar_t*
{
	if (this->unicode_string != nullptr)
		sdk::free_memory((unsigned __int64)this->unicode_string);

	sdk::multibyte_to_unicode(this->multibyte_string, (this->unicode_string = (wchar_t*)sdk::allocate_memory(this->get_length() * 2 + 2)));

	return this->unicode_string;
}

auto sdk::__multibyte_string::get_size() -> unsigned __int64
{
	return sdk::get_allocation_size((unsigned __int64)this->multibyte_string);
}

auto sdk::__multibyte_string::get_length() -> unsigned __int64
{
	return sdk::get_multibyte_string_length(this->multibyte_string);
}

auto sdk::__multibyte_string::left_find(char* sub_string, bool is_case_sensitive, unsigned __int64 ignore_count) -> unsigned __int64
{
	return sdk::left_find_multibyte_sub_string(this->multibyte_string, sub_string, is_case_sensitive, ignore_count);
}

auto sdk::__multibyte_string::right_find(char* sub_string, bool is_case_sensitive, unsigned __int64 ignore_count) -> unsigned __int64
{
	return sdk::right_find_multibyte_sub_string(this->multibyte_string, sub_string, is_case_sensitive, ignore_count);
}

auto sdk::__multibyte_string::to_upper() -> void
{
	return sdk::make_multibyte_string_uppercase(this->multibyte_string);
}

auto sdk::__multibyte_string::to_lower() -> void
{
	return sdk::make_multibyte_string_lowercase(this->multibyte_string);
}

auto sdk::__multibyte_string::left_pop() -> void
{
	if (this->get_length() == 0)
		return;

	sdk::copy_memory((unsigned __int64)this->multibyte_string, (unsigned __int64)this->multibyte_string + 1, this->get_length() - 1);

	return this->right_pop();
}

auto sdk::__multibyte_string::right_pop() -> void
{
	if (this->get_length() == 0)
		return;

	this->multibyte_string[this->get_length() - 1] = 0;
}

auto sdk::__multibyte_string::left_trim() -> void
{
	for (; this->multibyte_string[0] == 0x20; this->left_pop());
}

auto sdk::__multibyte_string::right_trim() -> void
{
	for (; this->multibyte_string[this->get_length() - 1] == 0x20; this->right_pop());
}

auto sdk::__multibyte_string::left_right_trim() -> void
{
	this->left_trim();

	this->right_trim();
}

auto sdk::__multibyte_string::concatenate(char* string) -> void
{
	auto new_string = (char*)sdk::allocate_memory(this->get_length() + sdk::get_multibyte_string_length(string) + 1);

	sdk::concatenate_multibyte_string(new_string, this->multibyte_string);
	sdk::concatenate_multibyte_string(new_string, string);

	sdk::free_memory((unsigned __int64)this->multibyte_string);

	this->multibyte_string = new_string;
}

auto sdk::__multibyte_string::concatenate(char* string_0, char* string_1) -> void
{
	this->concatenate(string_0);
	this->concatenate(string_1);
}

auto sdk::__multibyte_string::concatenate(char* string_0, char* string_1, char* string_2) -> void
{
	this->concatenate(string_0);
	this->concatenate(string_1);
	this->concatenate(string_2);
}

auto sdk::__multibyte_string::equals(char* string, bool is_case_sensitive) -> bool
{
	return sdk::multibyte_string_equals_multibyte_string(this->multibyte_string, string, is_case_sensitive);
}

sdk::__unicode_string::__unicode_string(unsigned __int64 length)
{
	this->unicode_string = (wchar_t*)sdk::allocate_memory(length * 2 + 2);
}

sdk::__unicode_string::__unicode_string(wchar_t* string)
{
	if (string != nullptr)
	{
		auto string_length = sdk::get_unicode_string_length(string);

		sdk::copy_memory((unsigned __int64)(this->unicode_string = (wchar_t*)sdk::allocate_memory(string_length * 2 + 2)), (unsigned __int64)string, string_length * 2);
	}

	else
		this->unicode_string = (wchar_t*)sdk::allocate_memory(sdk::__unicode_string::size * 2 + 2);
}

sdk::__unicode_string::__unicode_string(wchar_t* string, unsigned __int64 forced_length)
{
	if (string != nullptr)
	{
		auto string_length = sdk::get_unicode_string_length(string);

		if (string_length > forced_length)
			string_length = forced_length;

		sdk::copy_memory((unsigned __int64)(this->unicode_string = (wchar_t*)sdk::allocate_memory(string_length * 2 + 2)), (unsigned __int64)string, string_length * 2);
	}

	else
		this->unicode_string = (wchar_t*)sdk::allocate_memory(sdk::__unicode_string::size * 2 + 2);
}

sdk::__unicode_string::__unicode_string(const sdk::__unicode_string& string)
{
	if (string.unicode_string != nullptr)
	{
		auto string_length = sdk::get_unicode_string_length(string.unicode_string);

		sdk::copy_memory((unsigned __int64)(this->unicode_string = (wchar_t*)sdk::allocate_memory(string_length * 2 + 2)), (unsigned __int64)string.unicode_string, string_length * 2);
	}

	else
		this->unicode_string = (wchar_t*)sdk::allocate_memory(sdk::__unicode_string::size * 2 + 2);
}

sdk::__unicode_string::~__unicode_string()
{
	if (this->unicode_string != nullptr)
		sdk::free_memory((unsigned __int64)this->unicode_string);

	if (this->multibyte_string != nullptr)
		sdk::free_memory((unsigned __int64)this->multibyte_string);
}

auto sdk::__unicode_string::is_valid(sdk::__unicode_string unicode_string) -> bool
{
	return &unicode_string != nullptr && unicode_string.unicode_string != nullptr && unicode_string.unicode_string[0] != 0;
}

auto sdk::__unicode_string::set(wchar_t* string) -> void
{
	if (string == nullptr)
		return;

	sdk::free_memory((unsigned __int64)this->unicode_string);

	auto string_length = sdk::get_unicode_string_length(string);

	sdk::copy_memory((unsigned __int64)(this->unicode_string = (wchar_t*)sdk::allocate_memory(string_length * 2 + 2)), (unsigned __int64)string, string_length * 2);
}

auto sdk::__unicode_string::get_unicode_string() -> wchar_t*
{
	return this->unicode_string;
}

auto sdk::__unicode_string::get_multibyte_string() -> char*
{
	if (this->multibyte_string != nullptr)
		sdk::free_memory((unsigned __int64)this->multibyte_string);

	sdk::unicode_to_multibyte(this->unicode_string, this->multibyte_string = (char*)sdk::allocate_memory(this->get_length() + 1));

	return this->multibyte_string;
}

auto sdk::__unicode_string::get_size() -> unsigned __int64
{
	return sdk::get_allocation_size((unsigned __int64)this->unicode_string);
}

auto sdk::__unicode_string::get_length() -> unsigned __int64
{
	return sdk::get_unicode_string_length(this->unicode_string);
}

auto sdk::__unicode_string::left_find(wchar_t* sub_string, bool is_case_sensitive, unsigned __int64 ignore_count) -> unsigned __int64
{
	return sdk::left_find_unicode_sub_string(this->unicode_string, sub_string, is_case_sensitive, ignore_count);
}

auto sdk::__unicode_string::right_find(wchar_t* sub_string, bool is_case_sensitive, unsigned __int64 ignore_count) -> unsigned __int64
{
	return sdk::right_find_unicode_sub_string(this->unicode_string, sub_string, is_case_sensitive, ignore_count);
}

auto sdk::__unicode_string::to_upper() -> void
{
	return sdk::make_unicode_string_uppercase(this->unicode_string);
}

auto sdk::__unicode_string::to_lower() -> void
{
	return sdk::make_unicode_string_lowercase(this->unicode_string);
}

auto sdk::__unicode_string::left_pop() -> void
{
	if (this->get_length() == 0)
		return;

	sdk::copy_memory((unsigned __int64)this->unicode_string, (unsigned __int64)this->unicode_string + 2, this->get_length() * 2 - 2);

	return this->right_pop();
}

auto sdk::__unicode_string::right_pop() -> void
{
	if (this->get_length() == 0)
		return;
	
	this->unicode_string[this->get_length() - 1] = 0;
}

auto sdk::__unicode_string::left_trim() -> void
{
	for (; this->unicode_string[0] == 0x20; this->left_pop());
}

auto sdk::__unicode_string::right_trim() -> void
{
	for (; this->unicode_string[this->get_length() - 1] == 0x20; this->right_pop());
}

auto sdk::__unicode_string::left_right_trim() -> void
{
	this->left_trim();

	this->right_trim();
}

auto sdk::__unicode_string::concatenate(wchar_t* string) -> void
{
	auto new_string = (wchar_t*)sdk::allocate_memory(this->get_length() * 2 + sdk::get_unicode_string_length(string) * 2 + 2);

	sdk::concatenate_unicode_string(new_string, this->unicode_string);
	sdk::concatenate_unicode_string(new_string, string);

	sdk::free_memory((unsigned __int64)this->unicode_string);

	this->unicode_string = new_string;
}

auto sdk::__unicode_string::concatenate(wchar_t* string_0, wchar_t* string_1) -> void
{
	this->concatenate(string_0);
	this->concatenate(string_1);
}

auto sdk::__unicode_string::concatenate(wchar_t* string_0, wchar_t* string_1, wchar_t* string_2) -> void
{
	this->concatenate(string_0);
	this->concatenate(string_1);
	this->concatenate(string_2);
}

auto sdk::__unicode_string::equals(wchar_t* unicode_string, bool is_case_sensitive) -> bool
{
	return sdk::unicode_string_equals_unicode_string(this->unicode_string, unicode_string, is_case_sensitive);
}

auto sdk::get_hardware_identifier() -> sdk::__multibyte_string
{
	auto hardware_identifier = sdk::__multibyte_string();

	auto system_processor_brand = sdk::__multibyte_string();

	if (sdk::nt_query_system_information(0x69, system_processor_brand.get_multibyte_string(), (unsigned __int32)system_processor_brand.get_size()) != 0)
		REPORT_EXIT_RETURN(nullptr);

	if (!sdk::__multibyte_string::is_valid(system_processor_brand))
		REPORT_EXIT_RETURN(nullptr);

	system_processor_brand.left_right_trim();

	hardware_identifier.concatenate(XOR("["), system_processor_brand.get_multibyte_string(), XOR("]"));

	auto dd = _DISPLAY_DEVICEW(sizeof(_DISPLAY_DEVICEW));

	if (sdk::nt_user_enum_display_devices(&dd) != 0)
		REPORT_EXIT_RETURN(nullptr);

	auto display_device = sdk::__unicode_string(dd.DeviceString);

	if (!sdk::__unicode_string::is_valid(display_device))
		REPORT_EXIT_RETURN(nullptr);

	display_device.left_right_trim();

	hardware_identifier.concatenate(XOR("["), display_device.get_multibyte_string(), XOR("]"));

	auto ffvi = _FILE_FS_VOLUME_INFORMATION();

	if (sdk::nt_query_volume_file_information(nullptr, &ffvi, sizeof(_FILE_FS_VOLUME_INFORMATION), 1) != 0)
		REPORT_EXIT_RETURN(nullptr);

	auto volume_serial_number = sdk::__multibyte_string();

	snprintf(volume_serial_number.get_multibyte_string(), volume_serial_number.get_size(), XOR("%lu"), ffvi.VolumeSerialNumber);

	if (!sdk::__multibyte_string::is_valid(volume_serial_number))
		REPORT_EXIT_RETURN(nullptr);

	hardware_identifier.concatenate(XOR("["), volume_serial_number.get_multibyte_string(), XOR("]"));

	hardware_identifier = (char*)picosha2::hash256_hex_string(std::string(hardware_identifier.get_multibyte_string())).c_str();

	if (!sdk::__multibyte_string::is_valid(hardware_identifier))
		REPORT_EXIT_RETURN(nullptr);

	return hardware_identifier;
}

auto sdk::__absolute_jump::create() -> bool
{
	if (this->process_handle == nullptr || this->source_address == 0 || this->target_address == 0)
		REPORT_EXIT_RETURN(false);

	auto mbi = _MEMORY_BASIC_INFORMATION();

	if (sdk::nt_query_virtual_memory(this->process_handle, (void*)this->source_address, 0, &mbi, sizeof(_MEMORY_BASIC_INFORMATION)) != 0 || mbi.BaseAddress == nullptr)
		REPORT_EXIT_RETURN(false);

	if (sdk::nt_read_virtual_memory(this->process_handle, (void*)this->source_address, this->old_instructions, 14) != 0)
		REPORT_EXIT_RETURN(false);

	unsigned __int32 old_protection = PAGE_EXECUTE_READ, new_protection = PAGE_EXECUTE_READWRITE;

	if (sdk::nt_protect_virtual_memory(this->process_handle, mbi.BaseAddress, &mbi.RegionSize, new_protection, &old_protection) != 0)
		REPORT_EXIT_RETURN(false);

	unsigned __int8 absolute_jump[] =
	{
		0xff, 0x25,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};

	*(unsigned __int64*)&absolute_jump[6] = this->target_address;

	if (sdk::nt_write_virtual_memory(this->process_handle, (void*)this->source_address, absolute_jump, 14) != 0)
		REPORT_EXIT_RETURN(false);

	if (sdk::nt_protect_virtual_memory(this->process_handle, mbi.BaseAddress, &mbi.RegionSize, old_protection, &new_protection) != 0)
		REPORT_EXIT_RETURN(false);

	return true;
}

auto sdk::__absolute_jump::remove() -> bool
{
	if (this->process_handle == nullptr || this->source_address == 0)
		REPORT_EXIT_RETURN(false);

	auto mbi = _MEMORY_BASIC_INFORMATION();

	if (sdk::nt_query_virtual_memory(this->process_handle, (void*)this->source_address, 0, &mbi, sizeof(_MEMORY_BASIC_INFORMATION)) != 0 || mbi.BaseAddress == nullptr)
		REPORT_EXIT_RETURN(false);

	unsigned __int32 old_protection = PAGE_EXECUTE_READ, new_protection = PAGE_EXECUTE_READWRITE;

	if (sdk::nt_protect_virtual_memory(this->process_handle, mbi.BaseAddress, &mbi.RegionSize, new_protection, &old_protection) != 0)
		REPORT_EXIT_RETURN(false);

	if (sdk::nt_write_virtual_memory(this->process_handle, (void*)this->source_address, this->old_instructions, 14) != 0)
		REPORT_EXIT_RETURN(false);

	if (sdk::nt_protect_virtual_memory(this->process_handle, mbi.BaseAddress, &mbi.RegionSize, old_protection, &new_protection) != 0)
		REPORT_EXIT_RETURN(false);

	return true;
}

sdk::__timer::__timer(unsigned __int64 old_kernel_system_time, unsigned __int64 new_kernel_system_time)
{
	this->old_kernel_system_time = min(old_kernel_system_time, new_kernel_system_time);
	this->new_kernel_system_time = max(old_kernel_system_time, new_kernel_system_time);
}

sdk::__timer::__timer()
{
	this->old_kernel_system_time = KERNEL_SYSTEM_TIME;
}

sdk::__timer::~__timer()
{

}

auto sdk::__timer::update() -> void
{
	this->old_kernel_system_time = KERNEL_SYSTEM_TIME;
}

auto sdk::__timer::has_elapsed(double milliseconds, bool fist_kernel_system_time_return_true, bool update_old_kernel_system_time) -> bool
{
	if (this->fist_kernel_system_time == 0 && fist_kernel_system_time_return_true)
	{
		this->fist_kernel_system_time = KERNEL_SYSTEM_TIME;

		return true;
	}

	if ((this->elapsed_milliseconds = (double)((this->new_kernel_system_time = KERNEL_SYSTEM_TIME) - this->old_kernel_system_time) / 10000.) >= milliseconds)
	{
		if (update_old_kernel_system_time)
			this->old_kernel_system_time = this->new_kernel_system_time;

		return true;
	}

	return false;
}

auto sdk::__timer::get_elapsed_milliseconds() -> double
{
	this->elapsed_milliseconds = (double)((this->new_kernel_system_time = KERNEL_SYSTEM_TIME) - this->old_kernel_system_time) / 10000.;
	this->old_kernel_system_time = this->new_kernel_system_time;

	return this->elapsed_milliseconds;
}

auto sdk::generate_random_value(double minimum_value, double maximum_value) -> double
{
	static std::random_device random_device;

	static std::mt19937 mt19937(random_device());

	return std::uniform_real_distribution<>(minimum_value, maximum_value)(mt19937);
}