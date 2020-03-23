#include "Scene.h"


Scene::Scene() {}

Scene::~Scene() {}


void Scene::setState(Scene::State state)
{
	this->state = state;
	this->init();
}

void Scene::setLevel(int level)
{
	this->init();
}


void Scene::init()
{
	switch (this->state)
	{
		case Scene::State::MENU:
		{
			this->menu.init();
			break;
		}
		case Scene::State::PLAY:
		{
			this->play.init();
			break;
		}
		default:
		{
			std::cout << "[SCENE::init] Wrong game state: " << std::endl;
			exit(EXIT_FAILURE);
		}
	}
}

void Scene::update(int deltaTime)
{
	if (Settings::playing && this->state != Scene::State::PLAY)
	{
		this->state = Scene::State::PLAY;
		this->init();
	}

	this->currentTime += deltaTime;

	switch (this->state)
	{
		case Scene::State::MENU:
		{
			this->menu.update(deltaTime);
			break;
		}
		case Scene::State::PLAY:
		{
			this->play.update(deltaTime);
			break;
		}
		default:
		{
			std::cout << "[SCENE::update] wrong game state: " << std::endl;
			exit(EXIT_FAILURE);
		}
	}
}

void Scene::render()
{
	switch (this->state)
	{
	case Scene::State::MENU:
		this->menu.render();
		break;
	case Scene::State::PLAY:
		this->play.render();
		//this->renderPlay();
		break;
	default:
		std::cout << "[SCENE::render] Wrong game state: " << std::endl;
		exit(EXIT_FAILURE);
	}
}