#pragma once

#include "NdMod.hpp"

class NdMod;

class NdDerived {
public:
	template <typename Derived>
	struct is_derived_from_NdMod {
		static constexpr bool value = std::is_base_of<NdMod, Derived>::value;
	};
};