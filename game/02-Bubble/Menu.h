#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE


#include "Keyboard.h"
#include "Settings.h"
#include "ShaderProgram.h"
#include "Sprite.h"
#include "Texture.h"
#include "Sounds.h"

#include <glm/gtc/matrix_transform.hpp>
#include <GL/glut.h>

#include <iostream>
#include <string>


class Menu
{
public:

	enum class State { MENU, CONT, CRED, CONG };

	inline static const std::string PATH_MENU = Settings::PATH_MENU + Settings::IMG_MENU;
	inline static const std::string PATH_SELE = Settings::PATH_MENU + Settings::IMG_SELE;
	inline static const std::string PATH_CONT = Settings::PATH_MENU + Settings::IMG_CONT;
	inline static const std::string PATH_CRED = Settings::PATH_MENU + Settings::IMG_CRED;
	inline static const std::string PATH_CONG = Settings::PATH_MENU + Settings::IMG_CONG;

public:

	Menu();
	~Menu();

	void init();
	void update(int deltaTime);
	void render();

private:

	void initSelector();

	void initMenu();
	void updateMenu(int deltaTime);
	void renderMenu();
	
	void initControls();
	void updateControls(int deltaTime);
	void renderControls();

	void initCredits();
	void updateCredits(int deltaTime);
	void renderCredits();

	void initCongrats();
	void updateCongrats(int deltaTime);
	void renderCongrats();

	void initShader();

private:

	Menu::State state = Menu::State::MENU;

	Sprite* spriteMenu;
	Sprite* spriteSelector;
	Sprite* spriteControls;
	Sprite* spriteCredits;
	Sprite* spriteCongrats;

	Texture textureMenu;
	Texture textureSelector;
	Texture textureControls;
	Texture textureCredits;
	Texture textureCongrats;

	ShaderProgram shader;

	glm::vec2 selectorPos = glm::vec2(480.f / 7.f, 235.f);
};


#endif // _MENU_INCLUDE