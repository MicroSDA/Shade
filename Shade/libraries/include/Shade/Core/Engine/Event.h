#pragma once
#include "Shade/Core/CoreAPI.h"
#include <SDL2/SDL.h>
//union SDL_Event;

namespace se
{
	class SE_API Event
	{
		friend class EventManager;
	public:
		enum class Type : uint32_t
		{
			FirstEvent = 0x0,
			Quit = 0x100,
			Display = 0x150,
			Window = 0x200,
			System,

			KeyDown = 0x300,
			KeyUp,
			TextEditing,
			TextInput,
			KeyMapChanged,

			MouseMotion = 0x400,
			MouseButtonDown,
			MouseButtonUp,
			MouseWheel,

			CustomEvent = 0x8000,
			LastEvent = 0xFFFF
		};
		enum class Window : uint32_t
		{
			None,
			Show,			// Window has been show
			Hidden,			// Window has been hidden
			Exposed,		// Window has been exposed and should beredrawn

			Moved,			// Window has been moved

			Resized,		// Window has been resized
			SizeChanged,	// The window size has changed

			Minimized,		// Window has been minimized
			Maximized,		// Window has been maximized
			Restored,		// Window has been restored to normal size and position

			Enter,			// Window has gained mouse focus
			Leave,			// Window has lost mouse focus
			FocusGained,	// Window has gained keyboard focus 
			FocusLost,		// Window has lost keyboard focus
			Close,			// The window manager requests that the window be closed
			TakeFocus,
			HitTest
		};
		struct Keyboard
		{
			enum class SCode : uint32_t
			{
				Unknown = 0,
				A = 4,
				B = 5,
				C = 6,
				D = 7,
				E = 8,
				F = 9,
				G = 10,
				H = 11,
				I = 12,
				J = 13,
				K = 14,
				L = 15,
				M = 16,
				N = 17,
				O = 18,
				P = 19,
				Q = 20,
				R = 21,
				S = 22,
				T = 23,
				U = 24,
				V = 25,
				W = 26,
				X = 27,
				Y = 28,
				Z = 29,

				Num_1 = 30,
				Num_2 = 31,
				Num_3 = 32,
				Num_4 = 33,
				Num_5 = 34,
				Num_6 = 35,
				Num_7 = 36,
				Num_8 = 37,
				Num_9 = 38,
				Num_0 = 39,

				Return = 40,
				Escape = 41,
				Backspace = 42,
				Tab = 43,
				Space = 44,

				Minus = 45,
				Eauals = 46,
				LeftBracket = 47,
				RightBracket = 48,
				BackSlash = 49,
				NonUshash = 50,
				Semicolon = 51,
				Apostrophe = 52,
				Grave = 53,

				Comma = 54,
				Period = 55,
				Slash = 56,

				Capslock = 57,

				F1 = 58,
				F2 = 59,
				F3 = 60,
				F4 = 61,
				F5 = 62,
				F6 = 63,
				F7 = 64,
				F8 = 65,
				F9 = 66,
				F10 = 67,
				F11 = 68,
				F12 = 69,

				PrintScreen = 70,
				ScrollLock = 71,
				Pause = 72,
				Insert = 73,

				Home = 74,
				PageUp = 75,
				Delete = 76,
				End = 77,
				PageDown = 78,
				Right = 79,
				Left = 80,
				Donw = 81,
				Up = 82,

				NumlockClear = 83,

				Kp_Divide = 84,
				Kp_Multiply = 85,
				Kp_Minus = 86,
				Kp_Plus = 87,
				Kp_Enter = 88,
				Kp_1 = 89,
				Kp_2 = 90,
				Kp_3 = 91,
				Kp_4 = 92,
				Kp_5 = 93,
				Kp_6 = 94,
				Kp_7 = 95,
				Kp_8 = 96,
				Kp_9 = 97,
				Kp_0 = 98,
				Kp_Period = 99,

				NonUsBackSlash = 100,

				Application = 101,
				Power = 102,
				Kp_Equals = 103,
				F13 = 104,
				F14 = 105,
				F15 = 106,
				F16 = 107,
				F17 = 108,
				F18 = 109,
				F19 = 110,
				F20 = 111,
				F21 = 112,
				F22 = 113,
				F23 = 114,
				F24 = 115,
				Executr = 116,
				Help = 117,
				Menu = 118,
				Select = 119,
				Stop = 120,
				Again = 121,
				Undo = 122,
				Cut = 123,
				Copy = 124,
				Paste = 125,
				Find = 126,
				Mute = 127,
				VolumeUp = 128,
				VolumeDown = 129,
				Kp_Comma = 133,
				Kp_EaualsAS400 = 134,
				International1 = 135,
				International2 = 136,
				International3 = 137,
				International4 = 138,
				International5 = 139,
				International6 = 140,
				International7 = 141,
				International8 = 142,
				International9 = 143,
				Lang1 = 144, /**< Hangul/English toggle */
				Lang2 = 145, /**< Hanja conversion */
				Lang3 = 146, /**< Katakana */
				Lang4 = 147, /**< Hiragana */
				Lang5 = 148, /**< Zenkaku/Hankaku */
				Lang6 = 149, /**< reserved */
				Lang7 = 150, /**< reserved */
				Lang8 = 151, /**< reserved */
				Lang9 = 152, /**< reserved */
				Alterase = 153, /**< Erase-Eaze */
				Sysreq = 154,
				Cancel = 155,
				Clear = 156,
				Prior = 157,
				Return2 = 158,
				Separator = 159,
				Out = 160,
				Oper = 161,
				ClearAgain = 162,
				Crsel = 163,
				Exsel = 164,

