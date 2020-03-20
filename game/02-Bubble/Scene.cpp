#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Scene.h"
#include "Game.h"


#define SCREEN_X 0
#define SCREEN_Y 0

#define MOVE_FORWARD 0;
#define MOVE_RIGHT 1;
#define MOVE_LEFT 2;
#define MOVE_BACKWARD 3;


Scene::Scene()
{
	this->level1 = NULL;
	this->level2 = NULL;
	this->level3 = NULL;
	this->level4 = NULL;
	this->level5 = NULL;

	this->player1 = NULL;
	this->player2 = NULL;
	this->player3 = NULL;
	this->player4 = NULL;
	this->player5 = NULL;

	this->spriteRock = NULL;
	this->spriteWall = NULL;
}

Scene::~Scene()
{
	if (this->level1 != NULL) delete this->level1;
	if (this->level2 != NULL) delete this->level2;
	if (this->level3 != NULL) delete this->level3;
	if (this->level4 != NULL) delete this->level4;
	if (this->level5 != NULL) delete this->level5;

	if (this->player1 != NULL) delete this->player1;
	if (this->player2 != NULL) delete this->player2;
	if (this->player3 != NULL) delete this->player3;
	if (this->player4 != NULL) delete this->player4;
	if (this->player5 != NULL) delete this->player5;

	if (this->spriteRock != NULL) delete this->spriteRock;
	if (this->spriteWall != NULL) delete this->spriteWall;
}


int Scene::getState() const
{
	return this->state;
}

int Scene::getLevel() const
{
	return this->level;
}


void Scene::setState(Scene::State state)
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

	this->menu.setShader(this->texProgram);

	switch (this->state)
	{
		case this->State::MENU:
		{
			this->menu.init();
			break;
		}
		case this->State::PLAY:
		{
			this->initPlay();
			break;
		}
		default:
		{
			std::cout << "[SCENE::init] Wrong game state: " << this->state << std::endl;
			exit(EXIT_FAILURE);
		}
	}
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
		std::cout << "[SCENE::initPlay] Wrong game level: " << this->level << std::endl;
		cin >> this->level; // DEBUG
		exit(EXIT_FAILURE);
	}
}

void Scene::initLevel1()
{
	this->level1 = TileMap::createTileMap(PATH_LVL1, glm::vec2(SCREEN_X, SCREEN_Y), this->texProgram);
	
	this->player1 = new Player();
	this->player1->init(glm::ivec2(SCREEN_X, SCREEN_Y), this->texProgram);
	this->player1->setTileMap(this->level1);
	this->player1->setPosition(glm::vec2(1 * this->level1->getTileSize(), 1 * this->level1->getTileSize()));

	this->currentTime = 0.0f;
}

void Scene::initLevel2()
{
	this->level2 = TileMap::createTileMap(PATH_LVL2, glm::vec2(SCREEN_X, SCREEN_Y), this->texProgram);

	this->spritesheetRock.loadFromFile("images/rock.png", TEXTURE_PIXEL_FORMAT_RGBA);
	this->spriteRock = Sprite::createSprite(glm::ivec2(24, 24), glm::vec2(1.f, 1.f), &this->spritesheetRock, &this->texProgram);
	this->spriteRock->setNumberAnimations(0);
	this->spriteRock->setPosition(glm::vec2(9 * this->level2->getTileSize(), 10 * this->level2->getTileSize()));

	this->spritesheetWall.loadFromFile("images/tiles.png", TEXTURE_PIXEL_FORMAT_RGBA);
	this->spriteWall = Sprite::createSprite(glm::ivec2(24, 24), glm::vec2(2.f / 32.f, 2.f / 66.f), &this->spritesheetWall, &this->texProgram);
	this->spriteWall->setNumberAnimations(0);
	this->spriteWall->setPosition(glm::vec2(5 * this->level2->getTileSize(), 5 * this->level2->getTileSize()));

	this->player2 = new Player();
	this->player2->init(glm::ivec2(SCREEN_X, SCREEN_Y), this->texProgram);
	this->player2->setTileMap(this->level2);
	this->player2->setPosition(glm::vec2(1 * this->level2->getTileSize(), 1 * this->level2->getTileSize()));

	this->rock.setMap(this->level2);
	this->rock.setShader(this->texProgram);
	this->rock.setType(Object::Type::FLAG);
	this->rock.init();

	this->currentTime = 0.0f;
}


