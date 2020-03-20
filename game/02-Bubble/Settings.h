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

	inline static const std::string IMG_FLAG  = "flag.png";
	inline static const std::string IMG_FLOOR = "floor.png";
	inline static const std::string IMG_LAVA  = "fluid.png";
	inline static const std::string IMG_ROCK  = "rock.png";
	inline static const std::string IMG_WATER = "fluid.png";

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
};


#endif // _SETTINGS_INCLUDE