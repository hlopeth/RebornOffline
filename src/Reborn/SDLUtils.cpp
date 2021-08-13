#include "Core.h"
#include "SDLUtils.h"

KeyCode Reborn::ToRebornKeyCode(SDL_Keycode sdlKeyCode)
{
	KeyCode rebornKeyCode = KeyCode::key_unknown;
	switch (sdlKeyCode)
	{
	case SDLK_UNKNOWN: rebornKeyCode = KeyCode::key_unknown; break;
	case SDLK_RETURN: rebornKeyCode = KeyCode::key_return; break;
	case SDLK_ESCAPE: rebornKeyCode = KeyCode::key_escape; break;
	case SDLK_BACKSPACE: rebornKeyCode = KeyCode::key_backspace; break;
	case SDLK_TAB: rebornKeyCode = KeyCode::key_tab; break;
	case SDLK_SPACE: rebornKeyCode = KeyCode::key_space; break;
	case SDLK_EXCLAIM: rebornKeyCode = KeyCode::key_exclaim; break;
	case SDLK_QUOTEDBL: rebornKeyCode = KeyCode::key_quotedbl; break;
	case SDLK_HASH: rebornKeyCode = KeyCode::key_hash; break;
	case SDLK_PERCENT: rebornKeyCode = KeyCode::key_percent; break;
	case SDLK_DOLLAR: rebornKeyCode = KeyCode::key_dollar; break;
	case SDLK_AMPERSAND: rebornKeyCode = KeyCode::key_ampersand; break;
	case SDLK_QUOTE: rebornKeyCode = KeyCode::key_quote; break;
	case SDLK_LEFTPAREN: rebornKeyCode = KeyCode::key_leftParen; break;
	case SDLK_RIGHTPAREN: rebornKeyCode = KeyCode::key_rightParen ; break;
	case SDLK_ASTERISK: rebornKeyCode = KeyCode::key_asterisk; break;
	case SDLK_PLUS: rebornKeyCode = KeyCode::key_plus; break;
	case SDLK_COMMA: rebornKeyCode = KeyCode::key_comma; break;
	case SDLK_MINUS: rebornKeyCode = KeyCode::key_minus; break;
	case SDLK_PERIOD: rebornKeyCode = KeyCode::key_period; break;
	case SDLK_SLASH: rebornKeyCode = KeyCode::key_slash; break;
	case SDLK_0: rebornKeyCode = KeyCode::key_0; break;
	case SDLK_1: rebornKeyCode = KeyCode::key_1; break;
	case SDLK_2: rebornKeyCode = KeyCode::key_2; break;
	case SDLK_3: rebornKeyCode = KeyCode::key_3; break;
	case SDLK_4: rebornKeyCode = KeyCode::key_4; break;
	case SDLK_5: rebornKeyCode = KeyCode::key_5; break;
	case SDLK_6: rebornKeyCode = KeyCode::key_6; break;
	case SDLK_7: rebornKeyCode = KeyCode::key_7; break;
	case SDLK_8: rebornKeyCode = KeyCode::key_8; break;
	case SDLK_9: rebornKeyCode = KeyCode::key_9; break;
	case SDLK_COLON: rebornKeyCode = KeyCode::key_colon; break;
	case SDLK_SEMICOLON: rebornKeyCode = KeyCode::key_semicolon; break;
	case SDLK_LESS: rebornKeyCode = KeyCode::key_less; break;
	case SDLK_EQUALS: rebornKeyCode = KeyCode::key_equals; break;
	case SDLK_GREATER: rebornKeyCode = KeyCode::key_greater; break;
	case SDLK_QUESTION: rebornKeyCode = KeyCode::key_question; break;
	case SDLK_AT: rebornKeyCode = KeyCode::key_at; break;

	case SDLK_LEFTBRACKET: rebornKeyCode = KeyCode::key_leftbracket; break;
	case SDLK_BACKSLASH: rebornKeyCode = KeyCode::key_backslach; break;
	case SDLK_RIGHTBRACKET: rebornKeyCode = KeyCode::key_rightbracket; break;
	case SDLK_CARET: rebornKeyCode = KeyCode::key_caret; break;
	case SDLK_UNDERSCORE: rebornKeyCode = KeyCode::key_underscore; break;
	case SDLK_BACKQUOTE: rebornKeyCode = KeyCode::key_backquote; break;
	case SDLK_a: rebornKeyCode = KeyCode::key_a; break;
	case SDLK_b: rebornKeyCode = KeyCode::key_b; break;
	case SDLK_c: rebornKeyCode = KeyCode::key_c; break;
	case SDLK_d: rebornKeyCode = KeyCode::key_d; break;
	case SDLK_e: rebornKeyCode = KeyCode::key_e; break;
	case SDLK_f: rebornKeyCode = KeyCode::key_f; break;
	case SDLK_g: rebornKeyCode = KeyCode::key_g; break;
	case SDLK_h: rebornKeyCode = KeyCode::key_h; break;
	case SDLK_i: rebornKeyCode = KeyCode::key_i; break;
	case SDLK_j: rebornKeyCode = KeyCode::key_j; break;
	case SDLK_k: rebornKeyCode = KeyCode::key_k; break;
	case SDLK_l: rebornKeyCode = KeyCode::key_l; break;
	case SDLK_m: rebornKeyCode = KeyCode::key_m; break;
	case SDLK_n: rebornKeyCode = KeyCode::key_n; break;
	case SDLK_o: rebornKeyCode = KeyCode::key_o; break;
	case SDLK_p: rebornKeyCode = KeyCode::key_p; break;
	case SDLK_q: rebornKeyCode = KeyCode::key_q; break;
	case SDLK_r: rebornKeyCode = KeyCode::key_r; break;
	case SDLK_s: rebornKeyCode = KeyCode::key_s; break;
	case SDLK_t: rebornKeyCode = KeyCode::key_t; break;
	case SDLK_u: rebornKeyCode = KeyCode::key_u; break;
	case SDLK_v: rebornKeyCode = KeyCode::key_v; break;
	case SDLK_w: rebornKeyCode = KeyCode::key_w; break;
	case SDLK_x: rebornKeyCode = KeyCode::key_x; break;
	case SDLK_y: rebornKeyCode = KeyCode::key_y; break;
	case SDLK_z: rebornKeyCode = KeyCode::key_z; break;



	default: rebornKeyCode = KeyCode::key_unknown; break;
	}
	return rebornKeyCode;
}

MouseButtonCode Reborn::ToRebornMoseButtonCode(Uint8 sdlButtonCode)
{
	MouseButtonCode rebornButtonCode = MouseButtonCode::button_unknown;
	switch (sdlButtonCode)
	{
	case SDL_BUTTON_LEFT: rebornButtonCode = MouseButtonCode::button_left; break;
	case SDL_BUTTON_MIDDLE: rebornButtonCode = MouseButtonCode::button_middle; break;
	case SDL_BUTTON_RIGHT: rebornButtonCode = MouseButtonCode::button_right; break;
	default: rebornButtonCode = MouseButtonCode::button_unknown; break;
	}
	return rebornButtonCode;
}
