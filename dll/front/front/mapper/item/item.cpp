
#include "../mapper.hpp"

client::mapper::__item::__item(_jobject* object)
{
	this->object = object;
}

client::mapper::__item::__item(const client::mapper::__item& item)
{
	if (item.object != nullptr)
		this->object = client::mapper::jni->NewLocalRef(item.object);
}

client::mapper::__item::~__item()
{
	if (this->object != nullptr)
		client::mapper::jni->DeleteLocalRef(this->object);
}

auto client::mapper::__item::get_id() -> __int32
{
	static auto method = []() -> client::mapper::__method
	{
		auto signature = sdk::__multibyte_string();

		signature.concatenate(XOR("("));
		signature.concatenate(client::mapper::classes[XOR("Item")].signature.get_multibyte_string());
		signature.concatenate(XOR(")I"));

		auto method = client::mapper::classes[XOR("Item")].get_method(XOR("getIdFromItem"), signature);

		if (method.identifier == nullptr)
			method = client::mapper::classes[XOR("Item")].get_method(XOR("func_150891_b"), signature);

		if (method.identifier == nullptr)
			method = client::mapper::classes[XOR("Item")].get_method(XOR("b"), signature);

		return method;
	}();

	return client::mapper::jni->CallStaticIntMethod(client::mapper::classes[XOR("Item")].klass, method.identifier, this->object);
}

auto client::mapper::__item::is_sword() -> bool
{
	auto id = this->get_id();

	return id == 267 || id == 268 || id == 272 || id == 276 || id == 283;
}

auto client::mapper::__item::is_axe() -> bool
{
	auto id = this->get_id();

	return id == 258 || id == 271 || id == 275 || id == 279 || id == 286;
}

auto client::mapper::__item::is_pickaxe() -> bool
{
	auto id = this->get_id();

	return id == 278 || id == 257 || id == 274 || id == 270 || id == 285;
}

auto client::mapper::__item::is_shovel() -> bool
{
	auto id = this->get_id();

	return id == 277 || id == 256 || id == 284 || id == 273 || id == 269;
}

auto client::mapper::__item::is_block() -> bool
{
	auto id = this->get_id();

	return id >= 1 && id <= 5 || id == 7 || id >= 13 && id <= 30 || id >= 33 && id <= 35 || id >= 41 && id <= 49 || id >= 52 && id <= 53 || id >= 56 && id <= 58 || id >= 60 && id <= 62 ||
		id == 67 || id >= 73 && id <= 74 || id >= 78 && id <= 80 || id == 82 || id >= 84 && id <= 91 || id >= 95 && id <= 103 || id >= 108 && id <= 110 || id >= 112 && id <= 114 || id >= 120 && id <= 121 ||
		id >= 123 && id <= 126 || id >= 128 && id <= 129 || id >= 133 && id <= 139 || id >= 152 && id <= 153 || id >= 155 && id <= 156 || id >= 158 && id <= 166 || id >= 168 && id <= 170 || id >= 172 && id <= 174 || id >= 178 && id <= 182;
}