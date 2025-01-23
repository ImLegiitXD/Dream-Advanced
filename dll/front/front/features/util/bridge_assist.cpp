
#include "../features.hpp"

auto client::features::util::bridge_assist::run(client::mapper::__minecraft& minecraft) -> void
{
	static auto old_sneaking_state = false;

	auto set_sneaking = [&](bool sneaking_state) -> bool
	{
		auto find_window_with_class_name = [](sdk::__unicode_string class_name) -> void*
		{
			if (!sdk::__unicode_string::is_valid(class_name))
				REPORT_EXIT_RETURN(nullptr);

			auto us_0 = _UNICODE_STRING((unsigned __int16)(class_name.get_length() * 2), (unsigned __int16)(class_name.get_length() * 2 + 2), class_name.get_unicode_string()), us_1 = _UNICODE_STRING();

			return sdk::nt_user_find_window_ex(&us_0, &us_1);
		};

		if (sneaking_state == old_sneaking_state)
			return sneaking_state;
		else if (find_window_with_class_name(XOR(L"LWJGL")) == GetForegroundWindow())
		{
			keybd_event(VK_LSHIFT, 0, (sneaking_state ? 0 : KEYEVENTF_KEYUP), 0);
			
			return sneaking_state;
		}

		return !sneaking_state;
	};

	if (!client::features::util::bridge_assist::enabled)
		return (void)(old_sneaking_state = set_sneaking(false));

	if (minecraft.get_current_screen().object != nullptr)
		return (void)(old_sneaking_state = set_sneaking(false));

	auto local_player = minecraft.get_local_player();
	auto local_player_view_position = local_player.get_view_position(minecraft.get_timer().get_partial_ticks());

	if (client::features::util::bridge_assist::blocks_only)
	{
		auto local_player_held_item_stack = local_player.get_held_item_stack();
		auto local_player_held_item = (local_player_held_item_stack.object == nullptr ? client::mapper::__item(nullptr) : local_player_held_item_stack.get_item());

		if (local_player_held_item.object == nullptr || !local_player_held_item.is_block())
			return (void)(old_sneaking_state = set_sneaking(false));
	}

	auto local_player_fixed_view_position = client::mapper::__vec3
	{
		(double)floor(local_player_view_position.x),
		(double)local_player_view_position.y - (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17 ? 2 : 1),
		(double)floor(local_player_view_position.z)
	};

	return (void)(old_sneaking_state = set_sneaking(
		local_player.get_on_ground() &&
		minecraft.get_world().get_block_id(
			local_player_fixed_view_position.x,
			local_player_fixed_view_position.y,
			local_player_fixed_view_position.z
		) == 0 &&
		(client::features::util::bridge_assist::pitch_check ? local_player.get_view_angles().y > 65.5f : true)
	));
}