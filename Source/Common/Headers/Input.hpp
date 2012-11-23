#ifndef __DAWN_INPUT_HPP__
#define __DAWN_INPUT_HPP__

namespace Dawn
{
	typedef enum
	{
		D_TAB		= 9,
		D_ENTER		= 13,
		D_ESCAPE	= 27,
		D_SPACE		= 32,
		D_BACKSPACE = 128,
		D_CAPSLOCK,
		D_SCROLL,
		D_POWER,
		D_PAUSE,

		D_UPARROW	= 133,
		D_DOWNARROW,
		D_LEFTARROW,
		D_RIGHTARROW,

		// Super keys (they really are!)
		D_LSUPER	= 137,
		D_RSUPER,

		D_ALT	= 140,
		D_CTRL,
		D_SHIFT,
		D_INS,
		D_DELETE,
		D_PGDN,
		D_PGUP,
		D_HOME,
		D_END,

		D_F1 = 149,
		D_F2,
		D_F3,
		D_F4,
		D_F5,
		D_F6,
		D_F7,
		D_F8,
		D_F9,
		D_F10,
		D_F11,
		D_F12,

		// Key pad
		D_NP_HOME = 165,
		D_NP_UPARROW,
		D_NP_PGUP,
		D_NP_LEFTARROW,
		D_NP_5,
		D_NP_RIGTARROW,
		D_NP_END,
		D_NP_DOWNARROW,
		D_NP_PGDN,
		D_NP_ENTER,
		D_NP_INS,
		D_NP_DEL,
		D_NP_SLASH,
		D_NP_MINUS,
		D_NP_PLUS,
		D_NP_NUMLOCK,
		D_NP_ASTERISK,
		D_NP_EQUAL,

		D_MOUSE1 = 187,
		D_MOUSE2,
		D_MOUSE3,
		D_MOUSE4,
		D_MOUSE5,
		D_MOUSE6,
		D_MOUSE7,
		D_MOUSE8,

		D_MWHEELDOWN =195,
		D_MWHEELUP,

		D_PRINT_SCR = 252,
		D_RIGHT_ALT = 253,
		D_LAST_KEY = 254
	}KeyID;
}

#endif