void Scene::update(int deltaTime)
{
	if (Settings::playing && this->state != this->State::PLAY)
	{
		this->state = this->State::PLAY;
		this->init();
	}

	this->currentTime += deltaTime;

	switch (this->state)
	{
	case MENU:
		this->menu.update(deltaTime);
		break;
	case PLAY:
		this->updatePlay(deltaTime);
		break;
	default:
		std::cout << "[SCENE::update] Wrong game state: " << this->state << std::endl;
		exit(EXIT_FAILURE);
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
		std::cout << "[SCENE::updatePlay] Wrong game level: " << this->level << std::endl;
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
	glm::ivec2 posPlayer = this->player2->getPosition();
	glm::ivec2 posRock = this->spriteRock->getPosition();

	this->player2->update(deltaTime);
	this->spriteRock->update(deltaTime);
	this->spriteWall->update(deltaTime);

	if (this->checkCollisionStop()) // caso wall
	{
		this->player2->setPosition(posPlayer);
	}

	if (this->checkCollisionMove()) // caso piedra
	{
		int orientation = this->player2->getAnimation();

		switch (orientation)
		{
		case 0: // FORWARD
			this->spriteRock->setPosition(glm::ivec2(posRock.x, posRock.y + 24));
			break;
		case 1: // RIGHT
			this->spriteRock->setPosition(glm::ivec2(posRock.x + 24, posRock.y));
			break;
		case 2: // LEFT
			this->spriteRock->setPosition(glm::ivec2(posRock.x - 24, posRock.y));
			break;
		case 3: // BACKWARD
			this->spriteRock->setPosition(glm::ivec2(posRock.x, posRock.y - 24));
			break;
		default:
			exit(EXIT_FAILURE);
		}
	}

	posRock = this->rock.getPosition();

	this->rock.update(deltaTime);

	if (posPlayer.x == posRock.x && posPlayer.y == posRock.y)
	{
		if (this->rock.getBehaviour() == Object::Behaviour::PUSH)
		{
			int orientation = this->player2->getAnimation();

			switch (orientation)
			{
			case 0: // FORWARD
				this->rock.setPosition(glm::ivec2(posRock.x, posRock.y + 24));
				break;
			case 1: // RIGHT
				this->rock.setPosition(glm::ivec2(posRock.x + 24, posRock.y));
				break;
			case 2: // LEFT
				this->rock.setPosition(glm::ivec2(posRock.x - 24, posRock.y));
				break;
			case 3: // BACKWARD
				this->rock.setPosition(glm::ivec2(posRock.x, posRock.y - 24));
				break;
			default:
				exit(EXIT_FAILURE);
			}
		}

		if (this->rock.getBehaviour() == Object::Behaviour::WIN)
		{
			Settings::playing = false;
			this->state = MENU;
			this->init();
		}
	}
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
		this->menu.render();
		break;
	case PLAY:
		this->renderPlay();
		break;
	default:
		std::cout << "[SCENE::render] Wrong game state: " << this->state << std::endl;
		exit(EXIT_FAILURE);
	}
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
		std::cout << "[SCENE::renderPlay] Wrong game level: " << this->level << std::endl;
		cin >> this->level; // DEBUG
		exit(EXIT_FAILURE);
	}
}

void Scene::renderLevel1()
{
	this->level1->render();
	this->player1->render();
}

void Scene::renderLevel2()
{
	this->level2->render();

	this->texProgram.setUniform4f("color", 0.2f, 0.2f, 0.2f, 1.0f); // grey => wall
	this->spriteWall->render();

	this->texProgram.setUniform4f("color", 0.7f, 0.5f, 0.2f, 1.0f); // brown => rock
	this->spriteRock->render();

	this->texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f); // white => baba
	this->player2->render();

	this->rock.render();
}


void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		std::cout << "Vertex Shader Error" << std::endl;
		std::cout << "" << vShader.log() << std::endl << std::endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		std::cout << "Fragment Shader Error" << std::endl;
		std::cout << "" << fShader.log() << std::endl << std::endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		std::cout << "Shader Linking Error" << std::endl;
		std::cout << "" << texProgram.log() << std::endl << std::endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

bool Scene::checkCollisionStop() const
{
	glm::ivec2 posPlayer = this->player2->getPosition();
	glm::ivec2 posWall = this->spriteWall->getPosition();

	if (posPlayer.x == posWall.x && posPlayer.y == posWall.y)
	{
		return true;
	}

	return false;
}

bool Scene::checkCollisionMove() const
{
	glm::ivec2 posPlayer = this->player2->getPosition();
	glm::ivec2 posRock = this->spriteRock->getPosition();

	if (posPlayer.x == posRock.x && posPlayer.y == posRock.y)
	{
		return true;
	}

	return false;
}