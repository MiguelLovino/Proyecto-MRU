#include "Jugador.h"

Jugador::Jugador(int ancho, int alto)
{
	jugador_txt = new Texture;
	jugador_txt->loadFromFile("recursos/soldado2.png");
	jugador_sprite = new Sprite;
	Cuerpo_colicion = new RectangleShape;
	jugador_sprite->setTexture(*jugador_txt);
	jugador_sprite->setPosition(ancho / 2, alto - 40);
	//jugador_sprite->setScale(2.5, 2.5);
	Cuerpo_colicion->setPosition(jugador_sprite->getPosition());
	Cuerpo_colicion->setSize((Vector2f::Vector2(jugador_sprite->getTexture()->getSize().x - 10 * 2.5, jugador_sprite->getTexture()->getSize().y * 2.5)));
	Cuerpo_colicion->setFillColor(Color::Red);
	velocidad.x = 150;
	velocidad.y = -7;
	aceleracion.x = 5;
	aceleracion.y = 10;
	recibir_da�o_buffer.loadFromFile("recursos/sonido/dolor.ogg");
	recibir_da�o_sound.setBuffer(recibir_da�o_buffer);

}

Jugador::~Jugador()
{
	delete jugador_txt;
	delete jugador_sprite;
}

void Jugador::saltar()
{

	jugador_sprite->move(0, velocidad.y * tiempo_delta);

}

void Jugador::mov_derecha()
{
	jugador_sprite->move(velocidad.x * tiempo_delta, 0);
}

void Jugador::mov_izquierda()
{
	jugador_sprite->move(velocidad.x * -1 * tiempo_delta, 0);
}

void Jugador::actualizar(Vector2f mira, RectangleShape limiteD, RectangleShape limiteI, int ancho, int alto)
{
	//reposicion del colider
	if (mira_derecha == true)
	{
		Cuerpo_colicion->setSize((Vector2f::Vector2(jugador_sprite->getTexture()->getSize().x  - 30, jugador_sprite->getTexture()->getSize().y )));
		Cuerpo_colicion->setPosition(jugador_sprite->getPosition().x + 13, jugador_sprite->getPosition().y);
	}
	if (mira_izquierda == true)
	{
		Cuerpo_colicion->setSize((Vector2f::Vector2(jugador_sprite->getTexture()->getSize().x  + 30 * -1, jugador_sprite->getTexture()->getSize().y )));
		Cuerpo_colicion->setPosition(jugador_sprite->getPosition().x - 30, jugador_sprite->getPosition().y);
	}
	//actualizo el colider
	//Cuerpo_colicion->setPosition(jugador_sprite->getPosition());

	//actualizo el tiempol
	tiempo_delta = Reloj.restart().asSeconds();
	//se debe poner los limites para que no caiga fuera del mapa.
	//actualizar gravedad
	if (jugador_sprite->getPosition().y > alto - jugador_sprite->getGlobalBounds().height)
	{
		jugador_sprite->setPosition(jugador_sprite->getPosition().x, alto - jugador_sprite->getGlobalBounds().height);
		velocidad.y = -7;
	}
	if (jugador_sprite->getPosition().y < alto - jugador_sprite->getGlobalBounds().height)
	{
		velocidad.y += aceleracion.y * tiempo_delta; // controlar en futuro (GRAVEDAD DEL PERSONAJE/ESENARIO)
		jugador_sprite->move(0, velocidad.y);

	}
	dar_vuelta(mira);
	// colicion lado derecho 
	if (jugador_sprite->getGlobalBounds().intersects(limiteD.getGlobalBounds()))
	{
		if (mira_derecha == true)
		{

			jugador_sprite->setPosition(limiteD.getPosition().x - jugador_sprite->getGlobalBounds().width, jugador_sprite->getPosition().y);

		}
		if (mira_izquierda == true)
		{

			jugador_sprite->setPosition(limiteD.getPosition().x, jugador_sprite->getPosition().y);

		}
	}
	// colicion lado izquierdo
	if (jugador_sprite->getGlobalBounds().intersects(limiteI.getGlobalBounds()))
	{
		if (mira_derecha == true)
		{

			jugador_sprite->setPosition(limiteI.getPosition().x - jugador_sprite->getGlobalBounds().width, jugador_sprite->getPosition().y);

		}
		if (mira_izquierda == true)
		{

			jugador_sprite->setPosition(limiteI.getPosition().x + jugador_sprite->getGlobalBounds().width, jugador_sprite->getPosition().y);

		}
	}


	if (jugador_sprite->getPosition().x < 0)
	{
		jugador_sprite->setPosition(0, jugador_sprite->getPosition().y);
	}

}

void Jugador::dar_vuelta(Vector2f mira)
{
	if (mira.x > jugador_sprite->getPosition().x)
	{

		jugador_sprite->setScale(1, 1);

		if (mira_izquierda == true)
		{
			jugador_sprite->setPosition(jugador_sprite->getPosition().x - jugador_sprite->getGlobalBounds().width, jugador_sprite->getPosition().y);

			mira_izquierda = false;
			mira_derecha = true;
		}

	}
	else
	{

		jugador_sprite->setScale(1 * -1, 1);

		if (mira_derecha == true)
		{
			jugador_sprite->setPosition(jugador_sprite->getPosition().x + jugador_sprite->getGlobalBounds().width, jugador_sprite->getPosition().y);
			mira_derecha = false;
			mira_izquierda = true;
		}

	}
}

void Jugador::reset(int ancho)
{
	jugador_sprite->setPosition(ancho / 2, jugador_sprite->getPosition().y);
}
