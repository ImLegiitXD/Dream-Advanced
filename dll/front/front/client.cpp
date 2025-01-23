
#include "client.hpp"

auto client::initialize(unsigned __int64 reserved) -> __int32
{
	//if (sdk::compare_memory((unsigned __int64)client::hardware_identifier, (unsigned __int64)sdk::get_hardware_identifier().get_multibyte_string(), 64) != 64)
		//REPORT_EXIT_RETURN(1);

	//if (reserved != 0xa11ac4)
	//	REPORT_EXIT_RETURN(1);

	if (client::hooks::initialize() != 0)
		REPORT_EXIT_RETURN(1);

	return 1;
}

auto client::uninitialize(unsigned __int64 reserved) -> __int32
{
	//if (reserved != 0xde1ac4)
	//	REPORT_EXIT_RETURN(1);

	if (client::hooks::uninitialize() != 0)
	REPORT_EXIT_RETURN(1);

	return 1;
}