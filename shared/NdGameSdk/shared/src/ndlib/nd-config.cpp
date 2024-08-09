#include "nd-config.hpp"

namespace NdGameSdk::ndlib {

	ndlib::debug::DMENU& NdConfig::GetDmenu() {
		return *GetConfig<ndlib::debug::DMENU>(Config::DevMenu);
	}
}