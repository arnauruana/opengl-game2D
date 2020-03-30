#include "Level.h"
#include "Keyboard.h"


Level::Level()
{
	this->player = NULL;
}

Level::~Level()
{
	if (this->player != NULL) delete this->player;
}


void Level::setPath(const std::string& path)
{
	this->path = path;
}

void Level::setShader(const ShaderProgram& shader)
{
	this->shader = shader;
}


void Level::init()
{
	if (!this->loadMap())
	{
		std::cerr << "[LEVEL::init] error while loading map" << std::endl;
		exit(EXIT_FAILURE);
	}
	Sounds::instance().playMusic(true);
	glutSetWindowTitle("WINDOW IS GAME");
}

void Level::update(int deltaTime)
{
	if (this->updateBehaviour) this->assignBehaviours();

	if (keyboard::key['r'] || keyboard::key['R'])
	{
		this->cleanMap();
		this->loadMap();

		keyboard::key['r'] == false;
		keyboard::key['R'] == false;

		glutSetWindowTitle("WINDOW IS GAME");
	}

	if (keyboard::key['b'] || keyboard::key['B'])
	{
		this->cleanMap();

		Settings::playing = false;
		Settings::level = 1;
		Settings::changeLevel = false;

		keyboard::key['b'] == false;
		keyboard::key['B'] == false;
	}

	this->updatePlayer(deltaTime);
	this->updateObjects(deltaTime);
}

void Level::render()
{
	this->renderObjects();
	this->renderPlayer();
}


bool Level::loadMap()
{
	glutSetWindowTitle("WINDOW IS LOADING");

	ifstream fin(this->path);

	if (!fin.is_open())
	{
		return false;
	}

	std::string header;
	fin >> header;
	if (header != "MAP")
	{
		return false;
	}

	int mapWidth, mapHeight;
	fin >> mapWidth >> mapHeight;

	int spriteSize;
	fin >> spriteSize;

	std::string obj;
	for (int r = 0; r < mapHeight; ++r)
	{
		for (int c = 0; c < mapWidth; ++c)
		{
			fin >> obj;

			if (obj != "none")
			{
				if (obj == "baba")
				{
					this->player = new Player();
					this->player->init(glm::ivec2(0, 0), this->shader);
					this->player->setPosition(glm::vec2(c * spriteSize, r * spriteSize));
				}
				else
				{
					Object* object = Object::create();
					this->objects.push_back(object);

					if (obj == "flag") object->setType(Object::Type::FLAG);
					if (obj == "lava") object->setType(Object::Type::LAVA);
					if (obj == "rock") object->setType(Object::Type::ROCK);
					if (obj == "wall") object->setType(Object::Type::WALL);
					if (obj == "water") object->setType(Object::Type::WATER);

					if (obj == "BABA") object->setType(Object::Type::TXT_BABA);
					if (obj == "FLAG") object->setType(Object::Type::TXT_FLAG);
					if (obj == "LAVA") object->setType(Object::Type::TXT_LAVA);
					if (obj == "ROCK") object->setType(Object::Type::TXT_ROCK);
					if (obj == "WALL") object->setType(Object::Type::TXT_WALL);

					if (obj == "IS") object->setType(Object::Type::TXT_IS);
					if (obj == "NEAR") object->setType(Object::Type::TXT_NEAR);

					if (obj == "DEFEAT") object->setType(Object::Type::TXT_DEFEAT);
					if (obj == "PUSH") object->setType(Object::Type::TXT_PUSH);
					if (obj == "STOP") object->setType(Object::Type::TXT_STOP);
					if (obj == "WATER") object->setType(Object::Type::TXT_WATER);
					if (obj == "WIN") object->setType(Object::Type::TXT_WIN);
					if (obj == "YOU") object->setType(Object::Type::TXT_YOU);

					object->setShader(this->shader);
					object->init();
					object->setPosition(glm::vec2(c * spriteSize, r * spriteSize));
				}
			}
		}
	}

	this->assignBehaviours();

	return true;
}


void Level::updatePlayer(int deltaTime)
{
	this->player->update(deltaTime);
}

void Level::cleanMap() {
	int x = objects.size() - 1;
	for (int x = objects.size() - 1; x >= 0; --x) {
		delete objects[x];
		objects.pop_back();
	}
}

void Level::renderPlayer()
{
	this->shader.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	this->player->render();
}


void Level::updateObjects(int deltaTime)
{
	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->update(deltaTime);
		collision(objects[i], player);
	}
}

void Level::renderObjects()
{
	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->render();
	}
}


