
#include "../mapper.hpp"

client::mapper::__axis_aligned::__axis_aligned(_jobject* object)
{
	this->object = object;
}

client::mapper::__axis_aligned::__axis_aligned(const client::mapper::__axis_aligned& axis_aligned)
{
	if (axis_aligned.object != nullptr)
		this->object = client::mapper::jni->NewLocalRef(axis_aligned.object);
}

client::mapper::__axis_aligned::~__axis_aligned()
{
	if (this->object != nullptr)
		client::mapper::jni->DeleteLocalRef(this->object);
}

auto client::mapper::__axis_aligned::get_bounds() -> std::pair<client::mapper::__vec3, client::mapper::__vec3>
{
	static auto field_0 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("minX"), XOR("D"));
	static auto field_1 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("minY"), XOR("D"));
	static auto field_2 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("minZ"), XOR("D"));
	static auto field_3 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("maxX"), XOR("D"));
	static auto field_4 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("maxY"), XOR("D"));
	static auto field_5 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("maxZ"), XOR("D"));

	if (field_0.identifier == nullptr)
		field_0 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("field_72340_a"), XOR("D"));

	if (field_0.identifier == nullptr)
		field_0 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("a"), XOR("D"));

	if (field_1.identifier == nullptr)
		field_1 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("field_72338_b"), XOR("D"));

	if (field_1.identifier == nullptr)
		field_1 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("b"), XOR("D"));

	if (field_2.identifier == nullptr)
		field_2 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("field_72339_c"), XOR("D"));

	if (field_2.identifier == nullptr)
		field_2 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("c"), XOR("D"));

	if (field_3.identifier == nullptr)
		field_3 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("field_72336_d"), XOR("D"));

	if (field_3.identifier == nullptr)
		field_3 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("d"), XOR("D"));

	if (field_4.identifier == nullptr)
		field_4 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("field_72337_e"), XOR("D"));

	if (field_4.identifier == nullptr)
		field_4 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("e"), XOR("D"));

	if (field_5.identifier == nullptr)
		field_5 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("field_72334_f"), XOR("D"));

	if (field_5.identifier == nullptr)
		field_5 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("f"), XOR("D"));

	return std::pair<client::mapper::__vec3, client::mapper::__vec3>(
	{
		client::mapper::jni->GetDoubleField(this->object, field_0.identifier),
		client::mapper::jni->GetDoubleField(this->object, field_1.identifier),
		client::mapper::jni->GetDoubleField(this->object, field_2.identifier)
	},
	{
		client::mapper::jni->GetDoubleField(this->object, field_3.identifier),
		client::mapper::jni->GetDoubleField(this->object, field_4.identifier),
		client::mapper::jni->GetDoubleField(this->object, field_5.identifier)
	});
}

auto client::mapper::__axis_aligned::set_bounds(std::pair<client::mapper::__vec3, client::mapper::__vec3> bounds) -> void
{
	static auto field_0 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("minX"), XOR("D"));
	static auto field_1 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("minY"), XOR("D"));
	static auto field_2 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("minZ"), XOR("D"));
	static auto field_3 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("maxX"), XOR("D"));
	static auto field_4 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("maxY"), XOR("D"));
	static auto field_5 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("maxZ"), XOR("D"));

	if (field_0.identifier == nullptr)
		field_0 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("field_72340_a"), XOR("D"));

	if (field_0.identifier == nullptr)
		field_0 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("a"), XOR("D"));

	if (field_1.identifier == nullptr)
		field_1 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("field_72338_b"), XOR("D"));

	if (field_1.identifier == nullptr)
		field_1 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("b"), XOR("D"));

	if (field_2.identifier == nullptr)
		field_2 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("field_72339_c"), XOR("D"));

	if (field_2.identifier == nullptr)
		field_2 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("c"), XOR("D"));

	if (field_3.identifier == nullptr)
		field_3 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("field_72336_d"), XOR("D"));

	if (field_3.identifier == nullptr)
		field_3 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("d"), XOR("D"));

	if (field_4.identifier == nullptr)
		field_4 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("field_72337_e"), XOR("D"));

	if (field_4.identifier == nullptr)
		field_4 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("e"), XOR("D"));

	if (field_5.identifier == nullptr)
		field_5 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("field_72334_f"), XOR("D"));

	if (field_5.identifier == nullptr)
		field_5 = client::mapper::classes[XOR("AxisAlignedBB")].get_field(XOR("f"), XOR("D"));

	client::mapper::jni->SetDoubleField(this->object, field_0.identifier, bounds.first.x);
	client::mapper::jni->SetDoubleField(this->object, field_1.identifier, bounds.first.y);
	client::mapper::jni->SetDoubleField(this->object, field_2.identifier, bounds.first.z);
	client::mapper::jni->SetDoubleField(this->object, field_3.identifier, bounds.second.x);
	client::mapper::jni->SetDoubleField(this->object, field_4.identifier, bounds.second.y);
	client::mapper::jni->SetDoubleField(this->object, field_5.identifier, bounds.second.z);
}

auto client::mapper::__axis_aligned::calculate_interception(client::mapper::__vec3 view_position, client::mapper::__vec3 view_vector) -> client::mapper::__moving_object_position
{
	static auto method = []() -> client::mapper::__method
	{
		auto signature = sdk::__multibyte_string();

		signature.concatenate(XOR("("));
		signature.concatenate(client::mapper::classes[XOR("Vec3")].signature.get_multibyte_string());
		signature.concatenate(client::mapper::classes[XOR("Vec3")].signature.get_multibyte_string());
		signature.concatenate(XOR(")"));
		signature.concatenate(client::mapper::classes[XOR("MovingObjectPosition")].signature.get_multibyte_string());

		auto method = client::mapper::classes[XOR("AxisAlignedBB")].get_method(XOR("calculateIntercept"), signature);

		if (method.identifier == nullptr)
			method = client::mapper::classes[XOR("AxisAlignedBB")].get_method(XOR("func_72327_a"), signature);

		if (method.identifier == nullptr)
			method = client::mapper::classes[XOR("AxisAlignedBB")].get_method(XOR("a"), signature);

		return method;
	}();

	return client::mapper::__moving_object_position(client::mapper::jni->CallObjectMethod(this->object, method.identifier, client::mapper::__vec3__(view_position).object, client::mapper::__vec3__(view_vector).object));
}