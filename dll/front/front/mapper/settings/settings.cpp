
#include "../mapper.hpp"

client::mapper::__settings::__settings(_jobject* object)
{
	this->object = object;
}

client::mapper::__settings::__settings(const client::mapper::__settings& settings)
{
	if (settings.object != nullptr)
		this->object = client::mapper::jni->NewLocalRef(settings.object);
}

client::mapper::__settings::~__settings()
{
	if (this->object != nullptr)
		client::mapper::jni->DeleteLocalRef(this->object);
}

auto client::mapper::__settings::get_mouse_sensitivity() -> float
{
	static auto field = client::mapper::classes[XOR("GameSettings")].get_field(XOR("mouseSensitivity"), XOR("F"));

	if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("GameSettings")].get_field(XOR("field_74341_c"), XOR("F"));

	if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("GameSettings")].get_field(XOR("a"), XOR("F"));

	return client::mapper::jni->GetFloatField(this->object, field.identifier);
}