#pragma once

#include "sdk.hpp"

namespace NdGameSdk {

	template<typename T>
	inline constexpr bool always_false_v = false;

	class SdkDerived {
	public:
		template <typename Derived>
		struct is_derived_from_ISdkComponent {
			static constexpr bool value = std::is_base_of<ISdkComponent, Derived>::value;
		};

		template <typename Derived>
		struct is_derived_from_ISdkComponent<std::shared_ptr<Derived>> : is_derived_from_ISdkComponent<Derived> {};

		template <typename Derived>
		struct is_derived_from_ISdkSubComponent {
			static constexpr bool value = std::is_base_of<ISdkSubComponent, Derived>::value;
		};

		template <typename Derived>
		struct is_derived_from_ISdkModule {
			static constexpr bool value = std::is_base_of<ISdkModule, Derived>::value;
		};
	};
}
