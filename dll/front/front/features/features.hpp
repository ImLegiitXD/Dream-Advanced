
#include "../mapper/mapper.hpp"

namespace client::features
{
	extern auto run_on_run_tick(client::mapper::__minecraft& minecraft) -> void;
	extern auto run_on_render_world(client::mapper::__minecraft& minecraft, unsigned __int64* last_render_world_kernel_system_time) -> void;
	extern auto run_on_update_animations(client::mapper::__minecraft& minecraft) -> void;
}

namespace client::features::combat::auto_click
{
	inline auto timer = sdk::__timer();

	__declspec(dllexport) inline auto enabled = false;
	__declspec(dllexport) inline auto clicks_per_second = 0.;
	__declspec(dllexport) inline auto whitelist_inventories = false;
	__declspec(dllexport) inline auto weapons_only = false;
	__declspec(dllexport) inline auto break_blocks = false;
	__declspec(dllexport) inline auto ignore_non_visible_players = false;
	__declspec(dllexport) inline auto ignore_naked_players = false;
	__declspec(dllexport) inline auto attacking_only = false;

	extern auto run(client::mapper::__minecraft& minecraft) -> void;
}

namespace client::features::combat::aim_assist
{
	inline auto angle_x_changes = 0.f;
	inline auto angle_y_changes = 0.f;

	__declspec(dllexport) inline auto enabled = false;
	__declspec(dllexport) inline auto distance = 0.;
	__declspec(dllexport) inline auto fov = 0.;
	__declspec(dllexport) inline auto speed = 0.;
	__declspec(dllexport) inline auto clicking_only = false;
	__declspec(dllexport) inline auto weapons_only = false;
	__declspec(dllexport) inline auto break_blocks = false;
	__declspec(dllexport) inline auto ignore_non_visible_players = false;
	__declspec(dllexport) inline auto ignore_naked_players = false;
	__declspec(dllexport) inline auto lock_target = false;
	__declspec(dllexport) inline auto silent = false;

	extern auto run(client::mapper::__minecraft& minecraft) -> void;
}

namespace client::features::combat::reach
{
	__declspec(dllexport) inline auto enabled = false;
	__declspec(dllexport) inline auto distance = 0.;
	__declspec(dllexport) inline auto weapons_only = false;
	__declspec(dllexport) inline auto sprinting_only = false;
	__declspec(dllexport) inline auto disable_in_liquids = false;
	__declspec(dllexport) inline auto ignore_non_visible_players = false;
	__declspec(dllexport) inline auto ignore_naked_players = false;
	__declspec(dllexport) inline auto draw_interception = false;
	__declspec(dllexport) inline auto color = client::mapper::__vec4(0., 0., 0., 0.);

	extern auto run(client::mapper::__minecraft& minecraft, bool draw_hit = false) -> void;
}

namespace client::features::combat::auto_jump
{
	__declspec(dllexport) inline auto enabled = false;
	__declspec(dllexport) inline auto chance_percentage = 0.;
	__declspec(dllexport) inline auto clicking_only = false;
	__declspec(dllexport) inline auto weapons_only = false;

	extern auto run(client::mapper::__minecraft& minecraft) -> void;
}

namespace client::features::combat::velocity
{
	__declspec(dllexport) inline auto enabled = false;
	__declspec(dllexport) inline auto horizontal_percentage = 0.;
	__declspec(dllexport) inline auto vertical_percentage = 0.;
	__declspec(dllexport) inline auto delay = 0.;
	__declspec(dllexport) inline auto clicking_only = false;
	__declspec(dllexport) inline auto weapons_only = false;
	__declspec(dllexport) inline auto push_back = false;

	extern auto run(client::mapper::__minecraft& minecraft) -> void;
}

namespace client::features::combat::fake_lag
{
	inline unsigned __int64 release_buffered_packets_function = 0;
	inline auto timer = sdk::__timer();

