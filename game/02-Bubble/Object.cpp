#include "Object.h"


Object::Object()
{
	this->sprite = NULL;
}

Object::~Object()
{
	if (this->sprite != NULL) delete this->sprite;
}


Object* Object::create()
{
	Object* object = new Object();
	return object;
}


Object::Behaviour Object::getBehaviour() const
{
	return this->behaviour;
}

Object::Direction Object::getDirection() const
{
	return this->direction;
}

Object::Type Object::getType() const
{
	return this->type;
}

glm::ivec2 Object::getPosition() const
{
	return this->sprite->getPosition();
}


void Object::setBehaviour(Object::Behaviour behaviour)
{
	this->behaviour = behaviour;
}

void Object::setDirection(Object::Direction direction)
{
	this->direction = direction;
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
	this->path = Settings::PATH_OBJECTS;

	this->type = type;

	switch (this->type)
	{
		case Object::Type::NONE:
		{
			this->behaviour = Object::Behaviour::NONE;
			break;
		}
		case Object::Type::FLAG:
		{
			this->path += Settings::IMG_FLAG;
			this->format = Settings::FORMAT_FLAG;
			this->behaviour = Object::Behaviour::NONE;
			this->color = glm::vec3(1.f, 1.f, 0.f);
			break;
		}
		case Object::Type::LAVA:
		{
			this->path += Settings::IMG_LAVA;
			this->format = Settings::FORMAT_LAVA;
			this->behaviour = Object::Behaviour::NONE;
			this->color = glm::vec3(1.0f, 0.f, 0.f);
			break;
		}
		case Object::Type::WALL:
		{
			this->path += Settings::IMG_WALL;
			this->format = Settings::FORMAT_FLOOR;
			this->behaviour = Object::Behaviour::NONE;
			this->color = glm::vec3(0.4f, 0.4f, 0.4f);
			break;
		}
		case Object::Type::ROCK:
		{
			this->path += Settings::IMG_ROCK;
			this->format = Settings::FORMAT_ROCK;
			this->behaviour = Object::Behaviour::NONE;
			this->color = glm::vec3(0.7f, 0.5f, 0.2f);
			break;
		}
		case Object::Type::TXT_BABA:
		{
			this->path += Settings::TXT_BABA;
			this->format = Settings::FORMAT_TXTBABA;
			this->behaviour = Object::Behaviour::PRE;
			this->color = glm::vec3(1.0f, 1.0f, 1.0f);
			break;
		}
		case Object::Type::TXT_ROCK:
		{
			this->path += Settings::TXT_ROCK;
			this->format = Settings::FORMAT_TXTROCK;
			this->behaviour = Object::Behaviour::PRE;
			this->color = glm::vec3(0.7f, 0.5f, 0.2f);
			break;
		}
		case Object::Type::TXT_WALL:
		{
			this->path += Settings::TXT_WALL;
			this->format = Settings::FORMAT_TXTWALL;
			this->behaviour = Object::Behaviour::PRE;
			this->color = glm::vec3(0.4f, 0.4f, 0.4f);
			break;
		}
		case Object::Type::TXT_FLAG:
		{
			this->path += Settings::TXT_FLAG;
			this->format = Settings::FORMAT_TXTFLAG;
			this->behaviour = Object::Behaviour::PRE;
			this->color = glm::vec3(1.f, 1.f, 0.f);
			break;
		}
		case Object::Type::TXT_IS:
		{
			this->path += Settings::TXT_IS;
			this->format = Settings::FORMAT_TXTIS;
			this->behaviour = Object::Behaviour::OP;
			this->color = glm::vec3(1.0f, 0.0f, 1.0f);
			break;
		}
		case Object::Type::TXT_YOU:
		{
			this->path += Settings::TXT_YOU;
			this->format = Settings::FORMAT_TXTYOU;
			this->behaviour = Object::Behaviour::POST;
			this->color = glm::vec3(1.0f, 1.0f, 1.0f);
			break;
		}
		case Object::Type::TXT_STOP:
		{
			this->path += Settings::TXT_STOP;
			this->format = Settings::FORMAT_TXTSTOP;
			this->behaviour = Object::Behaviour::POST;
			this->color = glm::vec3(0.4f, 0.4f, 0.4f);
			break;
		}
		case Object::Type::TXT_PUSH:
		{
			this->path += Settings::TXT_PUSH;
			this->format = Settings::FORMAT_TXTPUSH;
			this->behaviour = Object::Behaviour::POST;
			this->color = glm::vec3(0.7f, 0.5f, 0.2f);
			break;
		}
		case Object::Type::TXT_WIN:
		{
			this->path += Settings::TXT_WIN;
			this->format = Settings::FORMAT_TXTWIN;
			this->behaviour = Object::Behaviour::POST;
			this->color = glm::vec3(1.f, 1.f, 0.f);
			break;
		}
		case Object::Type::TXT_LAVA:
		{
			this->path += Settings::TXT_LAVA;
			this->format = Settings::FORMAT_TXTLAVA;
			this->behaviour = Object::Behaviour::PRE;
			this->color = glm::vec3(1.f, 0.f, 0.f);
			break;
		}
		case Object::Type::TXT_DEFEAT:
		{
			this->path += Settings::TXT_DEFEAT;
			this->format = Settings::FORMAT_TXTDEFEAT;
			this->behaviour = Object::Behaviour::POST;
			this->color = glm::vec3(1.f, 0.f, 0.f);
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

	this->sprite = Sprite::createSprite(glm::ivec2(24, 24), glm::vec2(1.f / 3.f, 1.f), &this->texture, &this->shader);
	this->sprite->setNumberAnimations(1);
	this->sprite->setAnimationSpeed(0, 4);
	this->sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	this->sprite->addKeyframe(0, glm::vec2(1.f / 3.f, 0.f));
	this->sprite->addKeyframe(0, glm::vec2(2.f / 3.f, 0.f));
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