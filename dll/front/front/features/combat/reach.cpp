
#include "../features.hpp"

auto client::features::combat::reach::run(client::mapper::__minecraft& minecraft, bool draw_hit) -> void
{
	if (!client::features::combat::reach::enabled)
		return;

	if (minecraft.get_current_screen().object != nullptr)
		return;

	struct __hit
	{
		client::mapper::__vec3 source;
		client::mapper::__vec3 target;
		double alpha = 0.;
		sdk::__timer timer;
	};

	static auto hit = __hit();

	if (client::features::combat::reach::draw_interception && draw_hit)
	{
		if (hit.alpha > 0.)
		{
			hit.alpha -= hit.timer.get_elapsed_milliseconds() * .001;
		
			auto local_player_view_position = minecraft.get_local_player().get_view_position(minecraft.get_timer().get_partial_ticks());

			auto hit_source_screen_position = client::features::visual::world_to_screen({ hit.source.x - local_player_view_position.x, hit.source.y - local_player_view_position.y, hit.source.z - local_player_view_position.z });
			auto hit_target_screen_position = client::features::visual::world_to_screen({ hit.target.x - local_player_view_position.x, hit.target.y - local_player_view_position.y, hit.target.z - local_player_view_position.z });

			ImGui::GetForegroundDrawList()->AddLine(
				{ hit_source_screen_position.x, hit_source_screen_position.y },
				{ hit_target_screen_position.x, hit_target_screen_position.y },
				ImGui::ColorConvertFloat4ToU32({ (float)client::features::combat::reach::color.x, (float)client::features::combat::reach::color.y, (float)client::features::combat::reach::color.z, (float)hit.alpha }),
				2.f
			);
		}

		return;
	}

	if ((sdk::nt_user_get_async_key_state(VK_LBUTTON) & 0x8000) == 0)
		return;

	auto local_player = minecraft.get_local_player();

	if (client::features::combat::reach::weapons_only)
	{
		auto local_player_held_item_stack = local_player.get_held_item_stack();

		if (local_player_held_item_stack.object == nullptr)
			return;

		auto local_player_held_item = local_player_held_item_stack.get_item();

		if (local_player_held_item.object == nullptr)
			return;

		if (!((client::features::combat::weapons::sword && local_player_held_item.is_sword()) || (client::features::combat::weapons::axe && local_player_held_item.is_axe()) ||
			(client::features::combat::weapons::pickaxe && local_player_held_item.is_pickaxe()) || (client::features::combat::weapons::shovel && local_player_held_item.is_shovel())))
			return;
	}

	if (client::features::combat::reach::sprinting_only && !local_player.get_flag(3))
		return;

	if (client::features::combat::reach::disable_in_liquids && local_player.is_offset_position_in_liquid(0., 0., 0.))
		return;

	auto timer_partial_ticks = minecraft.get_timer().get_partial_ticks();

	auto local_player_view_position = local_player.get_view_position(timer_partial_ticks);
	auto local_player_look_position = local_player.get_look_position(timer_partial_ticks);

	if (client::mapper::version != client::mapper::supported_versions::MINECRAFT_17)
		local_player_view_position.y += 1.62;

	auto local_player_view_vector = client::mapper::__vec3(
		local_player_view_position.x + local_player_look_position.x * client::features::combat::reach::distance,
		local_player_view_position.y + local_player_look_position.y * client::features::combat::reach::distance,
		local_player_view_position.z + local_player_look_position.z * client::features::combat::reach::distance
	);

	for (auto& player : minecraft.get_world().get_players())
	{
		if (client::mapper::jni->IsSameObject(local_player.object, player.object))
			continue;

		if (client::features::combat::reach::ignore_non_visible_players && !local_player.can_entity_be_seen(player))
			continue;

		if (client::features::combat::reach::ignore_naked_players && player.get_total_armor_value() == 0)
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

		if (player_bounding_box_interception.object == nullptr)
			continue;

		auto player_bounding_box_interception_hit_vector = player_bounding_box_interception.get_hit_vector();

		if (player_bounding_box_interception_hit_vector.object == nullptr)
			continue;

		hit.source = local_player_view_position;
		hit.target = player_bounding_box_interception_hit_vector.get_vec3();
		hit.alpha = 1.;

		hit.timer.update();

		minecraft.set_object_mouse_over(client::mapper::__moving_object_position(player, player_bounding_box_interception_hit_vector));

		return minecraft.set_pointed_entity(player);
	}
}