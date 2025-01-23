
#include "../mapper.hpp"

client::mapper::__minecraft::__minecraft()
{
	static auto field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("theMinecraft"), client::mapper::classes[XOR("Minecraft")].signature.get_multibyte_string());

	if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("field_71432_P"), client::mapper::classes[XOR("Minecraft")].signature.get_multibyte_string());

	if (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17)
	{
		if (field.identifier == nullptr)
			field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("M"), client::mapper::classes[XOR("Minecraft")].signature.get_multibyte_string());
	}
	else if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("S"), client::mapper::classes[XOR("Minecraft")].signature.get_multibyte_string());

	this->object = client::mapper::jni->GetStaticObjectField(client::mapper::classes[XOR("Minecraft")].klass, field.identifier);
}

client::mapper::__minecraft::__minecraft(const client::mapper::__minecraft& minecraft)
{
	if (minecraft.object != nullptr)
		this->object = client::mapper::jni->NewLocalRef(minecraft.object);
}

client::mapper::__minecraft::~__minecraft()
{
	if (this->object != nullptr)
		client::mapper::jni->DeleteLocalRef(this->object);
}

auto client::mapper::__minecraft::is_on_run_tick() -> bool
{
	auto is_on_run_tick = false;

	__int32 matrix_mode = 0;

	static auto module_export_address_0 = sdk::get_module_export_address(sdk::get_module_address(XOR(L"opengl32.dll")), XOR("glGetIntegerv"));

	((void(_stdcall*)(unsigned __int32, __int32*))module_export_address_0)(0xba0, &matrix_mode);

	if (matrix_mode == 0x1700)
	{
		static auto current_thread = []() -> _jobject*
		{
			_jobject* current_thread = nullptr, *temporal_current_thread = nullptr;

			client::mapper::jvmti->GetCurrentThread(&temporal_current_thread);

			current_thread = client::mapper::jni->NewGlobalRef(current_thread);

			client::mapper::jni->DeleteLocalRef(current_thread);

			return current_thread;
		}();

		jvmtiFrameInfo frame_information[1];

		long frame_count = 0;

		client::mapper::jvmti->GetStackTrace(current_thread, 4, 1, frame_information, &frame_count);

		for (auto x = 0; x < frame_count && !is_on_run_tick; ++x)
		{
			char* name = nullptr, * signature = nullptr, * reserved = nullptr;

			client::mapper::jvmti->GetMethodName(frame_information[x].method, &name, &signature, &reserved);

			if (name != nullptr && signature != nullptr)
			{
				if (sdk::__multibyte_string(signature).equals(XOR("()V")))
				{
					if (sdk::__multibyte_string(name).equals(XOR("runTick")))
						is_on_run_tick = true;

					if (sdk::__multibyte_string(name).equals(XOR("func_71407_l")))
						is_on_run_tick = true;

					if (sdk::__multibyte_string(name).equals(XOR("s")) || sdk::__multibyte_string(name).equals(XOR("p")))
						is_on_run_tick = true;
				}

				client::mapper::jvmti->Deallocate((unsigned __int8*)name);
			}

			if (signature != nullptr)
				client::mapper::jvmti->Deallocate((unsigned __int8*)signature);

			if (reserved != nullptr)
				client::mapper::jvmti->Deallocate((unsigned __int8*)reserved);
		}
	}

	return is_on_run_tick;
}

