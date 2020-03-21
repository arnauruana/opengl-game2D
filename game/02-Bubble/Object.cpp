#include "Object.h"


Object* Object::create()
{
	Object* object = new Object();
	return object;
}


Object::Behaviour Object::getBehaviour()
{
	return this->behaviour;
}

glm::ivec2 Object::getPosition()
{
	return this->sprite->getPosition();
}


void Object::setBehaviour(Object::Behaviour behaviour)
{
	this->behaviour = behaviour;
}

void Object::setPosition(const glm::vec2& position)
{
	this->sprite->setPosition(position);
}

void Object::setShader(const ShaderProgram& shader)
{
	this->shader = shader;
}

void Object::setType(Object::Type type)
{
	this->type = type;

	switch (this->type)
	{
		case Object::Type::FLAG:
		{
			this->path += Settings::IMG_FLAG;
			this->format = Settings::FORMAT_FLAG;
			this->behaviour = Object::Behaviour::WIN;
			this->color = glm::vec3(1.f, 1.f, 0.f);
			break;
		}
		case Object::Type::WALL:
		{
			this->path += Settings::IMG_FLOOR;
			this->format = Settings::FORMAT_FLOOR;
			this->behaviour = Object::Behaviour::STOP;
			this->color = glm::vec3(0.2f, 0.2f, 0.2f);
			break;
		}
		case Object::Type::ROCK:
		{
			this->path += Settings::IMG_ROCK;
			this->format = Settings::FORMAT_ROCK;
			this->behaviour = Object::Behaviour::PUSH;
			this->color = glm::vec3(0.7f, 0.5f, 0.2f);
			break;
		}
		default:
		{
			std::cout << "[OBJECT::setType] wrong object type" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
}


void Object::init()
{
	this->texture.loadFromFile(this->path, PixelFormat(this->format));
	
	this->sprite = Sprite::createSprite(glm::ivec2(24, 24), glm::vec2(1.f/3.f, 1.f), &this->texture, &this->shader);
	this->sprite->setNumberAnimations(1);
	this->sprite->setAnimationSpeed(0, 4);
	this->sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	this->sprite->addKeyframe(0, glm::vec2(1.f/3.f, 0.f));
	this->sprite->addKeyframe(0, glm::vec2(2.f/3.f, 0.f));
	this->sprite->changeAnimation(0);
}

void Object::update(int deltaTime)
{
	this->sprite->update(deltaTime);
}

void Object::render()
{
	this->shader.setUniform4f("color", this->color.x, this->color.y, this->color.z, 1.0f);
	this->sprite->render();
}


Object::Object()
{
	this->sprite = NULL;
}

Object::~Object()
{
	if (this->sprite != NULL) delete this->sprite;
}