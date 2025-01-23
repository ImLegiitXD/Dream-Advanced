
#include "../security/security.h"

#define LOADER_MAYOR_VERSION XOR("1")
#define LOADER_MINOR_VERSION XOR("0")

namespace client::core
{
	extern auto initialize() -> __int32;
	extern auto java_org_lwjgl_opengl_gl_11_ngl_push_matrix(void* jni, void* klass, unsigned __int64 function) -> void;
}

namespace client::core::menu
{
	inline auto initialized = false;
	inline unsigned __int64 target_process_identifier = 0;
	inline auto uninitialized = false;

	extern auto initialize() -> __int32;
	extern auto set_configuration() -> void;
}

namespace client::core::auth
{
	inline unsigned __int64 received_module = 0;

	extern auto initialize() -> __int32;
	extern auto send_message(sdk::__multibyte_string message) -> void;
}

namespace client::core::ipc
{
	inline auto settings = std::vector<std::pair<sdk::__multibyte_string, unsigned __int64>>();
	inline auto uninitialized = false;

	extern auto initialize(unsigned __int64 address) -> __int32;
	extern auto get_setting_address(sdk::__multibyte_string name) -> unsigned __int64;
}

namespace client::core::exit
{
	inline auto uninitialized = false;

	extern auto initialize() -> __int32;
}