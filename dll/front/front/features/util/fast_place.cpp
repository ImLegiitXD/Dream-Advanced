
#include "../features.hpp"

auto client::features::util::fast_place::run(client::mapper::__minecraft& minecraft) -> void
{
	if (!client::features::util::fast_place::enabled)
		return;

	if ((sdk::nt_user_get_async_key_state(VK_RBUTTON) & 0x8000) == 0)
		return;

	auto local_player = minecraft.get_local_player();
	auto local_player_held_item_stack = local_player.get_held_item_stack();
	auto local_player_held_item = (local_player_held_item_stack.object == nullptr ? client::mapper::__item(nullptr) : local_player_held_item_stack.get_item());

	if (local_player_held_item.object == nullptr || !local_player_held_item.is_block())
		return;

	if (minecraft.get_right_click_delay_timer() > (__int32)round(client::features::util::fast_place::delay))
		minecraft.set_right_click_delay_timer(0);
}