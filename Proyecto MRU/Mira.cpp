#include "Mira.h"

Mira::Mira()
{
	textura_mira = new Texture;
	textura_mira->loadFromFile("recursos/mira.png");

	sprite_mira = new Sprite;
	sprite_mira->setTexture(*textura_mira);
	
	sprite_mira->setOrigin(25,25);
	sprite_mira->setScale(0.75f, 0.75f);
}
