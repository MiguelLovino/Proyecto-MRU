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
	SoundBuffer recibir_daño_buffer;
	Sound recibir_daño_sound;
	float tiempo_delta;
	bool mira_derecha = true;
	bool mira_izquierda = true;
	RectangleShape* Cuerpo_colicion;
public:
	Jugador();
	~Jugador();
	Sprite get_sprite() { return *jugador_sprite; }
	void saltar();
	void mov_derecha();
	void mov_izquierda();
	void actualizar(Vector2f mira, RectangleShape limiteD, RectangleShape limiteI);
	void dar_vuelta(Vector2f mira);
	void reset();
	void reprodicir_dolor() { recibir_daño_sound.play(); }
	RectangleShape get_colider() { return *Cuerpo_colicion; }
};