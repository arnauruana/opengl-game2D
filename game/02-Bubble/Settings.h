#ifndef _SETTINGS_INCLUDE
#define _SETTINGS_INCLUDE


#include <string>


#define KEY_RETURN 13

#define TILE_BAR_WIDTH 8
#define TILE_BAR_HEIGHT 31


struct Settings
{
	inline static bool playing = false;

	inline static const int GAME_WINDOW_WIDTH = 480;
	inline static const int GAME_WINDOW_HEIGHT = 480;

	inline static const std::string PATH_IMG_MENU = "images/menu/";

	inline static const std::string IMG_MENU = "menu.jpg";
	inline static const std::string IMG_SELE = "selector.jpg";
	inline static const std::string IMG_CONT = "controls.jpg";
	inline static const std::string IMG_CRED = "credits.jpg";

	inline static enum Format { RGB, RGBA };

	inline static const Format FORMAT_MENU = Format::RGB;
	inline static const Format FORMAT_SELE = Format::RGBA;
	inline static const Format FORMAT_CONT = Format::RGB;
	inline static const Format FORMAT_CRED = Format::RGB;
};


#endif // _SETTINGS_INCLUDE