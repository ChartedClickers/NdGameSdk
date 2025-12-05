#pragma once

#include "NdMod.hpp"
#include <Utility/helper.hpp>

namespace ExampleMod
{
	class DevSandboxMod : public NdMod {

		std::string_view GetName() const override { return "DevSandboxMod"; }

	private:
		void OnNdModinitialize() override;

	};
}