				Kp_00 = 176,
				Kp_000 = 177,
				ThousandsSeparator = 178,
				DecimalSeparator = 179,
				CurrencyUint = 180,
				CurrencySubunit = 181,
				Kp_LeftParen = 182,
				Kp_RightParen = 183,
				Kp_LeftBrace = 184,
				Kp_RightBrace = 185,
				Kp_Tab = 186,
				Kp_BackSpace = 187,
				Kp_A = 188,
				Kp_B = 189,
				Kp_C = 190,
				Kp_D = 191,
				Kp_E = 192,
				Kp_F = 193,
				Kp_Xor = 194,
				Kp_Power = 195,
				Kp_Percent = 196,
				Kp_Less = 197,
				Kp_Grater = 198,
				Kp_Ampersand = 199,
				Kp_DblAmpersand = 200,
				Kp_VerticalBar = 201,
				Kp_DblVerticalBar = 202,
				Kp_Colon = 203,
				Kp_Hash = 204,
				Kp_Space = 205,
				Kp_At = 206,
				Kp_Exclam = 207,
				Kp_MemStore = 208,
				Kp_MemRecall = 209,
				Kp_MemClear = 210,
				Kp_MemAdd = 211,
				Kp_MemSubtract = 212,
				Kp_MemMultiply = 213,
				Kp_MemDivide = 214,
				Kp_PlusMinus = 215,
				Kp_Clear = 216,
				Kp_ClearEntry = 217,
				Kp_Binary = 218,
				Kp_Octal = 219,
				Kp_Decimal = 220,
				Kp_Hexadecimal = 221,

				LCtrl = 224,
				LShift = 225,

				LAlt = 226,
				LGui = 227,
				RCtrl = 228,
				RShift = 229,
				RAlt = 230,
				RGui = 231,

				Mode = 257,

				Audio = 258,
				AudioPrev = 259,
				AudioStop = 260,
				AudioPlay = 261,
				AudioMute = 262,
				MediaSelect = 263,
				Www = 264,
				Mail = 265,
				Calculator = 266,
				Computer = 267,
				Ac_Search = 268,
				Ac_Home = 269,
				Ac_Back = 270,
				Ac_Forward = 271,
				Ac_Stop = 272,
				Ac_Refresh = 273,
				Ac_Bookmarks = 274,

				BrightnessDown = 275,
				BrightnessUp = 276,
				DisplaySwitch = 277,
				KbdIllumToggle = 278,
				KbdIllumDown = 279,
				KbdIllumUp = 280,
				Eject = 281,
				Sleep = 282,

				App1 = 283,
				App2 = 284,

				AudioRewind = 285,
				AudioFastForward = 286,

				Num_Scancodes = 512

			} ScanCode = Event::Keyboard::SCode::Unknown;
			// TODO
			enum class KCode : uint32_t
			{

			} KeyCode;
		};
		struct Mouse
		{
			struct Motion
			{
				int32_t x = 0;
				int32_t y = 0;

			} Motion;

			struct Button
			{
				enum class KCode : uint8_t
				{
					None = 0,
					Left = 1,
					Middle = 2,
					Right = 3,

				} Code = Event::Mouse::Button::KCode::None;
				enum class KState : uint8_t
				{
					Pressed,
					Released
				} State;

			} Button;
			// TODO
			struct Whell
			{

			};

		};
		struct Text 
		{
			char Text[32];
		};
		Event() = default;
		~Event() = default;
		void SetType(const se::Event::Type& type);
		void SetWindow(const se::Event::Window& window);
		void SetKeyboard(const se::Event::Keyboard& keyboard);
		void SetMouse(const se::Event::Mouse& mouse);
		void SetText(const se::Event::Text& text);

		const se::Event::Type& GetType() const;
		const se::Event::Window& GetWindow()const;
		const se::Event::Keyboard& GetKeyboard()const;
		const se::Event::Mouse& GetMouse()const;
		const se::Event::Text& GetText()const;

		void operator = (const SDL_Event& event);
		operator SDL_Event ();
	private:
		se::Event::Type			m_Type = se::Event::Type::FirstEvent;
		se::Event::Window		m_Window = se::Event::Window::None;
		se::Event::Keyboard		m_Keyboard;
		se::Event::Mouse        m_Mouse;
		se::Event::Text         m_Text;
		SDL_Event               m_SdlEvent;
	};

}