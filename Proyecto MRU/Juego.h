#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include "Pelota.h"
#include "pantalla.h"
#include "Mira.h"
#include "Avion.h"
#include <string>
#include <vector>
#include "Proyectiles.h"
#include "Menu.h"
#include "Jugador.h"
#include "Barril.h"

using namespace sf;
using namespace std;
class Juego {

private:
	RenderWindow* pWnd;
	void ProcessEvent(Event& evt);
	void DrawGame();
	void UpdateGame();
	void ProcessCollisions();
	vector <Pelota*> pelotas;
	vector <Barril*> barril_explosivo;
	int pantalla_ancho = 1270;
	int pantalla_alto = 720;
	RectangleShape limite_ancho_izquierda;
	RectangleShape limite_ancho_derecha;
	int vida = 50000;
	int fase = 1;
	int puntaje = 0;
	int puntaje_fina = 0;
	int aceleracion_bomba = 15;
	float velocidad_barril = 5;
	bool Game_over = false;
	int acercamiento = 0;
	Event evt;
	//tiempos
	Clock* reloj;
	Time* tiempo1;
	float tiempo2 = 0;
	float tiempo3 = 1.50f;
	float tiempo4 = 0.50;
	float tiempo_barril_explosivo = 1;
	Vector2f mouserposition;
	Vector2f bombaposition;
	Vector2f proyectil_pos_de_disparo;
	/***********************************************/
	Pantalla* pantalla_fondo;
	Avion* bombardero;
	Vector2f zona_disparoRECTrecsize;
	int cant_bombas = 0;
	int max_bombas = 3;
	int cant_barriles = 0;
	int max_barriles = 2;
	Mira* Mira_cursor;
	Jugador* soldado;
	vector<Proyectil*> proyectil_torretaDOS;
	void disparar_proyectiles(Vector2f pos_bocacha, float rotacion);
	bool bombas_en_pantalla();
	void velocidad_de_las_bombas();
	Menu* menus;
	//rect para despues borrar para soldado y bombardero
	sf::RectangleShape* soldadoRECT;
	RectangleShape* avionRECT;
	RectangleShape* zona_disparoRECT;
	//sonidos
	SoundBuffer buffer_explo;
	Sound sound_explo;
	SoundBuffer buffer_vida_menos;
	Sound sound_vida_menos;

public:
	Juego(int alto, int ancho, string titulo);
	~Juego();
	void Go();
	void prueba_en_consola();
	void resetear_juego();
};