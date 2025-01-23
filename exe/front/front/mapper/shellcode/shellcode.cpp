
#include "../mapper.hpp"

auto client::mapper::shellcode::create(void* process_handle, unsigned __int64 raw_module, unsigned __int64 address) -> bool
{
	if (process_handle == nullptr || raw_module == 0 || address == 0)
		REPORT_EXIT_RETURN(false);

	sdk::copy_memory(address, raw_module, 0x1000);

	auto module_nt_headers = (_IMAGE_NT_HEADERS64*)(raw_module + (unsigned __int64)((_IMAGE_DOS_HEADER*)raw_module)->e_lfanew);

	auto module_section_header = (_IMAGE_SECTION_HEADER*)((unsigned __int64)module_nt_headers + sizeof(_IMAGE_NT_HEADERS64));

	for (unsigned __int16 x = 0; x < module_nt_headers->FileHeader.NumberOfSections; ++x, ++module_section_header)
		sdk::copy_memory(address + (unsigned __int64)module_section_header->VirtualAddress, raw_module + (unsigned __int64)module_section_header->PointerToRawData, (unsigned __int64)module_section_header->SizeOfRawData);

	for (
		auto module_base_relocation = (_IMAGE_BASE_RELOCATION*)(address + (unsigned __int64)module_nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);
		module_base_relocation->VirtualAddress != 0;
		*(unsigned __int64*)&module_base_relocation += (unsigned __int64)module_base_relocation->SizeOfBlock)
	{
		auto base_relocation_entry = (unsigned short*)(module_base_relocation + 1);

		for (unsigned __int32 x = 0; x < ((unsigned __int32)module_base_relocation->SizeOfBlock - sizeof(_IMAGE_BASE_RELOCATION)) / sizeof(unsigned short); ++x, ++base_relocation_entry)
		{
			if ((*base_relocation_entry >> 0x0c) == IMAGE_REL_BASED_DIR64)
				*(unsigned __int64*)(address + (unsigned __int64)module_base_relocation->VirtualAddress + (unsigned __int64)(*base_relocation_entry & 0xfff)) += address - (unsigned __int64)module_nt_headers->OptionalHeader.ImageBase;
		}
	}

	auto module_import_directory = (_IMAGE_IMPORT_DESCRIPTOR*)(address + (unsigned __int64)module_nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);

	auto module_export_directory = (_IMAGE_EXPORT_DIRECTORY*)(address + (unsigned __int64)module_nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

	auto module_export_directory_functions = (unsigned __int32*)(address + (unsigned __int64)module_export_directory->AddressOfFunctions);

	for (; module_import_directory->Name != 0; ++module_import_directory)
	{
		auto module_file_name = sdk::__multibyte_string((char*)(address + (unsigned __int64)module_import_directory->Name));

		if (!sdk::__multibyte_string::is_valid(module_file_name))
			REPORT_EXIT_RETURN(false);

		auto module_address = sdk::get_module_address_ex(process_handle, module_file_name.get_unicode_string());

		if (module_address == 0)
			EXTRA_REPORT_EXIT_RETURN(module_file_name, false);

		for (
			auto original_first_thunk = address + (unsigned __int64)module_import_directory->OriginalFirstThunk, first_thunk = address + (unsigned __int64)module_import_directory->FirstThunk;
			*(unsigned __int64*)original_first_thunk != 0;
			original_first_thunk += sizeof(unsigned __int64), first_thunk += sizeof(unsigned __int64))
		{
			*(unsigned __int64*)first_thunk = ((*(unsigned __int64*)original_first_thunk & IMAGE_ORDINAL_FLAG64) != 0 ?
				address + (unsigned __int64)((unsigned __int32*)(address + (unsigned __int64)module_export_directory_functions))[(unsigned __int64)(*(unsigned __int64*)original_first_thunk & 0xffff) - (unsigned __int64)module_export_directory->Base] :
				sdk::get_module_export_address_ex(process_handle, module_address, (char*)(((_IMAGE_IMPORT_BY_NAME*)(address + *(unsigned __int64*)original_first_thunk))->Name)));
		}
	}

	return true;
}

auto __fastcall client::mapper::shellcode::process_attach_detach() -> void
{
	if (auto shellcode_function_address = (unsigned __int64)client::mapper::shellcode::process_attach_detach + 0x100 - sizeof(unsigned __int64), shellcode_function = *(unsigned __int64*)shellcode_function_address; shellcode_function != 0)
	{
		*(unsigned __int64*)shellcode_function_address = 0;

		return ((void(__cdecl*)())shellcode_function)();
	}
}

auto __fastcall client::mapper::shellcode::process_attach() -> void
{
	auto module_address = *(unsigned __int64*)((unsigned __int64)client::mapper::shellcode::process_attach + 0x100 - sizeof(unsigned __int64));

	auto module_nt_headers = (_IMAGE_NT_HEADERS64*)(module_address + (unsigned __int64)((_IMAGE_DOS_HEADER*)module_address)->e_lfanew);

	if (auto module_nt_headers = (_IMAGE_NT_HEADERS64*)(module_address + (unsigned __int64)((_IMAGE_DOS_HEADER*)module_address)->e_lfanew); module_nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].Size != 0)
	{
		for (
			auto tls_callback = ((_IMAGE_TLS_DIRECTORY64*)(module_address + (unsigned __int64)module_nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress))->AddressOfCallBacks;
			tls_callback != 0 && *(unsigned __int64*)tls_callback != 0;
			tls_callback += sizeof(unsigned __int64))
		{
			((void(__cdecl*)(unsigned __int64, unsigned __int32, unsigned __int64))(*(unsigned __int64*)tls_callback))(module_address, DLL_PROCESS_ATTACH, 0);
		}
	}

	if (module_nt_headers->OptionalHeader.AddressOfEntryPoint != 0)
		((__int32(__cdecl*)(unsigned __int64, unsigned __int32, unsigned __int64))(module_address + (unsigned __int64)module_nt_headers->OptionalHeader.AddressOfEntryPoint))(module_address, DLL_PROCESS_ATTACH, 0xa11ac4);

	*(unsigned __int64*)module_address = 0x0123456789abcdef;
}

auto __fastcall client::mapper::shellcode::process_detach() -> void
{
	auto module_address = *(unsigned __int64*)((unsigned __int64)client::mapper::shellcode::process_detach + 0x100 - sizeof(unsigned __int64));

	if (auto module_nt_headers = (_IMAGE_NT_HEADERS64*)(module_address + (unsigned __int64)((_IMAGE_DOS_HEADER*)module_address)->e_lfanew); module_nt_headers->OptionalHeader.AddressOfEntryPoint != 0)
		((__int32(__cdecl*)(unsigned __int64, unsigned __int32, unsigned __int64))(module_address + (unsigned __int64)module_nt_headers->OptionalHeader.AddressOfEntryPoint))(module_address, DLL_PROCESS_DETACH, 0xde1ac4);

	*(unsigned __int64*)module_address = 0xfedcba9876543210;
}