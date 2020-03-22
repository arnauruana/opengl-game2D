#include "Play.h"


Play::Play() {}

Play::~Play() {}


void Play::setShader(const ShaderProgram& shader)
{
	this->shader = shader;
}


void Play::init()
{
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