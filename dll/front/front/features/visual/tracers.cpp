
#include "../features.hpp"

auto client::features::visual::tracers::run(client::mapper::__minecraft& minecraft) -> void
{
	if (!client::features::visual::tracers::enabled)
		return;

	auto timer = minecraft.get_timer();
	auto timer_partial_ticks = timer.get_partial_ticks();

	auto world = minecraft.get_world();
	auto world_players = world.get_players();

	auto local_player = minecraft.get_local_player();
	auto local_player_view_position = local_player.get_view_position(timer_partial_ticks);

	for (auto& player : world_players)
	{
		if (client::mapper::jni->IsSameObject(local_player.object, player.object))
			continue;

		auto player_health = player.get_health();

		if (player_health <= 0.f)
			continue;

		if (!client::features::visual::tracers::draw_invisible_players && player.get_flag(5))
			continue;

		auto player_view_position = player.get_view_position(timer_partial_ticks);

		auto local_player_view_position_distance_to_player_view_position = local_player_view_position.get_distance_to_vec3(player_view_position);

		if (local_player_view_position_distance_to_player_view_position > 255.)
			continue;

		client::features::visual::render_tracer(
			{ player_view_position.x - local_player_view_position.x, player_view_position.y - local_player_view_position.y + .9, player_view_position.z - local_player_view_position.z },
			client::features::visual::tracers::color,
			client::features::visual::tracers::draw_distance,
			local_player_view_position_distance_to_player_view_position,
			client::features::visual::tracers::draw_hurt_time,
			(client::features::visual::tracers::draw_hurt_time ? player.get_hurt_time() : 0)
		);
	}
}