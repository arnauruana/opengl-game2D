#include "Object.h"


Object::Object()
{
	this->sprite = NULL;
}

Object::~Object()
{
	if (this->sprite != NULL) delete this->sprite;
}


void Object::setType(Object::Type type)
{
	this->type = type;
}

void Object::setMap(TileMap* map)
{
	this->map = map;
}

void Object::setShader(const ShaderProgram& shader)
{
	this->shader = shader;
}


void Object::init()
{
	if (this->type != Object::Type::ROCK) return;

	this->texture.loadFromFile("images/rock.png", TEXTURE_PIXEL_FORMAT_RGBA);
	this->sprite = Sprite::createSprite(glm::ivec2(24, 24), glm::vec2(1.f, 1.f), &this->texture, &this->shader);
	this->sprite->setNumberAnimations(0);
	this->sprite->setPosition(glm::vec2(2 * this->map->getTileSize(), 2 * this->map->getTileSize()));
}

void Object::update(int deltaTime)
{
	this->sprite->update(deltaTime);
}

void Object::render()
{
	this->sprite->render();
}