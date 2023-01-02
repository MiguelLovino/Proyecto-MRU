#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
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

public:
	Proyectil(Vector2f pos_bocacha, float rotacion);
	Sprite get_sprite() { return *sprite_proyectil; }
	void actualizar(float rotacion);
	FloatRect get_bounds() { return sprite_proyectil->getGlobalBounds(); }
};