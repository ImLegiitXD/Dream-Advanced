
#include "../mapper.hpp"

client::mapper::__world::__world(_jobject* object)
{
	this->object = object;
}

client::mapper::__world::__world(const client::mapper::__world& world)
{
	if (world.object != nullptr)
		this->object = client::mapper::jni->NewLocalRef(world.object);
}

client::mapper::__world::~__world()
{
	if (this->object != nullptr)
		client::mapper::jni->DeleteLocalRef(this->object);
}

auto client::mapper::__world::get_players() -> std::vector<client::mapper::__player>
{
	auto players = std::vector<client::mapper::__player>();

	static auto field = client::mapper::classes[XOR("WorldClient")].get_field(XOR("playerEntities"), client::mapper::classes[XOR("List")].signature.get_multibyte_string());

	if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("WorldClient")].get_field(XOR("field_73010_i"), client::mapper::classes[XOR("List")].signature.get_multibyte_string());

	if (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17)
	{
		if (field.identifier == nullptr)
			field = client::mapper::classes[XOR("WorldClient")].get_field(XOR("h"), client::mapper::classes[XOR("List")].signature.get_multibyte_string());
	}
	else if (field.identifier == nullptr)
		field = client::mapper::classes[XOR("WorldClient")].get_field(XOR("j"), client::mapper::classes[XOR("List")].signature.get_multibyte_string());

	auto object = client::mapper::jni->GetObjectField(this->object, field.identifier);

	static auto method = client::mapper::classes[XOR("List")].get_method(XOR("toArray"), XOR("()[Ljava/lang/Object;"));

	auto array_object = (_jobjectArray*)client::mapper::jni->CallObjectMethod(object, method.identifier);

	for (__int32 x = 0, array_object_length = client::mapper::jni->GetArrayLength(array_object); x < array_object_length; ++x)
	{
		auto player = client::mapper::__player(client::mapper::jni->GetObjectArrayElement(array_object, x));

		if (![&]() -> bool
		{
			auto player_name = player.get_name();

			auto player_name_length = player_name.get_length();

			if (player_name_length < 3)
				return true;

			for (unsigned __int64 x = 0; x < player_name_length; ++x)
			{
				if (!(
					(player_name.get_multibyte_string()[x] >= 'a' && player_name.get_multibyte_string()[x] <= 'z') ||
					(player_name.get_multibyte_string()[x] >= 'A' && player_name.get_multibyte_string()[x] <= 'Z') ||
					(player_name.get_multibyte_string()[x] >= '0' && player_name.get_multibyte_string()[x] <= '9') ||
					(player_name.get_multibyte_string()[x] == '_')))
					return true;
			}

			return false;
		}())
			players.push_back(player);
	}

	client::mapper::jni->DeleteLocalRef(object);
	client::mapper::jni->DeleteLocalRef(array_object);

	return players;
}

