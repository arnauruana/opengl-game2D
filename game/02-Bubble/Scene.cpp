#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

#include "Scene.h"
#include "Game.h"

#include <GL/glew.h>
#include <GL/glut.h>


#define KEY_RETURN 13

#define SCREEN_X 0
#define SCREEN_Y 0


Scene::Scene()
{
	this->map1 = NULL;
	this->map2 = NULL;
	this->map3 = NULL;
	this->map4 = NULL;
	this->map5 = NULL;

	this->player1 = NULL;
	this->player2 = NULL;
	this->player3 = NULL;
	this->player4 = NULL;
	this->player5 = NULL;

	this->spriteMenu = NULL;
	this->spriteControls = NULL;
	this->spriteCredits = NULL;
	this->spriteSelector = NULL;
}

Scene::~Scene()
{
	if (this->map1 != NULL) delete this->map1;
	if (this->map2 != NULL) delete this->map2;
	if (this->map3 != NULL) delete this->map3;
	if (this->map4 != NULL) delete this->map4;
	if (this->map5 != NULL) delete this->map5;

	if (this->player1 != NULL) delete this->player1;
	if (this->player2 != NULL) delete this->player2;
	if (this->player3 != NULL) delete this->player3;
	if (this->player4 != NULL) delete this->player4;
	if (this->player5 != NULL) delete this->player5;

	if (this->spriteMenu != NULL) delete this->spriteMenu;
	if (this->spriteControls != NULL) delete this->spriteControls;
	if (this->spriteCredits != NULL) delete this->spriteCredits;
	if (this->spriteSelector != NULL) delete this->spriteSelector;
}


int Scene::getState()
{
	return this->state;
}

int Scene::getLevel()
{
	return this->level;
}


void Scene::setState(int state)
{
	this->state = state;
	this->init();
}

void Scene::setLevel(int level)
{
	this->level = level;
	this->init();
}


void Scene::init()
{
	this->initShaders();

	this->projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	
	switch (this->state)
	{
	case MENU:
		this->initMenu();
		break;
	case CONT:
		this->initControls();
		break;
	case CRED:
		this->initCredits();
		break;
	case PLAY:
		this->initPlay();
		break;
	default:
		cout << "[SCENE::init] Wrong game state: " << this->state << endl;
		cin >> this->state; // DEBUG
		exit(EXIT_FAILURE);
	}
}

void Scene::initMenu()
{
	this->spritesheetMenu.loadFromFile("images/menu.jpg", TEXTURE_PIXEL_FORMAT_RGB);
	this->spriteMenu = Sprite::createSprite(glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(1.f, 1.f), &this->spritesheetMenu, &this->texProgram);
	this->spriteMenu->setNumberAnimations(0);
	this->spriteMenu->setPosition(glm::vec2(0.f, 0.f));

	this->spritesheetSelector.loadFromFile("images/selector.jpg", TEXTURE_PIXEL_FORMAT_RGBA);
	this->spriteSelector = Sprite::createSprite(glm::ivec2(SCREEN_WIDTH/3 - 30, 36), glm::vec2(1.f, 1.f), &this->spritesheetSelector, &this->texProgram);
	this->spriteSelector->setNumberAnimations(0);
	this->spriteSelector->setPosition(this->selectorPos);
}

void Scene::initControls()
{
	this->spritesheetControls.loadFromFile("images/controls.jpg", TEXTURE_PIXEL_FORMAT_RGB);
	this->spriteControls = Sprite::createSprite(glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(1.f, 1.f), &this->spritesheetControls, &this->texProgram);
	this->spriteControls->setNumberAnimations(0);
	this->spriteControls->setPosition(glm::vec2(0.f, 0.f));
}

void Scene::initCredits()
{
	this->spritesheetCredits.loadFromFile("images/credits.jpg", TEXTURE_PIXEL_FORMAT_RGB);
	this->spriteCredits = Sprite::createSprite(glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(1.f, 1.f), &this->spritesheetCredits, &this->texProgram);
	this->spriteCredits->setNumberAnimations(0);
	this->spriteCredits->setPosition(glm::vec2(0.f, 0.f));
}

void Scene::initPlay()
{
	switch (this->level)
	{
	case LVL1:
		this->initLevel1();
		break;
	case LVL2:
		this->initLevel2();
		break;
	case LVL3:
		break;
	case LVL4:
		break;
	case LVL5:
		break;
	default:
		cout << "[SCENE::initPlay] Wrong game level: " << this->level << endl;
		cin >> this->level; // DEBUG
		exit(EXIT_FAILURE);
	}
}

void Scene::initLevel1()
{
	this->map1 = TileMap::createTileMap(PATH_LVL1, glm::vec2(SCREEN_X, SCREEN_Y), this->texProgram);
	
	this->player1 = new Player();
	this->player1->init(glm::ivec2(SCREEN_X, SCREEN_Y), this->texProgram);
	this->player1->setTileMap(this->map1);
	this->player1->setPosition(glm::vec2(1 * this->map1->getTileSize(), 1 * this->map1->getTileSize()));

	this->currentTime = 0.0f;
}

void Scene::initLevel2()
{
	this->map2 = TileMap::createTileMap(PATH_LVL2, glm::vec2(SCREEN_X, SCREEN_Y), this->texProgram);

	this->spritesheetRock.loadFromFile("images/tiles.png", TEXTURE_PIXEL_FORMAT_RGBA);
	this->spriteRock = Sprite::createSprite(glm::ivec2(24, 24), glm::vec2(1.f/32.f, 1.f/66.f), &this->spritesheetRock, &this->texProgram);
	this->spriteRock->setNumberAnimations(0);
	this->spriteRock->setPosition(glm::vec2(9 * this->map2->getTileSize(), 10 * this->map2->getTileSize()));

	this->player2 = new Player();
	this->player2->init(glm::ivec2(SCREEN_X, SCREEN_Y), this->texProgram);
	this->player2->setTileMap(this->map2);
	this->player2->setPosition(glm::vec2(1 * this->map2->getTileSize(), 1 * this->map2->getTileSize()));

	this->currentTime = 0.0f;
}


