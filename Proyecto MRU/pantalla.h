#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Pantalla
{
private:
	Texture* texture_fondoPantalla;
	Sprite* sprite_fondoPantalla;
public:
	Pantalla();
	Sprite get_sprite_fondoPantalla() { return *sprite_fondoPantalla;}
};