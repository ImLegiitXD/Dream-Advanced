
#include "mapper.hpp"

auto client::mapper::map(sdk::__unicode_string module_file_path) -> unsigned __int64
{
	unsigned __int64 module_address = 0;

	if (!sdk::__unicode_string::is_valid(module_file_path))
		REPORT_EXIT_RETURN(0);

	auto fixed_module_file_path = sdk::__unicode_string(XOR(L"\\??\\"));

	fixed_module_file_path.concatenate(module_file_path.get_unicode_string());

	auto us = _UNICODE_STRING((unsigned __int16)(fixed_module_file_path.get_length() * 2), (unsigned __int16)(fixed_module_file_path.get_length() * 2 + 2), fixed_module_file_path.get_unicode_string());

	auto oa = _OBJECT_ATTRIBUTES(sizeof(_OBJECT_ATTRIBUTES), 0, &us, OBJ_CASE_INSENSITIVE);

	void* module_file_handle = nullptr;

	if (sdk::nt_open_file(&module_file_handle, FILE_READ_DATA, &oa, FILE_SHARE_READ) != 0 || module_file_handle == nullptr)
		EXTRA_REPORT_EXIT_RETURN(module_file_path, 0);

	void* section_handle = nullptr;

	if (sdk::nt_create_section(&section_handle, SECTION_MAP_READ, nullptr, PAGE_READONLY, SEC_IMAGE, module_file_handle) != 0 || section_handle == nullptr)
		EXTRA_REPORT_EXIT_RETURN(module_file_path, 0);

	if (sdk::nt_close(module_file_handle) != 0)
		EXTRA_REPORT_EXIT_RETURN(module_file_path, 0);

	if (unsigned __int64 memory_section_view_size = 0; sdk::nt_map_view_of_section(section_handle, CURRENT_PROCESS_HANDLE, (void**)&module_address, &memory_section_view_size, PAGE_READONLY) != 0x40000003 || module_address == 0)
		EXTRA_REPORT_EXIT_RETURN(module_file_path, 0);

	if (sdk::nt_close(section_handle) != 0)
		EXTRA_REPORT_EXIT_RETURN(module_file_path, 0);

	return module_address;
}

auto client::mapper::unmap(unsigned __int64 module_address) -> bool
{
	if (module_address == 0)
		REPORT_EXIT_RETURN(false);

	if (sdk::nt_unmap_view_of_section(CURRENT_PROCESS_HANDLE, (void*)module_address) != 0)
		REPORT_EXIT_RETURN(false);

	return true;
}

auto client::mapper::__module::create() -> bool
{
	if (this->process_handle == nullptr || this->raw_module == 0 || (this->original_process_attach_detach_function == 0 && this->modified_process_attach_detach_function != 0))
		REPORT_EXIT_RETURN(false);

	auto li = _LARGE_INTEGER();

	li.QuadPart = (__int64)((_IMAGE_NT_HEADERS64*)(this->raw_module + (unsigned __int64)((_IMAGE_DOS_HEADER*)this->raw_module)->e_lfanew))->OptionalHeader.SizeOfImage + 0x1000;

	void* section_handle = nullptr;

	if (sdk::nt_create_section(&section_handle, SECTION_MAP_WRITE | SECTION_MAP_READ | SECTION_MAP_EXECUTE, &li, PAGE_EXECUTE_READWRITE, SEC_COMMIT, nullptr) != 0 || section_handle == nullptr)
		REPORT_EXIT_RETURN(false);

	auto module_adresses = std::vector<unsigned __int64>();

	for (; this->address == 0;)
	{
		if (sdk::nt_map_view_of_section(section_handle, CURRENT_PROCESS_HANDLE, (void**)&this->address, (unsigned __int64*)&li.QuadPart, PAGE_READWRITE) != 0 || this->address == 0)
			REPORT_EXIT_RETURN(false);

		if (sdk::nt_map_view_of_section(section_handle, this->process_handle, (void**)&this->address, (unsigned __int64*)&li.QuadPart, PAGE_EXECUTE_READWRITE) != 0)
		{
			module_adresses.push_back(this->address);

			this->address = 0;
		}
	}

	if (sdk::nt_close(section_handle) != 0)
		REPORT_EXIT_RETURN(false);

	for (auto& module_adress : module_adresses)
	{
		if (sdk::nt_unmap_view_of_section(CURRENT_PROCESS_HANDLE, (void*)module_adress) != 0)
			REPORT_EXIT_RETURN(false);
	}

	if (!client::mapper::shellcode::create(this->process_handle, this->raw_module, this->address))
		REPORT_EXIT_RETURN(false);

	sdk::copy_memory(
		(this->process_attach_detach_function = this->address + (unsigned __int64)li.QuadPart - 0x1000),
		(this->original_process_attach_detach_function != 0 && this->modified_process_attach_detach_function != 0 ? this->modified_process_attach_detach_function : (unsigned __int64)client::mapper::shellcode::process_attach_detach),
		0x100
	);

	sdk::copy_memory((this->process_attach_function = this->process_attach_detach_function + 0x100), (unsigned __int64)client::mapper::shellcode::process_attach, 0x100);
	sdk::copy_memory((this->process_detach_function = this->process_attach_function + 0x100), (unsigned __int64)client::mapper::shellcode::process_detach, 0x100);

	*(unsigned __int64*)(this->process_attach_function + 0x100 - sizeof(unsigned __int64)) = this->address;
	*(unsigned __int64*)(this->process_detach_function + 0x100 - sizeof(unsigned __int64)) = this->address;

	sdk::copy_memory((this->original_pe_header = sdk::allocate_memory(0x1000)), this->address, 0x1000);

	this->modified_pe_header = sdk::allocate_memory(0x1000);

	return true;
}

