
#include "../hooks.hpp"

auto client::hooks::get_time(JNIEnv_* jni, _jclass* klass) -> __int64
{
	if (static auto timer = sdk::__timer(); timer.has_elapsed(1000., true))
	{
		void* process_handle = nullptr;

		if (sdk::nt_open_process(&process_handle, PROCESS_QUERY_LIMITED_INFORMATION, client::hooks::loader_process_identifier) != 0 || process_handle == nullptr)
			REPORT_EXIT_RETURN(1);

		if (auto pbi = _PROCESS_BASIC_INFORMATION(); sdk::nt_query_information_process(process_handle, 0, &pbi, sizeof(_PROCESS_BASIC_INFORMATION)) != 0 || pbi.ExitStatus != STILL_ACTIVE)
			REPORT_EXIT_RETURN(1);

		if (sdk::nt_close(process_handle) != 0)
			REPORT_EXIT_RETURN(1);
	}

	if (jni != nullptr && klass != nullptr)
	{
		static auto initialize = [&]() -> __int32
		{
			if (client::mapper::initialize(jni) != 0)
				REPORT_EXIT_RETURN(1);

			if (client::mapper::initialize() != 0)
				REPORT_EXIT_RETURN(1);

			return 0;
		}();

		if (client::mapper::jni != nullptr && client::mapper::jvmti != nullptr)
		{
			if (client::mapper::__minecraft::is_on_run_tick())
			{
				if (auto minecraft = client::mapper::__minecraft(); minecraft.object != nullptr && minecraft.is_valid())
					client::features::run_on_run_tick(minecraft);
			}
		}
	}

	return ((__int64(__stdcall*)(JNIEnv_*, _jclass*))client::hooks::original_get_time)(jni, klass);
}