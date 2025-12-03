#include "nd-frame-state.hpp"

namespace NdGameSdk::ndlib {

	bool NdFrameState::NdKeyboardLayer::isEnabled() {
		return this->Get()->m_enabled;
	}

	bool NdFrameState::NdKeyboardLayer::isDebugKeyboard() {
		return this->Get()->m_DebugKeyboard;
	}

	bool NdFrameState::NdKeyboardLayer::isDown(Key k) const noexcept {
		const auto code = static_cast<std::uint32_t>(k);
		const auto& live = this->Get()->m_keys;

		// letters: engine sets the lowercase bit, so accept either
		if (code >= 'A' && code <= 'Z')
			return  testBit(live, code) // upper-case bit
			|| testBit(live, code | 0x20U); // lower-case bit

		return  testBit(live, code);
	}

	bool NdFrameState::NdKeyboardLayer::wasPressed(Key k) const noexcept {
		const auto code = static_cast<std::uint32_t>(k);

		// Letters A..Z live in two slots – test both
		if (code >= 'A' && code <= 'Z')
			return testBit(this->Get()->m_keysPressed, code)  // uppercase
			|| testBit(this->Get()->m_keysPressed, code | 0x20U); // lowercase 

		return testBit(this->Get()->m_keysPressed, code);
	}

	bool NdFrameState::NdKeyboardLayer::wasReleased(Key k) const noexcept {
		const auto code = static_cast<std::uint32_t>(k);

		if (code >= 'A' && code <= 'Z') {
			const bool up = testBit(this->Get()->m_keys, code)
				|| testBit(this->Get()->m_keys, code | 0x20U);
			const bool down = testBit(this->Get()->m_keyState, code)
				|| testBit(this->Get()->m_keyState, code | 0x20U);
			return up && !down;
		}

		return  testBit(this->Get()->m_keys, code)
			&& !testBit(this->Get()->m_keyState, code);
	}

	bool NdFrameState::NdKeyboardLayer::isAlphaDown(char asciiUpper) const noexcept {
		const auto upper = static_cast<std::uint32_t>(asciiUpper & 0xDF);
		return testBit(this->Get()->m_keyState, upper) ||
			testBit(this->Get()->m_keyState, upper | 0x20);
	}

	bool NdFrameState::NdKeyboardLayer::wasAlphaPressed(char asciiUpper) const noexcept {
		const auto upper = static_cast<std::uint32_t>(asciiUpper & 0xDF);
		return  testBit(this->Get()->m_keysPressed, upper) ||
			testBit(this->Get()->m_keysPressed, upper | 0x20U);
	}

	bool NdFrameState::NdKeyboardLayer::isComboDown(Key main, Key mod) const noexcept {
		return isDown(main) && isDown(mod);
	}

	bool NdFrameState::NdKeyboardLayer::isCtrlDown() const noexcept {
		return isDown(Key::LeftCtrl) || isDown(Key::RightCtrl) || isDown(Key::Ctrl);
	}

	void NdFrameState::NdKeyboardLayer::DebugkeysPressed() const noexcept {
		for (std::uint32_t code = 0; code < 0x100; ++code) {
			if (testBit(this->Get()->m_keysPressed, code))
				spdlog::info("ND key 0x{:02X} was pressed", code);
		}
	}

	bool NdFrameState::NdKeyboardLayer::testBit(const std::uint64_t banks[4], std::uint32_t code) noexcept {
		return (banks[code >> kBankShift] &
			(1ull << (code & kBankMask))) != 0;
	}

	uint64_t NdFrameState::GetGameFrameNumber() {
		return this->Get()->m_gameFrameNumber;
	}

	bool NdFrameState::IsKeyboardDevMode() const {
		return this->Get()->m_KeyboardDevMode;
	}

	NdFrameState::NdKeyboardLayer* NdFrameState::GetIMEKeyboard() {
		return reinterpret_cast<NdKeyboardLayer*>(&this->Get()->m_IMEKeyboard);
	}

	NdFrameState::NdKeyboardLayer* NdFrameState::GetGameKeyboard() {
		return reinterpret_cast<NdKeyboardLayer*>(&this->Get()->m_GameKeyboard);
	}
}