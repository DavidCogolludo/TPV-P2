#include "GlobosPG.h"
#include "TexturasSDL.h"
#include <vector>
#include "SDL.h"
#include <iostream>
#include "SDL_ttf.h"
#include "Sound.h"
#pragma once
class juegoPG
{
public:
	juegoPG();
	~juegoPG();
	void run();
private:
	SDL_Event e;
	std::vector<TexturasSDL*> vecTexturas;
	std::vector<GlobosPG*>vecGlobos;
	TexturasSDL* fuente;
	SDL_Color colorFuente;
	Sound *sound;

	SDL_Rect fondo;
	SDL_Window * pWin;        //The window we'll be rendering to
	SDL_Renderer * pRender;   //The renderer by the window  
	SDL_Texture *pTexture;    //The image we will load and show on the screen
	SDL_Color *pColor;

	const int SCREEN_WIDTH = 640;   //Screen dimension
	const int SCREEN_HEIGHT = 480;  //Screen dimension

	int contGlobos, globosTot, contPuntos, pmx, pmy;
	bool error, exit, gameOver;
	bool pause;


	bool initSDL(SDL_Window* & pWindow, SDL_Renderer* & pRenderer);	    // : Inicia el renderizador.En caso de error, muestra un mensaje y deja todos los
	//atributos con valores nulos.
	void closeSDL(SDL_Window* & pWindow, SDL_Renderer* & pRenderer);    // : Libera los atributos iniciados en initSDL.
	void render() const;				// : Limpia el buffer, pide a todos los globos que se dibujen y lo muestra.
	void onClick(int pmx, int pmy);										// : Pide a los globos que comprueben si lo han pinchado(máximo
	//uno) y actualiza el número de globos que quedan activos y los puntos obtenidos al pinchar globos.

	void update();														// : Pide a todos los globos que actualicen su estado, y actualiza el número de globos
	//que quedan activos.
	bool handle_event();				// : Comprueba si se ha producido el evento SDL_Quit o el evento soltar el botón
	//izquierdo del ratón.Para el caso SDL_Quit, ejecuta onExit().En el otro caso, ejecuta onClick(),
	//pasando como argumentos la posición del ratón.
	void onExit();
};

