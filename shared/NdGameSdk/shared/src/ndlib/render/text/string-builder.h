#pragma once
#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkRegenny.hpp"

#include "Utility/color.hpp"   

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/render/text/DebugStringBase.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/render/text/DebugStringBase.hpp>
#endif

namespace NdGameSdk::ndlib::render::text {

    // TODO: Refactor this...

	class NdGameSdk_API DebugStringBase : public ISdkRegenny<::regenny::shared::ndlib::render::text::DebugStringBase>
	{

    public:
        DebugStringBase() = default;

        DebugStringBase(
            glm::vec4 const& position,
            Color            abgrColor,
            float            scale = 1.0f,
            std::uint8_t     fade = 0u,
            char* utf8Text = nullptr)
        {
            auto* self = Get();
            self->unk08 = 0;
            self->vec = position;
            self->color = abgrColor.toUint64();
            self->scale = scale;
            self->fade = fade;
            self->reserved = 0x0;
            self->pText = utf8Text;
        }

        glm::vec4& position() { return Get()->vec; }
        glm::vec4  position() const { return Get()->vec; }

        void setText(char* utf8) { Get()->pText = utf8; }
        char* text() const { return Get()->pText; }

        std::uint32_t& color() { return Get()->color; }
        std::uint32_t  color() const { return Get()->color; }
        void setColor(Color abgrColor) { Get()->color = abgrColor.toUint64(); }

        float& scale() { return Get()->scale; }
        float  scale() const { return Get()->scale; }

	};

	static_assert(sizeof(DebugStringBase) == 0x48, "Size of DebugStringBase is not correct.");
}