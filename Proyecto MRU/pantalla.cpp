#include "pantalla.h"

Pantalla::Pantalla()
{
	texture_fondoPantalla = new Texture;
	texture_fondoPantalla->loadFromFile("recursos/fondo.png");
	sprite_fondoPantalla = new Sprite;
	sprite_fondoPantalla->setTexture(*texture_fondoPantalla);
}