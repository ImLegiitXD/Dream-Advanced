
#include "mapper.hpp"

auto client::mapper::initialize(JNIEnv_* jni) -> __int32
{
	(client::mapper::jni = jni)->GetJavaVM(&client::mapper::jvm);

	client::mapper::jvm->GetEnv((void**)&client::mapper::jvmti, JVMTI_VERSION_1_2);

	auto command_line = sdk::__unicode_string(sdk::get_process_enviroment_block()->ProcessParameters->CommandLine.Buffer);

	if (command_line.left_find(XOR(L"1.7.10")) != (unsigned __int64)-1)
		client::mapper::version = client::mapper::supported_versions::MINECRAFT_17;
	
	if (command_line.left_find(XOR(L"1.8.9")) != (unsigned __int64)-1)
		client::mapper::version = client::mapper::supported_versions::MINECRAFT_18;

	client::mapper::jni->ExceptionClear();

	return 0;
}

auto client::mapper::__class::get_field(sdk::__multibyte_string name, sdk::__multibyte_string signature) -> client::mapper::__field
{
	auto field = client::mapper::__field();

	for (auto& temporal_field : this->fields)
	{
		if (temporal_field.name.equals(name.get_multibyte_string()) && temporal_field.signature.equals(signature.get_multibyte_string()))
		{
			field = temporal_field;
			
			break;
		}
	}

	return field;
}

auto client::mapper::__class::get_method(sdk::__multibyte_string name, sdk::__multibyte_string signature) -> client::mapper::__method
{
	auto method = client::mapper::__method();

	for (auto& temporal_method : this->methods)
	{
		if (temporal_method.name.equals(name.get_multibyte_string()) && temporal_method.signature.equals(signature.get_multibyte_string()))
		{
			method = temporal_method;

			break;
		}
	}

	return method;
}

auto client::mapper::get_class(sdk::__multibyte_string name) -> client::mapper::__class
{
	auto klass = client::mapper::__class(name);

	klass.signature.concatenate(XOR("L"), name.get_multibyte_string(), XOR(";"));

	if (auto temporal_class = client::mapper::jni->FindClass(klass.signature.get_multibyte_string()); temporal_class != nullptr)
		client::mapper::jni->DeleteLocalRef(temporal_class);

	long loaded_classes_count = 0;

	_jclass** loaded_classes = nullptr;

	client::mapper::jvmti->GetLoadedClasses(&loaded_classes_count, (_jclass***)&loaded_classes);

	for (long x = 0; x < loaded_classes_count && klass.klass == nullptr; ++x)
	{
		char* class_signature = nullptr, *class_reserved = nullptr;

		client::mapper::jvmti->GetClassSignature(loaded_classes[x], &class_signature, &class_reserved);

		if (class_signature != nullptr)
		{
			if (sdk::__multibyte_string(class_signature).equals(klass.signature.get_multibyte_string()))
				klass.klass = (_jclass*)client::mapper::jni->NewGlobalRef(loaded_classes[x]);
		
			client::mapper::jvmti->Deallocate((unsigned __int8*)class_signature);
		}

		if (class_reserved != nullptr)
			client::mapper::jvmti->Deallocate((unsigned __int8*)class_reserved);
	}

	for (auto temporal_class_0 = (_jclass*)client::mapper::jni->NewLocalRef(klass.klass); temporal_class_0 != nullptr;)
	{
		long fields_count = 0;

		jfieldID* fields = nullptr;

		client::mapper::jvmti->GetClassFields(temporal_class_0, &fields_count, &fields);

		for (long x = 0; x < fields_count; ++x)
		{
			auto field = client::mapper::__field();

			field.identifier = fields[x];

			char* field_name = nullptr, *field_signature = nullptr, *field_reserved = nullptr;

			client::mapper::jvmti->GetFieldName(temporal_class_0, fields[x], &field_name, &field_signature, &field_reserved);

			if (field_name != nullptr)
			{
				field.name = field_name;

				client::mapper::jvmti->Deallocate((unsigned __int8*)field_name);
			}

			if (field_signature != nullptr)
			{
				field.signature = field_signature;

				client::mapper::jvmti->Deallocate((unsigned __int8*)field_signature);
			}

			if (field_reserved != nullptr)
				client::mapper::jvmti->Deallocate((unsigned __int8*)field_reserved);

			klass.fields.push_back(field);
		}

		client::mapper::jvmti->Deallocate((unsigned __int8*)fields);

		long methods_count = 0;

		jmethodID* methods = nullptr;

		client::mapper::jvmti->GetClassMethods(temporal_class_0, &methods_count, &methods);

		for (long x = 0; x < methods_count; ++x)
		{
			auto method = client::mapper::__method();

			method.identifier = methods[x];

			char* method_name = nullptr, *method_signature = nullptr, *method_reserved = nullptr;

			client::mapper::jvmti->GetMethodName(methods[x], &method_name, &method_signature, &method_reserved);

			if (method_name != nullptr)
			{
				method.name = method_name;

				client::mapper::jvmti->Deallocate((unsigned __int8*)method_name);
			}

			if (method_signature != nullptr)
			{
				method.signature = method_signature;

				client::mapper::jvmti->Deallocate((unsigned __int8*)method_signature);
			}

			if (method_reserved != nullptr)
				client::mapper::jvmti->Deallocate((unsigned __int8*)method_reserved);

			klass.methods.push_back(method);
		}

		client::mapper::jvmti->Deallocate((unsigned __int8*)methods);

		auto temporal_class_1 = client::mapper::jni->GetSuperclass(temporal_class_0);

		client::mapper::jni->DeleteLocalRef(temporal_class_0);

		temporal_class_0 = temporal_class_1;
	}

	client::mapper::jvmti->Deallocate((unsigned __int8*)loaded_classes);

	client::mapper::jni->ExceptionClear();

	return klass;
}

