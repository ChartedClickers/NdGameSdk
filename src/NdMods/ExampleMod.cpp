#include "ExampleMod.hpp"

namespace ExampleMod
{
	void Example::OnNdModinitialize()
	{
		auto SomeComponent1 = GetSharedSdkComponent<ndlib::EngineComponents>().get();

		//auto SomeComponent2 = GetNdModComponent<Example>().get();
	}

}