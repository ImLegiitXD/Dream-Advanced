
#include "imgui/imgui_custom_widgets.hpp"

auto client::core::menu::initialize() -> __int32
{
	auto twcew = tagWNDCLASSEXW(sizeof(tagWNDCLASSEXW), 0, WndProc, 0, 0, nullptr, nullptr, nullptr, nullptr, nullptr, XOR(L"WorkerW"), nullptr);

	RegisterClassExW(&twcew);

	imgui::window_handle = CreateWindowExW(0, twcew.lpszClassName, XOR(L"Spotify"), WS_BORDER, 0, 0, (__int32)imgui::window_size.x, (__int32)imgui::window_size.y, nullptr, nullptr, twcew.hInstance, nullptr);

	if (!CreateDeviceD3D(imgui::window_handle))
	{
		CleanupDeviceD3D();

		UnregisterClassW(twcew.lpszClassName, twcew.hInstance);

		REPORT_EXIT_RETURN(1);
	}

	imgui::set_up_window();

	ShowWindow(imgui::window_handle, SW_SHOWNORMAL);

	UpdateWindow(imgui::window_handle);

	ImGui::CreateContext();

	auto& io = ImGui::GetIO();

	io.IniFilename = nullptr;
	io.LogFilename = nullptr;
	io.FontDefault = io.Fonts->AddFontFromMemoryCompressedTTF(ImGui::Fonts::verdana_compressed_data, ImGui::Fonts::verdana_compressed_size, 16.f);
	io.MouseDrawCursor = false;

	ImGui_ImplWin32_Init(imgui::window_handle);

	ImGui_ImplDX10_Init(g_pd3dDevice);

	for (client::core::menu::initialized = true; !imgui::uninitialize; sdk::nt_delay_execution(imgui::delay))
	{
		for (auto tm = tagMSG(); PeekMessageA(&tm, nullptr, 0, 0, PM_REMOVE);)
		{
			TranslateMessage(&tm);

			DispatchMessageA(&tm);

			if (tm.message == WM_QUIT)
				imgui::uninitialize = true;
		}

		if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
		{
			CleanupRenderTarget();

			g_pSwapChain->ResizeBuffers(0, g_ResizeWidth, g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0);

			g_ResizeWidth = g_ResizeHeight = 0;

			CreateRenderTarget();
		}

		ImGui_ImplDX10_NewFrame();

		ImGui_ImplWin32_NewFrame();

		ImGui::NewFrame();

		imgui::delay = (imgui::title_bar({ 0.f, 0.f }, { imgui::window_size.x, 40.f }, imgui::window_size, XOR("DREAM"), XOR("ADVANCED"), LOADER_MAYOR_VERSION, LOADER_MINOR_VERSION) ? 1 : 10);

		if (client::core::menu::target_process_identifier == 0)
		{
			if (imgui::initialize_process_picker_window({ imgui::window_size.x * .5f - 150.f, imgui::window_size.y * .5f - 20.f }, { 300.f, 40.f }))
			{
				auto get_target_process_name_indentifier = []() -> std::pair<sdk::__multibyte_string, unsigned __int64>
				{
					auto target_process_name_indentifier = std::pair<sdk::__multibyte_string, unsigned __int64>();

					unsigned __int32 window_handles_count = 0;

					if (sdk::nt_user_build_hwnd_list(window_handles_count, nullptr, &window_handles_count) != 0xc0000023 || window_handles_count == 0)
						REPORT_EXIT_RETURN({});

					auto window_handles = sdk::allocate_memory(window_handles_count * sizeof(HWND__*));

					if (sdk::nt_user_build_hwnd_list(window_handles_count, (void**)window_handles, &window_handles_count) != 0)
						REPORT_EXIT_RETURN({});

					for (unsigned __int32 x = 0; x < window_handles_count && target_process_name_indentifier.second == 0; ++x)
					{
						auto current_window_handle = ((HWND__**)window_handles)[x];

						auto window_class_name = sdk::__unicode_string();

						if (auto us = _UNICODE_STRING(0, (__int16)window_class_name.get_size(), window_class_name.get_unicode_string());
							sdk::nt_user_get_class_name(current_window_handle, &us) != 0 && sdk::__unicode_string::is_valid(window_class_name) && window_class_name.equals(XOR(L"LWJGL")))
						{
							if (auto window_title = sdk::__unicode_string();
								sdk::nt_user_internal_get_window_text(current_window_handle, window_title.get_unicode_string(), window_title.get_size() / 2) != 0 && sdk::__unicode_string::is_valid(window_title))
							{
								window_title.to_upper();

								target_process_name_indentifier.first = window_title.get_multibyte_string();
								target_process_name_indentifier.second = (unsigned __int64)sdk::nt_user_query_window(current_window_handle, 0);
							}
						}
					}

					sdk::free_memory(window_handles);

					return target_process_name_indentifier;
				};

				auto target_process_name_indentifier = get_target_process_name_indentifier();

				if (target_process_name_indentifier.second == 0)
				{
					static auto button_0 = imgui::__button();

					button_0.name = XOR("WAITING FOR TARGET PROCESS...");

					imgui::button(button_0, { 300.f, 40.f });
				}

				else
				{
					static auto button_1 = imgui::__button();

					button_1.name = target_process_name_indentifier.first.get_multibyte_string();

					if (imgui::button(button_1, { 300.f, 40.f }))
						client::core::menu::target_process_identifier = target_process_name_indentifier.second;
				}

				imgui::uninitialize_process_picker_window();
			}
		}

		else if (client::core::ipc::uninitialized)
		{
			static auto main_category_selector = imgui::__category_selector(XOR("MAIN"), { { XOR("COMBAT"), 0.f }, { XOR("VISUAL"), 0.f }, { XOR("UTIL"), 0.f }, { XOR("SETTINGS"), 0.f } });

			imgui::category_selector(main_category_selector, { 150.f, 40.f }, { 650.f, 45.f }, { 100.f, 45.f }, 0);

			if (main_category_selector.index == 0)
			{
				static auto sub_category_selector = imgui::__category_selector(XOR("SUB"),
					{ { XOR("AUTO CLICK"), 0.f }, { XOR("AIM ASSIST"), 0.f }, { XOR("REACH"), 0.f }, { XOR("VELOCITY"), 0.f }, { XOR("AUTO JUMP"), 0.f }, { XOR("FAKE LAG"), 0.f }, { XOR("BACKTRACK"), 0.f }, { XOR("WEAPONS"), 0.f } });

				imgui::category_selector(sub_category_selector, { 0.f, 85.f }, { 150.f, 615.f }, { 150.f, 45.f }, 1);

				if (imgui::initialize_module_window({ 150., 85.f }, { 600.f, 615.f }))
				{
					if (sub_category_selector.index == 0)
					{
						static auto toggle_button = imgui::__toggle_button(XOR("ENABLED"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::auto_click::enabled")));

						imgui::toggle_button(toggle_button, { 65.f, 25.f });

						imgui::spacing();

						static auto slider = imgui::__slider(XOR("CLICKS PER SECOND"), (double*)client::core::ipc::get_setting_address(XOR("client::features::combat::auto_click::clicks_per_second")));

						imgui::slider(slider, 5., 20.);

						imgui::spacing();

						static auto check_box_0 = imgui::__check_box(XOR("WHITELIST INVENTORIES"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::auto_click::whitelist_inventories")));

						imgui::check_box(check_box_0, { 25.f, 25.f });

						static auto check_box_1 = imgui::__check_box(XOR("WEAPONS ONLY"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::auto_click::weapons_only")));

						imgui::check_box(check_box_1, { 25.f, 25.f });

						static auto check_box_2 = imgui::__check_box(XOR("BREAK BLOCKS"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::auto_click::break_blocks")));

						imgui::check_box(check_box_2, { 25.f, 25.f });

						static auto check_box_3 = imgui::__check_box(XOR("ATTACKING ONLY"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::auto_click::attacking_only")));

						imgui::check_box(check_box_3, { 25.f, 25.f });

						if (*check_box_3.value)
						{
							static auto check_box_4 = imgui::__check_box(XOR("IGNORE NON VISIBLE PLAYERS"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::auto_click::ignore_non_visible_players")));

							imgui::check_box(check_box_4, { 25.f, 25.f });

							static auto check_box_5 = imgui::__check_box(XOR("IGNORE NAKED PLAYERS"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::auto_click::ignore_naked_players")));

							imgui::check_box(check_box_5, { 25.f, 25.f });
						}
					}

					if (sub_category_selector.index == 1)
					{
						static auto toggle_button = imgui::__toggle_button(XOR("ENABLED"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::aim_assist::enabled")));

						imgui::toggle_button(toggle_button, { 65.f, 25.f });

						imgui::spacing();

						static auto slider_0 = imgui::__slider(XOR("DISTANCE"), (double*)client::core::ipc::get_setting_address(XOR("client::features::combat::aim_assist::distance")));

						imgui::slider(slider_0, 1., 6.);

						static auto slider_1 = imgui::__slider(XOR("FOV"), (double*)client::core::ipc::get_setting_address(XOR("client::features::combat::aim_assist::fov")));

						imgui::slider(slider_1, 30., 180.);

						static auto slider_2 = imgui::__slider(XOR("SPEED"), (double*)client::core::ipc::get_setting_address(XOR("client::features::combat::aim_assist::speed")));

                        imgui::slider(slider_2, 10., 100.);

						imgui::spacing();

						static auto check_box_0 = imgui::__check_box(XOR("CLICKING ONLY"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::aim_assist::clicking_only")));

						imgui::check_box(check_box_0, { 25.f, 25.f });

						static auto check_box_1 = imgui::__check_box(XOR("WEAPONS ONLY"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::aim_assist::weapons_only")));

						imgui::check_box(check_box_1, { 25.f, 25.f });

						static auto check_box_2 = imgui::__check_box(XOR("BREAK BLOCKS"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::aim_assist::break_blocks")));

						imgui::check_box(check_box_2, { 25.f, 25.f });

						static auto check_box_3 = imgui::__check_box(XOR("IGNORE NON VISIBLE PLAYERS"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::aim_assist::ignore_non_visible_players")));

						imgui::check_box(check_box_3, { 25.f, 25.f });

						static auto check_box_4 = imgui::__check_box(XOR("IGNORE NAKED PLAYERS"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::aim_assist::ignore_naked_players")));

						imgui::check_box(check_box_4, { 25.f, 25.f });

						static auto check_box_5 = imgui::__check_box(XOR("LOCK TARGET"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::aim_assist::lock_target")));

						imgui::check_box(check_box_5, { 25.f, 25.f });

						static auto check_box_6 = imgui::__check_box(XOR("SILENT"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::aim_assist::silent")));

						imgui::check_box(check_box_6, { 25.f, 25.f });
					}

					if (sub_category_selector.index == 2)
					{
						static auto toggle_button = imgui::__toggle_button(XOR("ENABLED"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::reach::enabled")));

						imgui::toggle_button(toggle_button, { 65.f, 25.f });

						imgui::spacing();

						static auto slider = imgui::__slider(XOR("DISTANCE"), (double*)client::core::ipc::get_setting_address(XOR("client::features::combat::reach::distance")));

						imgui::slider(slider, 3., 6.);

						imgui::spacing();

						static auto check_box_0 = imgui::__check_box(XOR("WEAPONS ONLY"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::reach::weapons_only")));

						imgui::check_box(check_box_0, { 25.f, 25.f });

						static auto check_box_1 = imgui::__check_box(XOR("SPRINTING ONLY"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::reach::sprinting_only")));

						imgui::check_box(check_box_1, { 25.f, 25.f });

						static auto check_box_2 = imgui::__check_box(XOR("DISABLE IN LIQUIDS"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::reach::disable_in_liquids")));

						imgui::check_box(check_box_2, { 25.f, 25.f });

						static auto check_box_3 = imgui::__check_box(XOR("IGNORE NON VISIBLE PLAYERS"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::reach::ignore_non_visible_players")));

						imgui::check_box(check_box_3, { 25.f, 25.f });

						static auto check_box_4 = imgui::__check_box(XOR("IGNORE NAKED PLAYERS"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::reach::ignore_naked_players")));

						imgui::check_box(check_box_4, { 25.f, 25.f });

						static auto check_box_5 = imgui::__check_box(XOR("DRAW INTERCEPTION"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::reach::draw_interception")));

						imgui::check_box(check_box_5, { 25.f, 25.f });

						imgui::spacing();

						static auto color_picker = imgui::__color_picker(XOR("COLOR"), (imgui::__vec4*)client::core::ipc::get_setting_address(XOR("client::features::combat::reach::color")));

						imgui::color_picker(color_picker, { 65.f, 25.f });
					}

					if (sub_category_selector.index == 3)
					{
						static auto toggle_button = imgui::__toggle_button(XOR("ENABLED"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::velocity::enabled")));

						imgui::toggle_button(toggle_button, { 65.f, 25.f });

						imgui::spacing();

						static auto slider_0 = imgui::__slider(XOR("HORIZONTAL %"), (double*)client::core::ipc::get_setting_address(XOR("client::features::combat::velocity::horizontal_percentage")));

						imgui::slider(slider_0, 1., 100.);

						static auto slider_1 = imgui::__slider(XOR("VERTICAL %"), (double*)client::core::ipc::get_setting_address(XOR("client::features::combat::velocity::vertical_percentage")));

						imgui::slider(slider_1, 1., 100.);

						static auto slider_2 = imgui::__slider(XOR("DELAY"), (double*)client::core::ipc::get_setting_address(XOR("client::features::combat::velocity::delay")));

						imgui::slider(slider_2, 0., 5.);

						imgui::spacing();

						static auto check_box_0 = imgui::__check_box(XOR("CLICKING ONLY"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::velocity::clicking_only")));

						imgui::check_box(check_box_0, { 25.f, 25.f });

						static auto check_box_1 = imgui::__check_box(XOR("WEAPONS ONLY"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::velocity::weapons_only")));

						imgui::check_box(check_box_1, { 25.f, 25.f });

						static auto check_box_2 = imgui::__check_box(XOR("PUSH BACK"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::velocity::push_back")));

						imgui::check_box(check_box_2, { 25.f, 25.f });
					}

					if (sub_category_selector.index == 4)
					{
						static auto toggle_button = imgui::__toggle_button(XOR("ENABLED"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::auto_jump::enabled")));

						imgui::toggle_button(toggle_button, { 65.f, 25.f });

						imgui::spacing();

						static auto slider = imgui::__slider(XOR("CHANCE %"), (double*)client::core::ipc::get_setting_address(XOR("client::features::combat::auto_jump::chance_percentage")));

						imgui::slider(slider, 1., 100.);

						imgui::spacing();

						static auto check_box_0 = imgui::__check_box(XOR("CLICKING ONLY"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::auto_jump::clicking_only")));

						imgui::check_box(check_box_0, { 25.f, 25.f });

						static auto check_box_1 = imgui::__check_box(XOR("WEAPONS ONLY"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::auto_jump::weapons_only")));

						imgui::check_box(check_box_1, { 25.f, 25.f });
					}

					if (sub_category_selector.index == 5)
					{
						static auto toggle_button = imgui::__toggle_button(XOR("ENABLED"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::fake_lag::enabled")));

						imgui::toggle_button(toggle_button, { 65.f, 25.f });

						imgui::spacing();

						static auto slider_0 = imgui::__slider(XOR("DELAY"), (double*)client::core::ipc::get_setting_address(XOR("client::features::combat::fake_lag::delay")));

						imgui::slider(slider_0, 50., 5000.);

						static auto slider_1 = imgui::__slider(XOR("DISTANCE"), (double*)client::core::ipc::get_setting_address(XOR("client::features::combat::fake_lag::distance")));

						imgui::slider(slider_1, 1., 6.);

						imgui::spacing();

						static auto check_box_0 = imgui::__check_box(XOR("CLICKING ONLY"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::fake_lag::clicking_only")));

						imgui::check_box(check_box_0, { 25.f, 25.f });

						static auto check_box_1 = imgui::__check_box(XOR("WEAPONS ONLY"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::fake_lag::weapons_only")));

						imgui::check_box(check_box_1, { 25.f, 25.f });

						static auto check_box_2 = imgui::__check_box(XOR("RELEASE WHEN DISTANCING"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::fake_lag::release_when_distancing")));

						imgui::check_box(check_box_2, { 25.f, 25.f });

						static auto check_box_3 = imgui::__check_box(XOR("RELEASE WHEN ATTACKED"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::fake_lag::release_when_attacked")));

						imgui::check_box(check_box_3, { 25.f, 25.f });

						static auto check_box_4 = imgui::__check_box(XOR("RELEASE WHEN ATTACKING"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::fake_lag::release_when_attacking")));

						imgui::check_box(check_box_4, { 25.f, 25.f });

						static auto check_box_5 = imgui::__check_box(XOR("DRAW LAST SENT POSITION"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::fake_lag::draw_last_sent_position")));

						imgui::check_box(check_box_5, { 25.f, 25.f });

						imgui::spacing();

						static auto color_picker = imgui::__color_picker(XOR("COLOR"), (imgui::__vec4*)client::core::ipc::get_setting_address(XOR("client::features::combat::fake_lag::color")));

						imgui::color_picker(color_picker, { 65.f, 25.f });
					}

					if (sub_category_selector.index == 6)
					{
						static auto toggle_button = imgui::__toggle_button(XOR("ENABLED"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::backtrack::enabled")));

						imgui::toggle_button(toggle_button, { 65.f, 25.f });

						imgui::spacing();

						static auto slider = imgui::__slider(XOR("DELAY"), (double*)client::core::ipc::get_setting_address(XOR("client::features::combat::backtrack::delay")));

						imgui::slider(slider, 50., 1000.);
					}

					if (sub_category_selector.index == 7)
					{
						static auto check_box_0 = imgui::__check_box(XOR("SWORD"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::weapons::sword")));

						imgui::check_box(check_box_0, { 25.f, 25.f });

						static auto check_box_1 = imgui::__check_box(XOR("AXE"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::weapons::axe")));

						imgui::check_box(check_box_1, { 25.f, 25.f });

						static auto check_box_2 = imgui::__check_box(XOR("PICKAXE"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::weapons::pickaxe")));

						imgui::check_box(check_box_2, { 25.f, 25.f });

						static auto check_box_3 = imgui::__check_box(XOR("SHOVEL"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::weapons::shovel")));

						imgui::check_box(check_box_3, { 25.f, 25.f });
					}

					imgui::uninitialize_module_window();
				}
			}

			if (main_category_selector.index == 1)
			{
				static auto sub_category_selector = imgui::__category_selector(XOR("SUB"),
					{ { XOR("PLAYER ESP 2D"), 0.f }, { XOR("PLAYER ESP 3D"), 0.f }, { XOR("NAMETAGS"), 0.f }, { XOR("TRACERS"), 0.f }, { XOR("CHAMS"), 0.f }, { XOR("BLOCK ESP"), 0.f }, { XOR("ARRAY LIST"), 0.f } });

				imgui::category_selector(sub_category_selector, { 0.f, 85.f }, { 150.f, 615.f }, { 150.f, 45.f }, 1);

				if (imgui::initialize_module_window({ 150., 85.f }, { 600.f, 615.f }))
				{
					if (sub_category_selector.index == 0)
					{
						static auto toggle_button = imgui::__toggle_button(XOR("ENABLED"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::player_esp_2d::enabled")));

						imgui::toggle_button(toggle_button, { 65.f, 25.f });

						imgui::spacing();

						static auto check_box_0 = imgui::__check_box(XOR("DRAW HEALTH"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::player_esp_2d::draw_health")));

						imgui::check_box(check_box_0, { 25.f, 25.f });

						static auto check_box_1 = imgui::__check_box(XOR("DRAW CORNERS"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::player_esp_2d::draw_corners")));

						imgui::check_box(check_box_1, { 25.f, 25.f });

						static auto check_box_2 = imgui::__check_box(XOR("DRAW HURT TIME"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::player_esp_2d::draw_hurt_time")));

						imgui::check_box(check_box_2, { 25.f, 25.f });

						static auto check_box_3 = imgui::__check_box(XOR("DRAW INVISIBLE PLAYERS"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::player_esp_2d::draw_invisible_players")));

						imgui::check_box(check_box_3, { 25.f, 25.f });

						imgui::spacing();

						static auto color_picker_0 = imgui::__color_picker(XOR("OUTLINE COLOR"), (imgui::__vec4*)client::core::ipc::get_setting_address(XOR("client::features::visual::player_esp_2d::outline_color")));

						imgui::color_picker(color_picker_0, { 65.f, 25.f });

						static auto color_picker_1 = imgui::__color_picker(XOR("LINE COLOR"), (imgui::__vec4*)client::core::ipc::get_setting_address(XOR("client::features::visual::player_esp_2d::line_color")));

						imgui::color_picker(color_picker_1, { 65.f, 25.f });

						static auto color_picker_2 = imgui::__color_picker(XOR("FILL COLOR"), (imgui::__vec4*)client::core::ipc::get_setting_address(XOR("client::features::visual::player_esp_2d::fill_color")));

						imgui::color_picker(color_picker_2, { 65.f, 25.f });
					}

					if (sub_category_selector.index == 1)
					{
						static auto toggle_button = imgui::__toggle_button(XOR("ENABLED"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::player_esp_3d::enabled")));

						imgui::toggle_button(toggle_button, { 65.f, 25.f });

						imgui::spacing();

						static auto check_box_0 = imgui::__check_box(XOR("DRAW HEALTH"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::player_esp_3d::draw_health")));

						imgui::check_box(check_box_0, { 25.f, 25.f });

						static auto check_box_1 = imgui::__check_box(XOR("DRAW HURT TIME"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::player_esp_3d::draw_hurt_time")));

						imgui::check_box(check_box_1, { 25.f, 25.f });

						static auto check_box_2 = imgui::__check_box(XOR("DRAW INVISIBLE PLAYERS"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::player_esp_3d::draw_invisible_players")));

						imgui::check_box(check_box_2, { 25.f, 25.f });

						imgui::spacing();

						static auto color_picker = imgui::__color_picker(XOR("COLOR"), (imgui::__vec4*)client::core::ipc::get_setting_address(XOR("client::features::visual::player_esp_3d::color")));

						imgui::color_picker(color_picker, { 65.f, 25.f });
					}

					if (sub_category_selector.index == 2)
					{
						static auto toggle_button = imgui::__toggle_button(XOR("ENABLED"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::nametags::enabled")));

						imgui::toggle_button(toggle_button, { 65.f, 25.f });

						imgui::spacing();

						static auto check_box_0 = imgui::__check_box(XOR("DRAW DISTANCE"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::nametags::draw_distance")));

						imgui::check_box(check_box_0, { 25.f, 25.f });

						static auto check_box_1 = imgui::__check_box(XOR("DRAW HEALTH"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::nametags::draw_health")));

						imgui::check_box(check_box_1, { 25.f, 25.f });

						static auto check_box_2 = imgui::__check_box(XOR("DRAW HURT TIME"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::nametags::draw_hurt_time")));

						imgui::check_box(check_box_2, { 25.f, 25.f });

						static auto check_box_3 = imgui::__check_box(XOR("DRAW INVISIBLE PLAYERS"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::nametags::draw_invisible_players")));

						imgui::check_box(check_box_3, { 25.f, 25.f });

						imgui::spacing();

						static auto color_picker = imgui::__color_picker(XOR("COLOR"), (imgui::__vec4*)client::core::ipc::get_setting_address(XOR("client::features::visual::nametags::color")));

						imgui::color_picker(color_picker, { 65.f, 25.f });
					}

					if (sub_category_selector.index == 3)
					{
						static auto toggle_button = imgui::__toggle_button(XOR("ENABLED"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::tracers::enabled")));

						imgui::toggle_button(toggle_button, { 65.f, 25.f });

						imgui::spacing();

						static auto check_box_0 = imgui::__check_box(XOR("DRAW DISTANCE"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::tracers::draw_distance")));

						imgui::check_box(check_box_0, { 25.f, 25.f });

						static auto check_box_1 = imgui::__check_box(XOR("DRAW HURT TIME"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::tracers::draw_hurt_time")));

						imgui::check_box(check_box_1, { 25.f, 25.f });

						static auto check_box_2 = imgui::__check_box(XOR("DRAW INVISIBLE PLAYERS"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::tracers::draw_invisible_players")));

						imgui::check_box(check_box_2, { 25.f, 25.f });

						imgui::spacing();

						static auto color_picker = imgui::__color_picker(XOR("COLOR"), (imgui::__vec4*)client::core::ipc::get_setting_address(XOR("client::features::visual::tracers::color")));

						imgui::color_picker(color_picker, { 65.f, 25.f });
					}

					if (sub_category_selector.index == 4)
					{
						static auto toggle_button = imgui::__toggle_button(XOR("ENABLED"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::chams::enabled")));

						imgui::toggle_button(toggle_button, { 65.f, 25.f });

						imgui::spacing();

						static auto check_box_0 = imgui::__check_box(XOR("DRAW INVISIBLE PLAYERS"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::chams::draw_invisible_players")));

						imgui::check_box(check_box_0, { 25.f, 25.f });

						static auto check_box_1 = imgui::__check_box(XOR("CUSTOM COLOR"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::chams::custom_color")));

						imgui::check_box(check_box_1, { 25.f, 25.f });

						imgui::spacing();

						static auto color_picker = imgui::__color_picker(XOR("COLOR"), (imgui::__vec4*)client::core::ipc::get_setting_address(XOR("client::features::visual::chams::color")));

						imgui::color_picker(color_picker, { 65.f, 25.f });
					}

					if (sub_category_selector.index == 5)
					{
						static auto toggle_button = imgui::__toggle_button(XOR("ENABLED"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::block_esp::enabled")));

						imgui::toggle_button(toggle_button, { 65.f, 25.f });

						imgui::spacing();

						static auto check_box_0 = imgui::__check_box(XOR("DRAW DIAMOND"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::block_esp::draw_diamond")));

						imgui::check_box(check_box_0, { 25.f, 25.f });

						static auto check_box_1 = imgui::__check_box(XOR("DRAW EMERALD"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::block_esp::draw_emerald")));

						imgui::check_box(check_box_1, { 25.f, 25.f });

						static auto check_box_2 = imgui::__check_box(XOR("DRAW GOLD"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::block_esp::draw_gold")));

						imgui::check_box(check_box_2, { 25.f, 25.f });

						static auto check_box_3 = imgui::__check_box(XOR("DRAW IRON"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::block_esp::draw_iron")));

						imgui::check_box(check_box_3, { 25.f, 25.f });

						static auto check_box_4 = imgui::__check_box(XOR("DRAW LAPIS"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::block_esp::draw_lapis")));

						imgui::check_box(check_box_4, { 25.f, 25.f });

						static auto check_box_5 = imgui::__check_box(XOR("DRAW COAL"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::block_esp::draw_coal")));

						imgui::check_box(check_box_5, { 25.f, 25.f });

						static auto check_box_6 = imgui::__check_box(XOR("DRAW REDSTONE"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::block_esp::draw_redstone")));

						imgui::check_box(check_box_6, { 25.f, 25.f });

						static auto check_box_7 = imgui::__check_box(XOR("DRAW CHESTS"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::block_esp::draw_chests")));

						imgui::check_box(check_box_7, { 25.f, 25.f });
					}

					if (sub_category_selector.index == 6)
					{
						static auto toggle_button = imgui::__toggle_button(XOR("ENABLED"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::array_list::enabled")));

						imgui::toggle_button(toggle_button, { 65.f, 25.f });

						imgui::spacing();

						static auto check_box = imgui::__check_box(XOR("DRAW WATERMARK"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::array_list::draw_watermark")));

						imgui::check_box(check_box, { 25.f, 25.f });
					}

					imgui::uninitialize_module_window();
				}
			}

			if (main_category_selector.index == 2)
			{
				static auto sub_category_selector = imgui::__category_selector(XOR("SUB"), { { XOR("BRIDGE ASSIST"), 0.f }, { XOR("SPRINT"), 0.f }, { XOR("FAST PLACE"), 0.f }, { XOR("SPEED"), 0.f } });

				imgui::category_selector(sub_category_selector, { 0.f, 85.f }, { 150.f, 615.f }, { 150.f, 45.f }, 1);

				if (imgui::initialize_module_window({ 150., 85.f }, { 600.f, 615.f }))
				{
					if (sub_category_selector.index == 0)
					{
						static auto toggle_button = imgui::__toggle_button(XOR("ENABLED"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::util::bridge_assist::enabled")));

						imgui::toggle_button(toggle_button, { 65.f, 25.f });

						imgui::spacing();

						static auto check_box_0 = imgui::__check_box(XOR("PITCH CHECK"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::util::bridge_assist::pitch_check")));

						imgui::check_box(check_box_0, { 25.f, 25.f });

						static auto check_box_1 = imgui::__check_box(XOR("BLOCKS ONLY"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::util::bridge_assist::blocks_only")));

						imgui::check_box(check_box_1, { 25.f, 25.f });
					}

					if (sub_category_selector.index == 1)
					{
						static auto toggle_button = imgui::__toggle_button(XOR("ENABLED"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::util::sprint::enabled")));

						imgui::toggle_button(toggle_button, { 65.f, 25.f });
					}

					if (sub_category_selector.index == 2)
					{
						static auto toggle_button = imgui::__toggle_button(XOR("ENABLED"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::util::fast_place::enabled")));

						imgui::toggle_button(toggle_button, { 65.f, 25.f });

						imgui::spacing();

						static auto slider = imgui::__slider(XOR("DELAY"), (double*)client::core::ipc::get_setting_address(XOR("client::features::util::fast_place::delay")));

						imgui::slider(slider, 0., 5.);
					}

					if (sub_category_selector.index == 3)
					{
						static auto toggle_button = imgui::__toggle_button(XOR("ENABLED"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::util::speed::enabled")));

						imgui::toggle_button(toggle_button, { 65.f, 25.f });

						imgui::spacing();

						static auto slider_0 = imgui::__slider(XOR("GROUND SPEED"), (double*)client::core::ipc::get_setting_address(XOR("client::features::util::speed::speed_value_0")));

						imgui::slider(slider_0, 0., 5.);

						static auto slider_1 = imgui::__slider(XOR("AIR SPEED"), (double*)client::core::ipc::get_setting_address(XOR("client::features::util::speed::speed_value_1")));

						imgui::slider(slider_1, 0., 5.);

						imgui::spacing();

						static auto check_box_0 = imgui::__check_box(XOR("SLOW"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::util::speed::slow")));

						imgui::check_box(check_box_0, { 25.f, 25.f });

						static auto slider_2 = imgui::__slider(XOR("SLOW TICKS"), (double*)client::core::ipc::get_setting_address(XOR("client::features::util::speed::slow_ticks")));

						imgui::slider(slider_2, 0., 5.);

						static auto slider_3 = imgui::__slider(XOR("SLOW SPEED"), (double*)client::core::ipc::get_setting_address(XOR("client::features::util::speed::slow_value")));

						imgui::slider(slider_3, 0., 5.);

						imgui::spacing();

						static auto check_box_1 = imgui::__check_box(XOR("JUMP"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::util::speed::jump")));

						imgui::check_box(check_box_1, { 25.f, 25.f });

						static auto slider_4 = imgui::__slider(XOR("JUMP SPEED"), (double*)client::core::ipc::get_setting_address(XOR("client::features::util::speed::jump_value")));

						imgui::slider(slider_4, 0., 5.);

						imgui::spacing();

						static auto check_box_2 = imgui::__check_box(XOR("FALL"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::util::speed::fall")));

						imgui::check_box(check_box_2, { 25.f, 25.f });

						static auto slider_5 = imgui::__slider(XOR("FALL SPEED"), (double*)client::core::ipc::get_setting_address(XOR("client::features::util::speed::fall_value")));

						imgui::slider(slider_5, 0., 5.);
					}

					imgui::uninitialize_module_window();
				}
			}

			if (main_category_selector.index == 3)
			{
				static auto sub_category_selector = imgui::__category_selector(XOR("SUB"), { { XOR("GLOBAL"), 0.f }, { XOR("CONFIG"), 0.f } });

				imgui::category_selector(sub_category_selector, { 0.f, 85.f }, { 150.f, 615.f }, { 150.f, 45.f }, 1);

				if (imgui::initialize_module_window({ 150., 85.f }, { 600.f, 615.f }))
				{
					if (sub_category_selector.index == 0)
					{
						static auto check_box_0 = imgui::__check_box(XOR("IGNORE TEAMMATES"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::settings::ignore_teammates")));

						imgui::check_box(check_box_0, { 25.f, 25.f });

						static auto check_box_1 = imgui::__check_box(XOR("STREAM PROOF"), (bool*)client::core::ipc::get_setting_address(XOR("client::features::settings::use_opengl_32_swap_buffers")));

						imgui::check_box(check_box_1, { 25.f, 25.f });
					}

					if (sub_category_selector.index == 1)
					{

					}

					imgui::uninitialize_module_window();
				}
			}
		}

		ImGui::GetForegroundDrawList()->AddRect({ 0.f, 0.f }, imgui::window_size, ImGui::ColorConvertFloat4ToU32({ .2f, .2f, .2f, 1.f }));

		ImGui::Render();

		static float clear_color_with_alpha[] = { .12f, .12f, .12f, 1.f };

		g_pd3dDevice->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);

		g_pd3dDevice->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);

		ImGui_ImplDX10_RenderDrawData(ImGui::GetDrawData());

		g_pSwapChain->Present(0, 0);
	}

	ImGui_ImplDX10_Shutdown();

	ImGui_ImplWin32_Shutdown();

	ImGui::DestroyContext();

	CleanupDeviceD3D();

	DestroyWindow(imgui::window_handle);

	UnregisterClassW(twcew.lpszClassName, twcew.hInstance);

	for (client::core::menu::uninitialized = true; KERNEL_SYSTEM_TIME != 0; sdk::nt_delay_execution(100));

	REPORT_EXIT_RETURN(1);
}

auto client::core::menu::set_configuration() -> void
{
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::auto_click::enabled")) = false;
	*(double*)client::core::ipc::get_setting_address(XOR("client::features::combat::auto_click::clicks_per_second")) = 12.;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::auto_click::whitelist_inventories")) = true;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::auto_click::weapons_only")) = false;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::auto_click::break_blocks")) = false;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::auto_click::attacking_only")) = false;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::auto_click::ignore_non_visible_players")) = true;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::auto_click::ignore_naked_players")) = false;

	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::aim_assist::enabled")) = false;
	*(double*)client::core::ipc::get_setting_address(XOR("client::features::combat::aim_assist::distance")) = 6.;
	*(double*)client::core::ipc::get_setting_address(XOR("client::features::combat::aim_assist::fov")) = 180.;
	*(double*)client::core::ipc::get_setting_address(XOR("client::features::combat::aim_assist::speed")) = 80.;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::aim_assist::clicking_only")) = true;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::aim_assist::weapons_only")) = false;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::aim_assist::break_blocks")) = false;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::aim_assist::ignore_non_visible_players")) = true;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::aim_assist::ignore_naked_players")) = false;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::aim_assist::lock_target")) = true;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::aim_assist::silent")) = false;

	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::reach::enabled")) = false;
	*(double*)client::core::ipc::get_setting_address(XOR("client::features::combat::reach::distance")) = 3.05;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::reach::weapons_only")) = false;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::reach::sprinting_only")) = false;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::reach::disable_in_liquids")) = false;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::reach::ignore_non_visible_players")) = true;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::reach::ignore_naked_players")) = false;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::reach::draw_interception")) = true;
	*(imgui::__vec4*)client::core::ipc::get_setting_address(XOR("client::features::combat::reach::color")) = { .85f, .3f, .3f, .9f };

	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::velocity::enabled")) = false;
	*(double*)client::core::ipc::get_setting_address(XOR("client::features::combat::velocity::horizontal_percentage")) = 90.;
	*(double*)client::core::ipc::get_setting_address(XOR("client::features::combat::velocity::vertical_percentage")) = 100.;
	*(double*)client::core::ipc::get_setting_address(XOR("client::features::combat::velocity::delay")) = 1.;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::velocity::clicking_only")) = true;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::velocity::weapons_only")) = false;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::velocity::push_back")) = false;

	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::auto_jump::enabled")) = false;
	*(double*)client::core::ipc::get_setting_address(XOR("client::features::combat::auto_jump::chance_percentage")) = 80.;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::auto_jump::clicking_only")) = true;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::auto_jump::weapons_only")) = false;

	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::fake_lag::enabled")) = false;
	*(double*)client::core::ipc::get_setting_address(XOR("client::features::combat::fake_lag::delay")) = 450.;
	*(double*)client::core::ipc::get_setting_address(XOR("client::features::combat::fake_lag::distance")) = 6.;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::fake_lag::clicking_only")) = true;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::fake_lag::weapons_only")) = false;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::fake_lag::release_when_distancing")) = true;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::fake_lag::release_when_attacked")) = true;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::fake_lag::release_when_attacking")) = true;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::fake_lag::draw_last_sent_position")) = true;
	*(imgui::__vec4*)client::core::ipc::get_setting_address(XOR("client::features::combat::fake_lag::color")) = { .3f, .3f, .85f, .35f };

	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::backtrack::enabled")) = false;
	*(double*)client::core::ipc::get_setting_address(XOR("client::features::combat::backtrack::delay")) = 250.;

	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::weapons::sword")) = true;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::weapons::axe")) = true;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::weapons::pickaxe")) = false;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::combat::weapons::shovel")) = false;

	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::player_esp_2d::enabled")) = false;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::player_esp_2d::draw_health")) = false;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::player_esp_2d::draw_corners")) = false;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::player_esp_2d::draw_hurt_time")) = true;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::player_esp_2d::draw_invisible_players")) = false;
	*(imgui::__vec4*)client::core::ipc::get_setting_address(XOR("client::features::visual::player_esp_2d::outline_color")) = { .1f, .1f, .1f, .9f };
	*(imgui::__vec4*)client::core::ipc::get_setting_address(XOR("client::features::visual::player_esp_2d::line_color")) = { .3f, .3f, .85f, .9f };
	*(imgui::__vec4*)client::core::ipc::get_setting_address(XOR("client::features::visual::player_esp_2d::fill_color")) = { 0.f, 0.f, 0.f, .2f };

	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::player_esp_3d::enabled")) = false;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::player_esp_3d::draw_health")) = false;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::player_esp_3d::draw_hurt_time")) = true;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::player_esp_3d::draw_invisible_players")) = false;
	*(imgui::__vec4*)client::core::ipc::get_setting_address(XOR("client::features::visual::player_esp_3d::color")) = { .3f, .3f, .85f, .35f };

	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::nametags::enabled")) = false;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::nametags::draw_distance")) = false;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::nametags::draw_health")) = false;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::nametags::draw_hurt_time")) = true;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::nametags::draw_invisible_players")) = false;
	*(imgui::__vec4*)client::core::ipc::get_setting_address(XOR("client::features::visual::nametags::color")) = { .85f, .85f, .85f, .9f };

	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::tracers::enabled")) = false;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::tracers::draw_distance")) = false;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::tracers::draw_hurt_time")) = true;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::tracers::draw_invisible_players")) = false;
	*(imgui::__vec4*)client::core::ipc::get_setting_address(XOR("client::features::visual::tracers::color")) = { .3f, .3f, .85f, .9f };

	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::chams::enabled")) = false;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::chams::draw_invisible_players")) = false;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::chams::custom_color")) = true;
	*(imgui::__vec4*)client::core::ipc::get_setting_address(XOR("client::features::visual::chams::color")) = { .3f, .3f, .85f, .9f };

	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::block_esp::enabled")) = false;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::block_esp::draw_diamond")) = true;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::block_esp::draw_emerald")) = true;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::block_esp::draw_gold")) = true;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::block_esp::draw_iron")) = true;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::block_esp::draw_lapis")) = true;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::block_esp::draw_coal")) = true;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::block_esp::draw_redstone")) = true;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::block_esp::draw_chests")) = true;

	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::array_list::enabled")) = false;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::visual::array_list::draw_watermark")) = false;

	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::util::bridge_assist::enabled")) = false;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::util::bridge_assist::pitch_check")) = true;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::util::bridge_assist::blocks_only")) = true;

	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::util::sprint::enabled")) = false;

	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::util::fast_place::enabled")) = false;
	*(double*)client::core::ipc::get_setting_address(XOR("client::features::util::fast_place::delay")) = 1.;

	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::settings::ignore_teammates")) = true;
	*(bool*)client::core::ipc::get_setting_address(XOR("client::features::settings::use_opengl_32_swap_buffers")) = false;
}