#include "Sound.h"


Sound::Sound()
{
	pMusic = nullptr;
	pFx = nullptr;
}


Sound::~Sound()
{
	
}

void Sound::loadMusic(std::string name){
	pMusic = Mix_LoadMUS(name.c_str());
}
void Sound::loadFX(std::string name){
	pFx = Mix_LoadWAV(name.c_str());
}