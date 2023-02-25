#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "Mira.h"
#include "pantalla.h"
using namespace sf;
using namespace std;

class Menu {
private:
	bool pantalla_menu = true;
	bool pantalla_juego = false;
	bool pantalla_fin = false;
	bool rep_reiniciar = true;
	bool rep_salir = true;
	bool rep_jugar = true;
	bool menu_loop = true;
	bool batalla_loop = false;
	Text* texto_inicio;
	Text* nombre_juego;
	Text* texto_juego_vida;
	Text* texto_juego_puntaje;
	Text* texto_juego_fase;
	Text* texto_fin;
	Text* texo_salir;
	Font* fuente_txt;
	Text* puntaje_final;
	SoundBuffer buffer_menu;
	Sound sonido_menu;
	SoundBuffer Buffer_menu_loop;
	Sound sonido_menu_loop;
	SoundBuffer batalla_buffer;
	Sound batalla_sound;
	Clock* reloj_principal;
	float tiempo_principal = 0;
	float retardo_principal = 0.1;
	bool escala_dinamica = true;
	Texture* vida_txt;
	Sprite* vida_spr[5];
	Texture tutorial_txt;
	Sprite tutorial_spr;


public:
	Menu();
	void inicio_actualizar(Mira* mira, Vector2f mouserposition, RenderWindow* pWnd, Event& eventito);
	void dibujar_inicio(RenderWindow* pWnd, Pantalla* pantalla_fondo, Mira* Mira_cursor);
	void fin_actualizar(Mira* mira, Vector2f mouserposition, RenderWindow* pWnd, Event& eventito, int puntaje);
	void dibujar_fin(RenderWindow* pWnd, Pantalla* pantalla_fondo, Mira* Mira_cursor);
	void menu_juego_actualizar(int vida, int puntaje, int fase);
	void dibujar_menu_juego(RenderWindow* pWnd, Pantalla* pantalla_fondo, Mira* Mira_cursor, int vida);
	bool get_pantalla_juego() { return pantalla_juego; }
	void set_pantalla_juego(bool valor) { pantalla_juego = valor; }
	void set_pantalla_fin(bool valor) { pantalla_fin = valor; }
	void animacion_nomre_juego(int ancho);
};

