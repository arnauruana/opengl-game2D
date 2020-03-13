#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

#include "Scene.h"
#include "Game.h"

#include <GL/glew.h>
#include <GL/glut.h>


#define KEY_RETURN 13

#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 25


Scene::Scene()
{
	this->map = NULL;
	this->player = NULL;
}

Scene::~Scene()
{
	if (this->map != NULL)
	{
		delete this->map;
	}

	if (this->player != NULL)
	{
		delete this->player;
	}
}


void Scene::init()
{
	this->initShaders();

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
	this->projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

	// background
	this->spritesheetMenu.loadFromFile("images/menu.jpg", TEXTURE_PIXEL_FORMAT_RGB);
	this->spriteMenu = Sprite::createSprite(glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(1.f, 1.f), &this->spritesheetMenu, &this->texProgram);
	this->spriteMenu->setNumberAnimations(0);
	this->spriteMenu->setPosition(glm::vec2(0.f, 0.f));

	// selector
	this->spritesheetSelector.loadFromFile("images/selector.jpg", TEXTURE_PIXEL_FORMAT_RGBA);
	this->spriteSelector = Sprite::createSprite(glm::ivec2(SCREEN_WIDTH/3 - 30, 36), glm::vec2(1.f, 1.f), &this->spritesheetSelector, &this->texProgram);
	this->spriteSelector->setNumberAnimations(0);
	this->spriteSelector->setPosition(this->selectorPos);
}

void Scene::initControls()
{
	this->projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

	// background
	this->spritesheetControls.loadFromFile("images/controls.jpg", TEXTURE_PIXEL_FORMAT_RGB);
	this->spriteControls = Sprite::createSprite(glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(1.f, 1.f), &this->spritesheetControls, &this->texProgram);
	this->spriteControls->setNumberAnimations(0);
	this->spriteControls->setPosition(glm::vec2(0.f, 0.f));
}

void Scene::initCredits()
{
	this->projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

	// background
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
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
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
	player->update(deltaTime);
}


void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	if (state == MENU) {
		spriteMenu->render();
		spriteSelector->render();
	}
	else if (state == CRED) {
		spriteCredits->render();
	}
	else if (state == CONT) {
		spriteControls->render();
	}
	else // state == playing
	{
		map->render();
		player->render();
	}
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