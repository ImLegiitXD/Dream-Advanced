
#include "../mapper.hpp"

client::mapper::__player::__player(_jobject* object)
{
	this->object = object;
}

client::mapper::__player::__player(const client::mapper::__player& player)
{
	if (player.object != nullptr)
		this->object = client::mapper::jni->NewLocalRef(player.object);
}

client::mapper::__player::~__player()
{
	if (this->object != nullptr)
		client::mapper::jni->DeleteLocalRef(this->object);
}

auto client::mapper::__player::get_position() -> client::mapper::__vec3
{
	static auto field_0 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("posX"), XOR("D"));
	static auto field_1 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("posY"), XOR("D"));
	static auto field_2 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("posZ"), XOR("D"));

	if (field_0.identifier == nullptr)
		field_0 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("field_70165_t"), XOR("D"));

	if (field_0.identifier == nullptr)
		field_0 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("s"), XOR("D"));

	if (field_1.identifier == nullptr)
		field_1 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("field_70163_u"), XOR("D"));

	if (field_1.identifier == nullptr)
		field_1 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("t"), XOR("D"));

	if (field_2.identifier == nullptr)
		field_2 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("field_70161_v"), XOR("D"));

	if (field_2.identifier == nullptr)
		field_2 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("u"), XOR("D"));

	return client::mapper::__vec3(
		client::mapper::jni->GetDoubleField(this->object, field_0.identifier),
		client::mapper::jni->GetDoubleField(this->object, field_1.identifier),
		client::mapper::jni->GetDoubleField(this->object, field_2.identifier)
	);
}

auto client::mapper::__player::set_position(client::mapper::__vec3 position) -> void
{
	static auto field_0 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("posX"), XOR("D"));
	static auto field_1 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("posY"), XOR("D"));
	static auto field_2 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("posZ"), XOR("D"));

	if (field_0.identifier == nullptr)
		field_0 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("field_70165_t"), XOR("D"));

	if (field_0.identifier == nullptr)
		field_0 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("s"), XOR("D"));

	if (field_1.identifier == nullptr)
		field_1 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("field_70163_u"), XOR("D"));

	if (field_1.identifier == nullptr)
		field_1 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("t"), XOR("D"));

	if (field_2.identifier == nullptr)
		field_2 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("field_70161_v"), XOR("D"));

	if (field_2.identifier == nullptr)
		field_2 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("u"), XOR("D"));

	client::mapper::jni->SetDoubleField(this->object, field_0.identifier, position.x);
	client::mapper::jni->SetDoubleField(this->object, field_1.identifier, position.y);
	client::mapper::jni->SetDoubleField(this->object, field_2.identifier, position.z);
}

auto client::mapper::__player::get_old_position() -> client::mapper::__vec3
{
	static auto field_0 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("prevPosX"), XOR("D"));
	static auto field_1 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("prevPosY"), XOR("D"));
	static auto field_2 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("prevPosZ"), XOR("D"));

	if (field_0.identifier == nullptr)
		field_0 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("field_70169_q"), XOR("D"));

	if (field_0.identifier == nullptr)
		field_0 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("p"), XOR("D"));

	if (field_1.identifier == nullptr)
		field_1 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("field_70167_r"), XOR("D"));

	if (field_1.identifier == nullptr)
		field_1 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("q"), XOR("D"));

	if (field_2.identifier == nullptr)
		field_2 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("field_70166_s"), XOR("D"));

	if (field_2.identifier == nullptr)
		field_2 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("r"), XOR("D"));

	return client::mapper::__vec3(
		client::mapper::jni->GetDoubleField(this->object, field_0.identifier),
		client::mapper::jni->GetDoubleField(this->object, field_1.identifier),
		client::mapper::jni->GetDoubleField(this->object, field_2.identifier)
	);
}

