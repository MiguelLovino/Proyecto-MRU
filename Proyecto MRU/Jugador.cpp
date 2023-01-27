#include "Jugador.h"

Jugador::Jugador()
{
	jugador_txt = new Texture;
	jugador_txt->loadFromFile("recursos/jugador.png");
	jugador_sprite = new Sprite;
	jugador_sprite->setTexture(*jugador_txt);
	jugador_sprite->setPosition(400, 480);
	jugador_sprite->setScale(1.5,1.5);
	velocidad.x = 300;
	velocidad.y = 2;
	aceleracion.x = 5;
	aceleracion.y = 10;
}

Jugador::~Jugador()
{
	delete jugador_txt;
	delete jugador_sprite;
}

void Jugador::saltar()
{
	//movimiento rectilineo uniforme variado CONTROLAR
	//solo debe saltar si esta tocando el suelo
	if (jugador_sprite->getPosition().y >= 480)
	{
	velocidad.y = 5000;
	jugador_sprite->move(0, velocidad.y * tiempo_delta*-1);
	velocidad.y = 2;
	}
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
	//se debe poner los limites para que no caiga fuera del mapa.
	//actualizar gravedad
	if (jugador_sprite->getPosition().y < 480)
	{
	velocidad.y += aceleracion.y * tiempo_delta; // controlar en futuro
	jugador_sprite->move(0, velocidad.y);

	}

}
