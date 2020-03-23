#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include "Menu.h"
#include "Play.h"


class Scene
{
public:

	enum class State { MENU, PLAY };

public:

	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();

private:

	inline void updateState();

	inline void initMenu();
	inline void updateMenu(int deltaTime);
	inline void renderMenu();

	inline void initPlay();
	inline void updatePlay(int deltaTime);
	inline void renderPlay();

private:

	Scene::State state = Scene::State::MENU;

	Menu menu;
	Play play;
};


#endif // _SCENE_INCLUDE