auto client::mapper::__player::set_old_position(client::mapper::__vec3 old_position) -> void
{
	static auto field_0 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("prevPosX"), XOR("D"));
	static auto field_1 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("prevPosY"), XOR("D"));
	static auto field_2 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("prevPosZ"), XOR("D"));

	if (field_0.identifier == nullptr)
		field_0 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("field_70169_q"), XOR("D"));

	if (field_0.identifier == nullptr)
		field_0 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("p"), XOR("D"));

	if (field_1.identifier == nullptr)
		field_1 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("field_70167_r"), XOR("D"));

	if (field_1.identifier == nullptr)
		field_1 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("q"), XOR("D"));

	if (field_2.identifier == nullptr)
		field_2 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("field_70166_s"), XOR("D"));

	if (field_2.identifier == nullptr)
		field_2 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("r"), XOR("D"));

	client::mapper::jni->SetDoubleField(this->object, field_0.identifier, old_position.x);
	client::mapper::jni->SetDoubleField(this->object, field_1.identifier, old_position.y);
	client::mapper::jni->SetDoubleField(this->object, field_2.identifier, old_position.z);
}

auto client::mapper::__player::get_motion() -> client::mapper::__vec3
{
	static auto field_0 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("motionX"), XOR("D"));
	static auto field_1 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("motionY"), XOR("D"));
	static auto field_2 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("motionZ"), XOR("D"));

	if (field_0.identifier == nullptr)
		field_0 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("field_70159_w"), XOR("D"));

	if (field_0.identifier == nullptr)
		field_0 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("v"), XOR("D"));

	if (field_1.identifier == nullptr)
		field_1 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("field_70181_x"), XOR("D"));

	if (field_1.identifier == nullptr)
		field_1 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("w"), XOR("D"));

	if (field_2.identifier == nullptr)
		field_2 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("field_70179_y"), XOR("D"));

	if (field_2.identifier == nullptr)
		field_2 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("x"), XOR("D"));

	return client::mapper::__vec3(
		client::mapper::jni->GetDoubleField(this->object, field_0.identifier),
		client::mapper::jni->GetDoubleField(this->object, field_1.identifier),
		client::mapper::jni->GetDoubleField(this->object, field_2.identifier)
	);
}

auto client::mapper::__player::set_motion(client::mapper::__vec3 motion) -> void
{
	static auto field_0 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("motionX"), XOR("D"));
	static auto field_1 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("motionY"), XOR("D"));
	static auto field_2 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("motionZ"), XOR("D"));

	if (field_0.identifier == nullptr)
		field_0 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("field_70159_w"), XOR("D"));

	if (field_0.identifier == nullptr)
		field_0 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("v"), XOR("D"));

	if (field_1.identifier == nullptr)
		field_1 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("field_70181_x"), XOR("D"));

	if (field_1.identifier == nullptr)
		field_1 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("w"), XOR("D"));

	if (field_2.identifier == nullptr)
		field_2 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("field_70179_y"), XOR("D"));

	if (field_2.identifier == nullptr)
		field_2 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("x"), XOR("D"));

	client::mapper::jni->SetDoubleField(this->object, field_0.identifier, motion.x);
	client::mapper::jni->SetDoubleField(this->object, field_1.identifier, motion.y);
	client::mapper::jni->SetDoubleField(this->object, field_2.identifier, motion.z);
}

auto client::mapper::__player::get_on_ground() -> bool
{
	static auto field = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("onGround"), XOR("Z"));

	if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("field_70122_E"), XOR("Z"));

	if (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17)
	{
		if (field.identifier == nullptr)
			field = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("D"), XOR("Z"));
	}
	else if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("C"), XOR("Z"));

	return client::mapper::jni->GetBooleanField(this->object, field.identifier);
}

auto client::mapper::__player::jump() -> void
{
	static auto method = client::mapper::classes[XOR("EntityPlayer")].get_method(XOR("jump"), XOR("()V"));

	if (method.identifier == nullptr)
		method = client::mapper::classes[XOR("EntityPlayer")].get_method(XOR("func_70664_aZ"), XOR("()V"));

	if (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17)
	{
		if (method.identifier == nullptr)
			method = client::mapper::classes[XOR("EntityPlayer")].get_method(XOR("bj"), XOR("()V"));
	}
	else if (method.identifier == nullptr)
		method = client::mapper::classes[XOR("EntityPlayer")].get_method(XOR("bF"), XOR("()V"));

	return client::mapper::jni->CallVoidMethod(this->object, method.identifier);
}

