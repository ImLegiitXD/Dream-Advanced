
#include "../security.h"

auto client::security::checks::is_virtual_computer(unsigned __int64 fixed_value, unsigned __int64* value) -> unsigned __int64
{
	if (fixed_value == 0 || value == nullptr)
		REPORT_EXIT_RETURN(1);

	if (client::security::checks::is_virtual_computer_checks_count != 0)
		REPORT_EXIT_RETURN(1);

	auto shdi = _SYSTEM_HYPERVISOR_DETAIL_INFORMATION();

	if (sdk::nt_query_system_information(0x9f, &shdi, sizeof(_SYSTEM_HYPERVISOR_DETAIL_INFORMATION)) != 0)
		REPORT_EXIT_RETURN(1);

	if (sdk::count_memory_matches((unsigned __int64)&shdi, sizeof(_SYSTEM_HYPERVISOR_DETAIL_INFORMATION), 0) != sizeof(_SYSTEM_HYPERVISOR_DETAIL_INFORMATION))
	{
		auto hypervisor_vendor = sdk::__multibyte_string((char*)&shdi.HvVendorAndMaxFunction.Data[1], 12);

		if (!sdk::__multibyte_string::is_valid(hypervisor_vendor))
			REPORT_EXIT_RETURN(1);

		if (!hypervisor_vendor.equals(XOR("Microsoft Hv")))
			EXTRA_REPORT_EXIT_RETURN(hypervisor_vendor, 1);
	}

	++client::security::checks::is_virtual_computer_checks_count;

	*value = fixed_value;

	return sdk::current_process_load_kernel_system_time;
}

auto client::security::checks::is_debugger_present(unsigned __int64 fixed_value, unsigned __int64* value) -> unsigned __int64
{
	if (fixed_value == 0 || value == nullptr)
		REPORT_EXIT_RETURN(1);

	if (client::security::checks::is_debugger_present_checks_count != 0)
		REPORT_EXIT_RETURN(1);

	if (auto skdi = _SYSTEM_KERNEL_DEBUGGER_INFORMATION(); sdk::nt_query_system_information(0x23, &skdi, sizeof(_SYSTEM_KERNEL_DEBUGGER_INFORMATION)) != 0 || skdi.DebuggerEnabled != 0 || skdi.DebuggerNotPresent == 0)
		REPORT_EXIT_RETURN(1);

	++client::security::checks::is_debugger_present_checks_count;

	if (void* current_process_debug_port = 0; sdk::nt_query_information_process(CURRENT_PROCESS_HANDLE, 0x7, &current_process_debug_port, sizeof(void*)) != 0 || current_process_debug_port != nullptr)
		REPORT_EXIT_RETURN(1);

	++client::security::checks::is_debugger_present_checks_count;

	if (void* current_process_debug_object_handle = nullptr; sdk::nt_query_information_process(CURRENT_PROCESS_HANDLE, 0x1e, &current_process_debug_object_handle, sizeof(void*)) == 0 || current_process_debug_object_handle != nullptr)
		REPORT_EXIT_RETURN(1);

	++client::security::checks::is_debugger_present_checks_count;

	if (unsigned __int32 current_process_debug_flags = 0; sdk::nt_query_information_process(CURRENT_PROCESS_HANDLE, 0x1f, &current_process_debug_flags, sizeof(unsigned __int32)) == 0 && current_process_debug_flags == 0)
		REPORT_EXIT_RETURN(1);

	++client::security::checks::is_debugger_present_checks_count;

	*value = fixed_value;

	return sdk::current_process_load_kernel_system_time;
}

