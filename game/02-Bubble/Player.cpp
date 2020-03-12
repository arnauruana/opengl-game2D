#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	MOVE_FORWARD, MOVE_RIGHT, MOVE_LEFT, MOVE_BACKWARD
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	spritesheet.loadFromFile("images/baba.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.20, 0.25), &spritesheet, &shaderProgram);
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
	sprite->update(deltaTime);
	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if(sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posPlayer.x -= 2;
		
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posPlayer.x += 2;
		
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_UP))
	{
		if (sprite->animation() != MOVE_BACKWARD)
			sprite->changeAnimation(MOVE_BACKWARD);
		posPlayer.y -= 2;
		
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
	{
		if (sprite->animation() != MOVE_FORWARD)
			sprite->changeAnimation(MOVE_FORWARD);
		posPlayer.y += 2;
		
	}
	
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}


void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}