auto client::mapper::__player::is_swing_in_progress() -> bool
{
	static auto field = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("isSwingInProgress"), XOR("Z"));

	if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("field_82175_bq"), XOR("Z"));

	if (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17)
	{
		if (field.identifier == nullptr)
			field = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("at"), XOR("Z"));
	}
	else if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("ar"), XOR("Z"));

	return client::mapper::jni->GetBooleanField(this->object, field.identifier);
}

auto client::mapper::__player::get_hurt_time() -> __int32
{
	static auto field = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("hurtTime"), XOR("I"));

	if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("field_70737_aN"), XOR("I"));

	if (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17)
	{
		if (field.identifier == nullptr)
			field = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("ay"), XOR("I"));
	}
	else if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("ax"), XOR("I"));

	return client::mapper::jni->GetIntField(this->object, field.identifier);
}

auto client::mapper::__player::set_hurt_time(__int32 hurt_time) -> void
{
	static auto field = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("hurtTime"), XOR("I"));

	if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("field_70737_aN"), XOR("I"));

	if (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17)
	{
		if (field.identifier == nullptr)
			field = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("ay"), XOR("I"));
	}
	else if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("ax"), XOR("I"));

	return client::mapper::jni->SetIntField(this->object, field.identifier, hurt_time);
}

auto client::mapper::__player::is_vulnerable() -> bool
{
	return this->get_health() > 0.f && this->get_hurt_time() < 5;
}

auto client::mapper::__player::get_view_position(float partial_ticks) -> client::mapper::__vec3
{
	auto position = this->get_position(), old_position = this->get_old_position();

	return client::mapper::__vec3(
		old_position.x + (position.x - old_position.x) * partial_ticks,
		old_position.y + (position.y - old_position.y) * partial_ticks,
		old_position.z + (position.z - old_position.z) * partial_ticks
	);
}

auto client::mapper::__player::get_look_position(float partial_ticks) -> client::mapper::__vec3
{
	auto get_vec3_for_rotation = [](float yaw, float pitch) -> client::mapper::__vec3
	{
		float f0 = cos(-yaw * .017453292 - 3.14159265358979323846);
		float f1 = sin(-yaw * .017453292 - 3.14159265358979323846);
		float f2 = cos(-pitch * .017453292);
		float f3 = sin(-pitch * .017453292);

		return client::mapper::__vec3(f1 * -f2, f3, f0 * -f2);
	};

	auto view_angles = this->get_view_angles(), old_view_angles = this->get_view_angles();

	return get_vec3_for_rotation(
		old_view_angles.x + (view_angles.x - old_view_angles.x) * partial_ticks,
		old_view_angles.y + (view_angles.y - old_view_angles.y) * partial_ticks
	);
}

auto client::mapper::__player::get_view_angles() -> client::mapper::__vec2
{
	static auto field_0 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("rotationYaw"), XOR("F"));
	static auto field_1 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("rotationPitch"), XOR("F"));

	if (field_0.identifier == nullptr)
		field_0 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("field_70177_z"), XOR("F"));

	if (field_0.identifier == nullptr)
		field_0 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("y"), XOR("F"));

	if (field_1.identifier == nullptr)
		field_1 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("field_70125_A"), XOR("F"));

	if (field_1.identifier == nullptr)
		field_1 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("z"), XOR("F"));

	return client::mapper::__vec2(
		client::mapper::jni->GetFloatField(this->object, field_0.identifier),
		client::mapper::jni->GetFloatField(this->object, field_1.identifier)
	);
}

auto client::mapper::__player::set_view_angles(client::mapper::__vec2 view_angles) -> void
{
	static auto field_0 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("rotationYaw"), XOR("F"));
	static auto field_1 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("rotationPitch"), XOR("F"));

	if (field_0.identifier == nullptr)
		field_0 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("field_70177_z"), XOR("F"));

	if (field_0.identifier == nullptr)
		field_0 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("y"), XOR("F"));

	if (field_1.identifier == nullptr)
		field_1 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("field_70125_A"), XOR("F"));

	if (field_1.identifier == nullptr)
		field_1 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("z"), XOR("F"));

	client::mapper::jni->SetFloatField(this->object, field_0.identifier, view_angles.x);
	client::mapper::jni->SetFloatField(this->object, field_1.identifier, view_angles.y);
}

