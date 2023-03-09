#include "Granada.h"

Granada::Granada(Vector2f pos_bocacha, Vector2f mira)
{
	granada_txt = new Texture;
	granada_txt->loadFromFile("recursos/granada_mru.png");

	granada_spr = new Sprite;
	granada_spr->setTexture(*granada_txt);

	reloj = new Clock();

	velocidad.x = 135;
	velocidad.y = -75;

	aceleracion.x = 0;
	aceleracion.y = 158.8f;

	granada_spr->setOrigin(granada_spr->getLocalBounds().width / 2, granada_spr->getLocalBounds().height / 2);
	granada_spr->setPosition(pos_bocacha);

	if (mira.x < pos_bocacha.x)
	{
		velocidad.x *= -1;
	}
}

void Granada::actualizar()
{
	//tiro oblicuo
	tiempo_delta = reloj->restart().asSeconds();
	//mru en eje X
	nueva_pos.x = granada_spr->getPosition().x + velocidad.x * tiempo_delta;
	//mruv en eje y
	velocidad.y += aceleracion.y * tiempo_delta;
	nueva_pos.y = granada_spr->getPosition().y + velocidad.y * tiempo_delta;
	//rotar
	granada_spr->rotate(5);
	granada_spr->setPosition(nueva_pos);
}
void Granada::dibujar()
{
}

Granada::~Granada()
{
	delete granada_txt;
	delete granada_spr;
	delete reloj;
}
