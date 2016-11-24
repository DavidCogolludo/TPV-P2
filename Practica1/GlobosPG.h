#include "SDL.h"
#include "TexturasSDL.h"
#pragma once
class GlobosPG
{
private:
	bool pinchado;
	bool visible, deshinchado;
	int puntos;
	int x, y;
	static const int AP = 5, DT = 5;
	SDL_Rect rect;
	static const int PVIS = 70;
	static const int PDES = 30;
public:
	GlobosPG(TexturasSDL* img, int px, int py);
	~GlobosPG();

	TexturasSDL* pTextura;

	bool dameEstado();
	int damePuntos();
	int damePosX();
	int damePosY();
	void draw(SDL_Renderer* prenderer);				// : Si procede dibuja la textura.
	bool onClick(int pmx, int pmy);				// : Si procede comprueba si ha sido dado.En caso positivo
	//actualiza su estado y devuelve true.

	bool update();							   // : Si procede actualiza su estado.Devuelve true si como resultado el globo
	//desaparece definitivamente(queda desinflado).

};

