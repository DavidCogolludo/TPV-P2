#include "GlobosPG.h"
#include "TexturasSDL.h"
#include "SDL.h"  // Para utilizar SDL
#include "SDL_image.h"
#include <iostream>  // la consola: cin / cout
using namespace std; // Para cualificar automaticamente con std:: los identificadores de la librería estandar 
//----------------------------------------------------------------------------------------------------------------------

GlobosPG::GlobosPG(TexturasSDL* img, int px, int py)
{
	visible = true;
	deshinchado = false;
	pinchado = false;
	puntos = 1;
	pTextura = img;
	x = px;
	y = py;
	rect.x = px;
	rect.y = py;
	rect.w = 50; // pTextura->getW();
	rect.h = 50; // pTextura->getH();
}


GlobosPG::~GlobosPG()
{
}
//-----------------------------------------------------------------------------------------------------------------------------------
bool GlobosPG::dameEstado(){
	return pinchado;
}
int GlobosPG::damePuntos(){
	return puntos;
}
int GlobosPG::damePosX(){
	return rect.x;
}
int GlobosPG::damePosY(){
	return rect.y;
}
//-----------------------------------------------------------------------------------------------------------------------------------
void GlobosPG::draw(SDL_Renderer* prenderer){
	//SDL_RenderCopy(pRender, pTextura, &fRect, &winRect);
	if (visible && !pinchado) pTextura->draw(prenderer,rect);
}
//-------------------------------------------------------------------------------------------------------------------

bool GlobosPG::onClick(int pmx, int pmy){
	bool encontrado = false;
	int xMax = x + pTextura->getW();
	int yMax = y + pTextura->getH();
	if (visible && !pinchado && pmx < xMax && pmx > x && pmy < yMax && pmy > y){
		//cout << "Has obtenido puntos";
		pinchado = true;
		encontrado = true;
	}
	return encontrado;
}
//--------------------------------------------------------------------------------------------------------------------------

bool GlobosPG::update(){
	if (rand() % 100 < PVIS) visible = true; 
	else visible = false;

	if (rand() % 100 < PDES){
		deshinchado = true;
		puntos += AP;
		rect.w -= DT;
		rect.h -= DT;
	}

	if (rect.w == 0)
		pinchado = true;
	return false;
}