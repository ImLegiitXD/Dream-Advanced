
#include "../mapper.hpp"

client::mapper::__moving_object_position::__moving_object_position(_jobject* object)
{
	this->object = object;
}

client::mapper::__moving_object_position::__moving_object_position(client::mapper::__player player, client::mapper::__vec3__ vec3)
{
	static auto method = []() -> client::mapper::__method
	{
		auto signature = sdk::__multibyte_string();

		signature.concatenate(XOR("("));
		signature.concatenate(client::mapper::classes[XOR("Entity")].signature.get_multibyte_string());
		signature.concatenate(client::mapper::classes[XOR("Vec3")].signature.get_multibyte_string());
		signature.concatenate(XOR(")V"));

		return client::mapper::classes[XOR("MovingObjectPosition")].get_method(XOR("<init>"), signature);
	}();

	this->object = client::mapper::jni->NewObject(client::mapper::classes[XOR("MovingObjectPosition")].klass, method.identifier, player.object, vec3.object);
}

client::mapper::__moving_object_position::__moving_object_position(const client::mapper::__moving_object_position& moving_object_position)
{
	if (moving_object_position.object != nullptr)
		this->object = client::mapper::jni->NewLocalRef(moving_object_position.object);
}

client::mapper::__moving_object_position::~__moving_object_position()
{
	if (this->object != nullptr)
		client::mapper::jni->DeleteLocalRef(this->object);
}

auto client::mapper::__moving_object_position::get_type_of_hit() -> __int32
{
	static auto type_of_hit_field = client::mapper::classes[XOR("MovingObjectPosition")].get_field(XOR("typeOfHit"), client::mapper::classes[XOR("MovingObjectPosition_MovingObjectType")].signature.get_multibyte_string());

	if (type_of_hit_field.identifier == nullptr)
		type_of_hit_field = client::mapper::classes[XOR("MovingObjectPosition")].get_field(XOR("field_72313_a"), client::mapper::classes[XOR("MovingObjectPosition_MovingObjectType")].signature.get_multibyte_string());

	if (type_of_hit_field.identifier == nullptr)
		type_of_hit_field = client::mapper::classes[XOR("MovingObjectPosition")].get_field(XOR("a"), client::mapper::classes[XOR("MovingObjectPosition_MovingObjectType")].signature.get_multibyte_string());

	auto object = client::mapper::jni->GetObjectField(this->object, type_of_hit_field.identifier);

	static auto ordinal_field = client::mapper::classes[XOR("Enum")].get_field(XOR("ordinal"), XOR("I"));

	auto type_of_hit = jni->GetIntField(object, ordinal_field.identifier);

	client::mapper::jni->DeleteLocalRef(object);

	return type_of_hit;
}

auto client::mapper::__moving_object_position::get_hit_vector() -> client::mapper::__vec3__
{
	static auto field = client::mapper::classes[XOR("MovingObjectPosition")].get_field(XOR("hitVec"), client::mapper::classes[XOR("Vec3")].signature.get_multibyte_string());

	if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("MovingObjectPosition")].get_field(XOR("field_72307_f"), client::mapper::classes[XOR("Vec3")].signature.get_multibyte_string());

	if (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17)
	{
		if (field.identifier == nullptr)
			field = client::mapper::classes[XOR("MovingObjectPosition")].get_field(XOR("f"), client::mapper::classes[XOR("Vec3")].signature.get_multibyte_string());
	}
	else if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("MovingObjectPosition")].get_field(XOR("c"), client::mapper::classes[XOR("Vec3")].signature.get_multibyte_string());

	return client::mapper::__vec3__(client::mapper::jni->GetObjectField(this->object, field.identifier));
}