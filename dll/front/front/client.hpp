
#include "hooks/hooks.hpp"

namespace client
{
	__declspec(dllexport) inline char hardware_identifier[64];

	extern auto initialize(unsigned __int64 reserved) -> __int32;
	extern auto uninitialize(unsigned __int64 reserved) -> __int32;
}