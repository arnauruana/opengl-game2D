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


int Object::getAnimation() const
{
	return this->sprite->animation();
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
		case Object::Type::BABA:
		{
			this->path += Settings::IMG_BABA;
			this->format = Settings::FORMAT_BABA;
			this->behaviour = Object::Behaviour::NONE;
			this->color = glm::vec3(1.f, 1.f, 1.f);
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
	
	if (this->type == Object::Type::BABA)
	{
		this->sprite = Sprite::createSprite(glm::ivec2(24, 24), glm::vec2(0.20, 0.25), &this->texture, &this->shader);
		this->sprite->setNumberAnimations(4);

		this->sprite->setAnimationSpeed(Object::Animation::MOVE_BACKWARD, 8);
		this->sprite->addKeyframe(Object::Animation::MOVE_BACKWARD, glm::vec2(0.f, 0.25f));
		this->sprite->addKeyframe(Object::Animation::MOVE_BACKWARD, glm::vec2(0.2f, 0.25f));
		this->sprite->addKeyframe(Object::Animation::MOVE_BACKWARD, glm::vec2(0.4f, 0.25f));
		this->sprite->addKeyframe(Object::Animation::MOVE_BACKWARD, glm::vec2(0.6f, 0.25f));
		this->sprite->addKeyframe(Object::Animation::MOVE_BACKWARD, glm::vec2(0.8f, 0.25f));

		this->sprite->setAnimationSpeed(Object::Animation::MOVE_FORWARD, 8);
		this->sprite->addKeyframe(Object::Animation::MOVE_FORWARD, glm::vec2(0.f, 0.75f));
		this->sprite->addKeyframe(Object::Animation::MOVE_FORWARD, glm::vec2(0.2f, 0.75f));
		this->sprite->addKeyframe(Object::Animation::MOVE_FORWARD, glm::vec2(0.4f, 0.75f));
		this->sprite->addKeyframe(Object::Animation::MOVE_FORWARD, glm::vec2(0.6f, 0.75f));
		this->sprite->addKeyframe(Object::Animation::MOVE_FORWARD, glm::vec2(0.8f, 0.75f));

		this->sprite->setAnimationSpeed(Object::Animation::MOVE_LEFT, 8);
		this->sprite->addKeyframe(Object::Animation::MOVE_LEFT, glm::vec2(0.f, 0.5f));
		this->sprite->addKeyframe(Object::Animation::MOVE_LEFT, glm::vec2(0.2f, 0.5f));
		this->sprite->addKeyframe(Object::Animation::MOVE_LEFT, glm::vec2(0.4f, 0.5f));
		this->sprite->addKeyframe(Object::Animation::MOVE_LEFT, glm::vec2(0.6f, 0.5f));
		this->sprite->addKeyframe(Object::Animation::MOVE_LEFT, glm::vec2(0.8f, 0.5f));
		
		this->sprite->setAnimationSpeed(Object::Animation::MOVE_RIGHT, 8);
		this->sprite->addKeyframe(Object::Animation::MOVE_RIGHT, glm::vec2(0.f, 0.0f));
		this->sprite->addKeyframe(Object::Animation::MOVE_RIGHT, glm::vec2(0.2f, 0.0f));
		this->sprite->addKeyframe(Object::Animation::MOVE_RIGHT, glm::vec2(0.4f, 0.0f));
		this->sprite->addKeyframe(Object::Animation::MOVE_RIGHT, glm::vec2(0.6f, 0.0f));
		this->sprite->addKeyframe(Object::Animation::MOVE_RIGHT, glm::vec2(0.8f, 0.0f));

		this->sprite->changeAnimation(Object::Animation::MOVE_FORWARD);
	}
	else
	{
		this->sprite = Sprite::createSprite(glm::ivec2(24, 24), glm::vec2(1.f / 3.f, 1.f), &this->texture, &this->shader);
		this->sprite->setNumberAnimations(1);
		
		this->sprite->setAnimationSpeed(0, 5);
		this->sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
		this->sprite->addKeyframe(0, glm::vec2(1.f / 3.f, 0.f));
		this->sprite->addKeyframe(0, glm::vec2(2.f / 3.f, 0.f));
		
		this->sprite->changeAnimation(0);
	}
}

void Object::update(int deltaTime)
{
	if (this->dead) return;

	this->sprite->update(deltaTime);

	if (this->behaviour == Object::Behaviour::YOU)
	{
		glm::vec2 pos = this->sprite->getPosition();

		if (keyboard::skey[GLUT_KEY_LEFT])
		{
			this->direction = Object::Direction::LEFT;

			if (this->sprite->animation() != MOVE_LEFT)
			{
				this->sprite->changeAnimation(MOVE_LEFT);
			}

			if (pos.x == 0) return; // not leave the map

			pos.x -= 24;
			this->sprite->setPosition(pos);

			keyboard::skey[GLUT_KEY_LEFT] = false;

			Sounds::instance().playSoundEffect("MOVE");
		}
		else if (keyboard::skey[GLUT_KEY_RIGHT])
		{
			this->direction = Object::Direction::RIGHT;

			if (this->sprite->animation() != MOVE_RIGHT)
			{
				this->sprite->changeAnimation(MOVE_RIGHT);
			}

			if (pos.x == 480 - 24) return; // not leave the map

			pos.x += 24;
			this->sprite->setPosition(pos);

			keyboard::skey[GLUT_KEY_RIGHT] = false;

			Sounds::instance().playSoundEffect("MOVE");
		}
		else if (keyboard::skey[GLUT_KEY_UP])
		{
			this->direction = Object::Direction::BACKWARD;

			if (this->sprite->animation() != MOVE_BACKWARD)
			{
				this->sprite->changeAnimation(MOVE_BACKWARD);
			}

			if (pos.y == 0) return; // not leave the map

			pos.y -= 24;
			this->sprite->setPosition(pos);

			keyboard::skey[GLUT_KEY_UP] = false;

			Sounds::instance().playSoundEffect("MOVE");
		}
		else if (keyboard::skey[GLUT_KEY_DOWN])
		{
			this->direction = Object::Direction::FORWARD;

			if (this->sprite->animation() != MOVE_FORWARD)
			{
				this->sprite->changeAnimation(MOVE_FORWARD);
			}

			if (pos.y == 480 - 24) return; // not leave the map

			pos.y += 24;
			this->sprite->setPosition(pos);

			keyboard::skey[GLUT_KEY_DOWN] = false;

			Sounds::instance().playSoundEffect("MOVE");
		}
	}
}

void Object::render()
{
	if (this->dead) return;

	this->shader.setUniform4f("color", this->color.x, this->color.y, this->color.z, 1.0f);
	this->sprite->render();
}