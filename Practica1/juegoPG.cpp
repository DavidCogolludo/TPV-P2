#include "juegoPG.h"
#include "GlobosPG.h"
#include "TexturasSDL.h"
#include "SDL.h"  // Para utilizar SDL
#include "SDL_image.h"
#include <iostream>  // la consola: cin / cout
#include <vector>
#include <string>
#include "SDL_mixer.h"
#include "SDL_ttf.h"
using namespace std; // Para cualificar automaticamente con std:: los identificadores de la librería estandar 

//---------------------------------------------------------------------------------------------------------------
juegoPG::juegoPG()
{
	srand(1);
	std::string str = "Textura";
	pWin = nullptr;  	//The window we'll be rendering to
	pRender = nullptr;   //The renderer by the window
	fondo.h = SCREEN_HEIGHT;
	fondo.w = SCREEN_WIDTH;
	fondo.x = fondo.y = 0;
	pause = false;


	initSDL(pWin, pRender);



	//contGlobos = 20;
	contGlobos = 2;
	globosTot = contGlobos;
	contPuntos = 0;
	vecTexturas.resize(2);
	vecGlobos.resize(contGlobos);
	//Cargamos las texturas
	for (unsigned int i = 0; i < vecTexturas.size(); i++){
		vecTexturas[i] = new TexturasSDL;
		vecTexturas[i]->load(pRender, "..\\bmps\\" + (str += to_string(i + 1)) + ".png");
		str = "Textura";
	}
	//Cargamos la fuente
	fuente = new TexturasSDL;
	fuente->loadFuente("..\\bmps\\font.ttf", 200);

	//Cargamos los globos
	for (unsigned int i = 0; i < vecGlobos.size(); i++){
		//vecGlobos[i] = new GlobosPG(vecTexturas[1], rand() % (SCREEN_WIDTH - 25), rand() % (SCREEN_HEIGHT - 50));
		//25 es la mitad de lo que ocupa la textura globo
		vecGlobos[i] = new GlobosPG(vecTexturas[1], (SCREEN_WIDTH / 2) - (25 * i), (SCREEN_HEIGHT / 2) - (25 * i));
	}
	//Cargamos la música y los Fx
	sound = new Sound;
	sound->loadMusic("..\\sounds\\music.mp3");
	sound->loadFX("..\\sounds\\balloon.wav");
	//Inicializamos el color para el texto
	colorFuente.r = 130;
	colorFuente.g = 214;
	colorFuente.b = 28;

	pTexture = nullptr;    //The image we will load and show on the screen
	pColor = nullptr;
	error = exit = false;
	gameOver = false;


}


juegoPG::~juegoPG()
{
	for (unsigned int i = 0; i < vecGlobos.size(); i++)
		delete vecGlobos[i];
	for (unsigned int i = 0; i < vecTexturas.size(); i++)
		delete vecTexturas[i];

	delete sound;
	delete fuente;
	vecGlobos.clear();
	vecTexturas.clear();
	
}
//--------------------------------------------------------------------------------------------------------------------
void juegoPG::run(){
	if (!error) {
		Uint32 msUpdate = 500;
		Mix_PlayMusic(sound->pMusic, -1);
		std::cout << "PLAY \n";
		Uint32 lastUpdate = SDL_GetTicks();
		render();
		handle_event();
		while (!exit && !gameOver) {
			if (!pause){
				if (SDL_GetTicks() - lastUpdate >= msUpdate) { // while(elapsed >= MSxUpdate)
					update();
					lastUpdate = SDL_GetTicks();
				}
				render();
			}
			exit = handle_event();
		}
		if (exit) cout << "EXIT \n";
		else {
			string s = "Has obtenido " + to_string(contPuntos) + " puntos";
			cout << s + "\n";
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SCORE", s.c_str(), nullptr);
		}
		closeSDL(pWin, pRender);
		SDL_Delay(1000); //cin.get();

	}
}
//----------------------------------------------------------------------------------------------------------------------
bool juegoPG::handle_event(){
	if (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT){
			onExit();
			return true;
		}
		else if (e.type == SDL_KEYUP){
			if (e.key.keysym.sym == SDLK_p && !pause){
				pause = true;
			}
			else if (e.key.keysym.sym == SDLK_p && pause){
				pause = false;
			}
		}
		else if (e.type == SDL_MOUSEBUTTONUP) {
			if (e.button.button == SDL_BUTTON_LEFT) {
				//cout << "CLICK";
				onClick(e.button.x, e.button.y);
			}
		}
	}
	return false;
}

void juegoPG::onClick(int pmx, int pmy){
	bool encontrado = false;
	unsigned int it = vecGlobos.size() - 1;
	while (!encontrado && it >= 0){
		encontrado = vecGlobos[it]->onClick(pmx, pmy);
		it--;
	}
	if (encontrado){
		Mix_PlayChannel(-1, sound->pFx, 0);
		contPuntos += vecGlobos[it + 1]->damePuntos();
		//cout << contPuntos;

	}

}

void juegoPG::update(){
	int cont = 0;
	for (unsigned int i = 0; i < vecGlobos.size(); i++){
		vecGlobos[i]->update();
		if (vecGlobos[i]->dameEstado())cont++;
	}
	contGlobos = cont;
	//cout << contGlobos;
	if (contGlobos == globosTot)
		gameOver = true;
}
//---------------------------------------------------------------------------------------------------------------------
bool juegoPG::initSDL(SDL_Window* &pWindow, SDL_Renderer* &pRenderer) {

	bool success = true; //Initialization flag

	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "SDL could not initialize! \nSDL_Error: " << SDL_GetError() << '\n';
		success = false;
	}
	else {
		//Create window: SDL_CreateWindow("SDL Hello World", posX, posY, width, height, SDL_WINDOW_SHOWN);
		pWindow = SDL_CreateWindow("Ghost balloons", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (pWindow == nullptr){
			cout << "Window could not be created! \nSDL_Error: " << SDL_GetError() << '\n';
			success = false;
		}
		else {
			//Get window surface:
			pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
			SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255); //Set background color to black 
			if (pRenderer == nullptr){
				cout << "Renderer could not be created! \nSDL_Error: " << SDL_GetError() << '\n';
				success = false;
			}
		}
	}

	TTF_Init();			//Inicializamos la libreria  de fuentes
	Mix_Init(27);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	return success;
}
//-----------------------------------------------------------------------------------------------------------------

void juegoPG::closeSDL(SDL_Window* & pWindow, SDL_Renderer* & pRenderer) {
	Mix_FreeChunk(sound->pFx);
	Mix_FreeMusic(sound->pMusic);

	Mix_Quit();
	TTF_Quit();
	SDL_DestroyRenderer(pRenderer);
	pRenderer = nullptr;

	SDL_DestroyWindow(pWindow);
	pWindow = nullptr;

	SDL_Quit();
}
//--------------------------------------------------------------------------------------------------------------------------

void juegoPG::render() const {

	//Clear the window to background color 
	SDL_RenderClear(pRender);

	//Draw background
	vecTexturas[0]->draw(pRender, fondo);
	//SDL_RenderCopy(pRender, vecTexturas[0]->pTexture, nullptr, nullptr);
	for (unsigned int i = 0; i < vecGlobos.size(); i++)
		vecGlobos[i]->draw(pRender);

	// Draw marcador
	fuente->loadFromText(pRender, to_string(contPuntos), colorFuente);
	fuente->draw(pRender, fuente->font.recFont);
	//hacer for para cada globo

	//Show the window
	SDL_RenderPresent(pRender);
}
void juegoPG::onExit(){

}