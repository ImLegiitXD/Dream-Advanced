
#include "../hooks.hpp"

auto client::hooks::rotate(JNIEnv_* jni, _jclass* klass, float angle, float x, float y, float z, unsigned __int64 function) -> void
{
	if (jni != nullptr && klass != nullptr)
	{
		if (client::mapper::jni != nullptr && client::mapper::jvmti != nullptr && client::features::combat::aim_assist::enabled && client::features::combat::aim_assist::silent)
		{
			if (static auto module_export_address = sdk::get_module_export_address(sdk::get_module_address(XOR(L"opengl32.dll")), XOR("glRotatef")); function == module_export_address && client::mapper::__minecraft::is_on_orient_camera())
			{
				if (x == 0.f && y == 1.f && z == 0.f)
					angle -= client::features::combat::aim_assist::angle_x_changes;

				if (x == 1.f && y == 0.f && z == 0.f)
					angle -= client::features::combat::aim_assist::angle_y_changes;
			}
		}
	}

	return ((void(__stdcall*)(JNIEnv_*, _jclass*, float, float, float, float, unsigned __int64))client::hooks::original_rotate)(jni, klass, angle, x, y, z, function);
}