#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Mira.h"
#include "cmath"

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
	float longitud = 0;
	float velocidad_proyectil = 500;
	SoundBuffer buffer_proyectil;
	Sound sound_proyectil;

public:
	Proyectil(Vector2f pos_bocacha, Vector2f mira);
	~Proyectil();
	Sprite get_sprite() { return *sprite_proyectil; }
	void actualizar();
	FloatRect get_bounds() { return sprite_proyectil->getGlobalBounds(); }
};