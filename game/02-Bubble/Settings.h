#ifndef _SETTINGS_INCLUDE
#define _SETTINGS_INCLUDE


#include <string>


#define KEY_RETURN 13
#define KEY_SCAPE 27

#define TILE_BAR_WIDTH 8
#define TILE_BAR_HEIGHT 31


struct Settings
{
	inline static bool playing = false;

	inline static const int GAME_WINDOW_WIDTH  = 480;
	inline static const int GAME_WINDOW_HEIGHT = 480;

	inline static const std::string PATH_MENU = "images/menu/";

	inline static const std::string IMG_MENU = "menu.jpg";
	inline static const std::string IMG_SELE = "selector.jpg";
	inline static const std::string IMG_CONT = "controls.jpg";
	inline static const std::string IMG_CRED = "credits.jpg";

	inline static const std::string PATH_OBJECTS = "images/object/";

	inline static const std::string IMG_BABA = "baba.png";
	inline static const std::string IMG_FLAG = "flag.png";
	inline static const std::string IMG_LAVA = "fluid.png";
	inline static const std::string IMG_ROCK = "rock.png";
	inline static const std::string IMG_WALL = "wall.png";
	inline static const std::string IMG_WATER = "fluid.png";

	inline static const std::string TXT_BABA = "word-baba.png";
	inline static const std::string TXT_FLAG = "word-flag.png";
	inline static const std::string TXT_ROCK = "word-rock.png";
	inline static const std::string TXT_WALL = "word-wall.png";
	inline static const std::string TXT_LAVA = "word-lava.png";
	inline static const std::string TXT_DEFEAT = "word-defeat.png";


	inline static const std::string TXT_IS = "word-is.png";
	inline static const std::string TXT_NEAR = "word-near.png";

	inline static const std::string TXT_PUSH = "word-push.png";
	inline static const std::string TXT_STOP = "word-stop.png";
	inline static const std::string TXT_WIN = "word-win.png";
	inline static const std::string TXT_YOU = "word-you.png";

	enum class Format { RGB, RGBA };

	inline static const Format FORMAT_MENU = Format::RGB;
	inline static const Format FORMAT_SELE = Format::RGBA;
	inline static const Format FORMAT_CONT = Format::RGB;
	inline static const Format FORMAT_CRED = Format::RGB;

	inline static const Format FORMAT_FLAG  = Format::RGBA;
	inline static const Format FORMAT_FLOOR = Format::RGBA;
	inline static const Format FORMAT_LAVA  = Format::RGBA;
	inline static const Format FORMAT_ROCK  = Format::RGBA;
	inline static const Format FORMAT_WATER = Format::RGBA;

	inline static const Format FORMAT_TXTBABA = Format::RGBA;
	inline static const Format FORMAT_TXTFLAG = Format::RGBA;
	inline static const Format FORMAT_TXTROCK = Format::RGBA;
	inline static const Format FORMAT_TXTWALL = Format::RGBA;
	inline static const Format FORMAT_TXTLAVA = Format::RGBA;
	inline static const Format FORMAT_TXTDEFEAT = Format::RGBA;

	inline static const Format FORMAT_TXTIS = Format::RGBA;
	inline static const Format FORMAT_TXTNEAR = Format::RGBA;

	inline static const Format FORMAT_TXTPUSH = Format::RGBA;
	inline static const Format FORMAT_TXTSTOP = Format::RGBA;
	inline static const Format FORMAT_TXTWIN = Format::RGBA;
	inline static const Format FORMAT_TXTYOU = Format::RGBA;
};


#endif // _SETTINGS_INCLUDE