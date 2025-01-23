
#include "../hooks.hpp"

auto set_release_buffered_packets_function = client::features::combat::fake_lag::release_buffered_packets_function = (unsigned __int64)client::hooks::release_buffered_packets;

auto client::hooks::send(
	unsigned __int64 socket, client::hooks::__packet* packets, unsigned __int32 packets_count, unsigned __int32* requested_size, unsigned __int32 flags, _OVERLAPPED* overlapped, client::hooks::__completition_routine completion_routine) -> __int32
{
	for (; client::hooks::send_called; sdk::nt_delay_execution(1));

	if (overlapped == nullptr && completion_routine == nullptr)
	{
		if (client::mapper::jni != nullptr && client::mapper::jvmti != nullptr && client::features::combat::fake_lag::enabled && !sdk::__timer(client::hooks::last_render_world_kernel_system_time, KERNEL_SYSTEM_TIME).has_elapsed(100.))
		{
			auto send_arguments = client::hooks::__send_arguments(socket, (client::hooks::__packet*)sdk::allocate_memory(packets_count * sizeof(client::hooks::__packet)), packets_count, requested_size, flags);

			for (unsigned __int32 x = 0; x < send_arguments.packets_count; ++x)
			{
				send_arguments.packets[x].size = packets[x].size;
				send_arguments.packets[x].address = sdk::allocate_memory(send_arguments.packets[x].size);

				sdk::copy_memory(send_arguments.packets[x].address, packets[x].address, (unsigned __int64)packets[x].size);
			}

			if (send_arguments.requested_size != nullptr)
			{
				for (unsigned __int32 x = 0; x < send_arguments.packets_count; ++x)
					*send_arguments.requested_size += send_arguments.packets[x].size;
			}

			client::hooks::buffered_send_arguments.push_back(send_arguments);

			return 0;
		}

		client::hooks::release_buffered_packets();
	}

	return ((__int32(__stdcall*)(unsigned __int64, client::hooks::__packet*, unsigned __int32, unsigned __int32*, unsigned __int32, _OVERLAPPED*, client::hooks::__completition_routine))
		client::hooks::original_send)(socket, packets, packets_count, requested_size, flags, overlapped, completion_routine);
}

auto client::hooks::release_buffered_packets(unsigned __int64 function) -> void
{
	client::hooks::send_called = true;

	for (auto& send_arguments : client::hooks::buffered_send_arguments)
	{
		unsigned __int32 requested_size = 0;

		((__int32(_stdcall*)(unsigned __int64, client::hooks::__packet*, unsigned __int32, unsigned __int32*, unsigned __int32, _OVERLAPPED*, client::hooks::__completition_routine))((function == 0 ? client::hooks::original_send : (void*)function)))
			(send_arguments.socket, send_arguments.packets, send_arguments.packets_count, &requested_size, send_arguments.flags, nullptr, nullptr);

		for (unsigned __int32 x = 0; x < send_arguments.packets_count; ++x)
			sdk::free_memory(send_arguments.packets[x].address);

		sdk::free_memory((unsigned __int64)send_arguments.packets);
	}

	client::hooks::buffered_send_arguments.clear();

	client::hooks::send_called = false;
}