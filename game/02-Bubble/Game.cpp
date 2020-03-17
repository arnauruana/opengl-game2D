#include "Game.h"

#include <GL/glew.h>
#include <GL/glut.h>


#define TILE_BAR_WIDTH 8
#define TILE_BAR_HEIGHT 31


Game::Game() {}

Game::~Game() {}


void Game::init()
{
	this->playing = true;
	this->windowF = false;

	this->scene.init();
}

bool Game::update(int deltaTime)
{
	this->scene.update(deltaTime);
	
	return this->playing;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	this->scene.render();
	glutSwapBuffers();
}

void Game::resize(int width, int height)
{
	if (this->windowF)
	{
		int max = width > height ? width : height;
		int min = width < height ? width : height;

		glViewport((max - min) / 2, 0, (GLsizei)min, (GLsizei)min);
	}
	else
	{
		glViewport(0, 0, (GLsizei)width, (GLsizei)height);
		glutReshapeWindow(Game::GAME_WINDOW_WIDTH, Game::GAME_WINDOW_HEIGHT);
	}
}


bool Game::getKey(int key) const
{
	return this->key[key];
}

bool Game::getSpecialKey(int key) const
{
	return this->skey[key];
}


void Game::keyPressed(int key)
{
	this->key[key] = true;

	if(key == 27) // Escape code
		this->playing = false;

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
	this->key[key] = false;
}

void Game::specialKeyPressed(int key)
{
	this->skey[key] = true;

	if (key == GLUT_KEY_F11) this->toggleFullScreen();
}

void Game::specialKeyReleased(int key)
{
	this->skey[key] = false;
}


void Game::mousePressed(int button)
{
}

void Game::mouseReleased(int button)
{
}

void Game::mouseMoved(int x, int y)
{
}


void Game::toggleFullScreen()
{
	if (!this->windowF)
	{
		this->enableFullScreen();
	}
	else
	{
		this->disableFullScreen();
	}
}

void Game::enableFullScreen()
{
	this->saveWindowContext();
	this->windowF = true;

	glutFullScreen();
}

void Game::disableFullScreen()
{
	this->restoreWindowContext();
	this->windowF = false;
}

void Game::saveWindowContext()
{
	this->windowX = glutGet(GLUT_WINDOW_X) - TILE_BAR_WIDTH;
	this->windowY = glutGet(GLUT_WINDOW_Y) - TILE_BAR_HEIGHT;

	this->windowW = glutGet(GLUT_WINDOW_WIDTH);
	this->windowH = glutGet(GLUT_WINDOW_HEIGHT);
}

void Game::restoreWindowContext()
{
	glutPositionWindow(this->windowX, this->windowY);
	glutReshapeWindow(this->windowW, this->windowH);
}