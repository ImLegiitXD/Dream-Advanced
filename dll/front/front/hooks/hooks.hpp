
#include "../features/features.hpp"

namespace client::hooks
{
	__declspec(dllexport) inline unsigned __int64 loader_process_identifier = 0;

	extern auto initialize() -> __int32;
	extern auto uninitialize() -> __int32;

	inline void* original_get_time = nullptr;

	extern auto get_time(JNIEnv_* jni, _jclass* klass) -> __int64;

	inline void* original_clear = nullptr;
	inline unsigned __int64 last_render_world_kernel_system_time = 0;

	extern auto clear(JNIEnv_* jni, _jclass* klass, __int32 mask, unsigned __int64 function) -> void;

	inline void* original_rotate = nullptr;

	extern auto rotate(JNIEnv_* jni, _jclass* klass, float angle, float x, float y, float z, unsigned __int64 function) -> void;

	inline void* original_atan_2 = nullptr;

	extern auto atan_2(JNIEnv_* jni, _jclass* klass, double abscissa, double ordinate) -> double;

	inline void* original_swap_buffers = nullptr;

	extern auto swap_buffers(HDC__* hdc) -> __int32;

	inline unsigned __int64 send_function = 0;
	inline void* original_send = nullptr;
	inline auto send_called = false;

	struct __packet
	{
		unsigned __int32 size = 0;
		unsigned __int64 address = 0;
	};

	typedef void(__stdcall* __completition_routine)(unsigned __int32, unsigned __int32, _OVERLAPPED*, unsigned __int32);

	extern auto send(
		unsigned __int64 socket, client::hooks::__packet* packets, unsigned __int32 packets_count, unsigned __int32* requested_size, unsigned __int32 flags, _OVERLAPPED* overlapped, client::hooks::__completition_routine completion_routine) -> __int32;

	struct __send_arguments
	{
		unsigned __int64 socket = 0;
		client::hooks::__packet* packets = nullptr;
		unsigned __int32 packets_count = 0;
		unsigned __int32* requested_size = nullptr;
		unsigned __int32 flags = 0;
	};

	inline auto buffered_send_arguments = std::vector<__send_arguments>();

	extern auto release_buffered_packets(unsigned __int64 function = 0) -> void;

	inline void* original_recv = nullptr;

	extern auto recv(
		unsigned __int64 socket, client::hooks::__packet* packets, unsigned __int32 packets_count, unsigned __int32* requested_size, unsigned __int32* flags, _OVERLAPPED* overlapped, client::hooks::__completition_routine completion_routine) -> __int32;
}