	__declspec(dllexport) inline auto enabled = false;
	__declspec(dllexport) inline auto delay = 0.;
	__declspec(dllexport) inline auto distance = 0.;
	__declspec(dllexport) inline auto clicking_only = false;
	__declspec(dllexport) inline auto weapons_only = false;
	__declspec(dllexport) inline auto release_when_distancing = false;
	__declspec(dllexport) inline auto release_when_attacked = false;
	__declspec(dllexport) inline auto release_when_attacking = false;
	__declspec(dllexport) inline auto draw_last_sent_position = false;
	__declspec(dllexport) inline auto color = client::mapper::__vec4(0., 0., 0., 0.);

	extern auto run(client::mapper::__minecraft& minecraft, bool draw_bounds = false) -> void;
}

namespace client::features::combat::backtrack
{
	__declspec(dllexport) inline auto enabled = false;
	__declspec(dllexport) inline auto delay = 0.;

	extern auto run(client::mapper::__minecraft& minecraft, bool draw_bounds = false) -> void;
}

namespace client::features::combat::weapons
{
	__declspec(dllexport) inline auto sword = false;
	__declspec(dllexport) inline auto axe = false;
	__declspec(dllexport) inline auto pickaxe = false;
	__declspec(dllexport) inline auto shovel = false;
}

namespace client::features::visual
{
	inline void* window = nullptr;

	inline auto requested_rendering = false;

	inline __int32 view_port[4] = {};
	inline double model_view_matrix[16] = {};
	inline double projection_matrix[16] = {};

	inline auto initialized_frame = false;

	extern auto world_to_screen(client::mapper::__vec3 vec3, bool can_reverse = false, bool ignore_z = false) -> client::mapper::__vec2;
	extern auto render_2d_bounding_box(
		client::mapper::__vec3 vec3, client::mapper::__vec4 outline_color, client::mapper::__vec4 line_color, client::mapper::__vec4 fill_color, bool draw_corners, bool draw_health, float health, bool draw_hurt_time, __int32 hurt_time) -> void;
	extern auto render_3d_bounding_box(client::mapper::__vec3 vec3, client::mapper::__vec4 color, bool draw_health, float health, bool draw_hurt_time, __int32 hurt_time) -> void;
	extern auto render_nametag(sdk::__multibyte_string name, client::mapper::__vec3 vec3, client::mapper::__vec4 color, bool draw_health, float health, bool draw_distance, double distance, bool draw_hurt_time, __int32 hurt_time) -> void;
	extern auto render_tracer(client::mapper::__vec3 vec3, client::mapper::__vec4 color, bool draw_distance, double distance, bool draw_hurt_time, __int32 hurt_time) -> void;
}

namespace client::features::visual::player_esp_2d
{
	__declspec(dllexport) inline auto enabled = false;
	__declspec(dllexport) inline auto outline_color = client::mapper::__vec4(0., 0., 0., 0.);
	__declspec(dllexport) inline auto line_color = client::mapper::__vec4(0., 0., 0., 0.);
	__declspec(dllexport) inline auto fill_color = client::mapper::__vec4(0., 0., 0., 0.);
	__declspec(dllexport) inline auto draw_corners = false;
	__declspec(dllexport) inline auto draw_health = false;
	__declspec(dllexport) inline auto draw_hurt_time = false;
	__declspec(dllexport) inline auto draw_invisible_players = false;

	extern auto run(client::mapper::__minecraft& minecraft) -> void;
}

namespace client::features::visual::player_esp_3d
{
	__declspec(dllexport) inline auto enabled = false;
	__declspec(dllexport) inline auto color = client::mapper::__vec4(0., 0., 0., 0.);
	__declspec(dllexport) inline auto draw_health = false;
	__declspec(dllexport) inline auto draw_hurt_time = false;
	__declspec(dllexport) inline auto draw_invisible_players = false;

	extern auto run(client::mapper::__minecraft& minecraft) -> void;
}

