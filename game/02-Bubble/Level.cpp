#include "Level.h"
#include "Keyboard.h"


Level::Level() {}

Level::~Level() {}


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
	this->win = false;

	if (!this->loadMap())
	{
		std::cerr << "[LEVEL::init] error while loading map" << std::endl;
		exit(EXIT_FAILURE);
	}

	Sounds::instance().playMusic(true);
	glutSetWindowTitle("WINDOW IS GAME");
}

void Level::updateLava() {
	int total,column,row;
	for (int i = 0; i < objects.size() - 1; ++i) {
		if (objects[i]->isFluid) {
			total = 0;
			column = i % 20;
			row = i / 20;

			if (column != 19) {
				if (objects[i + 1]->isFluid) total += 1;
			}
			else total +=1;
			
			if (column != 0) {
				if (objects[i - 1]->isFluid) total += 2;
			}
			else total += 2;

			if (row != 0) {
				if (objects[i - 20]->isFluid) total += 8;
			}
			else total += 8;

			if (row != 19) {
				if (objects[i + 20]->isFluid) total += 4;
			}
			else total += 4;

			objects[i]->setTexture(total + 1);
			objects[i]->setShader(this->shader);
			objects[i]->init();
			objects[i]->setPosition(glm::vec2(column * 24, row * 24));

		}
	}
}

void Level::update(int deltaTime)
{
	/*bool r, l, u, d;
	r = l = u = d = true;
	for (int i = 0; i < objects.size() - 1; ++i) {
		if (objects[i]->isFluid) {
			int column, row;
			column = i % 20;
			row = i / 20;
			if (column != 19) r = objects[i + 1]->isFluid;
			if (column != 0) l = objects[i - 1]->isFluid;
			if (row != 0) u = objects[i - 20]->isFluid;
			if (row != 19) d = objects[i + 20]->isFluid;
			if (r && l && u && d) { //16
				objects[i]->setTexture(16);
			}
			else if (l && u && d) { //15
				objects[i]->setTexture(15);

			}
			else if (r && u && d) { //14
				objects[i]->setTexture(14);
			}
			else if (r && l && d) { //13
				objects[i]->setTexture(13);
			}
			else if (r && u && l) { //12
				objects[i]->setTexture(12);
			}
			else if (u && d) { //11
				objects[i]->setTexture(11);
			}
			else if (l && d) { //10
				objects[i]->setTexture(10);
			}
			else if (u && l) { //9
				objects[i]->setTexture(9);
			}
			else if (r && d) { //8
				objects[i]->setTexture(8);
			}
			else if (u && r) { //7
				objects[i]->setTexture(7);
			}
			else if (r && l) { //6
				objects[i]->setTexture(6);
			}
			else if (d) { //5
				objects[i]->setTexture(5);
			}
			else if (u) { //4
				objects[i]->setTexture(4);
			}
			else if (l) { //3
				objects[i]->setTexture(3);
			}
			else if (r) { //2
				objects[i]->setTexture(2);
			}
			else {
				objects[i]->setTexture(1);
			}

			objects[i]->setShader(this->shader);
			objects[i]->init();
		}
	}
	*/
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

	bool up = keyboard::skey[GLUT_KEY_UP];
	bool down = keyboard::skey[GLUT_KEY_DOWN];
	bool left = keyboard::skey[GLUT_KEY_LEFT];
	bool right = keyboard::skey[GLUT_KEY_RIGHT];

	for (Object* object : this->objects)
	{
		object->update(deltaTime);

		bool move = true;
		if (object->getBehaviour() == Object::Behaviour::YOU)
		{
			glm::ivec2 pos = object->getPosition();

			if (up)
			{
				object->move(Object::Direction::BACKWARD);
				
				for (Object* obj : this->objects)
				{
					if (!this->collision(obj, object))
					{
						move = false;
					}
				}
				
				if (move && object->getMake() != Object::Type::NONE)
				{
					Object* obj = Object::create();
					this->objects.push_back(obj);
					
					obj->setType(object->getMake());
					obj->setShader(this->shader);
					obj->init();
					obj->setPosition(pos);
				}
			}
			else if (down)
			{
				object->move(Object::Direction::FORWARD);

				for (Object* obj : this->objects)
				{
					if (!this->collision(obj, object))
					{
						move = false;
					}
				}

				if (move && object->getMake() != Object::Type::NONE)
				{
					Object* obj = Object::create();
					this->objects.push_back(obj);

					obj->setType(object->getMake());
					obj->setShader(this->shader);
					obj->init();
					obj->setPosition(pos);
				}
			}
			else if (left)
			{
				object->move(Object::Direction::LEFT);

				for (Object* obj : this->objects)
				{
					if (!this->collision(obj, object))
					{
						move = false;
					}
				}

				if (move && object->getMake() != Object::Type::NONE)
				{
					Object* obj = Object::create();
					this->objects.push_back(obj);

					obj->setType(object->getMake());
					obj->setShader(this->shader);
					obj->init();
					obj->setPosition(pos);
				}
			}
			else if (right)
			{
				object->move(Object::Direction::RIGHT);

				for (Object* obj : this->objects)
				{
					if (!this->collision(obj, object))
					{
						move = false;
					}
				}

				if (move && object->getMake() != Object::Type::NONE)
				{
					Object* obj = Object::create();
					this->objects.push_back(obj);

					obj->setType(object->getMake());
					obj->setShader(this->shader);
					obj->init();
					obj->setPosition(pos);
				}
			}
		}
	}

	keyboard::skey[GLUT_KEY_UP] = false;
	keyboard::skey[GLUT_KEY_DOWN] = false;
	keyboard::skey[GLUT_KEY_LEFT] = false;
	keyboard::skey[GLUT_KEY_RIGHT] = false;

	Object::moved = false;
}