void Scene::update(int deltaTime)
{
	this->currentTime += deltaTime;

	switch (this->state)
	{
	case MENU:
		this->updateMenu(deltaTime);
		break;
	case CONT:
		this->updateControls(deltaTime);
		break;
	case CRED:
		this->updateCredits(deltaTime);
		break;
	case PLAY:
		this->updatePlay(deltaTime);
		break;
	default:
		cout << "[SCENE::update] Wrong game state: " << this->state << endl;
		cin >> this->state; // DEBUG
		exit(EXIT_FAILURE);
	}
}

void Scene::updateMenu(int deltaTime)
{
	this->spriteMenu->update(deltaTime);

	if (Game::instance().getSpecialKey(GLUT_KEY_UP))
	{
		this->selectorPos = this->spriteSelector->getPosition();

		int posY = int(this->selectorPos.y);
		switch (posY)
		{
		case 235:
			this->selectorPos.y = 325.f;
			break;
		case 280:
			this->selectorPos.y = 235.f;
			break;
		case 325:
			this->selectorPos.y = 280.f;
			break;
		default:
			cout << "[SCENE::updateMenu] Wrong selector position: " << posY << endl;
			cin >> posY; // DEBUG
			exit(EXIT_FAILURE);
		}
		this->spriteSelector->setPosition(this->selectorPos);

		Game::instance().specialKeyReleased(GLUT_KEY_UP);
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
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
			this->selectorPos.y = 235.f;
			break;
		default:
			cout << "[SCENE::updateMenu] Wrong selector position: " << posY << endl;
			cin >> posY; // DEBUG
			exit(EXIT_FAILURE);
		}
		this->spriteSelector->setPosition(this->selectorPos);

		Game::instance().specialKeyReleased(GLUT_KEY_DOWN);
	}
	else if (Game::instance().getKey(KEY_RETURN))
	{
		this->selectorPos = this->spriteSelector->getPosition();

		int posY = int(this->selectorPos.y);
		switch (posY)
		{
		case 235:
			this->selectorPos.y = 235.f;
			this->state = PLAY;
			break;
		case 280:
			this->selectorPos.y = 280.f;
			this->state = CONT;
			break;
		case 325:
			this->selectorPos.y = 325.f;
			this->state = CRED;
			break;
		default:
			cout << "[SCENE::updateMenu] Wrong selector position: " << posY << endl;
			cin >> posY; // DEBUG
			exit(EXIT_FAILURE);
		}
		
		this->init();
	}
}

void Scene::updateControls(int deltaTime)
{
	this->spriteControls->update(deltaTime);

	if (Game::instance().getKey('B') || Game::instance().getKey('b'))
	{
		this->state = MENU;
		this->init();
	}
}

void Scene::updateCredits(int deltaTime)
{
	this->spriteCredits->update(deltaTime);

	if (Game::instance().getKey('B') || Game::instance().getKey('b'))
	{
		this->state = MENU;
		this->init();
	}
}

void Scene::updatePlay(int deltaTime)
{
	switch (this->level)
	{
	case LVL1:
		this->updateLevel1(deltaTime);
		break;
	case LVL2:
		this->updateLevel2(deltaTime);
		break;
	case LVL3:
		break;
	case LVL4:
		break;
	case LVL5:
		break;
	default:
		cout << "[SCENE::updatePlay] Wrong game level: " << this->level << endl;
		cin >> this->level; // DEBUG
		exit(EXIT_FAILURE);
	}
}

void Scene::updateLevel1(int deltaTime)
{
	this->player1->update(deltaTime);
}

void Scene::updateLevel2(int deltaTime)
{
	this->player2->update(deltaTime);
	this->spriteRock->update(deltaTime);
}


void Scene::render()
{
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	glm::mat4 modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	switch (this->state)
	{
	case MENU:
		this->renderMenu();
		break;
	case CONT:
		this->renderControls();
		break;
	case CRED:
		this->renderCredits();
		break;
	case PLAY:
		this->renderPlay();
		break;
	default:
		cout << "[SCENE::render] Wrong game state: " << this->state << endl;
		cin >> this->state; // DEBUG
		exit(EXIT_FAILURE);
	}
}

void Scene::renderMenu()
{
	this->spriteMenu->render();
	this->spriteSelector->render();
}

void Scene::renderControls()
{
	this->spriteControls->render();
}

void Scene::renderCredits()
{
	this->spriteCredits->render();
}

void Scene::renderPlay()
{
	switch (this->level)
	{
	case LVL1:
		this->renderLevel1();
		break;
	case LVL2:
		this->renderLevel2();
		break;
	case LVL3:
		break;
	case LVL4:
		break;
	case LVL5:
		break;
	default:
		cout << "[SCENE::renderPlay] Wrong game level: " << this->level << endl;
		cin >> this->level; // DEBUG
		exit(EXIT_FAILURE);
	}
}

void Scene::renderLevel1()
{
	this->map1->render();
	this->player1->render();
}

void Scene::renderLevel2()
{
	this->map2->render();
	this->player2->render();

	this->texProgram.setUniform4f("color", 1.0f, 0.5f, 0.0f, 1.0f);
	this->spriteRock->render();
}


void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}