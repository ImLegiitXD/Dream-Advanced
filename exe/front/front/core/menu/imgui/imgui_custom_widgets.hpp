
#include "imgui_include.h"

namespace imgui
{
	inline auto window_size = ImVec2(750.f, 700.f);
	inline HWND__* window_handle = nullptr;

	auto set_up_window() -> void
	{
		//SysListView32

		SetWindowLongA(imgui::window_handle, GWL_STYLE, 0);

		auto tr = tagRECT();

		GetWindowRect(GetDesktopWindow(), &tr);

		SetWindowPos(
			imgui::window_handle,
			nullptr,
			100,
			100,
			(__int32)imgui::window_size.x,
			(__int32)imgui::window_size.y,
			SWP_NOZORDER | SWP_NOREDRAW | SWP_FRAMECHANGED | SWP_NOCOPYBITS
		);
	}

	inline auto uninitialize = false;
	inline auto delay = 10;

	auto title_bar(ImVec2 position, ImVec2 size, ImVec2 window_size, char* name, char* status, char* mayor_version, char* minor_version) -> bool
	{
		static auto result = false;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.f, 0.f));

		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(.55f, .55f, .55f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(.1f, .1f, .1f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(.2f, .2f, .2f, 1.f));

		ImGui::SetNextWindowPos(position);

		ImGui::SetNextWindowSize(size);

		if (ImGui::Begin(XOR("title_bar_window"), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoNav))
		{
			auto window_position = ImGui::GetWindowPos(), cursor_position = ImGui::GetCursorPos(), fixed_cursor_position = ImVec2(window_position.x + cursor_position.x, window_position.y + cursor_position.y);

			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.f, 0.f, 0.f, 0.f));
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 0.f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.f, 0.f, 0.f, 0.f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.f, 0.f, 0.f, 0.f));

			static auto local_click_position = ImVec2(0.f, 0.f);

			if (ImGui::Button(XOR("title_bar_window_button_0"), ImVec2(size.x - 80.f, size.y)); !result && ImGui::IsItemActive())
			{
				result = true;

				auto tp = tagPOINT();

				GetCursorPos(&tp);

				ScreenToClient(imgui::window_handle, &tp);

				local_click_position.x = (float)tp.x;
				local_click_position.y = (float)tp.y;
			}

			if (result && (sdk::nt_user_get_async_key_state(VK_LBUTTON) & 0x8000) == 0)
				result = false;

			if (result)
			{
				auto tp = tagPOINT();

				GetCursorPos(&tp);

				SetWindowPos(imgui::window_handle, nullptr, (__int32)((float)tp.x - local_click_position.x), (__int32)((float)tp.y - local_click_position.y), window_size.x, window_size.y, SWP_NOZORDER | SWP_NOREDRAW | SWP_NOCOPYBITS);

				UpdateWindow(imgui::window_handle);
			}

			ImGui::SameLine();

			if (ImGui::Button(XOR("~"), ImVec2(40.f, size.y)))
				PostMessageA(imgui::window_handle, WM_SYSCOMMAND, SC_MINIMIZE, 0);

			ImGui::SameLine();

			if (ImGui::Button(XOR("x"), ImVec2(40.f, size.y)))
				PostMessageA(imgui::window_handle, WM_SYSCOMMAND, SC_CLOSE, 0);

			ImGui::PopStyleColor(4);

			auto name_text_size = ImGui::CalcTextSize(name);

			ImGui::GetWindowDrawList()->AddText(ImVec2(fixed_cursor_position.x + 10.f, fixed_cursor_position.y + size.y * .5f - name_text_size.y * .5f - 1.f), ImGui::ColorConvertFloat4ToU32(ImVec4(.35f, .35f, .8f, 1.f)), name);

			auto status_text_size = ImGui::CalcTextSize(status);

			ImGui::GetWindowDrawList()->AddText(
				ImVec2(fixed_cursor_position.x + 10.f + name_text_size.x + 5.f, fixed_cursor_position.y + size.y * .5f - status_text_size.y * .5f - 1.f), ImGui::ColorConvertFloat4ToU32(ImGui::GetStyleColorVec4(ImGuiCol_Text)), status);

			auto mayor_version_text_size = ImGui::CalcTextSize(mayor_version);

			ImGui::GetWindowDrawList()->AddText(
				ImVec2(fixed_cursor_position.x + 10.f + name_text_size.x + 5.f + status_text_size.x + 5.f, fixed_cursor_position.y + size.y * .5f - mayor_version_text_size.y * .5f - 1.f),
				ImGui::ColorConvertFloat4ToU32(ImVec4(.35f, .35f, .8f, 1.f)),
				mayor_version
			);

			auto dot_text_size = ImGui::CalcTextSize(XOR("."));

			ImGui::GetWindowDrawList()->AddText(
				ImVec2(fixed_cursor_position.x + 10.f + name_text_size.x + 5.f + status_text_size.x + 5.f + mayor_version_text_size.x, fixed_cursor_position.y + size.y * .5f - dot_text_size.y * .5f - 1.f),
				ImGui::ColorConvertFloat4ToU32(ImGui::GetStyleColorVec4(ImGuiCol_Text)),
				XOR(".")
			);

			ImGui::GetWindowDrawList()->AddText(
				ImVec2(fixed_cursor_position.x + 10.f + name_text_size.x + 5.f + status_text_size.x + 5.f + mayor_version_text_size.x + dot_text_size.x, fixed_cursor_position.y + size.y * .5f - ImGui::CalcTextSize(minor_version).y * .5f - 1.f),
				ImGui::ColorConvertFloat4ToU32(ImVec4(.35f, .35f, .8f, 1.f)),
				minor_version
			);

			auto minimize_text_size = ImGui::CalcTextSize(XOR("-"));
			
			ImGui::GetWindowDrawList()->AddText(
				ImVec2(fixed_cursor_position.x + window_size.x - 40.f * 2.f + 40.f * .5f - minimize_text_size.x * .5f, fixed_cursor_position.y + size.y * .5f - minimize_text_size.y * .5f - 2.f),
				ImGui::ColorConvertFloat4ToU32(ImGui::GetStyleColorVec4(ImGuiCol_Text)),
				XOR("~")
			);

			auto close_text_size = ImGui::CalcTextSize(XOR("x"));

			ImGui::GetWindowDrawList()->AddText(
				ImVec2(fixed_cursor_position.x + window_size.x - 40.f + 40.f * .5f - close_text_size.x * .5f, fixed_cursor_position.y + size.y * .5f - close_text_size.y * .5f - 2.f),
				ImGui::ColorConvertFloat4ToU32(ImVec4(.35f, .35f, .8f, 1.f)),
				XOR("x")
			);

			ImGui::End();
		}
		
		ImGui::PopStyleColor(3);
		
		ImGui::PopStyleVar(2);

		return result;
	}

	auto initialize_process_picker_window(ImVec2 position, ImVec2 size) -> bool
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);

		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(.55f, .55f, .55f, 1.f));

		ImGui::SetNextWindowPos(position);

		ImGui::SetNextWindowSize(size);

		return ImGui::Begin(XOR("process_picker_window"), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoNav);
	}

	auto uninitialize_process_picker_window() -> void
	{
		ImGui::End();
	
		ImGui::PopStyleColor(1);

		ImGui::PopStyleVar(2);
	}

	auto initialize_module_window(ImVec2 position, ImVec2 size) -> bool
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(25.f, 25.f));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(5.f, 5.f));

		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(.55f, .55f, .55f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(.1f, .1f, .1f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(.2f, .2f, .2f, 1.f));

		ImGui::SetNextWindowPos(position);

		ImGui::SetNextWindowSize(size);

		return ImGui::Begin(XOR("module_window"), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoNav);
	}

	auto uninitialize_module_window() -> void
	{
		ImGui::End();			

		ImGui::PopStyleColor(3);

		ImGui::PopStyleVar(2);
	}

	struct __button
	{
		char* name = nullptr;
		float current_alpha = 0.f;
		float desired_alpha = 0.f;
	};

	inline auto button(imgui::__button& button, ImVec2 size) -> bool
	{
		auto result = false;

		auto window_position = ImGui::GetWindowPos(), cursor_position = ImGui::GetCursorPos(), fixed_cursor_position = ImVec2(window_position.x + cursor_position.x, window_position.y + cursor_position.y);

		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(.0f, .0f, .0f, .0f));
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(.0f, .0f, .0f, .0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(.0f, .0f, .0f, .0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(.0f, .0f, .0f, .0f));

		result = ImGui::Button(button.name, ImVec2(size.x, size.y));

		ImGui::PopStyleColor(4);

		button.current_alpha += ((button.desired_alpha = (ImGui::IsItemActive() ? .8f : (ImGui::IsItemHovered() ? 1.f : .6f))) - button.current_alpha) * 40.f * ImGui::GetIO().DeltaTime * .25f;

		ImGui::GetWindowDrawList()->AddRect(fixed_cursor_position, { fixed_cursor_position.x + size.x, fixed_cursor_position.y + size.y }, ImGui::ColorConvertFloat4ToU32(ImVec4(.2f, .2f, .2f, 1.f)));

		ImGui::GetWindowDrawList()->AddRectFilled(
			{ fixed_cursor_position.x + 1.f, fixed_cursor_position.y + 1.f }, { fixed_cursor_position.x + size.x - 1.f, fixed_cursor_position.y + size.y - 1.f }, ImGui::ColorConvertFloat4ToU32(ImVec4(.1f, .1f, .1f, button.current_alpha)));

		auto name_text_size = ImGui::CalcTextSize(button.name);

		ImGui::GetWindowDrawList()->AddText(
			{ fixed_cursor_position.x + size.x * .5f - name_text_size.x * .5f, fixed_cursor_position.y + size.y * .5f - name_text_size.y * .5f - 1.f }, ImGui::ColorConvertFloat4ToU32(ImGui::GetStyleColorVec4(ImGuiCol_Text)), button.name);
	
		return result;
	}

	struct __category_selector
	{
		char* name = nullptr;
		std::vector<std::pair<char*, float>> categories;
		unsigned __int32 index = 0;
		float current_position = 0.f;
		float desired_position = 0.f;
	};

	inline auto category_selector(imgui::__category_selector& category_selector, ImVec2 position, ImVec2 size, ImVec2 button_size, unsigned __int32 direction) -> void
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.f);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.f, 0.f));

		ImGui::SetNextWindowPos(position);

		ImGui::SetNextWindowSize(size);

		if (ImGui::Begin(category_selector.name, nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoNav))
		{		
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.f, 0.f, 0.f, 0.f));
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 0.f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.f, 0.f, 0.f, 0.f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.f, 0.f, 0.f, 0.f));

			auto io = ImGui::GetIO();

			for (unsigned __int32 x = 0; x < category_selector.categories.size(); ++x)
			{
				auto window_position = ImGui::GetWindowPos(), cursor_position = ImGui::GetCursorPos(), fixed_cursor_position = ImVec2(window_position.x + cursor_position.x, window_position.y + cursor_position.y);

				if (ImGui::Button(category_selector.categories[x].first, button_size))
				{
					category_selector.index = x;

					category_selector.desired_position = (direction == 0 ? button_size.x : button_size.y) * (float)category_selector.index;
				}

				category_selector.categories[x].second += ((category_selector.index == x ? 1.f : (ImGui::IsItemActive() ? .8f : (ImGui::IsItemHovered() ? 1.f : .6f))) - category_selector.categories[x].second) * 40.f * io.DeltaTime * .25f;

				auto name_text_size = ImGui::CalcTextSize(category_selector.categories[x].first);

				ImGui::GetWindowDrawList()->AddText(
					{ fixed_cursor_position.x + button_size.x * .5f - name_text_size.x * .5f, fixed_cursor_position.y + button_size.y * .5f - name_text_size.y * .5f },
					ImGui::ColorConvertFloat4ToU32(ImVec4(.55f, .55f, .55f, category_selector.categories[x].second)),
					category_selector.categories[x].first
				);

				if (direction == 0)
					ImGui::SameLine();
			}

			ImGui::PopStyleColor(4);

			category_selector.current_position += (category_selector.desired_position - category_selector.current_position) * 40.f * io.DeltaTime * .25f;

			if (direction == 0)
			{
				ImGui::GetForegroundDrawList()->AddLine(
					ImVec2(position.x + category_selector.current_position + button_size.x * .1f, position.y + button_size.y),
					ImVec2(position.x + category_selector.current_position + button_size.x - button_size.x * .1f, position.y + button_size.y),
					ImGui::ColorConvertFloat4ToU32({ .3f, .3f, .85f, 1.f })
				);
			}

			if (direction == 1)
			{
				ImGui::GetForegroundDrawList()->AddLine(
					ImVec2(position.x + button_size.x, position.y + category_selector.current_position + button_size.y * .2f),
					ImVec2(position.x + button_size.x, position.y + category_selector.current_position + button_size.y - button_size.y * .2f),
					ImGui::ColorConvertFloat4ToU32({ .3f, .3f, .85f, 1.f })
				);
			}

			ImGui::End();
		}

		ImGui::PopStyleVar(4);
	}

	struct __toggle_button
	{
		char* name = nullptr;
		bool* value = nullptr;
		float current_alpha = 0.f;
		float desired_alpha = 0.f;
		float current_background_alpha = 0.f;
		float desired_background_alpha = 0.f;
		bool linked_with_binds_thread = false;
		bool was_bind_pressed = false;
		__int32 bind = -1;
		imgui::__button button;
	};
	
	inline auto toggle_buttons = std::vector<imgui::__toggle_button*>();

	inline auto toggle_button(imgui::__toggle_button& toggle_button, ImVec2 size) -> void
	{
		auto window_position = ImGui::GetWindowPos(), cursor_position = ImGui::GetCursorPos(), fixed_cursor_position = ImVec2(window_position.x + cursor_position.x, window_position.y + cursor_position.y);

		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(.0f, .0f, .0f, .0f));
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(.0f, .0f, .0f, .0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(.0f, .0f, .0f, .0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(.0f, .0f, .0f, .0f));

		if (ImGui::Button(toggle_button.name, ImVec2(size.x, size.y)))
			*toggle_button.value = !*toggle_button.value;

		ImGui::PopStyleColor(4);

		auto io = ImGui::GetIO();

		toggle_button.current_alpha += ((toggle_button.desired_alpha = *toggle_button.value ? 1.f : 0.f) - toggle_button.current_alpha) * 40.f * io.DeltaTime * .25f;

		toggle_button.current_background_alpha += ((toggle_button.desired_background_alpha = ImGui::IsItemActive() ? .8f : ImGui::IsItemHovered() ? 1.f : .6f) - toggle_button.current_background_alpha) * 40.f * io.DeltaTime * .25f;

		ImGui::GetWindowDrawList()->AddRect(fixed_cursor_position, { fixed_cursor_position.x + size.x, fixed_cursor_position.y + size.y }, ImGui::ColorConvertFloat4ToU32(ImVec4(.2f, .2f, .2f, 1.f)));
		
		ImGui::GetWindowDrawList()->AddRectFilled(
			{ fixed_cursor_position.x + 1.f, fixed_cursor_position.y + 1.f }, { fixed_cursor_position.x + size.x - 1.f, fixed_cursor_position.y + size.y - 1.f },
			ImGui::ColorConvertFloat4ToU32(ImVec4(.15f, .15f, .15f, toggle_button.current_background_alpha))
		);

		ImGui::GetWindowDrawList()->AddRectFilled(
			{ fixed_cursor_position.x + (toggle_button.current_alpha * (size.x - size.y)) + 2.f, fixed_cursor_position.y + 2.f },
			{ fixed_cursor_position.x + size.y + (toggle_button.current_alpha * (size.x - size.y)) - 2.f, fixed_cursor_position.y + size.y - 2.f },
			ImGui::ColorConvertFloat4ToU32(ImVec4(.3f, .3f, .85f, toggle_button.current_alpha + .4f))
		);

		ImGui::SameLine();

		if (!toggle_button.linked_with_binds_thread)
		{
			imgui::toggle_buttons.push_back(&toggle_button);

			static auto create_binds_thread = []() -> __int32
			{
				void* thread_handle = nullptr;

				return sdk::nt_create_thread_ex(&thread_handle, THREAD_ALL_ACCESS, CURRENT_PROCESS_HANDLE, +[]() -> __int32
					{
						for (;; sdk::nt_delay_execution(10))
						{
							for (auto& toggle_button : imgui::toggle_buttons)
							{
								auto is_bind_pressed = (sdk::nt_user_get_async_key_state(toggle_button->bind) & 0x8000) != 0;

								if (is_bind_pressed && !toggle_button->was_bind_pressed)
									*toggle_button->value = !*toggle_button->value;

								toggle_button->was_bind_pressed = is_bind_pressed;
							}
						}
					},
					nullptr, THREAD_CREATE_FLAGS_BYPASS_DEBUGGER | THREAD_CREATE_FLAGS_BYPASS_PROCESS_FREEZE
				);
			}();

			toggle_button.linked_with_binds_thread = true;
		}

		auto fixed_bind_name = sdk::__multibyte_string();

		if (toggle_button.bind == -1)
			fixed_bind_name = XOR("CLICK TO BIND");
		
		else if (toggle_button.bind == -2)
		{
			fixed_bind_name = XOR("...");
		
			for (unsigned __int32 x = 3; x < 256 && toggle_button.bind == -2; ++x)
			{
				if ((sdk::nt_user_get_async_key_state(x) & 0x8000) != 0)
				{
					if (x == VK_ESCAPE)
						toggle_button.bind = -1;

					else
					{
						toggle_button.was_bind_pressed = true;
						toggle_button.bind = x;
					}
				}
			}
		}

		else if (toggle_button.bind > 2)
		{
			auto bind_name = sdk::__multibyte_string();

			if (GetKeyNameTextA((MapVirtualKeyA(toggle_button.bind, 4) << 16), bind_name.get_multibyte_string(), bind_name.get_size()) != 0 && sdk::__multibyte_string::is_valid(bind_name))
				fixed_bind_name.concatenate(bind_name.get_multibyte_string());
			
			else
				fixed_bind_name.concatenate(XOR("UNNAMED KEY"));
		}

		toggle_button.button.name = fixed_bind_name.get_multibyte_string();

		auto fixed_bind_name_text_size = ImGui::CalcTextSize(fixed_bind_name.get_multibyte_string());

		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetWindowSize().x - cursor_position.x * 2 - fixed_bind_name_text_size.x - 20.f - size.x - 5.f);

		if (imgui::button(toggle_button.button, ImVec2(fixed_bind_name_text_size.x + 20.f, size.y)))
			toggle_button.bind = -2;
	}

	struct __slider
	{
		char* name = nullptr;
		double* value = nullptr;
		float current_alpha = 0.f;
		float desired_alpha = 0.f;
		float current_position = 0.f;
		float desired_position = 0.f;
	};

	inline auto slider(imgui::__slider& slider, double minimun_value, double maximun_value) -> void
	{
		auto window_position = ImGui::GetWindowPos(),
			initial_cursor_position = ImGui::GetCursorPos(), cursor_position = initial_cursor_position, fixed_cursor_position = ImVec2(window_position.x + cursor_position.x, window_position.y + cursor_position.y);

		auto fixed_to_string = [](float _Val) -> sdk::__multibyte_string
		{
			const auto _Len = static_cast<size_t>(_CSTD _scprintf(XOR("%.2f"), _Val));

			auto _Str = sdk::__multibyte_string();

			sprintf_s(_Str.get_multibyte_string(), _Len + 1, XOR("%.2f"), _Val);
			
			return _Str;
		};

		auto fixed_slider_name = sdk::__multibyte_string(slider.name);

		ImGui::GetWindowDrawList()->AddText(
			{ fixed_cursor_position.x, fixed_cursor_position.y + 24.f * .5f - ImGui::CalcTextSize(fixed_slider_name.get_multibyte_string()).y * .5f - 1.f },
			ImGui::ColorConvertFloat4ToU32(ImGui::GetStyleColorVec4(ImGuiCol_Text)),
			fixed_slider_name.get_multibyte_string()
		);

		auto widget_max_position = ImGui::GetWindowSize().x - cursor_position.x * 2;

		cursor_position.x += widget_max_position - 300.f;
		fixed_cursor_position.x += widget_max_position - 300.f;

		ImGui::SetCursorPosX(cursor_position.x);

		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(.0f, .0f, .0f, .0f));
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(.0f, .0f, .0f, .0f));
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(.0f, .0f, .0f, .0f));
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(.0f, .0f, .0f, .0f));
		ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(.0f, .0f, .0f, .0f));
		ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(.0f, .0f, .0f, .0f));

		auto fixed_name = sdk::__multibyte_string(XOR("##"));

		fixed_name.concatenate(slider.name);

		auto value = (float)*slider.value;

		if (value < minimun_value)
			value = minimun_value;

		if (value > maximun_value)
			value = maximun_value;

		ImGui::SetNextItemWidth(300.f);

		ImGui::SliderFloat(fixed_name.get_multibyte_string(), &value, (float)minimun_value, (float)maximun_value, XOR("%.2f"), ImGuiSliderFlags_AlwaysClamp | ImGuiSliderFlags_NoInput);
	
		ImGui::PopStyleColor(6);

		*slider.value = (double)value;

		auto io = ImGui::GetIO();

		slider.current_alpha += ((slider.desired_alpha = ImGui::IsItemActive() ? .8f : ImGui::IsItemHovered() ? 1.f : .6f) - slider.current_alpha) * 40.f * io.DeltaTime * .25f;

		slider.current_position += ((slider.desired_position = (300.f - 4.f) * ((*slider.value - minimun_value) / (maximun_value - minimun_value))) - slider.current_position) * 40.f * io.DeltaTime * .25f;

		auto item_rect_size = ImGui::GetItemRectSize();

		ImGui::GetWindowDrawList()->AddRect(fixed_cursor_position, { fixed_cursor_position.x + 300.f, fixed_cursor_position.y + item_rect_size.y }, ImGui::ColorConvertFloat4ToU32(ImVec4(.2f, .2f, .2f, 1.f)));

		ImGui::GetWindowDrawList()->AddRectFilled(
			{ fixed_cursor_position.x + 1.f, fixed_cursor_position.y + 1.f }, { fixed_cursor_position.x + 300.f - 1.f, fixed_cursor_position.y + item_rect_size.y - 1.f }, ImGui::ColorConvertFloat4ToU32(ImVec4(.15f, .15f, .15f, slider.current_alpha)));
		
		ImGui::GetWindowDrawList()->AddRectFilled(
			{ fixed_cursor_position.x + 2.f, fixed_cursor_position.y + 2.f }, { fixed_cursor_position.x + 2.f + slider.current_position, fixed_cursor_position.y + item_rect_size.y - 2.f }, ImGui::ColorConvertFloat4ToU32(ImVec4(.3f, .3f, .85f, 1.f)));
	
		auto fixed_value = sdk::__multibyte_string(fixed_to_string(*slider.value).get_multibyte_string());

		auto fixed_value_text_size = ImGui::CalcTextSize(fixed_value.get_multibyte_string());

		auto fixed_value_cursor_position = fixed_cursor_position.x + slider.current_position + 6.f;

		if (fixed_value_cursor_position > fixed_cursor_position.x + 300.f - fixed_value_text_size.x - 6.f)
			fixed_value_cursor_position = fixed_cursor_position.x + 300.f - fixed_value_text_size.x - 6.f;

		ImGui::GetWindowDrawList()->AddText(
			{ fixed_value_cursor_position, fixed_cursor_position.y + 24.f * .5f - fixed_value_text_size.y * .5f - 2.f }, ImGui::ColorConvertFloat4ToU32(ImGui::GetStyleColorVec4(ImGuiCol_Text)), fixed_value.get_multibyte_string());
	}

	struct __check_box
	{
		char* name = nullptr;
		bool* value = nullptr;
		float current_alpha = 0.f;
		float desired_alpha = 0.f;
		float current_background_alpha = 0.f;
		float desired_background_alpha = 0.f;
	};

	inline auto check_box(imgui::__check_box& check_box, ImVec2 size) -> void
	{
		auto window_position = ImGui::GetWindowPos(),
			initial_cursor_position = ImGui::GetCursorPos(), cursor_position = initial_cursor_position, fixed_cursor_position = ImVec2(window_position.x + cursor_position.x, window_position.y + cursor_position.y);

		ImGui::GetWindowDrawList()->AddText(
			{ fixed_cursor_position.x, fixed_cursor_position.y + size.y * .5f - ImGui::CalcTextSize(check_box.name).y * .5f - 1.f }, ImGui::ColorConvertFloat4ToU32(ImGui::GetStyleColorVec4(ImGuiCol_Text)), check_box.name);

		auto widget_max_position = ImGui::GetWindowSize().x - cursor_position.x * 2;

		cursor_position.x += widget_max_position - size.x;
		fixed_cursor_position.x += widget_max_position - size.x;

		ImGui::SetCursorPosX(cursor_position.x);

		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(.0f, .0f, .0f, .0f));
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(.0f, .0f, .0f, .0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(.0f, .0f, .0f, .0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(.0f, .0f, .0f, .0f));

		if (ImGui::Button(check_box.name, ImVec2(size.x, size.y)))
			*check_box.value = !*check_box.value;

		ImGui::PopStyleColor(4);

		auto io = ImGui::GetIO();

		check_box.current_alpha += ((check_box.desired_alpha = *check_box.value ? 1.f : 0.f) - check_box.current_alpha) * 40.f * io.DeltaTime * .25f;

		check_box.current_background_alpha += ((check_box.desired_background_alpha = (ImGui::IsItemActive() ? .8f : (ImGui::IsItemHovered() ? 1.f : .6f))) - check_box.current_background_alpha) * 40.f * io.DeltaTime * .25f;

		ImGui::GetWindowDrawList()->AddRect(fixed_cursor_position, { fixed_cursor_position.x + size.x, fixed_cursor_position.y + size.y }, ImGui::ColorConvertFloat4ToU32(ImVec4(.2f, .2f, .2f, 1.f)));

		ImGui::GetWindowDrawList()->AddRectFilled(
			{ fixed_cursor_position.x + 1.f, fixed_cursor_position.y + 1.f },
			{ fixed_cursor_position.x + size.x - 1.f, fixed_cursor_position.y + size.y - 1.f },
			ImGui::ColorConvertFloat4ToU32(ImVec4(.15f, .15f, .15f, check_box.current_background_alpha))
		);

		ImGui::GetWindowDrawList()->AddRectFilled(
			{ fixed_cursor_position.x + 2.f, fixed_cursor_position.y + 2.f }, { fixed_cursor_position.x + size.x - 2.f, fixed_cursor_position.y + size.y - 2.f }, ImGui::ColorConvertFloat4ToU32(ImVec4(.3f, .3f, .85f, check_box.current_alpha)));
	}

	struct __vec4
	{
		double x = 0., y = 0., z = 0., a = 0.;
	};

	struct __color_picker
	{
		char* name = nullptr;
		imgui::__vec4* value = nullptr;
		bool pop_up_opened = false;
		float current_alpha = 0.f;
		float desired_alpha = 0.f;
		float current_background_alpha = 1.f;
		float desired_background_alpha = 1.f;
	};

	inline auto color_picker(imgui::__color_picker& color_picker, ImVec2 size) -> void
	{
		auto window_position = ImGui::GetWindowPos(),
			initial_cursor_position = ImGui::GetCursorPos(), cursor_position = initial_cursor_position, fixed_cursor_position = ImVec2(window_position.x + cursor_position.x, window_position.y + cursor_position.y);

		ImGui::GetWindowDrawList()->AddText(
			{ fixed_cursor_position.x, fixed_cursor_position.y + size.y * .5f - ImGui::CalcTextSize(color_picker.name).y * .5f - 1.f }, ImGui::ColorConvertFloat4ToU32(ImGui::GetStyleColorVec4(ImGuiCol_Text)), color_picker.name);

		auto widget_max_position = ImGui::GetWindowSize().x - cursor_position.x * 2;

		cursor_position.x += widget_max_position - size.x;
		fixed_cursor_position.x += widget_max_position - size.x;

		ImGui::SetCursorPosX(cursor_position.x);

		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(.0f, .0f, .0f, .0f));
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(.0f, .0f, .0f, .0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(.0f, .0f, .0f, .0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(.0f, .0f, .0f, .0f));

		if (ImGui::Button(color_picker.name, ImVec2(size.x, size.y)))
			color_picker.pop_up_opened = !color_picker.pop_up_opened;
		
		ImGui::PopStyleColor(4);

		auto io = ImGui::GetIO();

		color_picker.current_alpha += (color_picker.desired_alpha - color_picker.current_alpha) * 40.f * io.DeltaTime * .25f;

		color_picker.current_background_alpha += ((color_picker.desired_background_alpha = (ImGui::IsItemActive() ? .8f : (ImGui::IsItemHovered() ? 1.f : .6f))) - color_picker.current_background_alpha) * 40.f * io.DeltaTime * .25f;

		ImGui::GetWindowDrawList()->AddRect(fixed_cursor_position, { fixed_cursor_position.x + size.x, fixed_cursor_position.y + size.y }, ImGui::ColorConvertFloat4ToU32(ImVec4(.2f, .2f, .2f, 1.f)));

		ImGui::GetWindowDrawList()->AddRectFilled(
			{ fixed_cursor_position.x + 2.f, fixed_cursor_position.y + 2.f }, { fixed_cursor_position.x + size.x - 2.f, fixed_cursor_position.y + size.y - 2.f },
			ImGui::ColorConvertFloat4ToU32(ImVec4((float)color_picker.value->x, (float)color_picker.value->y, (float)color_picker.value->z, (float)color_picker.value->a * color_picker.current_background_alpha))
		);

		if (color_picker.pop_up_opened)
		{
			ImGui::OpenPopup(XOR("color_picker_pop_up"), ImGuiPopupFlags_NoOpenOverExistingPopup);

			if (color_picker.pop_up_opened)
			{
				ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(.1f, .1f, .1f, 1.f));
				//ImGui::PushStyleColor(ImGuiCol_ModalWindowDimBg, ImVec4(.1f, .1f, .1f, .3f));

				//ImGui::PushStyleColor just won't work, idk why
				ImGui::GetStyle().Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(.1f, .1f, .1f, .5f);

				if (ImGui::BeginPopupModal(XOR("color_picker_pop_up"), &color_picker.pop_up_opened, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar))
				{
					float col[4] = { (float)color_picker.value->x, (float)color_picker.value->y, (float)color_picker.value->z, (float)color_picker.value->a };

					ImGui::SetNextItemWidth(300.f);

					ImGui::ColorPicker4(XOR("##color_picker"), col,
						ImGuiColorEditFlags_NoSmallPreview |
						ImGuiColorEditFlags_NoInputs |
						ImGuiColorEditFlags_NoTooltip |
						ImGuiColorEditFlags_NoLabel |
						ImGuiColorEditFlags_NoSidePreview |
						ImGuiColorEditFlags_NoBorder |
						ImGuiColorEditFlags_AlphaBar |
						ImGuiColorEditFlags_AlphaPreviewHalf
					);

					color_picker.value->x = (double)col[0];
					color_picker.value->y = (double)col[1];
					color_picker.value->z = (double)col[2];
					color_picker.value->a = (double)col[3];

					if ((sdk::nt_user_get_async_key_state(VK_ESCAPE) & 0x8000) != 0 || (sdk::nt_user_get_async_key_state(VK_LBUTTON) & 0x8000) != 0 && !ImGui::IsItemHovered() && !ImGui::IsItemActive())
						color_picker.pop_up_opened = false;

					ImGui::EndPopup();
				}
			
				//ImGui::PopStyleColor(2);
				ImGui::PopStyleColor(1);
			}
		}
	}

	inline auto spacing() -> void
	{
		ImGui::Spacing();
		
		auto window_position = ImGui::GetWindowPos(), cursor_position = ImGui::GetCursorPos(), fixed_cursor_position = ImVec2(window_position.x + cursor_position.x, window_position.y + cursor_position.y);

		ImGui::GetWindowDrawList()->AddLine(fixed_cursor_position, { fixed_cursor_position.x + ImGui::GetWindowSize().x - cursor_position.x * 2, fixed_cursor_position.y }, ImGui::ColorConvertFloat4ToU32(ImVec4(.2f, .2f, .2f, 1.f)));

		ImGui::SetCursorPosY(cursor_position.y + 1.f);

		ImGui::Spacing();
		ImGui::Spacing();
	}
}