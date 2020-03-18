#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE


#include "Keyboard.h"
#include "Settings.h"
#include "ShaderProgram.h"
#include "Sprite.h"
#include "Texture.h"

#include <string>


class Menu
{
public:

	inline static const std::string PATH_MENU = Settings::PATH_IMG_MENU + Settings::IMG_MENU;
	inline static const std::string PATH_SELE = Settings::PATH_IMG_MENU + Settings::IMG_SELE;
	inline static const std::string PATH_CONT = Settings::PATH_IMG_MENU + Settings::IMG_CONT;
	inline static const std::string PATH_CRED = Settings::PATH_IMG_MENU + Settings::IMG_CRED;

	inline static enum State { MENU, CONT, CRED };

public:

	Menu();
	~Menu();

	void setShader(const ShaderProgram& shader);

	void init();
	void update(int deltaTime);
	void render();

private:

	void initMenu();
	void initSelector();
	void initControls();
	void initCredits();

	void updateMenu(int deltaTime);
	void updateControls(int deltaTime);
	void updateCredits(int deltaTime);

	void renderMenu();
	void renderControls();
	void renderCredits();

private:

	Menu::State state = this->State::MENU;

	Sprite* spriteMenu;
	Sprite* spriteSelector;
	Sprite* spriteControls;
	Sprite* spriteCredits;

	Texture textureMenu;
	Texture textureSelector;
	Texture textureControls;
	Texture textureCredits;

	ShaderProgram shader;

	glm::vec2 selectorPos = glm::vec2(480.f / 7.f, 235.f);
};


#endif // _MENU_INCLUDE