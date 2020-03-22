#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/glut.h>

#include "Player.h"
#include "Game.h"


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheet.loadFromFile("images/baba.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(24, 24), glm::vec2(0.20, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);
	
		sprite->setAnimationSpeed(MOVE_BACKWARD, 8);
		sprite->addKeyframe(MOVE_BACKWARD, glm::vec2(0.f, 0.25f));
		sprite->addKeyframe(MOVE_BACKWARD, glm::vec2(0.2f, 0.25f));
		sprite->addKeyframe(MOVE_BACKWARD, glm::vec2(0.4f, 0.25f));
		sprite->addKeyframe(MOVE_BACKWARD, glm::vec2(0.6f, 0.25f));
		sprite->addKeyframe(MOVE_BACKWARD, glm::vec2(0.8f, 0.25f));

		sprite->setAnimationSpeed(MOVE_FORWARD, 8);
		sprite->addKeyframe(MOVE_FORWARD, glm::vec2(0.f, 0.75f));
		sprite->addKeyframe(MOVE_FORWARD, glm::vec2(0.2f, 0.75f));
		sprite->addKeyframe(MOVE_FORWARD, glm::vec2(0.4f, 0.75f));
		sprite->addKeyframe(MOVE_FORWARD, glm::vec2(0.6f, 0.75f));
		sprite->addKeyframe(MOVE_FORWARD, glm::vec2(0.8f, 0.75f));

		
		sprite->setAnimationSpeed(MOVE_LEFT, 8);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.2f, 0.5f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.4f, 0.5f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.6f, 0.5f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.8f, 0.5f));
		
		sprite->setAnimationSpeed(MOVE_RIGHT, 8);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.2f, 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.4f, 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.6f, 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.8f, 0.f));
		
		
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::update(int deltaTime)
{
	this->sprite->update(deltaTime);

	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if (this->sprite->animation() != MOVE_LEFT)
		{
			this->sprite->changeAnimation(MOVE_LEFT);
		}

		if (this->posPlayer.x == 0) return; // not leave the map

		this->posPlayer.x -= 24;


		Game::instance().specialKeyReleased(GLUT_KEY_LEFT);
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if (this->sprite->animation() != MOVE_RIGHT)
		{
			this->sprite->changeAnimation(MOVE_RIGHT);
		}
		
		if (this->posPlayer.x == 480 - 24) return; // not leave the map

		this->posPlayer.x += 24;

		Game::instance().specialKeyReleased(GLUT_KEY_RIGHT);
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_UP))
	{
		if (this->sprite->animation() != MOVE_BACKWARD)
		{
			this->sprite->changeAnimation(MOVE_BACKWARD);
		}

		if (this->posPlayer.y == 0) return; // not leave the map
		
		this->posPlayer.y -= 24;
		
		Game::instance().specialKeyReleased(GLUT_KEY_UP);
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
	{
		if (this->sprite->animation() != MOVE_FORWARD)
		{
			this->sprite->changeAnimation(MOVE_FORWARD);
		}

		if (this->posPlayer.y == 480 - 24) return; // not leave the map
		
		this->posPlayer.y += 24;
		
		Game::instance().specialKeyReleased(GLUT_KEY_DOWN);
	}
	
	this->sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	this->sprite->render();
}


int Player::getAnimation() const
{
	return this->sprite->animation();
}

glm::ivec2 Player::getPosition() const
{
	return this->posPlayer;
}


void Player::setPosition(const glm::vec2 &pos)
{
	this->posPlayer = pos;
	this->sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}