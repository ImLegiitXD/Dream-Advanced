
#include "../../back/misc/imgui/backends/imgui_impl_win32.h"
#include "../../back/misc/imgui/backends/imgui_impl_opengl3.h"
#include "../../back/misc/imgui/backends/imgui_impl_opengl3_loader.h"
#include "../../back/misc/imgui/fonts/verdana.hpp"
#include "../../back/misc/minhook/include/MinHook.h"
#include "../../back/sdk.hpp"

namespace client::mapper
{
	inline JavaVM_* jvm = nullptr;
	inline JNIEnv_* jni = nullptr;
	inline _jvmtiEnv* jvmti = nullptr;

	enum supported_versions
	{
		MINECRAFT_17,
		MINECRAFT_18,
	};

	inline unsigned __int32 version = MINECRAFT_17;

	extern auto initialize(JNIEnv_* jni) -> __int32;
}

namespace client::mapper
{
	struct __field
	{
		sdk::__multibyte_string name;
		sdk::__multibyte_string signature;
		_jfieldID* identifier = nullptr;
	};

	struct __method
	{
		sdk::__multibyte_string name;
		sdk::__multibyte_string signature;
		_jmethodID* identifier = nullptr;
	};

	struct __class
	{
		sdk::__multibyte_string name;
		sdk::__multibyte_string signature;
		_jclass* klass = nullptr;
		std::vector<client::mapper::__field> fields;
		std::vector<client::mapper::__method> methods;

		auto get_field(sdk::__multibyte_string name, sdk::__multibyte_string signature) -> client::mapper::__field;
		auto get_method(sdk::__multibyte_string name, sdk::__multibyte_string signature) -> client::mapper::__method;
	};

	inline auto classes = std::map<std::string, client::mapper::__class>();

	extern auto get_class(sdk::__multibyte_string name) -> client::mapper::__class;
}

namespace client::mapper
{
	extern auto initialize() -> __int32;
	extern auto uninitialize() -> __int32;

	struct __player;

	struct __vec4
	{
		double x = 0., y = 0., z = 0., w = 0.f;
	};

	struct __vec3
	{
		double x = 0., y = 0., z = 0.;

		auto get_distance_to_vec3(client::mapper::__vec3 vec3) -> double;
		auto get_angle_x_difference_to_vec3(client::mapper::__vec3 target, float angle) -> float;
		auto get_angle_y_difference_to_vec3(client::mapper::__vec3 target, float angle) -> float;
	};

	struct __vec3__
	{
		__vec3__(client::mapper::__vec3 vec3);
		__vec3__(_jobject* object);
		__vec3__(const client::mapper::__vec3__& vec3);
		~__vec3__();

		_jobject* object = nullptr;

		auto get_vec3() -> client::mapper::__vec3;
	};

	struct __vec2
	{
		float x = 0.f, y = 0.f;
	};

	struct __item
	{
		__item(_jobject* object);
		__item(const client::mapper::__item& item);
		~__item();

		_jobject* object = nullptr;

		auto get_id() -> __int32;
		auto is_sword() -> bool;
		auto is_axe() -> bool;
		auto is_pickaxe() -> bool;
		auto is_shovel() -> bool;
		auto is_block() -> bool;
	};

	struct __item_stack
	{
		__item_stack(_jobject* object);
		__item_stack(const client::mapper::__item_stack& item_stack);
		~__item_stack();

		_jobject* object = nullptr;

		auto get_item() -> client::mapper::__item;
	};

	struct __moving_object_position
	{
		__moving_object_position(_jobject* object);
		__moving_object_position(client::mapper::__player player, client::mapper::__vec3__ vec3);
		__moving_object_position(const client::mapper::__moving_object_position& moving_object_position);
		~__moving_object_position();

		_jobject* object = nullptr;

		auto get_type_of_hit() -> __int32;
		auto get_hit_vector() -> client::mapper::__vec3__;
	};

	struct __axis_aligned
	{
		__axis_aligned(_jobject* object);
		__axis_aligned(const client::mapper::__axis_aligned& axis_aligned);
		~__axis_aligned();

		_jobject* object = nullptr;

		auto get_bounds() -> std::pair<client::mapper::__vec3, client::mapper::__vec3>;
		auto set_bounds(std::pair<client::mapper::__vec3, client::mapper::__vec3> bounds) -> void;
		auto calculate_interception(client::mapper::__vec3 view_position, client::mapper::__vec3 view_vector) -> client::mapper::__moving_object_position;
	};

	struct __player
	{
		__player(_jobject* object);
		__player(const client::mapper::__player& player);
		~__player();

