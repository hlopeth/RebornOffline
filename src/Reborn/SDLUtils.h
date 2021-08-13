#pragma once
#include "KeyCodes.h"
#include <SDL.h>

namespace Reborn {
	KeyCode ToRebornKeyCode(SDL_Keycode sdlKeyCode);
	MouseButtonCode ToRebornMoseButtonCode(Uint8 sdlButtonCode);
}