auto client::mapper::__minecraft::is_on_render_world() -> bool
{
	auto is_on_render_world = false;

	__int32 matrix_mode = 0;

	static auto module_export_address_0 = sdk::get_module_export_address(sdk::get_module_address(XOR(L"opengl32.dll")), XOR("glGetIntegerv"));

	((void(_stdcall*)(unsigned __int32, __int32*))module_export_address_0)(0xba0, &matrix_mode);

	if (matrix_mode == 0x1700)
	{
		static auto current_thread = []() -> _jobject*
		{
			_jobject* current_thread = nullptr, *temporal_current_thread = nullptr;

			client::mapper::jvmti->GetCurrentThread(&temporal_current_thread);

			current_thread = client::mapper::jni->NewGlobalRef(current_thread);

			client::mapper::jni->DeleteLocalRef(current_thread);

			return current_thread;
		}();

		jvmtiFrameInfo frame_information[3];

		long frame_count = 0;

		client::mapper::jvmti->GetStackTrace(current_thread, 2, 3, frame_information, &frame_count);

		for (auto x = 0; x < frame_count && !is_on_render_world; ++x)
		{
			char* name = nullptr, *signature = nullptr, *reserved = nullptr;

			client::mapper::jvmti->GetMethodName(frame_information[x].method, &name, &signature, &reserved);

			if (name != nullptr && signature != nullptr)
			{
				if (sdk::__multibyte_string(signature).equals(XOR("(FJ)V")))
				{
					if (sdk::__multibyte_string(name).equals(XOR("renderWorld")))
						is_on_render_world = true;

					if (sdk::__multibyte_string(name).equals(XOR("func_78471_a")))
						is_on_render_world = true;

					if (sdk::__multibyte_string(name).equals(XOR("b")) || sdk::__multibyte_string(name).equals(XOR("a")))
						is_on_render_world = true;
				}
			
				client::mapper::jvmti->Deallocate((unsigned __int8*)name);
			}

			if (signature != nullptr)
				client::mapper::jvmti->Deallocate((unsigned __int8*)signature);

			if (reserved != nullptr)
				client::mapper::jvmti->Deallocate((unsigned __int8*)reserved);
		}
	}

	return is_on_render_world;
}

auto client::mapper::__minecraft::is_on_orient_camera() -> bool
{
	auto is_on_orient_camera = false;

	__int32 matrix_mode = 0;

	static auto module_export_address_0 = sdk::get_module_export_address(sdk::get_module_address(XOR(L"opengl32.dll")), XOR("glGetIntegerv"));

	((void(_stdcall*)(unsigned __int32, __int32*))module_export_address_0)(0xba0, &matrix_mode);

	if (matrix_mode == 0x1700)
	{
		static auto current_thread = []() -> _jobject*
		{
			_jobject* current_thread = nullptr, *temporal_current_thread = nullptr;

			client::mapper::jvmti->GetCurrentThread(&temporal_current_thread);

			current_thread = client::mapper::jni->NewGlobalRef(current_thread);

			client::mapper::jni->DeleteLocalRef(current_thread);

			return current_thread;
		}();

		jvmtiFrameInfo frame_information[1];

		long frame_count = 0;

		client::mapper::jvmti->GetStackTrace(current_thread, 3, 1, frame_information, &frame_count);

		for (auto x = 0; x < frame_count && !is_on_orient_camera; ++x)
		{
			char* name = nullptr, * signature = nullptr, * reserved = nullptr;

			client::mapper::jvmti->GetMethodName(frame_information[x].method, &name, &signature, &reserved);

			if (name != nullptr && signature != nullptr)
			{
				if (sdk::__multibyte_string(signature).equals(XOR("(F)V")))
				{
					if (sdk::__multibyte_string(name).equals(XOR("orientCamera")))
						is_on_orient_camera = true;

					if (sdk::__multibyte_string(name).equals(XOR("func_78467_g")))
						is_on_orient_camera = true;

					if (sdk::__multibyte_string(name).equals(XOR("f")) || sdk::__multibyte_string(name).equals(XOR("h")))
						is_on_orient_camera = true;
				}

				client::mapper::jvmti->Deallocate((unsigned __int8*)name);
			}

			if (signature != nullptr)
				client::mapper::jvmti->Deallocate((unsigned __int8*)signature);

			if (reserved != nullptr)
				client::mapper::jvmti->Deallocate((unsigned __int8*)reserved);
		}
	}

	return is_on_orient_camera;
}

auto client::mapper::__minecraft::get_settings() -> client::mapper::__settings
{
	static auto field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("gameSettings"), client::mapper::classes[XOR("GameSettings")].signature.get_multibyte_string());

	if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("field_71474_y"), client::mapper::classes[XOR("GameSettings")].signature.get_multibyte_string());

	if (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17)
	{
		if (field.identifier == nullptr)
			field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("u"), client::mapper::classes[XOR("GameSettings")].signature.get_multibyte_string());
	}
	else if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("t"), client::mapper::classes[XOR("GameSettings")].signature.get_multibyte_string());

	return client::mapper::__settings(client::mapper::jni->GetObjectField(this->object, field.identifier));
}

