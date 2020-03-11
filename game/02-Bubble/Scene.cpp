#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include <GL/glew.h>
#include <GL/glut.h>


#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 25


Scene::Scene()
{
	map = NULL;
	player = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
}


void Scene::init()
{
	initShaders();

	if (state == "menu") {
		initMenu();
	}
	else if (state == "controls") { /* loadControls(); */
		initControls();
	}
	else if (state == "credits") { /* loadCredits(); */
		initCredits();
	}
	else { // state == playing
		if (current_lvl == 1)	   init_Lvl1();
		else if (current_lvl == 2) init_Lvl2();
		else if (current_lvl == 3) init_Lvl3();
		else if (current_lvl == 4) init_Lvl4();
		else if (current_lvl == 5) init_Lvl5();
	}
}

void Scene::initMenu()
{
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

	// background
	spritesheet.loadFromFile("images/menu.jpg", TEXTURE_PIXEL_FORMAT_RGB);
	sprite = Sprite::createSprite(glm::ivec2(640, 480), glm::vec2(1.f, 1.f), &spritesheet, &texProgram);
	sprite->setNumberAnimations(0);
	sprite->setPosition(glm::vec2(float(0), float(0)));
	
	// selector
	spritesheetSelector.loadFromFile("images/selector.jpg", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteSelector = Sprite::createSprite(glm::ivec2(180, 36), glm::vec2(1.f, 1.f), &spritesheetSelector, &texProgram);
	spriteSelector->setNumberAnimations(0);
	spriteSelector->setPosition(glm::vec2(float(85), float(235)));//play
	//spriteSelector->setPosition(glm::vec2(float(85), float(280))); //controls
	//spriteSelector->setPosition(glm::vec2(float(85), float(325))); //credits
}

void Scene::initCredits()
{
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

	// background
	spritesheetCredits.loadFromFile("images/credits.jpg", TEXTURE_PIXEL_FORMAT_RGB);
	spriteCredits = Sprite::createSprite(glm::ivec2(640, 480), glm::vec2(1.f, 1.f), &spritesheetCredits, &texProgram);
	spriteCredits->setNumberAnimations(0);
	spriteCredits->setPosition(glm::vec2(float(0), float(0)));
}

void Scene::initControls()
{
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

	// background
	spritesheetControls.loadFromFile("images/controls.jpg", TEXTURE_PIXEL_FORMAT_RGB);
	spriteControls = Sprite::createSprite(glm::ivec2(640, 480), glm::vec2(1.f, 1.f), &spritesheetControls, &texProgram);
	spriteControls->setNumberAnimations(0);
	spriteControls->setPosition(glm::vec2(float(0), float(0)));
}

void Scene::init_Lvl1()
{
	glClearColor(0.2, 0.2, 0.2, 1.0);
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Scene::init_Lvl2() {}

void Scene::init_Lvl3() {}

void Scene::init_Lvl4() {}

void Scene::init_Lvl5() {}


void Scene::updateCredits(int deltaTime) {
	spriteCredits->update(deltaTime);
	if (Game::instance().getKey('B') || Game::instance().getKey('b')) {
		state = "menu";
		init();
	}
}

void Scene::updateControls(int deltaTime) {
	spriteControls->update(deltaTime);
	if (Game::instance().getKey('B') || Game::instance().getKey('b')) {
		state = "menu";
		init();
	}
}

//235 280 325 posiciones y de selector
void Scene::updateMenu(int deltaTime) {
	sprite->update(deltaTime);
		if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
			glm::vec2 posSelector = spriteSelector->getPosition();
			if (posSelector.y == 235) posSelector.y = 325.f;
			else if (posSelector.y == 280) posSelector.y = 235;
			else if (posSelector.y == 325) posSelector.y = 280;


			spriteSelector->setPosition(posSelector);
			spriteSelector->render();
			Game::instance().specialKeyReleased(GLUT_KEY_UP);
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
			glm::vec2 posSelector = spriteSelector->getPosition();
			if (posSelector.y == 325) posSelector.y = 235.f;
			else if (posSelector.y == 280) posSelector.y = 325;
			else if (posSelector.y == 235) posSelector.y = 280;

			spriteSelector->setPosition(posSelector);
			spriteSelector->render();
			Game::instance().specialKeyReleased(GLUT_KEY_DOWN);

		}
		// return key == 13
		else if (Game::instance().getKey(13)) {
			if ((spriteSelector->getPosition()).y == 235) state = "playing";
			else if ((spriteSelector->getPosition()).y == 280) state = "controls";
			else state="credits";
			init();
		}
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	if (state == "menu") {
		updateMenu(deltaTime);
	}
	else if (state == "credits") {
		updateCredits(deltaTime);
	}
	else if (state == "controls") {
		updateControls(deltaTime);
	}
	else { // state == playing
		player->update(deltaTime);
	}
}


void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	
	if (state == "menu") {
		sprite->render();
		spriteSelector->render();
	}
	else if (state == "credits") {
		spriteCredits->render();
	}
	else if (state == "controls") {
		spriteControls->render();
	}
	else // state == playing
	{
		map->render();
		player->render();
	}
}


void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}