#include "items.h"

items::items(string path, int ancho)
{
	item_txt = new Texture;
	item_txt->loadFromFile(path);
	item_spr = new Sprite;
	item_spr->setTexture(*item_txt);
	reloj_principal = new Clock;
	velocidad.x = 0;
	velocidad.y = 75;
	aceleracion.x = 0;
	aceleracion.y = 0;
	item_spr->setPosition(rand() % ancho + 0, 0 - item_spr->getGlobalBounds().height);

}


void items::actualizar()
{
	//agregar que inicie con el inicio de la pantalla del juego
	tiempo_delta = reloj_principal->restart().asSeconds();
	nueva_pos.y = item_spr->getPosition().y + velocidad.y * tiempo_delta;
	item_spr->setPosition(item_spr->getPosition().x, nueva_pos.y);
	
}

void items::colision(int alto)
{

	//colision con el piso
	if (item_spr->getPosition().y >= (alto - item_spr->getGlobalBounds().height))
	{
		int x = item_spr->getPosition().x;
		int y = alto - item_spr->getGlobalBounds().height;
		item_spr->setPosition(x, y);
	}
	
}

items::~items()
{
	//destructor
	delete item_spr;
	delete item_txt;
	delete reloj_principal;

}