#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Proyectiles.h"
#include <vector>

using namespace sf;
using namespace std;

class Torreta
{
private:
	Texture* texture_torreta;
	Sprite sprite_torreta;
	vector<Proyectil*> proyectil_torreta;
	Clock* reloj;
	float tiempo1 = 0.0f;
	float tiempo2 = 0.0f;
public:
	Torreta();
	Sprite get_sprite_torreta() { return sprite_torreta; }
	vector<Proyectil*> get_proyectil_sprite() { return proyectil_torreta; }
	void rota_derecha();
	void rota_izquierda();
	void actualizar(RenderWindow* pWnd);
	void disparar_proyectiles(Vector2f pos_bocacha, float rotacion);

};