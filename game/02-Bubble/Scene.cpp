#include "Scene.h"


Scene::Scene()
{
	this->player1 = NULL;
	this->player2 = NULL;
}

Scene::~Scene()
{
	if (this->player1 != NULL) delete this->player1;
	if (this->player2 != NULL) delete this->player2;
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

	this->projection = glm::ortho(0.f, float(480 - 1), float(480 - 1), 0.f);

	this->menu.setShader(this->texProgram);

	switch (this->state)
	{
		case Scene::State::MENU:
		{
			this->menu.init();
			break;
		}
		case Scene::State::PLAY:
		{
			this->initPlay();
			break;
		}
		default:
		{
			std::cout << "[SCENE::init] Wrong game state: " << std::endl;
			exit(EXIT_FAILURE);
		}
	}
}

void Scene::initPlay()
{
	switch (this->level)
	{
	case LVL1:
	case LVL2:
	case LVL3:
	case LVL4:
	case LVL5:
		this->initLevel2();
		break;
	default:
		std::cout << "[SCENE::initPlay] Wrong game level: " << this->level << std::endl;
		cin >> this->level; // DEBUG
		exit(EXIT_FAILURE);
	}
}

void Scene::initLevel2()
{
	this->map.setShader(this->texProgram);
	this->map.init();

	this->currentTime = 0.0f;
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
		this->menu.update(deltaTime);
		break;
	case Scene::State::PLAY:
		this->updatePlay(deltaTime);
		break;
	default:
		std::cout << "[SCENE::update] Wrong game state: " << std::endl;
		exit(EXIT_FAILURE);
	}
}

void Scene::updatePlay(int deltaTime)
{
	switch (this->level)
	{
	case LVL1:
	case LVL2:
	case LVL3:
	case LVL4:
	case LVL5:
		this->updateLevel2(deltaTime);
		break;
	default:
		std::cout << "[SCENE::updatePlay] Wrong game level: " << this->level << std::endl;
		cin >> this->level; // DEBUG
		exit(EXIT_FAILURE);
	}
}

void Scene::updateLevel2(int deltaTime)
{
	map.update(deltaTime);
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
	case Scene::State::MENU:
		this->menu.render();
		break;
	case Scene::State::PLAY:
		this->renderPlay();
		break;
	default:
		std::cout << "[SCENE::render] Wrong game state: " << std::endl;
		exit(EXIT_FAILURE);
	}
}

void Scene::renderPlay()
{
	switch (this->level)
	{
	case LVL1:
	case LVL2:
	case LVL3:
	case LVL4:
	case LVL5:
		this->renderLevel2();
		break;
	default:
		std::cout << "[SCENE::renderPlay] Wrong game level: " << this->level << std::endl;
		exit(EXIT_FAILURE);
	}
}

void Scene::renderLevel2()
{
	this->map.render();
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