auto client::mapper::__player::get_old_view_angles() -> client::mapper::__vec2
{
	static auto field_0 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("prevRotationYaw"), XOR("F"));
	static auto field_1 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("prevRotationPitch"), XOR("F"));

	if (field_0.identifier == nullptr)
		field_0 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("field_70126_B"), XOR("F"));

	if (field_0.identifier == nullptr)
		field_0 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("A"), XOR("F"));

	if (field_1.identifier == nullptr)
		field_1 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("field_70127_C"), XOR("F"));

	if (field_1.identifier == nullptr)
		field_1 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("B"), XOR("F"));

	return client::mapper::__vec2(
		client::mapper::jni->GetFloatField(this->object, field_0.identifier),
		client::mapper::jni->GetFloatField(this->object, field_1.identifier)
	);
}

auto client::mapper::__player::set_old_view_angles(client::mapper::__vec2 old_view_angles) -> void
{
	static auto field_0 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("prevRotationYaw"), XOR("F"));
	static auto field_1 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("prevRotationPitch"), XOR("F"));

	if (field_0.identifier == nullptr)
		field_0 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("field_70126_B"), XOR("F"));

	if (field_0.identifier == nullptr)
		field_0 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("A"), XOR("F"));

	if (field_1.identifier == nullptr)
		field_1 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("field_70127_C"), XOR("F"));

	if (field_1.identifier == nullptr)
		field_1 = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("B"), XOR("F"));

	client::mapper::jni->SetFloatField(this->object, field_0.identifier, old_view_angles.x);
	client::mapper::jni->SetFloatField(this->object, field_1.identifier, old_view_angles.y);
}

auto client::mapper::__player::get_ticks_existed() -> __int32
{
	static auto field = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("ticksExisted"), XOR("I"));

	if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("field_70173_aa"), XOR("I"));

	if (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17)
	{
		if (field.identifier == nullptr)
			field = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("aa"), XOR("I"));
	}
	else if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("W"), XOR("I"));

	return client::mapper::jni->GetIntField(this->object, field.identifier);
}

auto client::mapper::__player::get_health() -> float
{
	static auto method = client::mapper::classes[XOR("EntityPlayerXP")].get_method(XOR("getHealth"), XOR("()F"));

	if (method.identifier == nullptr)
		method = client::mapper::classes[XOR("EntityPlayerXP")].get_method(XOR("func_110143_aJ"), XOR("()F"));

	if (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17)
	{
		if (method.identifier == nullptr)
			method = client::mapper::classes[XOR("EntityPlayerXP")].get_method(XOR("aS"), XOR("()F"));
	}
	else if (method.identifier == nullptr)
			method = client::mapper::classes[XOR("EntityPlayerXP")].get_method(XOR("bn"), XOR("()F"));

	return client::mapper::jni->CallFloatMethod(this->object, method.identifier);
}

auto client::mapper::__player::get_move_foreward() -> float
{
	static auto field = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("moveForward"), XOR("F"));

	if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("field_70701_bs"), XOR("F"));

	if (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17)
	{
		if (field.identifier == nullptr)
			field = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("be"), XOR("F"));
	}
	else if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("ba"), XOR("F"));

	return client::mapper::jni->GetFloatField(this->object, field.identifier);
}

auto client::mapper::__player::get_move_strafing() -> float
{
	static auto field = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("moveStrafing"), XOR("F"));

	if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("field_70702_br"), XOR("F"));

	if (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17)
	{
		if (field.identifier == nullptr)
			field = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("bd"), XOR("F"));
	}
	else if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("aZ"), XOR("F"));

	return client::mapper::jni->GetFloatField(this->object, field.identifier);
}

