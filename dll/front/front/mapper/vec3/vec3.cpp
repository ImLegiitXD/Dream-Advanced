
#include "../mapper.hpp"

client::mapper::__vec3__::__vec3__(client::mapper::__vec3 vec3)
{
	static auto method = client::mapper::classes[XOR("Vec3")].get_method(XOR("<init>"), XOR("(DDD)V"));

	this->object = client::mapper::jni->NewObject(client::mapper::classes[XOR("Vec3")].klass, method.identifier, vec3.x, vec3.y, vec3.z);
}

client::mapper::__vec3__::__vec3__(_jobject* object)
{
	this->object = object;
}

client::mapper::__vec3__::__vec3__(const client::mapper::__vec3__& vec3)
{
	if (vec3.object != nullptr)
		this->object = client::mapper::jni->NewLocalRef(vec3.object);
}

client::mapper::__vec3__::~__vec3__()
{
	if (this->object != nullptr)
		client::mapper::jni->DeleteLocalRef(this->object);
}

auto client::mapper::__vec3__::get_vec3() -> client::mapper::__vec3
{
	static auto field_0 = client::mapper::classes[XOR("Vec3")].get_field(XOR("xCoord"), XOR("D"));
	static auto field_1 = client::mapper::classes[XOR("Vec3")].get_field(XOR("yCoord"), XOR("D"));
	static auto field_2 = client::mapper::classes[XOR("Vec3")].get_field(XOR("zCoord"), XOR("D"));

	if (field_0.identifier == nullptr)
		field_0 = client::mapper::classes[XOR("Vec3")].get_field(XOR("field_72450_a"), XOR("D"));

	if (field_0.identifier == nullptr)
		field_0 = client::mapper::classes[XOR("Vec3")].get_field(XOR("a"), XOR("D"));

	if (field_1.identifier == nullptr)
		field_1 = client::mapper::classes[XOR("Vec3")].get_field(XOR("field_72448_b"), XOR("D"));

	if (field_1.identifier == nullptr)
		field_1 = client::mapper::classes[XOR("Vec3")].get_field(XOR("b"), XOR("D"));

	if (field_2.identifier == nullptr)
		field_2 = client::mapper::classes[XOR("Vec3")].get_field(XOR("field_72449_c"), XOR("D"));

	if (field_2.identifier == nullptr)
		field_2 = client::mapper::classes[XOR("Vec3")].get_field(XOR("c"), XOR("D"));

	return client::mapper::__vec3(
		client::mapper::jni->GetDoubleField(this->object, field_0.identifier),
		client::mapper::jni->GetDoubleField(this->object, field_1.identifier),
		client::mapper::jni->GetDoubleField(this->object, field_2.identifier)
	);
}

auto client::mapper::__vec3::get_distance_to_vec3(client::mapper::__vec3 vec3) -> double
{
	return sqrt(pow(this->x - vec3.x, 2) + pow(this->y - vec3.y, 2) + pow(this->z - vec3.z, 2));
}

auto client::mapper::__vec3::get_angle_x_difference_to_vec3(client::mapper::__vec3 target, float angle) -> float
{
	auto angle_x_difference_to_vec3 = atan2(target.z - this->z, target.x - this->x) * 180. / 3.14159265358979323846 - 90.;

	angle_x_difference_to_vec3 = (double)fmodf((float)angle_x_difference_to_vec3 - angle, 360.f);

	if (angle_x_difference_to_vec3 >= 180.)
		angle_x_difference_to_vec3 -= 360.;

	if (angle_x_difference_to_vec3 < -180.)
		angle_x_difference_to_vec3 += 360.;

	return (float)angle_x_difference_to_vec3;
}

auto client::mapper::__vec3::get_angle_y_difference_to_vec3(client::mapper::__vec3 target, float angle) -> float
{
	return (float)(atan2(this->y - target.y, sqrt(pow(target.x - this->x, 2) + pow(target.z - this->z, 2))) * 180. / 3.14159265358979323846) - angle;
}