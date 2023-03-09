#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Mira.h"


using namespace std;
using namespace sf;

class Granada
{
private:
	Sprite* granada_spr;
	Texture* granada_txt;
	Clock* reloj;
	Vector2f velocidad;
	Vector2f aceleracion;
	Vector2f nueva_pos;
	float reloj_principal;
	float tiempo_delta;
	float radio;
	float radianes;
	float pi = 3.14;

public:
	Granada(Vector2f pos_bocacha, Vector2f mira);
	~Granada();
	Sprite get_sprite() { return *granada_spr; }
	void dibujar();
	void actualizar();

};

