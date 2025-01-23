
#include "../features.hpp"

auto client::features::combat::auto_jump::run(client::mapper::__minecraft& minecraft) -> void
{
	if (!client::features::combat::auto_jump::enabled)
		return;

	if (minecraft.get_current_screen().object != nullptr)
		return;

	if (client::features::combat::auto_jump::clicking_only && (sdk::nt_user_get_async_key_state(VK_LBUTTON) & 0x8000) == 0)
		return;

	auto local_player = minecraft.get_local_player();

	if (client::features::combat::auto_jump::weapons_only)
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

	if (local_player.get_hurt_time() == 10 && local_player.get_on_ground())
	{
		if (client::features::combat::auto_jump::chance_percentage > sdk::generate_random_value(0., 100.))
		{
			if (static auto timer = sdk::__timer(); timer.has_elapsed(100., true))
			{
				timer.update();

				return local_player.jump();
			}
		}
	}
}