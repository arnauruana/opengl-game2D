#pragma once
#include <string>
#include <irrKlang.h>
#include <GL/glew.h>
#include <GL/glut.h>
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

using namespace std;
using namespace irrklang;

class Sounds
{
public:
	static Sounds& instance()
	{
		static Sounds S;

		return S;
	}

	void playMusic(bool& playing);
	void playSoundEffect(const string& effect);


private:
};

