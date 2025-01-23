
#include "../mapper.hpp"

client::mapper::__gui_screen::__gui_screen(_jobject* object)
{
	this->object = object;
}

client::mapper::__gui_screen::__gui_screen(const client::mapper::__gui_screen& gui_screen)
{
	if (gui_screen.object != nullptr)
		this->object = client::mapper::jni->NewLocalRef(gui_screen.object);
}

client::mapper::__gui_screen::~__gui_screen()
{
	if (this->object != nullptr)
		client::mapper::jni->DeleteLocalRef(this->object);
}

auto client::mapper::__gui_screen::is_inventory_instance() -> bool
{
	return client::mapper::jni->IsInstanceOf(this->object, client::mapper::classes[XOR("GuiInventory")].klass) || client::mapper::jni->IsInstanceOf(this->object, client::mapper::classes[XOR("GuiChest")].klass);
}