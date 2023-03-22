//
// Created by block on 1/19/2023.
//

#pragma once

#include <xenomods/engine/mm/MathTypes.hpp>
#include <nn/hid.hpp>

namespace xenomods {

	struct HidInput {
		struct State {
			std::uint64_t Buttons;
			glm::vec2 LAxis;
			glm::vec2 RAxis;
		};

		State stateCur {};
		State statePrev {};

		nn::hid::NpadId padId {};

		constexpr HidInput(nn::hid::NpadId id)
			: padId(id) {

		}

		void Poll();

		/**
		 * \defgroup input Input functions
		 * Standard style input functions. Can take any kind of integer to check.
		 * Strict functions ensure that only the specified combo is allowed to be held down.
		 * @{
		 */

		template<class T>
		inline bool InputHeld(T combo) {
			return bitMask(static_cast<T>(stateCur.Buttons), combo);
		}

		template<class T>
		inline bool InputUp(T combo) {
			return !bitMask(static_cast<T>(stateCur.Buttons), combo) && bitMask(static_cast<T>(statePrev.Buttons), combo);
		}

		template<class T>
		inline bool InputDown(T combo) {
			return bitMask(static_cast<T>(stateCur.Buttons), combo) && !bitMask(static_cast<T>(statePrev.Buttons), combo);
		}

		template<class T>
		inline bool InputHeldStrict(T combo) {
			return bitMaskStrict(static_cast<T>(stateCur.Buttons & 0xFFFF), combo);
		}

		template<class T>
		inline bool InputUpStrict(T combo) {
			return !bitMaskStrict(static_cast<T>(stateCur.Buttons & 0xFFFF), combo) && bitMaskStrict(static_cast<T>(statePrev.Buttons & 0xFFFF), combo);
		}

		template<class T>
		inline bool InputDownStrict(T combo) {
			return bitMaskStrict(static_cast<T>(stateCur.Buttons & 0xFFFF), combo) && !bitMaskStrict(static_cast<T>(statePrev.Buttons & 0xFFFF), combo);
		}

		/** @} */
	};

	HidInput* GetPlayer(int player);

	enum class Keybind : std::uint64_t {
		RELOAD_CONFIG = nn::hid::KEY_PLUS,
		BDAT_MSSCRAMBLETYPE_SWITCH = nn::hid::KEY_X,

		MOVEMENT_SPEED_UP = nn::hid::KEY_DUP,
		MOVEMENT_SPEED_DOWN = nn::hid::KEY_DDOWN,

		TEST_BUTTON = nn::hid::KEY_MINUS | nn::hid::KEY_A,
		TEMPINT_INC = nn::hid::KEY_DRIGHT | nn::hid::KEY_ZL,
		TEMPINT_DEC = nn::hid::KEY_DLEFT | nn::hid::KEY_ZL,

		MAPJUMP_JUMP = nn::hid::KEY_DDOWN | nn::hid::KEY_ZL,
		ACCESS_CLOSED_LANDMARKS = nn::hid::KEY_DUP | nn::hid::KEY_ZL,
		PLAYSE = nn::hid::KEY_MINUS | nn::hid::KEY_ZL,

		MOONJUMP = nn::hid::KEY_R | nn::hid::KEY_B,
		DISABLE_FALL_DAMAGE = nn::hid::KEY_A,

		RETURN_TO_TITLE = nn::hid::KEY_L | nn::hid::KEY_R | nn::hid::KEY_ZL | nn::hid::KEY_ZR,

		UI_RENDER_TOGGLE = nn::hid::KEY_Y,
		DEBUG_RENDER_TOGGLE = nn::hid::KEY_B,

		STRAIGHTEN_FONT = nn::hid::KEY_L | nn::hid::KEY_Y,

		EVENT_DEBUG_PREV = nn::hid::KEY_R | nn::hid::KEY_DLEFT,
		EVENT_DEBUG_NEXT = nn::hid::KEY_R | nn::hid::KEY_DRIGHT,
		EVENT_DEBUG_TOGGLE = nn::hid::KEY_R | nn::hid::KEY_DUP,

		FREECAM_TOGGLE = nn::hid::KEY_LSTICK | nn::hid::KEY_RSTICK,
		FREECAM_FOVHOLD = nn::hid::KEY_LSTICK,
		FREECAM_ROLLHOLD = nn::hid::KEY_RSTICK,
		FREECAM_SPEED_UP = nn::hid::KEY_ZL,
		FREECAM_SPEED_DOWN = nn::hid::KEY_L,
		FREECAM_TELEPORT = FREECAM_TOGGLE | nn::hid::KEY_L | nn::hid::KEY_R,

		LOGGER_TEST = nn::hid::KEY_PLUS | nn::hid::KEY_R,
		DISPLAY_VERSION = nn::hid::KEY_PLUS | nn::hid::KEY_MINUS,
	};

}; // namespace xenomods