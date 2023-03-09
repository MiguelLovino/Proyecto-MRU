#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Proyectiles.h"
#include "Granada.h"
#include <vector>

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
	float tiempo_delta = 0;
	bool mira_derecha = true;
	bool mira_izquierda = true;
	RectangleShape* Cuerpo_colicion;
	//vector <Proyectil*> disparos;
	float retardo_bala = 0.50f;
	float retardo_granda = 1.5f;

public:
	Jugador(int ancho, int alto);
	~Jugador();
	Sprite get_sprite() { return *jugador_sprite; }
	void saltar();
	void mov_derecha();
	void mov_izquierda();
	void actualizar(Vector2f mira, RectangleShape limiteD, RectangleShape limiteI, int ancho, int alto);
	void dar_vuelta(Vector2f mira);
	void reset(int ancho);
	void reprodicir_dolor() { recibir_daño_sound.play(); }
	RectangleShape get_colider() { return *Cuerpo_colicion; }
	void disparar_proyectiles(Vector2f pos_bocacha, Vector2f mouserposition, float &tiempo2, float &tiempo4, vector <Proyectil*>& disparos);
	void tirar_granadas(Vector2f pos_bocacha, Vector2f mouserposition, float& tiempo2, float& tiempo4, vector <Granada*>& granada);
}; 