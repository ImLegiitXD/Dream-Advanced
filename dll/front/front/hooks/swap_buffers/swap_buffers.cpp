
#include "../hooks.hpp"

auto client::hooks::swap_buffers(HDC__* hdc) -> __int32
{
	if (hdc != nullptr)
	{
		if (client::mapper::jni != nullptr && client::mapper::jvmti != nullptr && client::features::settings::use_opengl_32_swap_buffers && client::features::visual::requested_rendering && client::features::visual::initialized_frame)
		{
			glDisable(0x0BC0);

			ImGui::Render();

			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glEnable(0x0BC0);

			client::features::visual::requested_rendering = client::features::visual::initialized_frame = false;
		}
	}

	return ((__int32(__stdcall*)(HDC__*))client::hooks::original_swap_buffers)(hdc);
}