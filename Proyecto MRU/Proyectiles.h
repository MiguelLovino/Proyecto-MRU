#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Mira.h"
#include "Jugador.h"
using namespace sf;
using namespace std;

class Proyectil
{
private:

	Texture* texture_proyectil;
	Sprite* sprite_proyectil;
	Vector2f velocidad, aceleracion;
	Clock* reloj;
	float tiempo1 = 0;
	float tiempo2 = 0;
	float tiempodelta = 0;
	Vector2f direction;
	float longitud;
	float velocidad_proyectil = 500;
public:
	Proyectil(Vector2f pos_bocacha, float rotacion, Vector2f mira, Jugador* soldado);
	~Proyectil();
	Sprite get_sprite() { return *sprite_proyectil; }
	void actualizar(float rotacion);
	FloatRect get_bounds() { return sprite_proyectil->getGlobalBounds(); }
};