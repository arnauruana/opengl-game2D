#include "Play.h"


Play::Play() {}

Play::~Play() {}


void Play::init()
{
	this->initShader();

	int level = Settings::level;
	switch (level)
	{
		case 1:
		{
			this->state = Play::State::LEVEL1;
			break;
		}
		case 2:
		{
			this->state = Play::State::LEVEL2;
			break;
		}
		case 3:
		{
			this->state = Play::State::LEVEL3;
			break;
		}
		case 4:
		{
			this->state = Play::State::LEVEL4;
			break;
		}
		case 5:
		{
			this->state = Play::State::LEVEL5;
			break;
		}
		default:
		{
			std::cerr << "[PLAY::init] wrong level number" << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	this->level.setShader(this->shader);
	switch (this->state)
	{
		case Play::State::LEVEL1:
		{
			this->level.setPath(Settings::PATH_LEVEL1);
			break;
		}
		case Play::State::LEVEL2:
		{
			this->level.setPath(Settings::PATH_LEVEL2);
			break;
		}
		case Play::State::LEVEL3:
		{
			this->level.setPath(Settings::PATH_LEVEL3);
			break;
		}
		case Play::State::LEVEL4:
		{
			this->level.setPath(Settings::PATH_LEVEL4);
			break;
		}
		case Play::State::LEVEL5:
		{
			this->level.setPath(Settings::PATH_LEVEL5);
			break;
		}
		default:
		{
			std::cout << "[PLAY::init] wrong play state" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	this->level.init();
}

void Play::update(int deltaTime)
{
	if (Settings::changeLevel)
	{
		this->init();
		Settings::changeLevel = false;
	}

	this->level.update(deltaTime);
}

void Play::render()
{
	glm::mat4 projection = glm::ortho(0.f, float(480 - 1), float(480 - 1), 0.f);
	this->shader.use();
	this->shader.setUniformMatrix4f("projection", projection);
	this->shader.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	glm::mat4 modelview = glm::mat4(1.0f);
	this->shader.setUniformMatrix4f("modelview", modelview);
	this->shader.setUniform2f("texCoordDispl", 0.f, 0.f);

	this->level.render();
}


void Play::initShader()
{
	Shader vShader;
	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		std::cout << "Vertex Shader Error" << std::endl;
		std::cout << "" << vShader.log() << std::endl << std::endl;
	}

	Shader fShader;
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		std::cout << "Fragment Shader Error" << std::endl;
		std::cout << "" << fShader.log() << std::endl << std::endl;
	}

	this->shader.init();
	this->shader.addShader(vShader);
	this->shader.addShader(fShader);
	this->shader.link();
	if (!this->shader.isLinked())
	{
		std::cout << "Shader Linking Error" << std::endl;
		std::cout << "" << this->shader.log() << std::endl << std::endl;
	}
	this->shader.bindFragmentOutput("outColor");

	vShader.free();
	fShader.free();
}