auto client::mapper::__module::remove() -> bool
{
	if (this->process_handle == nullptr || this->address == 0)
		REPORT_EXIT_RETURN(false);

	if (sdk::nt_unmap_view_of_section(CURRENT_PROCESS_HANDLE, (void*)this->address) != 0)
		REPORT_EXIT_RETURN(false);

	if (sdk::nt_unmap_view_of_section(this->process_handle, (void*)this->address) != 0)
		REPORT_EXIT_RETURN(false);

	return true;
}

auto client::mapper::__module::attach() -> bool
{
	if (this->process_handle == nullptr || this->address == 0 || this->process_attach_detach_function == 0 || this->process_attach_function == 0 || this->modified_pe_header == 0)
		REPORT_EXIT_RETURN(false);

	*(unsigned __int64*)(this->process_attach_detach_function + 0x100 - sizeof(unsigned __int64)) = this->process_attach_function;

	if (this->original_process_attach_detach_function == 0)
	{
		void* thread_handle = nullptr;

		if (sdk::nt_create_thread_ex(&thread_handle, THREAD_ALL_ACCESS, this->process_handle, (void*)this->process_attach_detach_function, nullptr, 0) != 0 || thread_handle == nullptr)
			REPORT_EXIT_RETURN(false);

		for (; *(unsigned __int64*)this->address != 0x0123456789abcdef; sdk::nt_delay_execution(1));

		if (sdk::nt_close(thread_handle) != 0)
			REPORT_EXIT_RETURN(false);
	}

	else
	{
		auto absolute_jump = sdk::__absolute_jump(this->process_handle, this->original_process_attach_detach_function, this->process_attach_detach_function);

		if (!absolute_jump.create())
			REPORT_EXIT_RETURN(false);

		for (; *(unsigned __int64*)this->address != 0x0123456789abcdef; sdk::nt_delay_execution(1));

		if (!absolute_jump.remove())
			REPORT_EXIT_RETURN(false);
	}

	sdk::copy_memory(this->address, this->modified_pe_header, 0x1000);

	sdk::free_memory(this->modified_pe_header);

	return true;
}

auto client::mapper::__module::detach() -> bool
{
	if (this->process_handle == nullptr || this->address == 0 || this->process_attach_detach_function == 0 || this->process_detach_function == 0 || this->original_pe_header == 0)
		REPORT_EXIT_RETURN(false);

	*(unsigned __int64*)(this->process_attach_detach_function + 0x100 - sizeof(unsigned __int64)) = this->process_detach_function;

	sdk::copy_memory(this->address, this->original_pe_header, 0x1000);

	sdk::free_memory(this->original_pe_header);

	if (this->original_process_attach_detach_function == 0)
	{
		void* thread_handle = nullptr;

		if (sdk::nt_create_thread_ex(&thread_handle, THREAD_ALL_ACCESS, this->process_handle, (void*)this->process_attach_detach_function, nullptr, 0) != 0 || thread_handle == nullptr)
			REPORT_EXIT_RETURN(false);

		for (; *(unsigned __int64*)this->address != 0xfedcba9876543210; sdk::nt_delay_execution(1));

		if (sdk::nt_close(thread_handle) != 0)
			REPORT_EXIT_RETURN(false);
	}

	else
	{
		auto absolute_jump = sdk::__absolute_jump(this->process_handle, this->original_process_attach_detach_function, this->process_attach_detach_function);

		if (!absolute_jump.create())
			REPORT_EXIT_RETURN(false);

		for (; *(unsigned __int64*)this->address != 0xfedcba9876543210; sdk::nt_delay_execution(1));

		if (!absolute_jump.remove())
			REPORT_EXIT_RETURN(false);
	}

	return true;
}