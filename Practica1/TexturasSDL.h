#include "SDL.h"
#include <iostream>
#include "Fuente.h"
#pragma once
class TexturasSDL
{

private:
	int w, h;
	SDL_Texture* pTexture;
	
public:
	TexturasSDL();
	~TexturasSDL();

	Fuente font;

	void draw(SDL_Renderer*, SDL_Rect const& rect);
	bool loadFromText(SDL_Renderer* pRenderer, const std::string text, SDL_Color color);
	bool loadFuente(std::string nombre, int tamaño);
	int getW();
	int getH();
	bool load(SDL_Renderer* pRenderer, std::string const& nombArch);			// : Carga la imagen del archivo.En caso de
																//error lo muestra y devuelve false, y en otro caso genera la textura.Cuidado con la anterior textura.


	
	//bool load(SDL_Renderer* pRenderer, std:: string const& nombArch, SDL_Color const& colKey); //Una vez cargado el archivo, y antes de generar la textura, pone el color colKey transparente.
		
	//Puedes definir una función static SDL_Surface* load(string nombreArchivo) para cargar el	archivo.
};

