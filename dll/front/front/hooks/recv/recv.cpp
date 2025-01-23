
#include "../hooks.hpp"

auto client::hooks::recv(
	unsigned __int64 socket, client::hooks::__packet* packets, unsigned __int32 packets_count, unsigned __int32* requested_size, unsigned __int32* flags, _OVERLAPPED* overlapped, client::hooks::__completition_routine completion_routine) -> __int32
{
	//if ((sdk::nt_user_get_async_key_state(VK_LBUTTON) & 0x8000) != 0)
	//	sdk::nt_delay_execution(50);

	return ((__int32(__stdcall*)(unsigned __int64, client::hooks::__packet*, unsigned __int32, unsigned __int32*, unsigned __int32*, _OVERLAPPED*, client::hooks::__completition_routine))
		client::hooks::original_recv)(socket, packets, packets_count, requested_size, flags, overlapped, completion_routine);
}