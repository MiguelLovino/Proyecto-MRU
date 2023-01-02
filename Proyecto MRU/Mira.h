#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Mira
{
private:

	Texture* textura_mira;
	Sprite* sprite_mira;

public:
	Mira();
	Sprite get_sprite() { return *sprite_mira; }
	void set_pos_mira(Vector2f mouserposition) { return sprite_mira->setPosition(mouserposition); }
};