
#include "../features.hpp"

auto client::features::util::sprint::run(client::mapper::__minecraft& minecraft) -> void
{
	if (!client::features::util::sprint::enabled)
		return;

	auto local_player = minecraft.get_local_player();

	local_player.set_flag(3, !local_player.get_flag(1));
}