namespace client::features::visual::nametags
{
	__declspec(dllexport) inline auto enabled = false;
	__declspec(dllexport) inline auto color = client::mapper::__vec4(0., 0., 0., 0.);
	__declspec(dllexport) inline auto draw_health = false;
	__declspec(dllexport) inline auto draw_distance = false;
	__declspec(dllexport) inline auto draw_hurt_time = false;
	__declspec(dllexport) inline auto draw_invisible_players = false;

	extern auto run(client::mapper::__minecraft& minecraft) -> void;
}

namespace client::features::visual::tracers
{
	__declspec(dllexport) inline auto enabled = false;
	__declspec(dllexport) inline auto color = client::mapper::__vec4(0., 0., 0., 0.);
	__declspec(dllexport) inline auto draw_distance = false;
	__declspec(dllexport) inline auto draw_hurt_time = false;
	__declspec(dllexport) inline auto draw_invisible_players = false;

	extern auto run(client::mapper::__minecraft& minecraft) -> void;
}

namespace client::features::visual::chams
{
	__declspec(dllexport) inline auto enabled = false;
	__declspec(dllexport) inline auto custom_color = false;
	__declspec(dllexport) inline auto color = client::mapper::__vec4(0., 0., 0., 0.);
	__declspec(dllexport) inline auto draw_invisible_players = false;

	extern auto run(client::mapper::__minecraft& minecraft) -> void;
}

namespace client::features::visual::block_esp
{
	__declspec(dllexport) inline auto enabled = false;
	__declspec(dllexport) inline auto draw_diamond = false;
	__declspec(dllexport) inline auto draw_emerald = false;
	__declspec(dllexport) inline auto draw_iron = false;
	__declspec(dllexport) inline auto draw_gold = false;
	__declspec(dllexport) inline auto draw_lapis = false;
	__declspec(dllexport) inline auto draw_coal = false;
	__declspec(dllexport) inline auto draw_redstone = false;
	__declspec(dllexport) inline auto draw_chests = false;

	extern auto run(client::mapper::__minecraft& minecraft) -> void;
}

namespace client::features::visual::array_list
{
	__declspec(dllexport) inline auto enabled = false;
	__declspec(dllexport) inline auto draw_watermark = false;

	extern auto run(client::mapper::__minecraft& minecraft) -> void;
}

namespace client::features::util::bridge_assist
{
	__declspec(dllexport) inline auto enabled = false;
	__declspec(dllexport) inline auto blocks_only = false;
	__declspec(dllexport) inline auto pitch_check = false;

	extern auto run(client::mapper::__minecraft& minecraft) -> void;
}

namespace client::features::util::sprint
{
	__declspec(dllexport) inline auto enabled = false;

	extern auto run(client::mapper::__minecraft& minecraft) -> void;
}

namespace client::features::util::fast_place
{
	__declspec(dllexport) inline auto enabled = false;
	__declspec(dllexport) inline auto delay = 0.;

	extern auto run(client::mapper::__minecraft& minecraft) -> void;
}

namespace client::features::util::speed
{
	__declspec(dllexport) inline auto enabled = false;
	__declspec(dllexport) inline auto slow = false;
	__declspec(dllexport) inline auto jump = false;
	__declspec(dllexport) inline auto fall = false;
	__declspec(dllexport) inline auto slow_ticks = 0.;
	__declspec(dllexport) inline auto slow_value = 0.;
	__declspec(dllexport) inline auto jump_value = 0.;
	__declspec(dllexport) inline auto fall_value = 0.;
	__declspec(dllexport) inline auto speed_value_0 = 0.;
	__declspec(dllexport) inline auto speed_value_1 = 0.;

	extern auto run(client::mapper::__minecraft& minecraft) -> void;
}

namespace client::features::settings
{
	__declspec(dllexport) inline auto ignore_teammates = false;
	__declspec(dllexport) inline auto use_opengl_32_swap_buffers = false;
}