void Level::assignBehaviours()
{
	for (Object* object : this->objects)
	{
		Object::Type type = object->getType();

		Object::Type flag = Object::Type::FLAG;
		Object::Type lava = Object::Type::LAVA;
		Object::Type rock = Object::Type::ROCK;
		Object::Type wall = Object::Type::WALL;
		Object::Type water = Object::Type::WATER;

		if (type == flag || type == lava || type == rock || type == wall || type == water)
		{
			object->setBehaviour(Object::Behaviour::NONE);
		}
	}

	struct Text
	{
		Object::Type op = Object::Type::NONE;
		Object::Type pre = Object::Type::NONE;
		Object::Type post = Object::Type::NONE;
	};

	std::vector<Text> texts;

	for (Object* obj : this->objects)
	{
		if (obj->getBehaviour() == Object::Behaviour::OP)
		{
			Text txt;

			txt.op = obj->getType();

			glm::vec2 pos = obj->getPosition();

			Object* pre = find(pos.x - 24, pos.y);
			if (pre->getType() != Object::Type::NONE && pre->getBehaviour() == Object::Behaviour::PRE)
			{
				txt.pre = pre->getType();
			}

			Object* post = find(pos.x + 24, pos.y);
			if (post->getType() != Object::Type::NONE && (post->getBehaviour() == Object::Behaviour::POST || post->getBehaviour() == Object::Behaviour::PRE))
			{
				txt.post = post->getType();
			}

			if (txt.pre != Object::Type::NONE && txt.post != Object::Type::NONE)
			{
				texts.push_back(txt);
			}

			// ^^^ horizontal word checking ^^^ | vvv vertical vord checking vvv //

			Text txt2;

			txt2.op = obj->getType();

			pos = obj->getPosition();

			Object* pre2 = find(pos.x, pos.y - 24);
			if (pre2->getType() != Object::Type::NONE && pre2->getBehaviour() == Object::Behaviour::PRE)
			{
				txt2.pre = pre2->getType();
			}

			Object* post2 = find(pos.x, pos.y + 24);
			if (post2->getType() != Object::Type::NONE && (post2->getBehaviour() == Object::Behaviour::POST || post2->getBehaviour() == Object::Behaviour::PRE))
			{
				txt2.post = post2->getType();
			}

			if (txt2.pre != Object::Type::NONE && txt2.post != Object::Type::NONE)
			{
				texts.push_back(txt2);
			}
		}
	}

	for (Object* object : this->objects)
	{
		glm::vec2 position = object->getPosition();

		switch (object->getType())
		{
			case Object::Type::FLAG:
			{
				for (Text text : texts)
				{
					if (text.pre == Object::Type::TXT_FLAG && text.op == Object::Type::TXT_IS)
					{
						switch (text.post)
						{
							//subjects
							case Object::Type::TXT_LAVA:
							{
								object->setType(Object::Type::LAVA);
								object->init();
								object->setPosition(position);
								this->assignBehaviours();
								break;
							}
							case Object::Type::TXT_WATER:
							{
								object->setType(Object::Type::WATER);
								object->init();
								object->setPosition(position);
								this->assignBehaviours();
								break;
							}
							case Object::Type::TXT_ROCK:
							{
								object->setType(Object::Type::ROCK);
								object->init();
								object->setPosition(position);
								this->assignBehaviours();
								break;
							}
							case Object::Type::TXT_WALL:
							{
								object->setType(Object::Type::WALL);
								object->init();
								object->setPosition(position);
								this->assignBehaviours();
								break;
							}
							// predicates
							case Object::Type::TXT_DEFEAT:
							{
								object->setBehaviour(Object::Behaviour::DEFEAT);
								break;
							}
							case Object::Type::TXT_PUSH:
							{
								object->setBehaviour(Object::Behaviour::PUSH);
								break;
							}
							case Object::Type::TXT_STOP:
							{
								object->setBehaviour(Object::Behaviour::STOP);
								break;
							}
							case Object::Type::TXT_WIN:
							{
								object->setBehaviour(Object::Behaviour::WIN);
								break;
							}
							case Object::Type::TXT_YOU:
							{
								object->setBehaviour(Object::Behaviour::YOU);
								break;
							}
							default:
							{
								break;
							}
						}
					}
				}
				break;
			}
			case Object::Type::ROCK:
			{
				for (Text text : texts)
				{
					if (text.pre == Object::Type::TXT_ROCK && text.op == Object::Type::TXT_IS)
					{
						switch (text.post)
						{
							//subjects
							case Object::Type::TXT_LAVA:
							{
								object->setType(Object::Type::LAVA);
								object->init();
								object->setPosition(position);
								this->assignBehaviours();
								break;
							}
							case Object::Type::TXT_WATER:
							{
								object->setType(Object::Type::WATER);
								object->init();
								object->setPosition(position);
								this->assignBehaviours();
								break;
							}
							case Object::Type::TXT_FLAG:
							{
								object->setType(Object::Type::FLAG);
								object->init();
								object->setPosition(position);
								this->assignBehaviours();
								break;
							}
							case Object::Type::TXT_WALL:
							{
								object->setType(Object::Type::WALL);
								object->init();
								object->setPosition(position);
								this->assignBehaviours();
								break;
							}
							// predicates
							case Object::Type::TXT_DEFEAT:
							{
								object->setBehaviour(Object::Behaviour::DEFEAT);
								break;
							}
							case Object::Type::TXT_PUSH:
							{
								object->setBehaviour(Object::Behaviour::PUSH);
								break;
							}
							case Object::Type::TXT_STOP:
							{
								object->setBehaviour(Object::Behaviour::STOP);
								break;
							}
							case Object::Type::TXT_WIN:
							{
								object->setBehaviour(Object::Behaviour::WIN);
								break;
							}
							case Object::Type::TXT_YOU:
							{
								object->setBehaviour(Object::Behaviour::YOU);
								break;
							}
							default:
							{
								break;
							}
						}
					}
				}
				break;
			}
			case Object::Type::WALL:
			{
				for (Text text : texts)
				{
					if (text.pre == Object::Type::TXT_WALL && text.op == Object::Type::TXT_IS)
					{
						switch (text.post)
						{
							//subjects
							case Object::Type::TXT_LAVA:
							{
								object->setType(Object::Type::LAVA);
								object->init();
								object->setPosition(position);
								this->assignBehaviours();
								break;
							}
							case Object::Type::TXT_WATER:
							{
								object->setType(Object::Type::WATER);
								object->init();
								object->setPosition(position);
								this->assignBehaviours();
								break;
							}
							case Object::Type::TXT_FLAG:
							{
								object->setType(Object::Type::FLAG);
								object->init();
								object->setPosition(position);
								this->assignBehaviours();
								break;
							}
							case Object::Type::TXT_ROCK:
							{
								object->setType(Object::Type::ROCK);
								object->init();
								object->setPosition(position);
								this->assignBehaviours();
								break;
							}
							// predicates
							case Object::Type::TXT_DEFEAT:
							{
								object->setBehaviour(Object::Behaviour::DEFEAT);
								break;
							}
							case Object::Type::TXT_PUSH:
							{
								object->setBehaviour(Object::Behaviour::PUSH);
								break;
							}
							case Object::Type::TXT_STOP:
							{
								object->setBehaviour(Object::Behaviour::STOP);
								break;
							}
							case Object::Type::TXT_WIN:
							{
								object->setBehaviour(Object::Behaviour::WIN);
								break;
							}
							case Object::Type::TXT_YOU:
							{
								object->setBehaviour(Object::Behaviour::YOU);
								break;
							}
							default:
							{
								break;
							}
						}
					}
				}
				break;
			}
			default:
			{
				break;
			}
		}
	}

	this->updateBehaviour = false;
}

