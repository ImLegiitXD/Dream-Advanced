
#include "../features.hpp"

auto client::features::combat::auto_click::run(client::mapper::__minecraft& minecraft) -> void
{
	if (!client::features::combat::auto_click::enabled)
		return client::features::combat::auto_click::timer.update();

	if ((sdk::nt_user_get_async_key_state(VK_LBUTTON) & 0x8000) == 0 || (sdk::nt_user_get_async_key_state(VK_RBUTTON) & 0x8000) != 0)
		return client::features::combat::auto_click::timer.update();

	auto current_screen = minecraft.get_current_screen();

	auto is_in_inventory = (current_screen.object == nullptr ? false : current_screen.is_inventory_instance());

	if (is_in_inventory)
	{
		if (client::features::combat::auto_click::whitelist_inventories)
		{
			if ((sdk::nt_user_get_async_key_state(VK_LSHIFT) & 0x8000) == 0)
				return client::features::combat::auto_click::timer.update();
		}
	
		else
			return client::features::combat::auto_click::timer.update();
	}

	else if (current_screen.object != nullptr)
		return client::features::combat::auto_click::timer.update();

	auto local_player = minecraft.get_local_player();

	if (client::features::combat::auto_click::weapons_only && !is_in_inventory)
	{
		auto local_player_held_item_stack = local_player.get_held_item_stack();

		if (local_player_held_item_stack.object == nullptr)
			return client::features::combat::auto_click::timer.update();

		auto local_player_held_item = local_player_held_item_stack.get_item();

		if (local_player_held_item.object == nullptr)
			return client::features::combat::auto_click::timer.update();

		if (!((client::features::combat::weapons::sword && local_player_held_item.is_sword()) || (client::features::combat::weapons::axe && local_player_held_item.is_axe()) ||
			(client::features::combat::weapons::pickaxe && local_player_held_item.is_pickaxe()) || (client::features::combat::weapons::shovel && local_player_held_item.is_shovel())))
			return client::features::combat::auto_click::timer.update();
	}

	static auto last_message_sent = WM_LBUTTONUP;

	auto object_mouse_over = minecraft.get_object_mouse_over();

	if (client::features::combat::auto_click::break_blocks && object_mouse_over.object != nullptr && object_mouse_over.get_type_of_hit() == 1)
	{
		if (last_message_sent == WM_LBUTTONUP)
			PostMessageA((HWND__*)client::features::visual::window, (last_message_sent = (last_message_sent == WM_LBUTTONUP ? WM_LBUTTONDOWN : WM_LBUTTONUP)), VK_LBUTTON, 0);

		return client::features::combat::auto_click::timer.update();
	}

	if (client::features::combat::auto_click::attacking_only)
	{
		auto is_hittable_click = [&]() -> bool
		{
			auto timer_partial_ticks = minecraft.get_timer().get_partial_ticks();

			auto local_player_view_position = local_player.get_view_position(timer_partial_ticks);
			auto local_player_look_position = local_player.get_look_position(timer_partial_ticks);

			if (client::mapper::version != client::mapper::supported_versions::MINECRAFT_17)
				local_player_view_position.y += 1.62;

			auto local_player_view_vector = client::mapper::__vec3(
				local_player_view_position.x + local_player_look_position.x * (client::features::combat::reach::enabled ? client::features::combat::reach::distance : 3.),
				local_player_view_position.y + local_player_look_position.y * (client::features::combat::reach::enabled ? client::features::combat::reach::distance : 3.),
				local_player_view_position.z + local_player_look_position.z * (client::features::combat::reach::enabled ? client::features::combat::reach::distance : 3.)
			);

			for (auto& player : minecraft.get_world().get_players())
			{
				if (client::mapper::jni->IsSameObject(local_player.object, player.object))
					continue;

				if (client::features::combat::auto_click::ignore_non_visible_players && !local_player.can_entity_be_seen(player))
					continue;

				if (client::features::combat::auto_click::ignore_naked_players && player.get_total_armor_value() == 0)
					continue;


				if (!player.is_vulnerable())
					continue;

				auto player_bounding_box = player.get_bounding_box();

				if (player_bounding_box.object == nullptr)
					continue;

				auto player_bounding_box_bounds = player_bounding_box.get_bounds();

				player_bounding_box.set_bounds(
				{
					{ player_bounding_box_bounds.first.x - .1, player_bounding_box_bounds.first.y - .1, player_bounding_box_bounds.first.z - .1 },
					{ player_bounding_box_bounds.second.x + .1, player_bounding_box_bounds.second.y + .1, player_bounding_box_bounds.second.z + .1 }
				});

				auto player_bounding_box_interception = player_bounding_box.calculate_interception(local_player_view_position, local_player_view_vector);

				player_bounding_box.set_bounds(player_bounding_box_bounds);

				if (player_bounding_box_interception.object != nullptr)
					return true;
			}

			return false;
		};

		if (!is_hittable_click())
			return client::features::combat::auto_click::timer.update();
	}

	auto get_delay = [&]() -> double
	{
		static auto delay_minimum_maximum = client::mapper::__vec2(sdk::generate_random_value(15., 40.), sdk::generate_random_value(60., 85.));

		if (static auto sent_clicks = 0, max_sent_clicks = 50; sent_clicks++ > max_sent_clicks)
		{
			delay_minimum_maximum.x = sdk::generate_random_value(15., 40.);
			delay_minimum_maximum.y = sdk::generate_random_value(60., 85.);

			sent_clicks = 0, max_sent_clicks = (__int32)sdk::generate_random_value(30., 70.);
		}

		return sdk::generate_random_value(delay_minimum_maximum.x, delay_minimum_maximum.y) / (client::features::combat::auto_click::clicks_per_second / 10.);
	};

	if (static auto delay = get_delay(); client::features::combat::auto_click::timer.has_elapsed(delay))
	{
		delay = get_delay();

		PostMessageA((HWND__*)client::features::visual::window, (last_message_sent = (last_message_sent == WM_LBUTTONUP ? WM_LBUTTONDOWN : WM_LBUTTONUP)), VK_LBUTTON, 0);
	}
}