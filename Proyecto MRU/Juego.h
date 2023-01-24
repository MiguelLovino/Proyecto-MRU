#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Caballero.h"
#include "Pelota.h"
#include "pantalla.h"
#include "Mira.h"
#include "Avion.h"
#include <string>
#include <vector>
#include "Torreta.h"
#include "Proyectiles.h"
#include "Menu.h"

using namespace sf;
using namespace std;
class Juego {

private:
	RenderWindow* pWnd;
	void ProcessEvent(Event& evt);
	void DrawGame();
	void UpdateGame();
	void ProcessCollisions();
	Caballero *jugador;
	vector <Pelota*> pelotas;
	int pantalla_ancho = 800;
	int pantalla_alto = 600;
	int vida = 500;
	int fase = 1;
	int puntaje = 0;
	bool Game_over = false;

	//tiempos
	Clock* reloj;
	Time* tiempo1;
	float tiempo2 = 0;
	float tiempo3 = 1.50f;
	float tiempo4 = 0.50;
	Vector2f mouserposition;
	Vector2f bombaposition;
	Vector2f proyectil_pos_de_disparo;
	/***********************************************/
	Pantalla* pantalla_fondo;
	Avion* bombardero;
	Mira* Mira_cursor;
	Torreta* torretaaire;
	Proyectil* proyectil_torretaaire;
	vector<Proyectil*> proyectil_torretaDOS;
	void disparar_proyectiles(Vector2f pos_bocacha, float rotacion);
	Menu* menus;

public:
	
	
	Juego(int alto, int ancho, string titulo);
	~Juego();
	void Go();
	void prueba_en_consola();
	void resetear_juego();
};