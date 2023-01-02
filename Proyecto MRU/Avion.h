#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;
class Avion
{
private:
	Texture* texture_avion;
	Sprite* sprite_avion;
	Vector2f velocidad;
	Vector2f aceleracion;
	Clock* reloj;
	float tiempo1 = 0.0f;
	
public:
	Avion();
	Sprite get_sprite_avion() { return *sprite_avion; }
	void actualizar();
	void de_lado_a_lado();
	float get_velocidad_avion_X() { return velocidad.x; }
	bool posision_disparo();
};