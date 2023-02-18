#include "pantalla.h"

Pantalla::Pantalla(int ancho, int alto)
{
	texture_fondoPantalla = new Texture;
	texture_fondoPantalla->loadFromFile("recursos/fondo.png");
	sprite_fondoPantalla = new Sprite;
	sprite_fondoPantalla->setTexture(*texture_fondoPantalla);
	sprite_fondoPantalla->setScale(ancho / sprite_fondoPantalla->getGlobalBounds().width, alto / sprite_fondoPantalla->getGlobalBounds().height);
}