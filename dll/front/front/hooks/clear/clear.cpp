
#include "../hooks.hpp"

auto client::hooks::clear(JNIEnv_* jni, _jclass* klass, __int32 mask, unsigned __int64 function) -> void
{
	if (jni != nullptr && klass != nullptr)
	{
		if (client::mapper::jni != nullptr && client::mapper::jvmti != nullptr)
		{
			if (static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(XOR(L"opengl32.dll")), XOR("glClear")); function == module_export_address && mask == 0x100 && client::mapper::__minecraft::is_on_render_world())
			{
				if (auto minecraft = client::mapper::__minecraft(); minecraft.object != nullptr && minecraft.is_valid())
					client::features::run_on_render_world(minecraft, &client::hooks::last_render_world_kernel_system_time);
			}
		}
	}

	return ((void(__stdcall*)(JNIEnv_*, _jclass*, __int32, unsigned __int64))client::hooks::original_clear)(jni, klass, mask, function);
}