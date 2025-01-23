
#include "../hooks.hpp"

auto client::hooks::atan_2(JNIEnv_* jni, _jclass* klass, double abscissa, double ordinate) -> double
{
	if (jni != nullptr && klass != nullptr)
	{
		if (client::mapper::jni != nullptr && client::mapper::jvmti != nullptr)
		{
			if (auto minecraft = client::mapper::__minecraft(); minecraft.object != nullptr && minecraft.is_valid())
				client::features::run_on_update_animations(minecraft);
		}
	}

	return ((double(__stdcall*)(JNIEnv_*, _jclass*, double, double))client::hooks::original_atan_2)(jni, klass, abscissa, ordinate);
}