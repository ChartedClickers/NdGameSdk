#pragma once

#include "sdk.hpp"

namespace NdGameSdk {

	class NdGameSdk_API NdGameSdkException : public std::runtime_error {
	public:
		NdGameSdkException(const std::string& msg) : std::runtime_error(msg) {}
	};

}
