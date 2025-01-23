
#include "../features.hpp"

auto client::features::combat::velocity::run(client::mapper::__minecraft& minecraft) -> void
{
	if (!client::features::combat::velocity::enabled)
		return;

	if (minecraft.get_current_screen().object != nullptr)
		return;

	if (client::features::combat::velocity::clicking_only && (sdk::nt_user_get_async_key_state(VK_LBUTTON) & 0x8000) == 0)
		return;

	auto local_player = minecraft.get_local_player();

	if (client::features::combat::velocity::weapons_only)
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

	if (local_player.get_hurt_time() == 10 - (__int32)round(client::features::combat::velocity::delay))
	{
		if (static auto timer = sdk::__timer(); timer.has_elapsed(100., true))
		{
			timer.update();

			auto local_player_motion = local_player.get_motion();

			return local_player.set_motion(
			{
				local_player_motion.x * (client::features::combat::velocity::horizontal_percentage / 100.) * (client::features::combat::velocity::push_back ? -1. : 1.),
				local_player_motion.y * (client::features::combat::velocity::vertical_percentage / 100.),
				local_player_motion.z * (client::features::combat::velocity::horizontal_percentage / 100.) * (client::features::combat::velocity::push_back ? -1. : 1.)
			});
		}
	}
}