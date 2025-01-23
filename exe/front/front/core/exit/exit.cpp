
#include "../core.hpp"

auto client::core::exit::initialize() -> __int32
{
	if (sdk::nt_close(sdk::target_process_handle) != 0)
		REPORT_EXIT_RETURN(1);

	for (client::core::exit::uninitialized = true; KERNEL_SYSTEM_TIME != 0; sdk::nt_delay_execution(100));

	REPORT_EXIT_RETURN(1);
}