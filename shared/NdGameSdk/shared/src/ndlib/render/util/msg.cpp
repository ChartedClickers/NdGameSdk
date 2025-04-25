#include "msg.hpp"

#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <glm/vec2.hpp>

namespace NdGameSdk::ndlib::render::util
{
	void Msg::PrintToActiveMsgOutput(const char* pStr)
	{
		always_assert(Msg_PrintToActiveMsgOutput == nullptr, "function pointer is not initialized!");
		Msg_PrintToActiveMsgOutput(pStr);
	}

}
