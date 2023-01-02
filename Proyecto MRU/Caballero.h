#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Caballero {


private:
	Texture* caballero_texture;
	Sprite* caballero_sprite;
	Vector2f velocidad;
	Vector2f aceleracion;
	Clock* reloj;
	Time* tiempo1;
	float tiempo2 = 0;


public:
	Caballero();
	Sprite get_caballero_sprite() { return *caballero_sprite; }
	void actualizar_pos(float delta_t);
	void set_velocidad_x(float vel);
	void set_aceleracion_Yy(float acel);
};