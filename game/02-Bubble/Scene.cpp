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
	this->initShaders();

	this->projection = glm::ortho(0.f, float(480 - 1), float(480 - 1), 0.f);

	switch (this->state)
	{
		case Scene::State::MENU:
		{
			this->menu.setShader(this->texProgram);
			this->menu.init();
			break;
		}
		case Scene::State::PLAY:
		{
			this->play.setShader(this->texProgram);
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
		this->play.render();
		//this->renderPlay();
		break;
	default:
		std::cout << "[SCENE::render] Wrong game state: " << std::endl;
		exit(EXIT_FAILURE);
	}
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