void Level::collision(Object* object, Player* player)
{
	glm::vec2 posObj = object->getPosition();
	glm::vec2 posPlayer = player->getPosition();

	if (posObj.x == posPlayer.x && posObj.y == posPlayer.y)
	{
		switch (object->getBehaviour())
		{
			case Object::Behaviour::STOP:
			{
				switch (player->getAnimation())
				{
					case MOVE_FORWARD:
					{
						player->setPosition(glm::vec2(posPlayer.x, posPlayer.y - 24));
						break;
					}
					case MOVE_BACKWARD:
					{
						player->setPosition(glm::vec2(posPlayer.x, posPlayer.y + 24));
						break;
					}
					case MOVE_RIGHT:
					{
						player->setPosition(glm::vec2(posPlayer.x - 24, posPlayer.y));
						break;
					}
					case MOVE_LEFT:
					{
						player->setPosition(glm::vec2(posPlayer.x + 24, posPlayer.y));
						break;
					}
					default:
					{
						exit(1);
					}
				}
				break;
			}
			case Object::Behaviour::OP:
			case Object::Behaviour::PRE:
			case Object::Behaviour::POST:
			{
				this->updateBehaviour = true;
			}
			case Object::Behaviour::PUSH:
			{
				Sounds::instance().playSoundEffect("PUSH");
				switch (player->getAnimation())
				{
					case MOVE_FORWARD:
					{
						object->setPosition(glm::vec2(posPlayer.x, posPlayer.y + 24));
						object->setDirection(Object::Direction::FORWARD);

						if (!this->collision(object))
						{
							object->setPosition(posObj);
							player->setPosition(glm::vec2(posPlayer.x, posPlayer.y - 24));
						}

						break;
					}
					case MOVE_BACKWARD:
					{
						object->setPosition(glm::vec2(posPlayer.x, posPlayer.y - 24));
						object->setDirection(Object::Direction::BACKWARD);

						if (!this->collision(object))
						{
							object->setPosition(posObj);
							player->setPosition(glm::vec2(posPlayer.x, posPlayer.y + 24));
						}

						break;
					}
					case MOVE_RIGHT:
					{
						object->setPosition(glm::vec2(posPlayer.x + 24, posPlayer.y));
						object->setDirection(Object::Direction::RIGHT);

						if (!this->collision(object))
						{
							object->setPosition(posObj);
							player->setPosition(glm::vec2(posPlayer.x - 24, posPlayer.y));
						}

						break;
					}
					case MOVE_LEFT:
					{
						object->setPosition(glm::vec2(posPlayer.x - 24, posPlayer.y));
						object->setDirection(Object::Direction::LEFT);
						
						if (!this->collision(object))
						{
							object->setPosition(posObj);
							player->setPosition(glm::vec2(posPlayer.x + 24, posPlayer.y));
						}

						break;
					}
					default:
					{
						std::cerr << "[LEVEL::collision] wrong player animation" << endl;
						exit(EXIT_FAILURE);
					}
				}
				break;
			}
			case Object::Behaviour::WIN:
			{
				Sounds::instance().playSoundEffect("WIN");
				++Settings::level;
				Settings::changeLevel = true;
				this->cleanMap();
				break;
			}
			case Object::Behaviour::DEFEAT:
			{
				Sounds::instance().playSoundEffect("DEFEAT");
				break;
			}
		}
	}
}

