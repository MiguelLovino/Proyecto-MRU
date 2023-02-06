#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Jugador {

private:
	Texture* jugador_txt;
	Sprite* jugador_sprite;
	Vector2f velocidad;
	Vector2f aceleracion;
	Clock Reloj;
	float tiempo_delta;

public:
	Jugador();
	~Jugador();
	Sprite get_sprite() { return *jugador_sprite; }
	void saltar();
	void mov_derecha();
	void mov_izquierda();
	void actualizar(Vector2f mira);
	void dar_vuelta(Vector2f mira);
};