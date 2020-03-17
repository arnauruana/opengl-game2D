#include "Menu.h"


Menu::Menu()
{
	this->spriteMenu = NULL;
	this->spriteSelector = NULL;
}

Menu::~Menu()
{
	if (this->spriteMenu != NULL) delete this->spriteMenu;
	if (this->spriteSelector != NULL) delete this->spriteSelector;
}


void Menu::init()
{
	this->initMenu();
	this->initControls();
	this->initCredits();
	this->initSelector();
}

void Menu::update(int deltaTime)
{
	this->spriteMenu->update(deltaTime);
	this->spriteSelector->update(deltaTime);
}

void Menu::render()
{
	this->renderMenu();
	this->renderControls();
	this->renderCredits();
}


void Menu::setShader(const ShaderProgram& shader)
{
	this->shader = shader;
}


void Menu::initMenu()
{
	this->textureMenu.loadFromFile("images/menu.jpg", TEXTURE_PIXEL_FORMAT_RGB);
	this->spriteMenu = Sprite::createSprite(glm::ivec2(480, 480), glm::vec2(1.f, 1.f), &this->textureMenu, &this->shader);
	this->spriteMenu->setNumberAnimations(0);
	this->spriteMenu->setPosition(glm::vec2(0.f, 0.f));
}

void Menu::initControls()
{
	this->textureControls.loadFromFile("images/controls.jpg", TEXTURE_PIXEL_FORMAT_RGB);
	this->spriteControls = Sprite::createSprite(glm::ivec2(480, 480), glm::vec2(1.f, 1.f), &this->textureControls, &this->shader);
	this->spriteControls->setNumberAnimations(0);
	this->spriteControls->setPosition(glm::vec2(0.f, 0.f));
}

void Menu::initCredits()
{
	this->textureCredits.loadFromFile("images/credits.jpg", TEXTURE_PIXEL_FORMAT_RGB);
	this->spriteCredits = Sprite::createSprite(glm::ivec2(480, 480), glm::vec2(1.f, 1.f), &this->textureCredits, &this->shader);
	this->spriteCredits->setNumberAnimations(0);
	this->spriteCredits->setPosition(glm::vec2(0.f, 0.f));
}

void Menu::initSelector()
{
	this->textureSelector.loadFromFile("images/selector.jpg", TEXTURE_PIXEL_FORMAT_RGBA);
	this->spriteSelector = Sprite::createSprite(glm::ivec2(480 / 3 - 30, 36), glm::vec2(1.f, 1.f), &this->textureSelector, &this->shader);
	this->spriteSelector->setNumberAnimations(0);
	this->spriteSelector->setPosition(this->selectorPos);
}


void Menu::renderMenu()
{
	this->spriteMenu->render();
	this->spriteSelector->render();
}

void Menu::renderControls()
{
	this->spriteControls->render();
}

void Menu::renderCredits()
{
	this->spriteCredits->render();
}