bool Level::collision(Object* object)
{
	glm::vec2 posObject = object->getPosition();

	if (posObject.x < 0 || posObject.x > 480 - 24 || posObject.y < 0 || posObject.y > 480 - 24)
	{
		return false;
	}

	Object::Behaviour op = Object::Behaviour::OP;
	Object::Behaviour pre = Object::Behaviour::PRE;
	Object::Behaviour post = Object::Behaviour::POST;
	Object::Behaviour push = Object::Behaviour::PUSH;

	Object::Behaviour stop = Object::Behaviour::STOP;

	for (Object* obj : this->objects)
	{
		Object::Behaviour behObj = obj->getBehaviour();
		glm::vec2 posObj = obj->getPosition();

		if (posObj.x == posObject.x && posObj.y == posObject.y && object != obj)
		{
			if (behObj == stop)
			{
				return false;
			}
			if (behObj == op || behObj == pre || behObj == post || behObj == push)
			{
				switch (object->getDirection())
				{
					case Object::Direction::BACKWARD:
					{
						obj->setPosition(glm::vec2(posObj.x, posObj.y - 24));
						obj->setDirection(Object::Direction::BACKWARD);
						break;
					}
					case Object::Direction::FORWARD:
					{
						obj->setPosition(glm::vec2(posObj.x, posObj.y + 24));
						obj->setDirection(Object::Direction::FORWARD);
						break;
					}
					case Object::Direction::LEFT:
					{
						obj->setPosition(glm::vec2(posObj.x - 24, posObj.y));
						obj->setDirection(Object::Direction::LEFT);
						break;
					}
					case Object::Direction::RIGHT:
					{
						obj->setPosition(glm::vec2(posObj.x + 24, posObj.y));
						obj->setDirection(Object::Direction::RIGHT);
						break;
					}
					default:
					{
						std::cerr << "[LEVEL::collision] wrong object direction" << std::endl;
						exit(EXIT_FAILURE);
					}
				}

				if (!this->collision(obj))
				{
					obj->setPosition(posObj);
					return false;
				}
			}
		}
	}

	return true;
}

Object* Level::find(int posX, int posY) const
{
	for (Object* object : this->objects)
	{
		if (object->getPosition().x == posX && object->getPosition().y == posY)
		{
			if (object->getBehaviour() == Object::Behaviour::PRE || object->getBehaviour() == Object::Behaviour::POST)
			{
				return object;
			}
		}
	}

	Object* obj = Object::create();
	obj->setType(Object::Type::NONE);
	return obj;
}