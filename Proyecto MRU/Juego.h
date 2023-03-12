#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include "Bomba.h"
#include "pantalla.h"
#include "Mira.h"
#include "Avion.h"
#include <string>
#include <vector>
#include "Proyectiles.h"
#include "Menu.h"
#include "Jugador.h"
#include "Barril.h"
#include "Granada.h"

using namespace sf;
using namespace std;
class Juego {

private:
	RenderWindow* pWnd;
	void ProcessEvent(Event& evt);
	void DrawGame();
	void UpdateGame();
	void ProcessCollisions();
	vector <Bomba*> bombas;
	vector <Barril*> barril_explosivo;
	vector <Granada*> granada_de_mano;
	int pantalla_ancho = 1270;
	int pantalla_alto = 720;
	RectangleShape limite_ancho_izquierda;
	RectangleShape limite_ancho_derecha;
	int vida = 5;
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
	float tiempo5 = 1.5f;
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
	vector<Proyectil*> proyectiles_en_juego;
	bool bombas_en_pantalla();
	void dificultad_de_juego();
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
	void resetear_juego();
	void prueba_en_consola();
	/////////////////////////////////////**********Funciones con plantillas************//////////////////////////////////////
	template <typename T>
	void dibujar_vectores(const vector<T>& vector)
	{
		if (vector.size() > 0)
		{
			for (int i = 0; i < vector.size(); i++)
			{
				pWnd->draw(vector[i]->get_sprite());
			}
		}
	}
	template <typename V>
	void borrar_vectores(const vector<V>& vector)
	{
		for (auto it = vector.begin(); it != vector.end(); it++)
		{
			delete* it;
		}
		
	}
	template <typename A, typename D>
	void colicion_de_objetos(vector<A>& vector1, vector<D>& vector2)
	{
		if (vector1.size() >= 0 && proyectiles_en_juego.size() >= 0)
		{

			for (int i = 0; i < vector1.size(); i++)
			{
				for (int j = 0; j < vector2.size(); j++)
				{
					if (vector2[j]->get_sprite().getGlobalBounds().intersects(vector1[i]->get_sprite().getGlobalBounds()))
					{
						puntaje += 10;
						delete vector2[j];
						vector2.erase(vector2.begin() + j);
						sound_explo.play();
						delete vector1[i];
						vector1.erase(vector1.begin() + i);
						break;
					}
				}
			}
		}
	}
	template <typename p>
	void colicion_de_objeto_con_pantalla(vector<p>& vector)
	{
		if (vector.size() > 0)
		{
			for (int i = 0; i < vector.size(); i++)
			{
				int y = (int)vector[i]->get_sprite().getPosition().y;
				int x = (int)vector[i]->get_sprite().getPosition().x;

				if (y < 50 || y > pantalla_alto || x < 0 || x > pantalla_ancho)
				{
					delete vector[i];
					vector.erase(vector.begin() + i);
					break;
				}
			}
		}
	}
	
};

