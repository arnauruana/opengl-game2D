#include "Play.h"


Play::Play() {}

Play::~Play() {}


void Play::init()
{
	this->initShader();

	this->state = Play::State::LEVEL1;

	switch (this->state)
	{
		case Play::State::LEVEL1:
		{
			this->level1.setShader(this->shader);
			this->level1.init();
			break;
		}
		case Play::State::LEVEL2:
		{
			this->level2.setShader(this->shader);
			this->level2.init();
			break;
		}
		case Play::State::LEVEL3:
		{
			this->level3.setShader(this->shader);
			this->level3.init();
			break;
		}
		case Play::State::LEVEL4:
		{
			this->level4.setShader(this->shader);
			this->level4.init();
			break;
		}
		case Play::State::LEVEL5:
		{
			this->level5.setShader(this->shader);
			this->level5.init();
			break;
		}
		default:
		{
			std::cout << "[PLAY::init] wrong play state" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
}

void Play::update(int deltaTime)
{
	switch (this->state)
	{
		case Play::State::LEVEL1:
		{
			this->level1.update(deltaTime);
			break;
		}
		case Play::State::LEVEL2:
		{
			this->level2.update(deltaTime);
			break;
		}
		case Play::State::LEVEL3:
		{
			this->level3.update(deltaTime);
			break;
		}
		case Play::State::LEVEL4:
		{
			this->level4.update(deltaTime);
			break;
		}
		case Play::State::LEVEL5:
		{
			this->level5.update(deltaTime);
			break;
		}
		default:
		{
			std::cout << "[PLAY::update] wrong play state" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
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

	switch (this->state)
	{
		case Play::State::LEVEL1:
		{
			this->level1.render();
			break;
		}
		case Play::State::LEVEL2:
		{
			this->level2.render();
			break;
		}
		case Play::State::LEVEL3:
		{
			this->level3.render();
			break;
		}
		case Play::State::LEVEL4:
		{
			this->level4.render();
			break;
		}
		case Play::State::LEVEL5:
		{
			this->level5.render();
			break;
		}
		default:
		{
			std::cout << "[PLAY::render] wrong play state" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
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