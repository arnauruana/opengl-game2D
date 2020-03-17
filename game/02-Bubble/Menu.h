#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE


#include "ShaderProgram.h"
#include "Sprite.h"
#include "Texture.h"


class Menu
{

public:



public:

	Menu();
	~Menu();

	void init();
	void update(int deltaTime);
	void render();

	void setShader(const ShaderProgram& shader);

private:

	void initMenu();
	void initControls();
	void initCredits();
	void initSelector();

	void renderMenu();
	void renderControls();
	void renderCredits();

private:

	Sprite* spriteMenu;
	Sprite* spriteControls;
	Sprite* spriteCredits;
	Sprite* spriteSelector;

	Texture textureMenu;
	Texture textureControls;
	Texture textureCredits;
	Texture textureSelector;

	ShaderProgram shader;

	glm::vec2 selectorPos = glm::vec2(480.f / 7.f, 235.f);
};


#endif // _MENU_INCLUDE