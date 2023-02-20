#include "Mira.h"

Mira::Mira()
{
	textura_mira = new Texture;
	textura_mira->loadFromFile("recursos/mira.png");

	sprite_mira = new Sprite;
	sprite_mira->setTexture(*textura_mira);

	sprite_mira->setOrigin(textura_mira->getSize().x / 2, textura_mira->getSize().y / 2);
	//sprite_mira->setScale(0.75f, 0.75f);
}
