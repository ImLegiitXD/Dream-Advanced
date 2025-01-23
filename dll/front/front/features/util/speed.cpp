
#include "../features.hpp"

auto client::features::util::speed::run(client::mapper::__minecraft& minecraft) -> void
{
	if (!client::features::util::speed::enabled)
		return;

	if (minecraft.get_current_screen().object != nullptr)
		return;

	static unsigned __int64 ticks_existed = 0;

	auto local_player = minecraft.get_local_player();

	if (local_player.get_move_strafing() != 0.f || local_player.get_move_foreward() != 0.f)
	{
		auto local_player_angle_x = local_player.get_view_angles().x;

		auto local_player_strafe = local_player.get_move_strafing(), local_player_forward = local_player.get_move_foreward();

		auto forward = 0.f;

		if (local_player_forward < 0.f)
		{
			local_player_angle_x += 180.f;
		}

		if (local_player_forward < 0.f)
		{
			forward = -.5f;
		}
		else if (local_player_forward > 0.f)
		{
			forward = .5f;
		}
		else
		{
			forward = 1.f;
		}

		if (local_player_strafe > 0.f)
		{
			local_player_angle_x -= 90.f * forward;
		}

		if (local_player_strafe < 0.f)
		{
			local_player_angle_x += 90.f * forward;
		}

		auto local_player_direction = local_player_angle_x * .017453292f;

		auto on_ground = local_player.get_on_ground();

		if (on_ground && client::features::util::speed::jump)
		{
			auto local_player_motion = local_player.get_motion();

			local_player.set_motion(
				{
					local_player_motion.x,
					client::features::util::speed::jump_value,
					local_player_motion.z
				}
			);
		}

		if (!on_ground && client::features::util::speed::fall)
		{
			auto local_player_motion = local_player.get_motion();

			local_player.set_motion(
				{
					local_player_motion.x,
					-client::features::util::speed::fall_value,
					local_player_motion.z
				}
			);
		}

		if (client::features::util::speed::slow && ticks_existed++ == (unsigned __int64)round(client::features::util::speed::slow_ticks))
		{
			local_player.set_motion(
				{
					-(sin(local_player_direction) * client::features::util::speed::slow_value),
					local_player.get_motion().y,
					cos(local_player_direction) * client::features::util::speed::slow_value
				}
			);

			ticks_existed = 0;
		}
		else
		{
			auto new_speed = (on_ground ? client::features::util::speed::speed_value_0 : client::features::util::speed::speed_value_1);

			local_player.set_motion(
				{
					-(sin(local_player_direction) * new_speed),
					local_player.get_motion().y,
					cos(local_player_direction) * new_speed
				}
			);
		}
	}
	else
	{
		local_player.set_motion(
			{
				0.,
				local_player.get_motion().y,
				0.
			}
		);
	}
}