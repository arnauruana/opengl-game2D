#include "Menu.h"

#include <GL/glut.h>

#include <iostream>


Menu::Menu()
{
	this->spriteMenu = NULL;
	this->spriteSelector = NULL;
	this->spriteControls = NULL;
	this->spriteCredits = NULL;
}

Menu::~Menu()
{
	if (this->spriteMenu != NULL) delete this->spriteMenu;
	if (this->spriteSelector != NULL) delete this->spriteSelector;
	if (this->spriteControls != NULL) delete this->spriteControls;
	if (this->spriteCredits != NULL) delete this->spriteCredits;
}


void Menu::setShader(const ShaderProgram& shader)
{
	this->shader = shader;
}


void Menu::init()
{
	switch (this->state)
	{
		case this->State::MENU:
		{
			this->initMenu();
			break;
		}
		case this->State::CONT:
		{
			this->initControls();
			break;
		}
		case this->State::CRED:
		{
			this->initCredits();
			break;
		}
		default:
		{
			cout << "[MENU::init] Wrong menu state: " << this->state << endl;
			exit(EXIT_FAILURE);
		}
	}
}

void Menu::update(int deltaTime)
{
	switch (this->state)
	{
		case this->State::MENU:
		{
			this->updateMenu(deltaTime);
			break;
		}
		case this->State::CONT:
		{
			this->updateControls(deltaTime);
			break;
		}
		case this->State::CRED:
		{
			this->updateCredits(deltaTime);
			break;
		}
		default:
		{
			cout << "[MENU::update] Wrong menu state: " << this->state << endl;
			exit(EXIT_FAILURE);
		}
	}
}

void Menu::render()
{
	switch (this->state)
	{
		case this->State::MENU:
		{
			this->renderMenu();
			break;
		}
		case this->State::CONT:
		{
			this->renderControls();
			break;
		}
		case this->State::CRED:
		{
			this->renderCredits();
			break;
		}
		default:
		{
			cout << "[MENU::render] Wrong menu state: " << this->state << endl;
			exit(EXIT_FAILURE);
		}
	}
}


void Menu::initMenu()
{
	this->textureMenu.loadFromFile(Menu::PATH_MENU, PixelFormat(Settings::FORMAT_MENU));

	this->spriteMenu = Sprite::createSprite(glm::ivec2(Settings::GAME_WINDOW_WIDTH, Settings::GAME_WINDOW_HEIGHT), glm::vec2(1.f, 1.f), &this->textureMenu, &this->shader);
	this->spriteMenu->setNumberAnimations(0);
	this->spriteMenu->setPosition(glm::vec2(0.f, 0.f));

	this->initSelector();
}

void Menu::initSelector()
{
	this->textureSelector.loadFromFile(Menu::PATH_SELE, PixelFormat(Settings::FORMAT_SELE));
	
	this->spriteSelector = Sprite::createSprite(glm::ivec2(Settings::GAME_WINDOW_WIDTH / 3 - 30, 36), glm::vec2(1.f, 1.f), &this->textureSelector, &this->shader);
	this->spriteSelector->setNumberAnimations(0);
	this->spriteSelector->setPosition(this->selectorPos);
}

void Menu::initControls()
{
	this->textureControls.loadFromFile(Menu::PATH_CONT, PixelFormat(Settings::FORMAT_CONT));
	
	this->spriteControls = Sprite::createSprite(glm::ivec2(Settings::GAME_WINDOW_WIDTH, Settings::GAME_WINDOW_HEIGHT), glm::vec2(1.f, 1.f), &this->textureControls, &this->shader);
	this->spriteControls->setNumberAnimations(0);
	this->spriteControls->setPosition(glm::vec2(0.f, 0.f));
}

void Menu::initCredits()
{
	this->textureCredits.loadFromFile(Menu::PATH_CRED, PixelFormat(Settings::FORMAT_CRED));
	
	this->spriteCredits = Sprite::createSprite(glm::ivec2(Settings::GAME_WINDOW_WIDTH, Settings::GAME_WINDOW_HEIGHT), glm::vec2(1.f, 1.f), &this->textureCredits, &this->shader);
	this->spriteCredits->setNumberAnimations(0);
	this->spriteCredits->setPosition(glm::vec2(0.f, 0.f));
}


void Menu::updateMenu(int deltaTime)
{
	this->spriteMenu->update(deltaTime);

	if (keyboard::skey[GLUT_KEY_UP])
	{
		this->selectorPos = this->spriteSelector->getPosition();

		int posY = int(this->selectorPos.y);
		switch (posY)
		{
		case 235:
			break;
		case 280:
			this->selectorPos.y = 235.f;
			break;
		case 325:
			this->selectorPos.y = 280.f;
			break;
		default:
			cout << "[SCENE::updateMenu] Wrong selector position: " << posY << endl;
			exit(EXIT_FAILURE);
		}
		this->spriteSelector->setPosition(this->selectorPos);

		keyboard::skey[GLUT_KEY_UP] = false;
	}
	else if (keyboard::skey[GLUT_KEY_DOWN])
	{
		this->selectorPos = this->spriteSelector->getPosition();

		int posY = int(this->selectorPos.y);
		switch (posY)
		{
		case 235:
			this->selectorPos.y = 280.f;
			break;
		case 280:
			this->selectorPos.y = 325.f;
			break;
		case 325:
			break;
		default:
			cout << "[SCENE::updateMenu] Wrong selector position: " << posY << endl;
			exit(EXIT_FAILURE);
		}
		this->spriteSelector->setPosition(this->selectorPos);

		keyboard::skey[GLUT_KEY_DOWN] = false;
	}
	else if (keyboard::key[KEY_RETURN])
	{
		this->selectorPos = this->spriteSelector->getPosition();

		int posY = int(this->selectorPos.y);
		switch (posY)
		{
		case 235:
			this->selectorPos.y = 235.f;
			Settings::playing = true;
			break;
		case 280:
			this->selectorPos.y = 280.f;
			this->state = this->State::CONT;
			break;
		case 325:
			this->selectorPos.y = 325.f;
			this->state = this->State::CRED;
			break;
		default:
			cout << "[SCENE::updateMenu] Wrong selector position: " << posY << endl;
			exit(EXIT_FAILURE);
		}

		this->init();
	}
}

void Menu::updateControls(int deltaTime)
{
	this->spriteControls->update(deltaTime);

	if (keyboard::key['B'] || keyboard::key['b'])
	{
		this->state = this->State::MENU;
		this->init();
	}
}

void Menu::updateCredits(int deltaTime)
{
	this->spriteCredits->update(deltaTime);

	if (keyboard::key['B'] || keyboard::key['b'])
	{
		this->state = this->State::MENU;
		this->init();
	}
}


void Menu::renderMenu()
{
	this->spriteMenu->render();
	this->spriteSelector->render();
}

void Menu::renderControls()
{
	this->spriteControls->render();
}

void Menu::renderCredits()
{
	this->spriteCredits->render();
}