auto client::mapper::__minecraft::get_timer() -> client::mapper::__timer
{
	static auto field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("timer"), client::mapper::classes[XOR("Timer")].signature.get_multibyte_string());

	if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("field_71428_T"), client::mapper::classes[XOR("Timer")].signature.get_multibyte_string());

	if (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17)
	{
		if (field.identifier == nullptr)
			field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("Q"), client::mapper::classes[XOR("Timer")].signature.get_multibyte_string());
	}
	else if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("Y"), client::mapper::classes[XOR("Timer")].signature.get_multibyte_string());

	return client::mapper::__timer(client::mapper::jni->GetObjectField(this->object, field.identifier));
}

auto client::mapper::__minecraft::get_current_screen() -> client::mapper::__gui_screen
{
	static auto field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("currentScreen"), client::mapper::classes[XOR("GuiScreen")].signature.get_multibyte_string());

	if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("field_71462_r"), client::mapper::classes[XOR("GuiScreen")].signature.get_multibyte_string());

	if (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17)
	{
		if (field.identifier == nullptr)
			field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("n"), client::mapper::classes[XOR("GuiScreen")].signature.get_multibyte_string());
	}
	else if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("m"), client::mapper::classes[XOR("GuiScreen")].signature.get_multibyte_string());

	return client::mapper::__gui_screen(client::mapper::jni->GetObjectField(this->object, field.identifier));
}

auto client::mapper::__minecraft::get_render_manager() -> client::mapper::__render_manager
{
	if (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17)
	{
		static auto field = client::mapper::classes[XOR("RenderManager")].get_field(XOR("instance"), client::mapper::classes[XOR("RenderManager")].signature.get_multibyte_string());

		if (field.identifier == nullptr)
			field = client::mapper::classes[XOR("RenderManager")].get_field(XOR("field_78727_a"), client::mapper::classes[XOR("RenderManager")].signature.get_multibyte_string());

		if (field.identifier == nullptr)
			field = client::mapper::classes[XOR("RenderManager")].get_field(XOR("a"), client::mapper::classes[XOR("RenderManager")].signature.get_multibyte_string());

		return client::mapper::__render_manager(client::mapper::jni->GetStaticObjectField(client::mapper::classes[XOR("RenderManager")].klass, field.identifier));
	}
	else
	{
		static auto field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("renderManager"), client::mapper::classes[XOR("RenderManager")].signature.get_multibyte_string());

		if (field.identifier == nullptr)
			field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("field_175616_W"), client::mapper::classes[XOR("RenderManager")].signature.get_multibyte_string());

		if (field.identifier == nullptr)
			field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("aa"), client::mapper::classes[XOR("RenderManager")].signature.get_multibyte_string());

		return client::mapper::__render_manager(client::mapper::jni->GetObjectField(this->object, field.identifier));
	}
}

auto client::mapper::__minecraft::get_world() -> client::mapper::__world
{
	static auto field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("theWorld"), client::mapper::classes[XOR("WorldClient")].signature.get_multibyte_string());

	if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("field_71441_e"), client::mapper::classes[XOR("WorldClient")].signature.get_multibyte_string());

	if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("f"), client::mapper::classes[XOR("WorldClient")].signature.get_multibyte_string());

	return client::mapper::__world(client::mapper::jni->GetObjectField(this->object, field.identifier));
}

auto client::mapper::__minecraft::get_local_player() -> client::mapper::__player
{
	static auto field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("thePlayer"), client::mapper::classes[XOR("EntityPlayerXP")].signature.get_multibyte_string());

	if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("field_71439_g"), client::mapper::classes[XOR("EntityPlayerXP")].signature.get_multibyte_string());

	if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("h"), client::mapper::classes[XOR("EntityPlayerXP")].signature.get_multibyte_string());

	return client::mapper::__player(client::mapper::jni->GetObjectField(this->object, field.identifier));
}

auto client::mapper::__minecraft::get_object_mouse_over() -> client::mapper::__moving_object_position
{
	static auto field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("objectMouseOver"), client::mapper::classes[XOR("MovingObjectPosition")].signature.get_multibyte_string());

	if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("field_71476_x"), client::mapper::classes[XOR("MovingObjectPosition")].signature.get_multibyte_string());

	if (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17)
	{
		if (field.identifier == nullptr)
			field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("t"), client::mapper::classes[XOR("MovingObjectPosition")].signature.get_multibyte_string());
	}
	else if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("s"), client::mapper::classes[XOR("MovingObjectPosition")].signature.get_multibyte_string());

	return client::mapper::__moving_object_position(client::mapper::jni->GetObjectField(this->object, field.identifier));
}

