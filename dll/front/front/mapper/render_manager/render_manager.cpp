
#include "../mapper.hpp"

client::mapper::__render_manager::__render_manager(_jobject* object)
{
	this->object = object;
}

client::mapper::__render_manager::__render_manager(const client::mapper::__render_manager& render_manager)
{
	if (render_manager.object != nullptr)
		this->object = client::mapper::jni->NewLocalRef(render_manager.object);
}

client::mapper::__render_manager::~__render_manager()
{
	if (this->object != nullptr)
		client::mapper::jni->DeleteLocalRef(this->object);
}

auto client::mapper::__render_manager::render_player(client::mapper::__player player, float partial_ticks) -> bool
{
	static auto method = []() -> client::mapper::__method
	{
		auto signature = sdk::__multibyte_string();

		signature.concatenate(XOR("("));
		signature.concatenate(client::mapper::classes[XOR("Entity")].signature.get_multibyte_string());
		signature.concatenate(XOR("F)Z"));

		auto method = client::mapper::classes[XOR("RenderManager")].get_method(XOR("renderEntitySimple"), signature);

		if (method.identifier == nullptr)
			method = client::mapper::classes[XOR("RenderManager")].get_method(XOR("func_147937_a"), signature);

		if (method.identifier == nullptr)
			method = client::mapper::classes[XOR("RenderManager")].get_method(XOR("a"), signature);

		return method;
	}();

	return client::mapper::jni->CallBooleanMethod(this->object, method.identifier, player.object, partial_ticks);
}

auto client::mapper::__render_manager::render_player(client::mapper::__player player, double x, double y, double z, float yaw, float partial_ticks) -> bool
{
	static auto method = []() -> client::mapper::__method
	{
		auto signature = sdk::__multibyte_string();

		signature.concatenate(XOR("("));
		signature.concatenate(client::mapper::classes[XOR("Entity")].signature.get_multibyte_string());
		signature.concatenate(XOR("DDDFF)Z"));

		auto method = client::mapper::classes[XOR("RenderManager")].get_method(XOR("renderEntityWithPosYaw"), signature);

		if (method.identifier == nullptr)
			method = client::mapper::classes[XOR("RenderManager")].get_method(XOR("func_147940_a"), signature);

		if (method.identifier == nullptr)
			method = client::mapper::classes[XOR("RenderManager")].get_method(XOR("a"), signature);

		return method;
	}();

	return client::mapper::jni->CallBooleanMethod(this->object, method.identifier, player.object, x, y, z, yaw, partial_ticks);
}