#include "BdatRandomizer.hpp"

#include <bf2mods/DebugWrappers.hpp>
#include <bf2mods/HidInput.hpp>
#include <bf2mods/Logger.hpp>
#include <bf2mods/Utils.hpp>

#include "../State.hpp"
#include "../main.hpp"
#include "bf2mods/engine/bdat/Bdat.hpp"
#include "bf2mods/stuff/utils/util.hpp"
#include "nn/oe.h"
#include "version.h"

#include <skylaunch/hookng/Hooks.hpp>

namespace {
	struct MSTextHook : skylaunch::hook::Trampoline<MSTextHook> {
		static const char* Hook(unsigned char* pBdat, int n) {
			const char* sheetName = Bdat::getSheetName(pBdat);

			if(!strcmp(sheetName, "menu_ms")) {
				if(n == 1610) {
					// it says "Loading" in the japanese version too so I'm not allowed to moan about hardcoding this
					return "Loading (modded)";
				}
			}

			switch(bf2mods::BdatRandomizer::scrambleType) {
				using enum bf2mods::BdatRandomizer::BdatScrambleType;

				case ScrambleIndex:
					// scrambles the index of the ms text sheet
					return Orig(pBdat, (util::nnRand<int16_t>() % Bdat::getIdCount(pBdat)) + Bdat::getIdTop(pBdat));
				case ShowSheetName:
					return sheetName;
				case Off:
				default:
					return Orig(pBdat, n);
			}
		}
	};
} // namespace

namespace bf2mods {

	BdatRandomizer::BdatScrambleType BdatRandomizer::scrambleType = BdatRandomizer::BdatScrambleType::Off;

	void BdatRandomizer::Initialize() {
		g_Logger->LogDebug("Setting up BDAT randomizer...");

		// Hook stuff
		MSTextHook::HookAt(Bdat::getMSText);
	}

	void BdatRandomizer::Update() {
		if(GetPlayer(2)->InputDownStrict(Keybind::BDAT_SCRAMBLETYPE_TOGGLE)) {
			underlying_value(scrambleType) += 1;

			if(scrambleType >= BdatScrambleType::Count)
				scrambleType = BdatScrambleType::Off;

			g_Logger->LogInfo("Bdat scramble type set to {}", scrambleType);
		}
	}

	BF2MODS_REGISTER_MODULE(BdatRandomizer);

} // namespace bf2mods