auto client::mapper::__minecraft::set_object_mouse_over(client::mapper::__moving_object_position moving_object_position) -> void
{
	static auto field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("objectMouseOver"), client::mapper::classes[XOR("MovingObjectPosition")].signature.get_multibyte_string());

	if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("field_71476_x"), client::mapper::classes[XOR("MovingObjectPosition")].signature.get_multibyte_string());

	if (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17)
	{
		if (field.identifier == nullptr)
			field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("t"), client::mapper::classes[XOR("MovingObjectPosition")].signature.get_multibyte_string());
	}
	else if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("s"), client::mapper::classes[XOR("MovingObjectPosition")].signature.get_multibyte_string());

	return client::mapper::jni->SetObjectField(this->object, field.identifier, moving_object_position.object);
}

auto client::mapper::__minecraft::get_pointed_entity() -> client::mapper::__player
{
	static auto field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("pointedEntity"), client::mapper::classes[XOR("Entity")].signature.get_multibyte_string());

	if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("field_147125_j"), client::mapper::classes[XOR("Entity")].signature.get_multibyte_string());

	if (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17)
	{
		if (field.identifier == nullptr)
			field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("j"), client::mapper::classes[XOR("Entity")].signature.get_multibyte_string());
	}
	else if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("i"), client::mapper::classes[XOR("Entity")].signature.get_multibyte_string());

	return client::mapper::jni->GetObjectField(this->object, field.identifier);
}

auto client::mapper::__minecraft::set_pointed_entity(client::mapper::__player player) -> void
{
	static auto field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("pointedEntity"), client::mapper::classes[XOR("Entity")].signature.get_multibyte_string());

	if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("field_147125_j"), client::mapper::classes[XOR("Entity")].signature.get_multibyte_string());

	if (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17)
	{
		if (field.identifier == nullptr)
			field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("j"), client::mapper::classes[XOR("Entity")].signature.get_multibyte_string());
	}
	else if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("i"), client::mapper::classes[XOR("Entity")].signature.get_multibyte_string());

	return client::mapper::jni->SetObjectField(this->object, field.identifier, player.object);
}

auto client::mapper::__minecraft::get_left_click_delay_timer() -> __int32
{
	static auto field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("leftClickCounter"), XOR("I"));

	if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("field_71429_W"), XOR("I"));

	if (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17)
	{
		if (field.identifier == nullptr)
			field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("U"), XOR("I"));
	}
	else if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("ag"), XOR("I"));

	return client::mapper::jni->GetIntField(this->object, field.identifier);
}

auto client::mapper::__minecraft::set_left_click_delay_timer(__int32 right_click_delay_timer) -> void
{
	static auto field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("leftClickCounter"), XOR("I"));

	if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("field_71429_W"), XOR("I"));

	if (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17)
	{
		if (field.identifier == nullptr)
			field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("U"), XOR("I"));
	}
	else if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("ag"), XOR("I"));

	return client::mapper::jni->SetIntField(this->object, field.identifier, right_click_delay_timer);
}

auto client::mapper::__minecraft::get_right_click_delay_timer() -> __int32
{
	static auto field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("rightClickDelayTimer"), XOR("I"));

	if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("field_71467_ac"), XOR("I"));

	if (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17)
	{
		if (field.identifier == nullptr)
			field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("ad"), XOR("I"));
	}
	else if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("ap"), XOR("I"));

	return client::mapper::jni->GetIntField(this->object, field.identifier);
}

auto client::mapper::__minecraft::set_right_click_delay_timer(__int32 right_click_delay_timer) -> void
{
	static auto field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("rightClickDelayTimer"), XOR("I"));

	if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("field_71467_ac"), XOR("I"));

	if (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17)
	{
		if (field.identifier == nullptr)
			field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("ad"), XOR("I"));
	}
	else if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("Minecraft")].get_field(XOR("ap"), XOR("I"));

	return client::mapper::jni->SetIntField(this->object, field.identifier, right_click_delay_timer);
}

auto client::mapper::__minecraft::is_valid() -> bool
{
	if (this->get_settings().object == nullptr)
		return false;

	if (this->get_timer().object == nullptr)
		return false;

	if (this->get_render_manager().object == nullptr)
		return false;

	if (this->get_world().object == nullptr)
		return false;

	if (this->get_local_player().object == nullptr)
		return false;

	return true;
}