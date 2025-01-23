
#include "../mapper.hpp"

client::mapper::__item_stack::__item_stack(_jobject* object)
{
	this->object = object;
}

client::mapper::__item_stack::__item_stack(const client::mapper::__item_stack& item_stack)
{
	if (item_stack.object != nullptr)
		this->object = client::mapper::jni->NewLocalRef(item_stack.object);
}

client::mapper::__item_stack::~__item_stack()
{
	if (this->object != nullptr)
		client::mapper::jni->DeleteLocalRef(this->object);
}

auto client::mapper::__item_stack::get_item() -> client::mapper::__item
{
	static auto field = client::mapper::classes[XOR("ItemStack")].get_field(
		(client::mapper::version == client::mapper::supported_versions::MINECRAFT_17 ? XOR("theItem") : XOR("item")), client::mapper::classes[XOR("Item")].signature.get_multibyte_string());

	if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("ItemStack")].get_field(XOR("field_151002_e"), client::mapper::classes[XOR("Item")].signature.get_multibyte_string());

	if (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17)
	{
		if (field.identifier == nullptr)
			field = client::mapper::classes[XOR("ItemStack")].get_field(XOR("e"), client::mapper::classes[XOR("Item")].signature.get_multibyte_string());
	}
	else if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("ItemStack")].get_field(XOR("d"), client::mapper::classes[XOR("Item")].signature.get_multibyte_string());

	return client::mapper::__item(client::mapper::jni->GetObjectField(this->object, field.identifier));
}