#include "Jugador.h"

Jugador::Jugador()
{
	jugador_txt = new Texture;
	jugador_txt->loadFromFile("recursos/jugador.png");
	jugador_sprite = new Sprite;
	jugador_sprite->setTexture(*jugador_txt);
	jugador_sprite->setPosition(400, 480);
	jugador_sprite->setScale(1.5,1.5);
	velocidad.x = 150;
	velocidad.y = 150;
	aceleracion.x = 5;
	aceleracion.y = 5;
}

Jugador::~Jugador()
{
	delete jugador_txt;
	delete jugador_sprite;
}

void Jugador::saltar()
{
}

void Jugador::mov_derecha()
{
	jugador_sprite->move(velocidad.x * tiempo_delta,0);
}

void Jugador::mov_izquierda()
{
	jugador_sprite->move(velocidad.x * -1 * tiempo_delta, 0);
}

void Jugador::actualizar()
{
	//actualizo el tiempol
	tiempo_delta = Reloj.restart().asSeconds();
}
