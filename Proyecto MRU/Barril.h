#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

class Barril
{
private:
	CircleShape* barril_explosivo;
	Texture* barril_txt;
	float tiempo_delta = 0;
	float velocidad_x = 50;
	float aceleracion_x = 15;
	int pos_inicial = rand() % 2;
	Clock Reloj;

public:
	Barril(float vel, int ancho, int alto);
	~Barril();
	CircleShape get_sprite() { return *barril_explosivo; }
	void actualizar();
};