auto client::mapper::__player::get_total_armor_value() -> __int32
{
	static auto method = client::mapper::classes[XOR("EntityPlayerXP")].get_method(XOR("getTotalArmorValue"), XOR("()I"));

	if (method.identifier == nullptr)
		method = client::mapper::classes[XOR("EntityPlayerXP")].get_method(XOR("func_70658_aO"), XOR("()I"));

	if (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17)
	{
		if (method.identifier == nullptr)
			method = client::mapper::classes[XOR("EntityPlayerXP")].get_method(XOR("aV"), XOR("()I"));
	}
	else if (method.identifier == nullptr)
		method = client::mapper::classes[XOR("EntityPlayerXP")].get_method(XOR("br"), XOR("()I"));

	return client::mapper::jni->CallIntMethod(this->object, method.identifier);
}

auto client::mapper::__player::can_entity_be_seen(client::mapper::__player player) -> bool
{
	static auto method = []() -> client::mapper::__method
	{
		auto signature = sdk::__multibyte_string();

		signature.concatenate(XOR("("));
		signature.concatenate(client::mapper::classes[XOR("Entity")].signature.get_multibyte_string());
		signature.concatenate(XOR(")Z"));

		auto method = client::mapper::classes[XOR("EntityPlayerXP")].get_method(XOR("canEntityBeSeen"), signature);

		if (method.identifier == nullptr)
			method = client::mapper::classes[XOR("EntityPlayerXP")].get_method(XOR("func_70685_l"), signature);

		if (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17)
		{
			if (method.identifier == nullptr)
				method = client::mapper::classes[XOR("EntityPlayerXP")].get_method(XOR("p"), signature);
		}
		else if (method.identifier == nullptr)
			method = client::mapper::classes[XOR("EntityPlayerXP")].get_method(XOR("t"), signature);

		return method;
	}();

	return client::mapper::jni->CallBooleanMethod(this->object, method.identifier, player.object);
}

auto client::mapper::__player::get_flag(__int32 flag) -> bool
{
	static auto method = client::mapper::classes[XOR("EntityPlayerXP")].get_method(XOR("getFlag"), XOR("(I)Z"));

	if (method.identifier == nullptr)
		method = client::mapper::classes[XOR("EntityPlayerXP")].get_method(XOR("func_70083_f"), XOR("(I)Z"));

	if (method.identifier == nullptr)
		method = client::mapper::classes[XOR("EntityPlayerXP")].get_method(XOR("g"), XOR("(I)Z"));

	return client::mapper::jni->CallBooleanMethod(this->object, method.identifier, flag);
}

auto client::mapper::__player::set_flag(__int32 flag, bool state) -> void
{
	static auto method = client::mapper::classes[XOR("EntityPlayerXP")].get_method(XOR("setFlag"), XOR("(IZ)V"));

	if (method.identifier == nullptr)
		method = client::mapper::classes[XOR("EntityPlayerXP")].get_method(XOR("func_70052_a"), XOR("(IZ)V"));

	if (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17)
	{
		if (method.identifier == nullptr)
			method = client::mapper::classes[XOR("EntityPlayerXP")].get_method(XOR("a"), XOR("(IZ)V"));
	}
	else if (method.identifier == nullptr)
		method = client::mapper::classes[XOR("EntityPlayerXP")].get_method(XOR("b"), XOR("(IZ)V"));

	return client::mapper::jni->CallVoidMethod(this->object, method.identifier, flag, state);
}

auto client::mapper::__player::is_offset_position_in_liquid(double x, double y, double z) -> bool
{
	static auto method = client::mapper::classes[XOR("EntityPlayerXP")].get_method(XOR("isOffsetPositionInLiquid"), XOR("(DDD)Z"));

	if (method.identifier == nullptr)
		method = client::mapper::classes[XOR("EntityPlayerXP")].get_method(XOR("func_70038_c"), XOR("(DDD)Z"));

	if (method.identifier == nullptr)
		method = client::mapper::classes[XOR("EntityPlayerXP")].get_method(XOR("c"), XOR("(DDD)Z"));

	return !client::mapper::jni->CallBooleanMethod(this->object, method.identifier, x, y, z);
}