auto client::mapper::initialize() -> __int32
{
	client::mapper::classes[XOR("List")] = client::mapper::get_class(XOR("java/util/List"));
	client::mapper::classes[XOR("Enum")] = client::mapper::get_class(XOR("java/lang/Enum"));

	if (client::mapper::version == client::mapper::supported_versions::MINECRAFT_17)
	{
		client::mapper::classes[XOR("Minecraft")] = client::mapper::get_class(XOR("net/minecraft/client/Minecraft"));
	
		if (client::mapper::classes[XOR("Minecraft")].klass != nullptr)
		{
			client::mapper::classes[XOR("GameSettings")] = client::mapper::get_class(XOR("net/minecraft/client/settings/GameSettings"));
			client::mapper::classes[XOR("Timer")] = client::mapper::get_class(XOR("net/minecraft/util/Timer"));
			client::mapper::classes[XOR("GuiScreen")] = client::mapper::get_class(XOR("net/minecraft/client/gui/GuiScreen"));
			client::mapper::classes[XOR("GuiInventory")] = client::mapper::get_class(XOR("net/minecraft/client/gui/inventory/GuiInventory"));
			client::mapper::classes[XOR("GuiChest")] = client::mapper::get_class(XOR("net/minecraft/client/gui/inventory/GuiChest"));
			client::mapper::classes[XOR("RenderManager")] = client::mapper::get_class(XOR("net/minecraft/client/renderer/entity/RenderManager"));
			client::mapper::classes[XOR("WorldClient")] = client::mapper::get_class(XOR("net/minecraft/client/multiplayer/WorldClient"));
			client::mapper::classes[XOR("Entity")] = client::mapper::get_class(XOR("net/minecraft/entity/Entity"));
			client::mapper::classes[XOR("EntityPlayer")] = client::mapper::get_class(XOR("net/minecraft/entity/player/EntityPlayer"));
			client::mapper::classes[XOR("EntityPlayerXP")] = client::mapper::get_class(XOR("net/minecraft/client/entity/EntityClientPlayerMP"));
			client::mapper::classes[XOR("AxisAlignedBB")] = client::mapper::get_class(XOR("net/minecraft/util/AxisAlignedBB"));
			client::mapper::classes[XOR("MovingObjectPosition")] = client::mapper::get_class(XOR("net/minecraft/util/MovingObjectPosition"));
			client::mapper::classes[XOR("MovingObjectPosition_MovingObjectType")] = client::mapper::get_class(XOR("net/minecraft/util/MovingObjectPosition$MovingObjectType"));
			client::mapper::classes[XOR("ItemStack")] = client::mapper::get_class(XOR("net/minecraft/item/ItemStack"));
			client::mapper::classes[XOR("Item")] = client::mapper::get_class(XOR("net/minecraft/item/Item"));
			client::mapper::classes[XOR("Block")] = client::mapper::get_class(XOR("net/minecraft/block/Block"));
			client::mapper::classes[XOR("Vec3")] = client::mapper::get_class(XOR("net/minecraft/util/Vec3"));
		}

		else
		{
			client::mapper::classes[XOR("Minecraft")] = client::mapper::get_class(XOR("bao"));
			client::mapper::classes[XOR("GameSettings")] = client::mapper::get_class(XOR("bbj"));
			client::mapper::classes[XOR("Timer")] = client::mapper::get_class(XOR("bbr"));
			client::mapper::classes[XOR("GuiScreen")] = client::mapper::get_class(XOR("bdw"));
			client::mapper::classes[XOR("GuiInventory")] = client::mapper::get_class(XOR("bfu"));
			client::mapper::classes[XOR("GuiChest")] = client::mapper::get_class(XOR("bfi"));
			client::mapper::classes[XOR("RenderManager")] = client::mapper::get_class(XOR("bnn"));
			client::mapper::classes[XOR("WorldClient")] = client::mapper::get_class(XOR("bjf"));
			client::mapper::classes[XOR("Entity")] = client::mapper::get_class(XOR("sa"));
			client::mapper::classes[XOR("EntityPlayer")] = client::mapper::get_class(XOR("yz"));
			client::mapper::classes[XOR("EntityPlayerXP")] = client::mapper::get_class(XOR("bjk"));
			client::mapper::classes[XOR("AxisAlignedBB")] = client::mapper::get_class(XOR("azt"));
			client::mapper::classes[XOR("MovingObjectPosition")] = client::mapper::get_class(XOR("azu"));
			client::mapper::classes[XOR("MovingObjectPosition_MovingObjectType")] = client::mapper::get_class(XOR("azv"));
			client::mapper::classes[XOR("ItemStack")] = client::mapper::get_class(XOR("add"));
			client::mapper::classes[XOR("Item")] = client::mapper::get_class(XOR("adb"));
			client::mapper::classes[XOR("Block")] = client::mapper::get_class(XOR("aji"));
			client::mapper::classes[XOR("Vec3")] = client::mapper::get_class(XOR("azw"));
		}
	}

	else if (client::mapper::version == client::mapper::supported_versions::MINECRAFT_18)
	{
		client::mapper::classes[XOR("Minecraft")] = client::mapper::get_class(XOR("net/minecraft/client/Minecraft"));
		
		if (client::mapper::classes[XOR("Minecraft")].klass != nullptr)
		{
			client::mapper::classes[XOR("GameSettings")] = client::mapper::get_class(XOR("net/minecraft/client/settings/GameSettings"));
			client::mapper::classes[XOR("Timer")] = client::mapper::get_class(XOR("net/minecraft/util/Timer"));
			client::mapper::classes[XOR("GuiScreen")] = client::mapper::get_class(XOR("net/minecraft/client/gui/GuiScreen"));
			client::mapper::classes[XOR("GuiInventory")] = client::mapper::get_class(XOR("net/minecraft/client/gui/inventory/GuiInventory"));
			client::mapper::classes[XOR("GuiChest")] = client::mapper::get_class(XOR("net/minecraft/client/gui/inventory/GuiChest"));
			client::mapper::classes[XOR("RenderManager")] = client::mapper::get_class(XOR("net/minecraft/client/renderer/entity/RenderManager"));
			client::mapper::classes[XOR("WorldClient")] = client::mapper::get_class(XOR("net/minecraft/client/multiplayer/WorldClient"));
			client::mapper::classes[XOR("Entity")] = client::mapper::get_class(XOR("net/minecraft/entity/Entity"));
			client::mapper::classes[XOR("EntityPlayer")] = client::mapper::get_class(XOR("net/minecraft/entity/player/EntityPlayer"));
			client::mapper::classes[XOR("EntityPlayerXP")] = client::mapper::get_class(XOR("net/minecraft/client/entity/EntityPlayerSP"));
			client::mapper::classes[XOR("AxisAlignedBB")] = client::mapper::get_class(XOR("net/minecraft/util/AxisAlignedBB"));
			client::mapper::classes[XOR("MovingObjectPosition")] = client::mapper::get_class(XOR("net/minecraft/util/MovingObjectPosition"));
			client::mapper::classes[XOR("MovingObjectPosition_MovingObjectType")] = client::mapper::get_class(XOR("net/minecraft/util/MovingObjectPosition$MovingObjectType"));
			client::mapper::classes[XOR("ItemStack")] = client::mapper::get_class(XOR("net/minecraft/item/ItemStack"));
			client::mapper::classes[XOR("Item")] = client::mapper::get_class(XOR("net/minecraft/item/Item"));
			client::mapper::classes[XOR("Block")] = client::mapper::get_class(XOR("net/minecraft/block/Block"));
			client::mapper::classes[XOR("BlockPos")] = client::mapper::get_class(XOR("net/minecraft/util/BlockPos"));
			client::mapper::classes[XOR("IBlockState")] = client::mapper::get_class(XOR("net/minecraft/block/state/IBlockState"));
			client::mapper::classes[XOR("Vec3")] = client::mapper::get_class(XOR("net/minecraft/util/Vec3"));
		}

		else
		{
			client::mapper::classes[XOR("Minecraft")] = client::mapper::get_class(XOR("ave"));
			client::mapper::classes[XOR("GameSettings")] = client::mapper::get_class(XOR("avh"));
			client::mapper::classes[XOR("Timer")] = client::mapper::get_class(XOR("avl"));
			client::mapper::classes[XOR("GuiScreen")] = client::mapper::get_class(XOR("axu"));
			client::mapper::classes[XOR("GuiInventory")] = client::mapper::get_class(XOR("azc"));
			client::mapper::classes[XOR("GuiChest")] = client::mapper::get_class(XOR("ayr"));
			client::mapper::classes[XOR("RenderManager")] = client::mapper::get_class(XOR("biu"));
			client::mapper::classes[XOR("WorldClient")] = client::mapper::get_class(XOR("bdb"));
			client::mapper::classes[XOR("Entity")] = client::mapper::get_class(XOR("pk"));
			client::mapper::classes[XOR("EntityPlayer")] = client::mapper::get_class(XOR("wn"));
			client::mapper::classes[XOR("EntityPlayerXP")] = client::mapper::get_class(XOR("bew"));
			client::mapper::classes[XOR("AxisAlignedBB")] = client::mapper::get_class(XOR("aug"));
			client::mapper::classes[XOR("MovingObjectPosition")] = client::mapper::get_class(XOR("auh"));
			client::mapper::classes[XOR("MovingObjectPosition_MovingObjectType")] = client::mapper::get_class(XOR("auh$a"));
			client::mapper::classes[XOR("ItemStack")] = client::mapper::get_class(XOR("zx"));
			client::mapper::classes[XOR("Item")] = client::mapper::get_class(XOR("zw"));
			client::mapper::classes[XOR("Block")] = client::mapper::get_class(XOR("afh"));
			client::mapper::classes[XOR("BlockPos")] = client::mapper::get_class(XOR("cj"));
			client::mapper::classes[XOR("IBlockState")] = client::mapper::get_class(XOR("alz"));
			client::mapper::classes[XOR("Vec3")] = client::mapper::get_class(XOR("aui"));
		}
	}

	client::mapper::jni->ExceptionClear();

	return 0;
}

auto client::mapper::uninitialize() -> __int32
{
	for (auto& klass : client::mapper::classes)
		client::mapper::jni->DeleteGlobalRef(klass.second.klass);

	client::mapper::jni->ExceptionClear();

	return 0;
}