auto client::security::checks::is_process_tampered(unsigned __int64 fixed_value, unsigned __int64* value) -> unsigned __int64
{
	if (fixed_value == 0 || value == nullptr)
		REPORT_EXIT_RETURN(1);

	if (client::security::checks::is_process_tampered_checks_count != 0)
		REPORT_EXIT_RETURN(1);

	for (auto mbi = _MEMORY_BASIC_INFORMATION(); sdk::nt_query_virtual_memory(CURRENT_PROCESS_HANDLE, mbi.BaseAddress, 0, &mbi, sizeof(_MEMORY_BASIC_INFORMATION)) == 0; *(unsigned __int64*)&mbi.BaseAddress += mbi.RegionSize)
	{
		if (!((mbi.Protect & PAGE_EXECUTE) != 0 || (mbi.Protect & PAGE_EXECUTE_READ) != 0 || (mbi.Protect & PAGE_EXECUTE_READWRITE) != 0 || (mbi.Protect & PAGE_EXECUTE_WRITECOPY) != 0))
			continue;

		auto loaded_module_address = (unsigned __int64)mbi.AllocationBase;

		if (loaded_module_address == 0)
			REPORT_EXIT_RETURN(1);

		auto loaded_module_file_path = sdk::__unicode_string(sdk::get_module_file_path(loaded_module_address));

		if (!sdk::__unicode_string::is_valid(loaded_module_file_path))
			REPORT_EXIT_RETURN(1);

		if (sdk::get_module_address(&loaded_module_file_path.get_unicode_string()[1]) != loaded_module_address)
			EXTRA_REPORT_EXIT_RETURN(loaded_module_file_path, 1);

		if ([&]() -> bool
		{
			for (auto& module_file_path : client::security::callbacks::module_file_paths)
			{
				if (module_file_path.equals(loaded_module_file_path.get_unicode_string()))
					return true;
			}

			return false;
		}())
			continue;

		auto mapped_module_address = client::mapper::map(loaded_module_file_path);

		if (mapped_module_address == 0)
			EXTRA_REPORT_EXIT_RETURN(loaded_module_file_path, 1);

		if (sdk::compare_memory(loaded_module_address, mapped_module_address, 0x1000) != 0x1000)
			EXTRA_REPORT_EXIT_RETURN(loaded_module_file_path, 1);

		auto loaded_module_nt_headers = (_IMAGE_NT_HEADERS64*)(loaded_module_address + (unsigned __int64)((_IMAGE_DOS_HEADER*)loaded_module_address)->e_lfanew);
		auto mapped_module_nt_headers = (_IMAGE_NT_HEADERS64*)(mapped_module_address + (unsigned __int64)((_IMAGE_DOS_HEADER*)mapped_module_address)->e_lfanew);

		auto loaded_module_section_header = (_IMAGE_SECTION_HEADER*)((unsigned __int64)loaded_module_nt_headers + sizeof(_IMAGE_NT_HEADERS64));
		auto mapped_module_section_header = (_IMAGE_SECTION_HEADER*)((unsigned __int64)mapped_module_nt_headers + sizeof(_IMAGE_NT_HEADERS64));

		for (unsigned __int16 x = 0; x < loaded_module_nt_headers->FileHeader.NumberOfSections; ++x, ++loaded_module_section_header, ++mapped_module_section_header)
		{
			if ((loaded_module_section_header->Characteristics & IMAGE_SCN_MEM_WRITE) != 0)
				continue;

			auto section_name = sdk::__multibyte_string((char*)loaded_module_section_header->Name);

			if (!sdk::__multibyte_string::is_valid(section_name))
				EXTRA_REPORT_EXIT_RETURN(loaded_module_file_path, 1);

			if (section_name.equals(XOR(".rdata")) || section_name.equals(XOR(".mrdata")))
				continue;

			if (sdk::compare_memory(
				loaded_module_address + (unsigned __int64)loaded_module_section_header->VirtualAddress,
				mapped_module_address + (unsigned __int64)mapped_module_section_header->VirtualAddress,
				(unsigned __int64)loaded_module_section_header->SizeOfRawData) != (unsigned __int64)mapped_module_section_header->SizeOfRawData)
			{
				auto loaded_module_file_path_section_name = sdk::__unicode_string(loaded_module_file_path.get_unicode_string());

				loaded_module_file_path_section_name.concatenate(XOR(L"::"), section_name.get_unicode_string());

				EXTRA_REPORT_EXIT_RETURN(loaded_module_file_path_section_name, 1);
			}
		}

		if (!client::mapper::unmap(mapped_module_address))
			EXTRA_REPORT_EXIT_RETURN(loaded_module_file_path, 1);

		++client::security::checks::is_process_tampered_checks_count;
	}

	*value = fixed_value;

	return sdk::current_process_load_kernel_system_time;
}

