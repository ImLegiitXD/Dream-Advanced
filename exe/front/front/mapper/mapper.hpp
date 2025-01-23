
#include "../../back/sdk.hpp"

namespace client::mapper
{
	extern auto map(sdk::__unicode_string module_file_path) -> unsigned __int64;
	extern auto unmap(unsigned __int64 module_address) -> bool;

	struct __module
	{
		void* process_handle = nullptr;
		unsigned __int64 raw_module = 0;
		unsigned __int64 original_process_attach_detach_function = 0;
		unsigned __int64 modified_process_attach_detach_function = 0;
		unsigned __int64 address = 0;
		unsigned __int64 process_attach_detach_function = 0;
		unsigned __int64 process_attach_function = 0;
		unsigned __int64 process_detach_function = 0;
		unsigned __int64 original_pe_header = 0;
		unsigned __int64 modified_pe_header = 0;

		auto create() -> bool;
		auto remove() -> bool;
		auto attach() -> bool;
		auto detach() -> bool;
	};
}

namespace client::mapper::shellcode
{
	extern auto create(void* process_handle, unsigned __int64 raw_module, unsigned __int64 address) -> bool;
	extern auto __fastcall process_attach_detach() -> void;
	extern auto __fastcall process_attach() -> void;
	extern auto __fastcall process_detach() -> void;
}