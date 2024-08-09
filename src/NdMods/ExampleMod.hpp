#pragma once

#include "NdMod.hpp"

namespace ExampleMod
{
	class Example : public NdMod {

		std::string_view GetName() const override { return "ExampleNdMod"; }

	private:
		void OnNdModinitialize() override;

	};
}