auto client::security::checks::is_process_accessed(unsigned __int64 fixed_value, unsigned __int64* value) -> unsigned __int64
{
	if (fixed_value == 0 || value == nullptr)
		REPORT_EXIT_RETURN(1);

	if (client::security::checks::is_process_accessed_checks_count != 0)
		REPORT_EXIT_RETURN(1);

	void* current_process_token_handle = nullptr;

	if (sdk::nt_open_process_token(CURRENT_PROCESS_HANDLE, TOKEN_ALL_ACCESS, &current_process_token_handle) != 0 || current_process_token_handle == nullptr)
		REPORT_EXIT_RETURN(1);

	if (auto tp = _TOKEN_PRIVILEGES(1, { 0x14, 0, SE_PRIVILEGE_ENABLED }); sdk::nt_adjust_privileges_token(current_process_token_handle, &tp, sizeof(_TOKEN_PRIVILEGES)) != 0)
		REPORT_EXIT_RETURN(1);

	if (sdk::nt_close(current_process_token_handle) != 0)
		REPORT_EXIT_RETURN(1);

	_SYSTEM_HANDLE_INFORMATION* shi = nullptr;

	unsigned __int64 system_handle_information = 0, system_handle_information_size = 0x1000000;

	for (; shi == nullptr;)
	{
		if (sdk::nt_allocate_virtual_memory(CURRENT_PROCESS_HANDLE, (void**)&system_handle_information, &system_handle_information_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE) != 0 || system_handle_information == 0)
			REPORT_EXIT_RETURN(1);

		auto nt_query_system_information_result = sdk::nt_query_system_information(0x10, (void*)system_handle_information, (unsigned __int32)system_handle_information_size);

		if (nt_query_system_information_result == 0xc0000004)
		{
			if (sdk::nt_free_virtual_memory(CURRENT_PROCESS_HANDLE, (void**)&system_handle_information, &system_handle_information_size, MEM_RELEASE) != 0)
				REPORT_EXIT_RETURN(1);

			system_handle_information = 0;
			system_handle_information_size += 0x1000000;

			continue;
		}

		if (nt_query_system_information_result != 0)
			REPORT_EXIT_RETURN(1);

		shi = (_SYSTEM_HANDLE_INFORMATION*)system_handle_information;
	}

	auto pbi_0 = _PROCESS_BASIC_INFORMATION();

	if (sdk::nt_query_information_process(CURRENT_PROCESS_HANDLE, 0, &pbi_0, sizeof(_PROCESS_BASIC_INFORMATION)) != 0 || pbi_0.UniqueProcessId == 0)
		REPORT_EXIT_RETURN(1);

	auto opened_process_handles = std::vector<std::pair<unsigned __int64, void*>>();

	for (unsigned __int32 x = 0; x < shi->NumberOfHandles; ++x)
	{
		auto handle_owner_process_identifier = (unsigned __int64)shi->Handles[x].UniqueProcessId;

		if (handle_owner_process_identifier == pbi_0.UniqueProcessId)
			continue;

		if (!(shi->Handles[x].ObjectTypeIndex == 0x5 || shi->Handles[x].ObjectTypeIndex == 0x6 || shi->Handles[x].ObjectTypeIndex == 0x7))
			continue;

		if (shi->Handles[x].GrantedAccess == PROCESS_QUERY_LIMITED_INFORMATION)
			continue;

		auto fast_nt_open_process = [&](void** process_handle, unsigned __int32 process_access, unsigned __int64 process_identifier) -> __int32
		{
			for (auto& opened_process_handle : opened_process_handles)
			{
				if (opened_process_handle.first == process_identifier)
					return ((*process_handle = opened_process_handle.second) != nullptr ? 0 : 1);
			}

			auto nt_open_process_result = (sdk::nt_open_process(process_handle, process_access, process_identifier) == 0 && *process_handle != nullptr ? 0 : 1);

			if (nt_open_process_result == 0)
				opened_process_handles.push_back({ process_identifier, *process_handle });

			return nt_open_process_result;
		};

		void* process_handle = nullptr;

		if (fast_nt_open_process(&process_handle, PROCESS_ALL_ACCESS, handle_owner_process_identifier) != 0 || process_handle == nullptr)
			continue;

		auto local_handle = (void*)shi->Handles[x].HandleValue;

		void* cloned_process_handle = nullptr;

		if (sdk::nt_duplicate_object(process_handle, local_handle, CURRENT_PROCESS_HANDLE, &cloned_process_handle, 0, DUPLICATE_SAME_ACCESS) != 0 || cloned_process_handle == nullptr)
			continue;

		if (auto pbi_1 = _PROCESS_BASIC_INFORMATION(); sdk::nt_query_information_process(cloned_process_handle, 0, &pbi_1, sizeof(_PROCESS_BASIC_INFORMATION)) == 0 && pbi_1.UniqueProcessId == pbi_0.UniqueProcessId)
		{
			auto process_file_path = sdk::__unicode_string();

			if (auto spini = _SYSTEM_PROCESS_IMAGE_NAME_INFORMATION(handle_owner_process_identifier, _UNICODE_STRING(0, (__int16)process_file_path.get_size(), process_file_path.get_unicode_string()));
				sdk::nt_query_system_information(0x58, &spini, sizeof(_SYSTEM_PROCESS_IMAGE_NAME_INFORMATION)) != 0)
				REPORT_EXIT_RETURN(1);

			if (!sdk::__unicode_string::is_valid(process_file_path))
				REPORT_EXIT_RETURN(1);

			auto device_hard_disk_volume = sdk::__unicode_string(XOR(L"\\Device\\HarddiskVolume"));

			for (unsigned __int64 x = 0; x < device_hard_disk_volume.get_length() + 1; ++x)
				process_file_path.left_pop();

			if (!(process_file_path.equals(XOR(L"\\windows\\system32\\svchost.exe"), false) || process_file_path.equals(XOR(L"\\windows\\system32\\lsass.exe"), false)))
			{
				void* closed_process_handle = nullptr;

				if (sdk::nt_duplicate_object(process_handle, local_handle, CURRENT_PROCESS_HANDLE, &closed_process_handle, 0, DUPLICATE_CLOSE_SOURCE) != 0 || closed_process_handle == nullptr)
					EXTRA_REPORT_EXIT_RETURN(process_file_path, 1);

				if (sdk::nt_close(closed_process_handle) != 0)
					EXTRA_REPORT_EXIT_RETURN(process_file_path, 1);
			}
		}

		if (sdk::nt_close(cloned_process_handle) != 0)
			REPORT_EXIT_RETURN(1);

		++client::security::checks::is_process_accessed_checks_count;
	}

	for (auto& opened_process_handle : opened_process_handles)
	{
		if (sdk::nt_close(opened_process_handle.second) != 0)
			REPORT_EXIT_RETURN(1);
	}

	if (sdk::nt_free_virtual_memory(CURRENT_PROCESS_HANDLE, (void**)&system_handle_information, &system_handle_information_size, MEM_RELEASE) != 0)
		REPORT_EXIT_RETURN(1);

	*value = fixed_value;

	return sdk::current_process_load_kernel_system_time;
}