#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
using namespace sf;
using namespace std;
class Pelota
{

private:

	Texture* pelota_texture;
	Sprite* pelote_sprite;
	Vector2f velocidad, aceleracion;
	Clock* reloj_interno;
	float tiempo_interno = 0.0f;
	float tiempo_delta = 0;
	int random = 1;
	int random_despawn = rand() % 5 + 2;

public:
	Pelota(Vector2f mouse_pos, float velocidad_avion, int aceleracion_bomba);
	~Pelota();
	void set_aceleracion() { aceleracion.y += 500; }
	void actualizar(RectangleShape limite_D, RectangleShape limite_i);
	void rebote(RectangleShape limite_D, RectangleShape limite_i);
	float get_tiempor_interno() { return tiempo_interno; }
	Sprite get_sprite() { return *pelote_sprite; }
	float RandomNumber(float Min, float Max)
	{
		return ((float(rand()) / float(RAND_MAX)) * (Max - Min)) + Min;
	}
	int get_random_despawn() { return random_despawn; }

};