void Level::render()
{
	Object::Type BABA = Object::Type::BABA;
	Object::Type FLAG = Object::Type::FLAG;
	Object::Type LAVA = Object::Type::LAVA;
	Object::Type ROCK = Object::Type::ROCK;
	Object::Type WALL = Object::Type::WALL;

	Object::Behaviour YOU = Object::Behaviour::YOU;
	Object::Behaviour OP = Object::Behaviour::OP;
	Object::Behaviour PRE = Object::Behaviour::PRE;
	Object::Behaviour POST = Object::Behaviour::POST;

	for (Object* lava : this->objects)
	{
		if (lava->getType() == LAVA && lava->getBehaviour() != YOU)
		{
			lava->render();
		}
	}

	for (Object* wall : this->objects)
	{
		if (wall->getType() == WALL && wall->getBehaviour() != YOU)
		{
			wall->render();
		}
	}

	for (Object* flag : this->objects)
	{
		if (flag->getType() == FLAG && flag->getBehaviour() != YOU)
		{
			flag->render();
		}
	}

	for (Object* rock : this->objects)
	{
		if (rock->getType() == ROCK && rock->getBehaviour() != YOU)
		{
			rock->render();
		}
	}

	for (Object* baba : this->objects)
	{
		if (baba->getType() == BABA && baba->getBehaviour() != YOU)
		{
			baba->render();
		}
	}

	for (Object* word : this->objects)
	{
		Object::Behaviour beh = word->getBehaviour();
		if (beh == OP || beh == PRE || beh == POST)
		{
			word->render();
		}
	}

	for (Object* you : this->objects)
	{
		if (you->getBehaviour() == YOU)
		{
			you->render();
		}
	}
}


bool Level::loadMap()
{
	glutSetWindowTitle("WINDOW IS LOADING");

	this->cleanMap();

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
				Object* object = Object::create();
				this->objects.push_back(object);
				if (obj == "baba") object->setType(Object::Type::BABA);
				if (obj == "flag") object->setType(Object::Type::FLAG);
				if (obj == "lava") object->setType(Object::Type::LAVA);
				if (obj == "rock") object->setType(Object::Type::ROCK);
				if (obj == "wall") object->setType(Object::Type::WALL);

				if (obj == "BABA") object->setType(Object::Type::TXT_BABA);
				if (obj == "FLAG") object->setType(Object::Type::TXT_FLAG);
				if (obj == "LAVA") object->setType(Object::Type::TXT_LAVA);
				if (obj == "ROCK") object->setType(Object::Type::TXT_ROCK);
				if (obj == "WALL") object->setType(Object::Type::TXT_WALL);

				if (obj == "IS") object->setType(Object::Type::TXT_IS);
				if (obj == "MAKE") object->setType(Object::Type::TXT_MAKE);

				if (obj == "DEFEAT") object->setType(Object::Type::TXT_DEFEAT);
				if (obj == "PUSH") object->setType(Object::Type::TXT_PUSH);
				if (obj == "STOP") object->setType(Object::Type::TXT_STOP);
				if (obj == "WIN") object->setType(Object::Type::TXT_WIN);
				if (obj == "YOU") object->setType(Object::Type::TXT_YOU);

				object->setShader(this->shader);
				object->init();
				object->setPosition(glm::vec2(c * spriteSize, r * spriteSize));
			}
			else
			{
				Object* object = Object::create();
				this->objects.push_back(object);
				object->setType(Object::Type::NONE);
				object->init();
				object->setPosition(glm::vec2(c * spriteSize, r * spriteSize));
			}
		}
	}

	this->assignBehaviours();
	updateLava();

	return true;
}

