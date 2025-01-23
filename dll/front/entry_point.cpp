
#include "front/client.hpp"

auto set_internal_send_error_report_callback = sdk::internal_send_error_report_callback = (unsigned __int64)+[](sdk::__multibyte_string message) -> __int32
{
	((__int32(_stdcall*)(void*, char*, char*, unsigned __int32))sdk::get_module_export_address(sdk::get_module_address(USER_32_MODULE_FILE_PATH), XOR("MessageBoxA")))
		(nullptr, message.get_multibyte_string(), XOR("[EXE] unexpected error occurred, please contact staff"), 0);

	EXIT_RETURN(1);
};

auto DllMain(unsigned __int64 module_address, unsigned __int32 calling_reason, unsigned __int64 reserved) -> __int32
{
	return (calling_reason == DLL_PROCESS_ATTACH ? client::initialize(reserved) : (calling_reason == DLL_PROCESS_DETACH ? client::uninitialize(reserved) : 1));
}