auto client::mapper::__world::get_block_id(double x, double y, double z) -> __int32
{
	__int32 block_id = 0;

	if (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17)
	{
		static auto method_0 = []() -> client::mapper::__method
		{
			auto signature = sdk::__multibyte_string();

			signature.concatenate(XOR("(III)"));
			signature.concatenate(client::mapper::classes[XOR("Block")].signature.get_multibyte_string());

			auto method = client::mapper::classes[XOR("WorldClient")].get_method(XOR("getBlock"), signature);

			if (method.identifier == nullptr)
				method = client::mapper::classes[XOR("WorldClient")].get_method(XOR("func_147439_a"), signature);

			if (method.identifier == nullptr)
				method = client::mapper::classes[XOR("WorldClient")].get_method(XOR("a"), signature);

			return method;
		}();
	
		auto object = client::mapper::jni->CallObjectMethod(this->object, method_0.identifier, (__int32)x, (__int32)y, (__int32)z);

		static auto method_1 = []() -> client::mapper::__method
		{
			auto signature = sdk::__multibyte_string();

			signature.concatenate(XOR("("));
			signature.concatenate(client::mapper::classes[XOR("Block")].signature.get_multibyte_string());
			signature.concatenate(XOR(")I"));

			auto method = client::mapper::classes[XOR("Block")].get_method(XOR("getIdFromBlock"), signature);

			if (method.identifier == nullptr)
				method = client::mapper::classes[XOR("Block")].get_method(XOR("func_149682_b"), signature);

			if (method.identifier == nullptr)
				method = client::mapper::classes[XOR("Block")].get_method(XOR("b"), signature);

			return method;
		}();

		block_id = client::mapper::jni->CallStaticIntMethod(client::mapper::classes[XOR("Block")].klass, method_1.identifier, object);

		client::mapper::jni->DeleteLocalRef(object);
	}
	else
	{
		static auto method_0 = client::mapper::classes[XOR("BlockPos")].get_method(XOR("<init>"), XOR("(DDD)V"));
		
		auto object_0 = client::mapper::jni->NewObject(client::mapper::classes[XOR("BlockPos")].klass, method_0.identifier, x, y, z);

		static auto method_1 = []() -> client::mapper::__method
		{
			auto signature = sdk::__multibyte_string();

			signature.concatenate(XOR("("));
			signature.concatenate(client::mapper::classes[XOR("BlockPos")].signature.get_multibyte_string());
			signature.concatenate(XOR(")"));
			signature.concatenate(client::mapper::classes[XOR("IBlockState")].signature.get_multibyte_string());

			auto method = client::mapper::classes[XOR("WorldClient")].get_method(XOR("getBlockState"), signature);

			if (method.identifier == nullptr)
				method = client::mapper::classes[XOR("WorldClient")].get_method(XOR("func_180495_p"), signature);

			if (method.identifier == nullptr)
				method = client::mapper::classes[XOR("WorldClient")].get_method(XOR("p"), signature);

			return method;
		}();

		auto object_1 = client::mapper::jni->CallObjectMethod(this->object, method_1.identifier, object_0);

		static auto method_2 = []() -> client::mapper::__method
		{
			auto signature = sdk::__multibyte_string();

			signature.concatenate(XOR("()"));
			signature.concatenate(client::mapper::classes[XOR("Block")].signature.get_multibyte_string());

			auto method = client::mapper::classes[XOR("IBlockState")].get_method(XOR("getBlock"), signature);

			if (method.identifier == nullptr)
				method = client::mapper::classes[XOR("IBlockState")].get_method(XOR("func_177230_c"), signature);

			if (method.identifier == nullptr)
				method = client::mapper::classes[XOR("IBlockState")].get_method(XOR("c"), signature);

			return method;
		}();

		auto object_2 = client::mapper::jni->CallObjectMethod(object_1, method_2.identifier);

		static auto method_3 = []() -> client::mapper::__method
		{
			auto signature = sdk::__multibyte_string();

			signature.concatenate(XOR("("));
			signature.concatenate(client::mapper::classes[XOR("Block")].signature.get_multibyte_string());
			signature.concatenate(XOR(")I"));

			auto method = client::mapper::classes[XOR("Block")].get_method(XOR("getIdFromBlock"), signature);

			if (method.identifier == nullptr)
				method = client::mapper::classes[XOR("Block")].get_method(XOR("func_149682_b"), signature);

			if (method.identifier == nullptr)
				method = client::mapper::classes[XOR("Block")].get_method(XOR("a"), signature);

			return method;
		}();

		block_id = client::mapper::jni->CallStaticIntMethod(client::mapper::classes[XOR("Block")].klass, method_3.identifier, object_2);

		client::mapper::jni->DeleteLocalRef(object_0);
		client::mapper::jni->DeleteLocalRef(object_1);
		client::mapper::jni->DeleteLocalRef(object_2);
	}

	return block_id;
}