void Level::cleanMap() {
	int x = objects.size() - 1;
	for (int x = objects.size() - 1; x >= 0; --x) {
		delete objects[x];
		objects.pop_back();
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
		Object::Type baba = Object::Type::BABA;

		if (type == flag || type == lava || type == rock || type == wall || type == baba)
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

	// check the others
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
							case Object::Type::TXT_BABA:
							{
								object->setType(Object::Type::BABA);
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

					if (text.pre == Object::Type::TXT_FLAG && text.op == Object::Type::TXT_MAKE)
					{
						switch (text.post)
						{
							case Object::Type::TXT_LAVA:
							{
								object->setMake(Object::Type::LAVA);
								break;
							}
							case Object::Type::TXT_BABA:
							{
								object->setMake(Object::Type::BABA);
								break;
							}
							case Object::Type::TXT_ROCK:
							{
								object->setMake(Object::Type::ROCK);
								break;
							}
							case Object::Type::TXT_WALL:
							{
								object->setMake(Object::Type::WALL);
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
							case Object::Type::TXT_BABA:
							{
								object->setType(Object::Type::BABA);
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

					if (text.pre == Object::Type::TXT_ROCK && text.op == Object::Type::TXT_MAKE)
					{
						switch (text.post)
						{
							case Object::Type::TXT_BABA:
							{
								object->setMake(Object::Type::BABA);
								break;
							}
							case Object::Type::TXT_FLAG:
							{
								object->setMake(Object::Type::FLAG);
								break;
							}
							case Object::Type::TXT_LAVA:
							{
								object->setMake(Object::Type::LAVA);
								break;
							}
							case Object::Type::TXT_WALL:
							{
								object->setMake(Object::Type::WALL);
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
							case Object::Type::TXT_BABA:
							{
								object->setType(Object::Type::BABA);
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

					if (text.pre == Object::Type::TXT_WALL && text.op == Object::Type::TXT_MAKE)
					{
						switch (text.post)
						{
							case Object::Type::TXT_BABA:
							{
								object->setMake(Object::Type::BABA);
								break;
							}
							case Object::Type::TXT_FLAG:
							{
								object->setMake(Object::Type::FLAG);
								break;
							}
							case Object::Type::TXT_LAVA:
							{
								object->setMake(Object::Type::LAVA);
								break;
							}
							case Object::Type::TXT_ROCK:
							{
								object->setMake(Object::Type::ROCK);
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
			case Object::Type::LAVA:
			{
				for (Text text : texts)
				{
					if (text.pre == Object::Type::TXT_LAVA && text.op == Object::Type::TXT_IS)
					{
						switch (text.post)
						{
							//subjects
							case Object::Type::TXT_FLAG:
							{
								object->setType(Object::Type::FLAG);
								object->init();
								object->setPosition(position);
								this->assignBehaviours();
								break;
							}
							case Object::Type::TXT_BABA:
							{
								object->setType(Object::Type::BABA);
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

					if (text.pre == Object::Type::TXT_LAVA && text.op == Object::Type::TXT_MAKE)
					{
						switch (text.post)
						{
							case Object::Type::TXT_BABA:
							{
								object->setMake(Object::Type::BABA);
								break;
							}
							case Object::Type::TXT_FLAG:
							{
								object->setMake(Object::Type::FLAG);
								break;
							}
							case Object::Type::TXT_ROCK:
							{
								object->setMake(Object::Type::ROCK);
								break;
							}
							case Object::Type::TXT_WALL:
							{
								object->setMake(Object::Type::WALL);
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
			case Object::Type::BABA:
			{
				for (Text text : texts)
				{
					if (text.pre == Object::Type::TXT_BABA && text.op == Object::Type::TXT_IS)
					{
						switch (text.post)
						{
							//subjects
							case Object::Type::TXT_FLAG:
							{
								object->setType(Object::Type::FLAG);
								object->init();
								object->setPosition(position);
								this->assignBehaviours();
								break;
							}
							case Object::Type::TXT_LAVA:
							{
								object->setType(Object::Type::LAVA);
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

					if (text.pre == Object::Type::TXT_BABA && text.op == Object::Type::TXT_MAKE)
					{
						switch (text.post)
						{
							case Object::Type::TXT_ROCK:
							{
								object->setMake(Object::Type::ROCK);
								break;
							}
							case Object::Type::TXT_FLAG:
							{
								object->setMake(Object::Type::FLAG);
								break;
							}
							case Object::Type::TXT_LAVA:
							{
								object->setMake(Object::Type::LAVA);
								break;
							}
							case Object::Type::TXT_WALL:
							{
								object->setMake(Object::Type::WALL);
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

bool Level::collision(Object* object, Object* player)
{
	if (this->win) return false;

	glm::vec2 posObj = object->getPosition();
	glm::vec2 posPlayer = player->getPosition();

	if (posObj.x == posPlayer.x && posObj.y == posPlayer.y)
	{
		switch (object->getBehaviour())
		{
			case Object::Behaviour::STOP:
			{
				switch (player->getDirection())
				{
					case Object::Direction::FORWARD:
					{
						player->setPosition(glm::vec2(posPlayer.x, posPlayer.y - 24));
						break;
					}
					case Object::Direction::BACKWARD:
					{
						player->setPosition(glm::vec2(posPlayer.x, posPlayer.y + 24));
						break;
					}
					case Object::Direction::RIGHT:
					{
						player->setPosition(glm::vec2(posPlayer.x - 24, posPlayer.y));
						break;
					}
					case Object::Direction::LEFT:
					{
						player->setPosition(glm::vec2(posPlayer.x + 24, posPlayer.y));
						break;
					}
				}
				return false;
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
				switch (player->getDirection())
				{
					case Object::Direction::FORWARD:
					{
						object->setPosition(glm::vec2(posPlayer.x, posPlayer.y + 24));
						object->setDirection(Object::Direction::FORWARD);

						if (!this->collision(object))
						{
							object->setPosition(posObj);
							player->setPosition(glm::vec2(posPlayer.x, posPlayer.y - 24));
							return false;
						}

						break;
					}
					case Object::Direction::BACKWARD:
					{
						object->setPosition(glm::vec2(posPlayer.x, posPlayer.y - 24));
						object->setDirection(Object::Direction::BACKWARD);

						if (!this->collision(object))
						{
							object->setPosition(posObj);
							player->setPosition(glm::vec2(posPlayer.x, posPlayer.y + 24));
							return false;
						}

						break;
					}
					case Object::Direction::RIGHT:
					{
						object->setPosition(glm::vec2(posPlayer.x + 24, posPlayer.y));
						object->setDirection(Object::Direction::RIGHT);

						if (!this->collision(object))
						{
							object->setPosition(posObj);
							player->setPosition(glm::vec2(posPlayer.x - 24, posPlayer.y));
							return false;
						}

						break;
					}
					case Object::Direction::LEFT:
					{
						object->setPosition(glm::vec2(posPlayer.x - 24, posPlayer.y));
						object->setDirection(Object::Direction::LEFT);
						
						if (!this->collision(object))
						{
							object->setPosition(posObj);
							player->setPosition(glm::vec2(posPlayer.x + 24, posPlayer.y));
							return false;
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
				this->win = true;
				break;
			}
			case Object::Behaviour::DEFEAT:
			{
				Sounds::instance().playSoundEffect("DIE");
				player->setPosition(glm::vec2(480, 480));
				player->dead = true;
				break;
			}
		}
	}

	return true;
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
				else this->updateBehaviour = true;
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