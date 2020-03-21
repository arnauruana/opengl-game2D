#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


enum PlayerAnims
{
	MOVE_FORWARD, MOVE_RIGHT, MOVE_LEFT, MOVE_BACKWARD
};


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	
	glm::ivec2 getPosition() const;
	int getAnimation() const;

	void setPosition(const glm::vec2 &pos);
	
private:

	glm::ivec2 tileMapDispl, posPlayer;

	Sprite* sprite;
	Texture spritesheet;
};


#endif // _PLAYER_INCLUDE


