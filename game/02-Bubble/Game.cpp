#include "Game.h"


Game::Game() {}

Game::~Game() {}


void Game::init()
{
	glClearColor(0.165f, 0.14f, 0.14f, 1.0f);

	this->exit = false;
	this->windowF = false;

	this->scene.init();
}

bool Game::update(int deltaTime)
{
	this->scene.update(deltaTime);
	
	return !this->exit;
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
		glutReshapeWindow(Settings::GAME_WINDOW_WIDTH, Settings::GAME_WINDOW_HEIGHT);
	}
}


void Game::keyPressed(int key)
{
	keyboard::key[key] = true;

	switch (key)
	{
		case KEY_SCAPE:
		{
			this->exit = true;
			break;
		}
	}
}

void Game::keyReleased(int key)
{
	keyboard::key[key] = false;
}

void Game::specialKeyPressed(int key)
{
	keyboard::skey[key] = true;

	switch (key)
	{
		case GLUT_KEY_F11:
		{
			this->toggleFullScreen();
		}
	}
}

void Game::specialKeyReleased(int key)
{
	keyboard::skey[key] = false;
}


inline void Game::toggleFullScreen()
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

inline void Game::enableFullScreen()
{
	this->saveWindowContext();
	this->windowF = true;

	glutFullScreen();
}

inline void Game::disableFullScreen()
{
	this->restoreWindowContext();
	this->windowF = false;
}

inline void Game::saveWindowContext()
{
	this->windowX = glutGet(GLUT_WINDOW_X) - TILE_BAR_WIDTH;
	this->windowY = glutGet(GLUT_WINDOW_Y) - TILE_BAR_HEIGHT;

	this->windowW = glutGet(GLUT_WINDOW_WIDTH);
	this->windowH = glutGet(GLUT_WINDOW_HEIGHT);
}

inline void Game::restoreWindowContext() const
{
	glutPositionWindow(this->windowX, this->windowY);
	glutReshapeWindow(this->windowW, this->windowH);
}