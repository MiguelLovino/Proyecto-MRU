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
	Text *texto_inicio;
	Text *texto_juego;
	Text *texto_fin;
	Font *fuente_txt;
public:
	Menu();
	void inicio_actualizar(Mira *mira, Vector2f mouserposition);
	void dibujar_inicio(RenderWindow* pWnd, Pantalla* pantalla_fondo, Mira* Mira_cursor);
};

