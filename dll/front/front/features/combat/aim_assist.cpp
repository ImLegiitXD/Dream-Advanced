
#include "../features.hpp"

auto client::features::combat::aim_assist::run(client::mapper::__minecraft& minecraft) -> void
{
	static auto last_aimed_player_name = sdk::__multibyte_string();

	if (client::features::combat::aim_assist::clicking_only && (sdk::nt_user_get_async_key_state(VK_LBUTTON) & 0x8000) == 0)
		return last_aimed_player_name.set(XOR(""));

	if (!client::features::combat::aim_assist::enabled)
		return last_aimed_player_name.set(XOR(""));

	if (minecraft.get_current_screen().object != nullptr)
		return last_aimed_player_name.set(XOR(""));

	auto timer = minecraft.get_timer();
	auto timer_partial_ticks = timer.get_partial_ticks();

	auto world = minecraft.get_world();
	auto world_players = world.get_players();

	auto local_player = minecraft.get_local_player();
	auto local_player_hurt_time = local_player.get_hurt_time();
	auto local_player_view_angles = local_player.get_view_angles();
	auto local_player_view_position = local_player.get_view_position(timer_partial_ticks);
	auto local_player_look_position = local_player.get_look_position(timer_partial_ticks);
	auto local_player_held_item_stack = local_player.get_held_item_stack();
	auto local_player_held_item = (local_player_held_item_stack.object == nullptr ? client::mapper::__item(nullptr) : local_player_held_item_stack.get_item());

	if (client::mapper::version != client::mapper::supported_versions::MINECRAFT_17)
		local_player_view_position.y += 1.62;

	auto local_player_view_vector = client::mapper::__vec3(
		local_player_view_position.x + local_player_look_position.x * (client::features::combat::reach::enabled ? client::features::combat::reach::distance : 3.),
		local_player_view_position.y + local_player_look_position.y * (client::features::combat::reach::enabled ? client::features::combat::reach::distance : 3.),
		local_player_view_position.z + local_player_look_position.z * (client::features::combat::reach::enabled ? client::features::combat::reach::distance : 3.)
	);

	if (client::features::combat::aim_assist::weapons_only)
	{
		if (local_player_held_item.object == nullptr)
			return;

		auto is_holding_weapon = false;

		if (client::features::combat::weapons::sword && local_player_held_item.is_sword())
			is_holding_weapon = true;

		if (client::features::combat::weapons::axe && local_player_held_item.is_axe())
			is_holding_weapon = true;

		if (client::features::combat::weapons::pickaxe && local_player_held_item.is_pickaxe())
			is_holding_weapon = true;

		if (client::features::combat::weapons::shovel && local_player_held_item.is_shovel())
			is_holding_weapon = true;

		if (!is_holding_weapon)
			return;
	}

	if (client::features::combat::aim_assist::break_blocks)
	{
		if (auto object_mouse_over = minecraft.get_object_mouse_over(); object_mouse_over.object != nullptr && object_mouse_over.get_type_of_hit() == 1)
			return;
	}

	auto closest_entity_view_angles_difference = client::mapper::__vec2(FLT_MAX, FLT_MAX);

	auto can_intercept_closest_entity = false;

	auto temporal_last_aimed_player_name = sdk::__multibyte_string();

	for (auto& player : world_players)
	{
		if (client::mapper::jni->IsSameObject(local_player.object, player.object))
			continue;

		if (player.get_health() <= 0.f)
			continue;

		auto player_view_position = player.get_view_position(timer_partial_ticks);

		if (local_player_view_position.get_distance_to_vec3(player_view_position) > client::features::combat::aim_assist::distance)
			continue;

		if (client::features::combat::aim_assist::ignore_non_visible_players && !local_player.can_entity_be_seen(player))
			continue;

		if (client::features::combat::aim_assist::ignore_naked_players && player.get_total_armor_value() == 0)
			continue;

		if (client::features::settings::ignore_teammates && !local_player.can_attack_player(player))
			continue;

		auto player_name = player.get_name();

		if (client::features::combat::aim_assist::lock_target && sdk::__multibyte_string::is_valid(last_aimed_player_name) && !last_aimed_player_name.equals(player_name.get_multibyte_string()))
			continue;

		if (local_player_view_position.y > player_view_position.y)
		{
			if (local_player_view_position.y > player_view_position.y + 1.8)
				player_view_position.y = player_view_position.y + 1.8;
			else 
				player_view_position.y = local_player_view_position.y;
		}

		auto entity_view_angles_difference_x = local_player_view_position.get_angle_x_difference_to_vec3(player_view_position, local_player_view_angles.x);
		auto entity_view_angles_difference_y = local_player_view_position.get_angle_y_difference_to_vec3(player_view_position, local_player_view_angles.y);

		if (abs(entity_view_angles_difference_x) < client::features::combat::aim_assist::fov && abs(entity_view_angles_difference_x) < abs(closest_entity_view_angles_difference.x))
		{
			temporal_last_aimed_player_name = player_name;

			closest_entity_view_angles_difference.x = entity_view_angles_difference_x;
			closest_entity_view_angles_difference.y = entity_view_angles_difference_y;

			auto player_bounding_box = player.get_bounding_box();

			auto player_bounding_box_bounds = player_bounding_box.get_bounds();

			player_bounding_box.set_bounds(
			{
				{ player_bounding_box_bounds.first.x - .1, player_bounding_box_bounds.first.y - .1, player_bounding_box_bounds.first.z - .1 },
				{ player_bounding_box_bounds.second.x + .1, player_bounding_box_bounds.second.y + .1, player_bounding_box_bounds.second.z + .1 }
			});

			can_intercept_closest_entity = player_bounding_box.calculate_interception(local_player_view_position, local_player_view_vector).object != nullptr;

			player_bounding_box.set_bounds(player_bounding_box_bounds);
		}
	}

	last_aimed_player_name = temporal_last_aimed_player_name;

	if (closest_entity_view_angles_difference.x != FLT_MAX && closest_entity_view_angles_difference.y != FLT_MAX)
	{
		static auto timer = sdk::__timer();

		if (!timer.has_elapsed(1.))
			return;

		if (timer.elapsed_milliseconds > 10.)
			timer.elapsed_milliseconds = sdk::generate_random_value(1., 10.);

		auto game_sensitivity = minecraft.get_settings().get_mouse_sensitivity();

		auto sensitivity = game_sensitivity * .6f + .2f;

		auto aim_speed_x = (__int32)
			(client::features::combat::aim_assist::speed * min(game_sensitivity / game_sensitivity / game_sensitivity * .33f, 5.)) *
			(abs(closest_entity_view_angles_difference.x) / 45.) * sdk::generate_random_value(.725, (local_player.get_hurt_time() > 15 ? 2.25 : 1.35));

		auto aim_speed_y = (__int32)
			(client::features::combat::aim_assist::speed * min(game_sensitivity / game_sensitivity / game_sensitivity * .33f, 5.)) *
			(abs(closest_entity_view_angles_difference.y) / 45.) * sdk::generate_random_value(.725, (local_player.get_hurt_time() > 15 ? 2.25 : 1.35));

		auto new_angle_x = powf((sensitivity), 3) * 8.f * .03f * (__int32)timer.elapsed_milliseconds *
			(__int32)(abs(closest_entity_view_angles_difference.x) / closest_entity_view_angles_difference.x) * (aim_speed_x < 1 ? 1 : aim_speed_x);

		auto new_angle_y = powf((sensitivity), 3) * 8.f * .03f * (__int32)timer.elapsed_milliseconds *
			(__int32)(abs(closest_entity_view_angles_difference.y) / closest_entity_view_angles_difference.y) * (aim_speed_y < 1 ? 1 : aim_speed_y);

		if (abs(new_angle_x) < abs(closest_entity_view_angles_difference.x) && new_angle_x != 0.f)
		{
			client::features::combat::aim_assist::angle_x_changes += (float)new_angle_x;

			local_player.set_old_view_angles(local_player_view_angles), local_player.set_view_angles({ local_player_view_angles.x + (float)new_angle_x, local_player_view_angles.y });
		}

		local_player_view_angles = local_player.get_view_angles();

		if (abs(new_angle_y) < abs(closest_entity_view_angles_difference.y) && new_angle_y != 0.f)
		{
			client::features::combat::aim_assist::angle_y_changes += (float)new_angle_y;

			local_player.set_old_view_angles(local_player_view_angles), local_player.set_view_angles({ local_player_view_angles.x, local_player_view_angles.y + (float)new_angle_y });
		}
	}
}