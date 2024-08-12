#include "nd-config.hpp"

namespace NdGameSdk::ndlib {

	ndlib::debug::DMENU& NdConfig::GetDmenu() {
		return *GetConfig<ndlib::debug::DMENU>(Config::DMENU);
	}

	ndlib::debug::DMENU::MenuGroup& NdConfig::GetNdDevMenu() {
		return *GetConfig<ndlib::debug::DMENU::MenuGroup>(Config::NdDevMenu);
	}
}