
#include "../mapper.hpp"

client::mapper::__timer::__timer(_jobject* object)
{
	this->object = object;
}

client::mapper::__timer::__timer(const client::mapper::__timer& timer)
{
	if (timer.object != nullptr)
		this->object = client::mapper::jni->NewLocalRef(timer.object);
}

client::mapper::__timer::~__timer()
{
	if (this->object != nullptr)
		client::mapper::jni->DeleteLocalRef(this->object);
}

auto client::mapper::__timer::get_partial_ticks() -> float
{
	static auto field = client::mapper::classes[XOR("Timer")].get_field(XOR("renderPartialTicks"), XOR("F"));

	if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("Timer")].get_field(XOR("field_74281_c"), XOR("F"));

	if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("Timer")].get_field(XOR("c"), XOR("F"));

	return client::mapper::jni->GetFloatField(this->object, field.identifier);
}