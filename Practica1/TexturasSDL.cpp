#include "TexturasSDL.h"
#include "SDL.h"  // Para utilizar SDL
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>  // la consola: cin / cout
using namespace std; // Para cualificar automaticamente con std:: los identificadores de la librería estandar 
//------------------------------------------------------------------------------------------------------------------------------

TexturasSDL::TexturasSDL()
{
	pTexture = nullptr;
	pSurface = nullptr;
}


TexturasSDL::~TexturasSDL()
{
	SDL_DestroyTexture(pTexture);
}
//---------------------------------------------------------------------------------------------------------------------------
int TexturasSDL::getH(){
	return h;
}
int TexturasSDL::getW(){
	return w;
}
//---------------------------------------------------------------------------------------------------------------------------

bool TexturasSDL::load(SDL_Renderer* pRenderer, string const& nombArch){

	bool success = true;  //Loading success flag
	
	//Load image
	SDL_Surface* pSurface;
	pSurface = IMG_Load(nombArch.c_str());  // si usamos string: bmpName.c_str() 
	if (pSurface== nullptr) {
		cout << "Unable to load image " << nombArch.c_str() << "! \nSDL Error: " << SDL_GetError() << '\n';
		success = false;
	}
	else {
		//std::cout << h << w;
		SDL_DestroyTexture(pTexture);
		pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
		SDL_FreeSurface(pSurface);
		success = pTexture != nullptr;
		w = pSurface->w;
		h = pSurface->h;
	}
	
	return success;
}
//-------------------------------------------------------------------------------------------------------
void TexturasSDL::draw(SDL_Renderer* prenderer, SDL_Rect const& rect){
	SDL_RenderCopy(prenderer, pTexture, nullptr, &rect);  // nullptr, nullptr -> toda la textura en toda la ventana
}
 //-----------------------------------------------------------------------------------------------------
bool TexturasSDL::loadFromText(SDL_Renderer* pRenderer, const string text, SDL_Color color){
	SDL_Surface* pSurface;
	pSurface = font.textSolid(text, color);
	pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
	SDL_FreeSurface(pSurface);
	return true;
}
//-----------------------------------------------------------------------------------------------------------------------
bool TexturasSDL::loadFuente(std::string nombre, int tamano){

	font.load(nombre, tamano);
	return true;
}