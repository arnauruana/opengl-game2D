#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	scene.init();
}

bool Game::update(int deltaTime)
{
	scene.update(deltaTime);
	
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene.render();
}

void Game::keyPressed(int key)
{
	keys[key] = true;

	if(key == 27) // Escape code
		bPlay = false;

	// TEMPORARILY
	if (key == '0') this->scene.setState(MENU);
	if (key == '1') this->scene.setLevel(LVL1);
	if (key == '2') this->scene.setLevel(LVL2);
	if (key == '3') this->scene.setLevel(LVL3);
	if (key == '4') this->scene.setLevel(LVL4);
	if (key == '5') this->scene.setLevel(LVL5);
	// TEMPORARILY
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}