#include "Scene.h"


Scene::Scene() {}

Scene::~Scene() {}


void Scene::init()
{
	switch (this->state)
	{
		case Scene::State::MENU:
		{
			this->initMenu();
			break;
		}
		case Scene::State::PLAY:
		{
			this->initPlay();
			break;
		}
		default:
		{
			std::cerr << "[SCENE::init] wrong game state: " << std::endl;
			exit(EXIT_FAILURE);
		}
	}
}

void Scene::update(int deltaTime)
{
	this->updateState();

	switch (this->state)
	{
		case Scene::State::MENU:
		{
			this->updateMenu(deltaTime);
			break;
		}
		case Scene::State::PLAY:
		{
			this->updatePlay(deltaTime);
			break;
		}
		default:
		{
			std::cerr << "[SCENE::update] wrong game state: " << std::endl;
			exit(EXIT_FAILURE);
		}
	}
}

void Scene::render()
{
	switch (this->state)
	{
		case Scene::State::MENU:
		{
			this->renderMenu();
			break;
		}
		case Scene::State::PLAY:
		{
			this->renderPlay();
			break;
		}
		default:
		{
			std::cerr << "[SCENE::render] wrong game state: " << std::endl;
			exit(EXIT_FAILURE);
		}
	}
}


inline void Scene::updateState()
{
	if (Settings::playing && this->state != Scene::State::PLAY)
	{
		this->state = Scene::State::PLAY;
		this->init();
	}
	if (!Settings::playing && this->state == Scene::State::PLAY)
	{
		this->state = Scene::State::MENU;
		this->init();
	}
}


inline void Scene::initMenu()
{
	this->menu.init();
}

inline void Scene::updateMenu(int deltaTime)
{
	this->menu.update(deltaTime);
}

inline void Scene::renderMenu()
{
	this->menu.render();
}


inline void Scene::initPlay()
{
	this->play.init();
}

inline void Scene::updatePlay(int deltaTime)
{
	this->play.update(deltaTime);
}

inline void Scene::renderPlay()
{
	this->play.render();
}