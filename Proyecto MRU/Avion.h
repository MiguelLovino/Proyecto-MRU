#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
	SoundBuffer buffer_avion;
	Sound sound_avion;
	bool rep_avion = true;
	bool rep_avion2 = true;
	RectangleShape avion_en_pantalla;

public:
	Avion();
	Sprite get_sprite_avion() { return *sprite_avion; }
	void actualizar(RectangleShape zona_disparo);
	void de_lado_a_lado();
	void reset_avion();
	float get_velocidad_avion_X() { return velocidad.x; }
	bool posision_disparo(RectangleShape zona_disparo);
	void reproducir_sonido_avion();
};