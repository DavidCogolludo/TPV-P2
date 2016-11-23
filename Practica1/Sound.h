#pragma once
#include <SDL_mixer.h>
#include <iostream>
class Sound
{
public:
	Sound();
	~Sound();

	//Atributos
	Mix_Music *pMusic;
	Mix_Chunk *pFx;

	//Métodos
	void loadMusic(std:: string name);
	void loadFX(std::string name);
};

