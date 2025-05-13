#pragma once
#include "NdGameSdk/components/SdkRegenny.hpp"

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/NdFrameState.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/NdFrameState.hpp>
#endif

namespace NdGameSdk::ndlib {


	class NdGameSdk_API NdFrameState : public ISdkRegenny<regenny::shared::ndlib::NdFrameState>
	{
	public:
		class NdGameSdk_API NdKeyboardLayer : public ISdkRegenny<regenny::shared::ndlib::NdFrameState::NdKeyboardLayer>
		{
		public:
			enum class Key : std::uint32_t
			{
                Digit0 = '0', Digit1 = '1', Digit2 = '2', Digit3 = '3', Digit4 = '4',
                Digit5 = '5', Digit6 = '6', Digit7 = '7', Digit8 = '8', Digit9 = '9',

                A = 'A', B = 'B', C = 'C', D = 'D', E = 'E', F = 'F', G = 'G', H = 'H', I = 'I', J = 'J',
                K = 'K', L = 'L', M = 'M', N = 'N', O = 'O', P = 'P', Q = 'Q', R = 'R', S = 'S', T = 'T',
                U = 'U', V = 'V', W = 'W', X = 'X', Y = 'Y', Z = 'Z',

                /* printable -------------------------------------------------------- */
                Space = 0x20,
                BackSpace = 0xAB,

                /* function row --------------------------------------------------- */
                Esc = 0x9C,
                F1 = 0x9D, F2 = 0x9E, F3 = 0x9F, F4 = 0xA0,
                F5 = 0xA1, F6 = 0xA2, F7 = 0xA3, F8 = 0xA4,
                F9 = 0xA5, F10 = 0xA6, F11 = 0xA7, F12 = 0xA8,

                /* modifiers / system keys --------------------------------------- */
                Tab = 0x8F,
                LeftShift = 0x90,
                RightShift = 0x91,
                Shift = 0x92,

                Enter = 0x99,
                LeftCtrl = 0x93,
                RightCtrl = 0x94,
				Ctrl = 0x95,

                /* nav / editing -------------------------------------------------- */
                Insert = 0xAC, Delete = 0xAA,
                Home = 0xAF, End = 0xB0,
                PageUp = 0xAD, PageDn = 0xAE,
                ArrowLeft = 0xB1,
                ArrowRight = 0xB2,
                ArrowUp = 0xB3,
                ArrowDown = 0xB4,

                /* num-pad -------------------------------------------------------- */
                Num0 = 0x80, Num1 = 0x81, Num2 = 0x82, 
                Num3 = 0x83, Num4 = 0x84, Num5 = 0x85, 
                Num6 = 0x86,Num7 = 0x87, Num8 = 0x88, 
                Num9 = 0x89,
			};

			bool isEnabled();
            bool isDebugKeyboard();
			bool isDown(Key k) const noexcept;
			bool wasPressed(Key k) const noexcept;
			bool wasReleased(Key k) const noexcept;
			bool isAlphaDown(char asciiUpper) const noexcept;
			bool wasAlphaPressed(char asciiUpper) const noexcept;
			bool isComboDown(Key main, Key mod) const noexcept;
            bool isCtrlDown() const noexcept;
			void DebugkeysPressed() const noexcept;
        private:
			static bool testBit(const std::uint64_t banks[4], std::uint32_t code) noexcept;
			static constexpr std::size_t kBankMask = 0x3F; // 0x3F
			static constexpr std::size_t kBankShift = 6; // >> 6
		};

		uint64_t GetGameFrameNumber();
		bool IsKeyboardDevMode() const;

		NdKeyboardLayer* GetIMEKeyboard();
		NdKeyboardLayer* GetGameKeyboard();
	};

#if defined(T2R)
	static_assert(sizeof(NdFrameState) == 0x29518, "Size of NdFrameState is not correct.");
#elif defined(T1X)
	static_assert(sizeof(NdFrameState) == 0x288a0, "Size of NdFrameState is not correct.");
#endif

	static_assert(sizeof(NdFrameState::NdKeyboardLayer) == 0x1a60, "Size of NdKeyboardLayer is not correct.");
}