		_jobject* object = nullptr;

		auto get_position() -> client::mapper::__vec3;
		auto set_position(client::mapper::__vec3 position) -> void;
		auto get_old_position() -> client::mapper::__vec3;
		auto set_old_position(client::mapper::__vec3 position) -> void;
		auto get_motion() -> client::mapper::__vec3;
		auto set_motion(client::mapper::__vec3 motion) -> void;
		auto get_on_ground() -> bool;
		auto jump() -> void;
		auto is_swing_in_progress() -> bool;
		auto get_hurt_time() -> __int32;
		auto set_hurt_time(__int32 hurt_time) -> void;
		auto is_vulnerable() -> bool;
		auto get_view_position(float partial_ticks) -> client::mapper::__vec3;
		auto get_look_position(float partial_ticks) -> client::mapper::__vec3;	
		auto get_view_angles() -> client::mapper::__vec2;
		auto set_view_angles(client::mapper::__vec2 view_angles) -> void;
		auto get_old_view_angles() -> client::mapper::__vec2;
		auto set_old_view_angles(client::mapper::__vec2 old_view_angles) -> void;
		auto get_ticks_existed() -> __int32;
		auto get_health() -> float;
		auto get_move_foreward() -> float;
		auto get_move_strafing() -> float;
		auto get_total_armor_value() -> __int32;
		auto can_entity_be_seen(client::mapper::__player player) -> bool;
		auto get_flag(__int32 flag) -> bool;
		auto set_flag(__int32 flag, bool state) -> void;
		auto is_offset_position_in_liquid(double x, double y, double z) -> bool;
		auto get_held_item_stack() -> client::mapper::__item_stack;
		auto get_name() -> sdk::__multibyte_string;
		auto get_bounding_box() -> client::mapper::__axis_aligned;
		auto can_attack_player(client::mapper::__player player) -> bool;
	};

	struct __world
	{
		__world(_jobject* object);
		__world(const client::mapper::__world& world);
		~__world();

		_jobject* object = nullptr;

		auto get_players() -> std::vector<client::mapper::__player>;
		auto get_block_id(double x, double y, double z) -> __int32;
	};

	struct __render_manager
	{
		__render_manager(_jobject* object);
		__render_manager(const client::mapper::__render_manager& render_manager);
		~__render_manager();

		_jobject* object = nullptr;

		auto render_player(client::mapper::__player player, float partial_ticks) -> bool;
		auto render_player(client::mapper::__player player, double x, double y, double z, float yaw, float partial_ticks) -> bool;
	};

	struct __gui_screen
	{
		__gui_screen(_jobject* object);
		__gui_screen(const client::mapper::__gui_screen& gui_screen);
		~__gui_screen();

		_jobject* object = nullptr;

		auto is_inventory_instance() -> bool;
	};

	struct __timer
	{
		__timer(_jobject* object);
		__timer(const client::mapper::__timer& timer);
		~__timer();

		_jobject* object = nullptr;

		auto get_partial_ticks() -> float;
	};

	struct __settings
	{
		__settings(_jobject* object);
		__settings(const client::mapper::__settings& settings);
		~__settings();

		_jobject* object = nullptr;

		auto get_mouse_sensitivity() -> float;
	};

	struct __minecraft
	{
		__minecraft();
		__minecraft(const client::mapper::__minecraft& minecraft);
		~__minecraft();
	
		_jobject* object = nullptr;

		static auto is_on_run_tick() -> bool;
		static auto is_on_render_world() -> bool;
		static auto is_on_orient_camera() -> bool;

		auto get_settings() -> client::mapper::__settings;
		auto get_timer() -> client::mapper::__timer;
		auto get_current_screen() -> client::mapper::__gui_screen;
		auto get_render_manager() -> client::mapper::__render_manager;
		auto get_world() -> client::mapper::__world;
		auto get_local_player() -> client::mapper::__player;
		auto get_object_mouse_over() -> client::mapper::__moving_object_position;
		auto set_object_mouse_over(client::mapper::__moving_object_position moving_object_position) -> void;
		auto get_pointed_entity() -> client::mapper::__player;
		auto set_pointed_entity(client::mapper::__player player) -> void;
		auto get_left_click_delay_timer() -> __int32;
		auto set_left_click_delay_timer(__int32 right_click_delay_timer) -> void;
		auto get_right_click_delay_timer() -> __int32;
		auto set_right_click_delay_timer(__int32 right_click_delay_timer) -> void;
		auto is_valid() -> bool;
	};
}