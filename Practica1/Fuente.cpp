#include "Fuente.h"
#include "SDL_ttf.h"

Fuente::Fuente()
{
	recFont.h = 50;
	recFont.w = 70;
	recFont.x = 25;
	recFont.y = 25;
}


Fuente::~Fuente()
{
}

SDL_Surface* Fuente::textSolid(std::string texto, SDL_Color color) {
	return TTF_RenderText_Solid(pFont, texto.c_str(), color);
}

bool Fuente::load(std::string nombre, int tamano){
	pFont = TTF_OpenFont(nombre.c_str(), tamano);
	return true;
}