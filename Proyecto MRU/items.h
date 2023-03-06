#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Jugador.h"

using namespace std;
using namespace sf;

class items
{
private:
	Sprite* item_spr;
	Texture* item_txt;
	Vector2f velocidad;
	Vector2f aceleracion;
	Vector2f nueva_pos;
	Clock* reloj_principal;
	float tiempo_delta = 0;

public:
	items(string path, int ancho);
	~items();
	Sprite get_sprite() { return *item_spr; }
	void actualizar();
	void colision(int alto);
};