auto client::mapper::__player::get_held_item_stack() -> client::mapper::__item_stack
{
	static auto method = []() -> client::mapper::__method
	{
		auto signature = sdk::__multibyte_string();

		signature.concatenate(XOR("()"));
		signature.concatenate(client::mapper::classes[XOR("ItemStack")].signature.get_multibyte_string());

		auto method = client::mapper::classes[XOR("EntityPlayerXP")].get_method(XOR("getHeldItem"), signature);

		if (method.identifier == nullptr)
			method = client::mapper::classes[XOR("EntityPlayerXP")].get_method(XOR("func_70694_bm"), signature);

		if (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17)
		{
			if (method.identifier == nullptr)
				method = client::mapper::classes[XOR("EntityPlayerXP")].get_method(XOR("be"), signature);
		}
		else if (method.identifier == nullptr)
			method = client::mapper::classes[XOR("EntityPlayerXP")].get_method(XOR("bA"), signature);

		return method;
	}();

	return client::mapper::__item_stack(client::mapper::jni->CallObjectMethod(this->object, method.identifier));
}

auto client::mapper::__player::get_name() -> sdk::__multibyte_string
{
	static auto method = client::mapper::classes[XOR("EntityPlayerXP")].get_method((client::mapper::version == client::mapper::supported_versions::MINECRAFT_17 ? XOR("getCommandSenderName") : XOR("getName")), XOR("()Ljava/lang/String;"));

	if (method.identifier == nullptr)
		method = client::mapper::classes[XOR("EntityPlayerXP")].get_method(XOR("getCommandSenderName"), XOR("()Ljava/lang/String;"));

	if (method.identifier == nullptr)
		method = client::mapper::classes[XOR("EntityPlayerXP")].get_method(XOR("func_70005_c_"), XOR("()Ljava/lang/String;"));

	if (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17)
	{
		if (method.identifier == nullptr)
			method = client::mapper::classes[XOR("EntityPlayerXP")].get_method(XOR("b_"), XOR("()Ljava/lang/String;"));
	}
	else if (method.identifier == nullptr)
		method = client::mapper::classes[XOR("EntityPlayerXP")].get_method(XOR("e_"), XOR("()Ljava/lang/String;"));

	auto object = client::mapper::jni->CallObjectMethod(this->object, method.identifier);

	auto name = (char*)client::mapper::jni->GetStringUTFChars((_jstring*)object, nullptr);

	auto fixed_name = sdk::__multibyte_string(name);

	client::mapper::jni->ReleaseStringUTFChars((_jstring*)object, name);

	return fixed_name;
}

auto client::mapper::__player::get_bounding_box() -> client::mapper::__axis_aligned
{
	static auto field = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("boundingBox"), client::mapper::classes[XOR("AxisAlignedBB")].signature.get_multibyte_string());

	if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("field_70121_D"), client::mapper::classes[XOR("AxisAlignedBB")].signature.get_multibyte_string());

	if (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17)
	{
		if (field.identifier == nullptr)
			field = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("C"), client::mapper::classes[XOR("AxisAlignedBB")].signature.get_multibyte_string());
	}
	else if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("EntityPlayerXP")].get_field(XOR("f"), client::mapper::classes[XOR("AxisAlignedBB")].signature.get_multibyte_string());

	return client::mapper::__axis_aligned(client::mapper::jni->GetObjectField(this->object, field.identifier));
}

auto client::mapper::__player::can_attack_player(client::mapper::__player player) -> bool
{
	static auto method = []() -> client::mapper::__method
	{
		auto signature = sdk::__multibyte_string();

		signature.concatenate(XOR("("));
		signature.concatenate(client::mapper::classes[XOR("EntityPlayer")].signature.get_multibyte_string());
		signature.concatenate(XOR(")Z"));

		auto method = client::mapper::classes[XOR("EntityPlayerXP")].get_method(XOR("canAttackPlayer"), signature);

		if (method.identifier == nullptr)
			method = client::mapper::classes[XOR("EntityPlayerXP")].get_method(XOR("func_96122_a"), signature);

		if (method.identifier == nullptr)
			method = client::mapper::classes[XOR("EntityPlayerXP")].get_method(XOR("a"), signature);

		return method;
	}();

	return client::mapper::jni->CallBooleanMethod(this->object, method.identifier, player.object);
}