#include "Jugador.h"

Jugador::Jugador()
{
	jugador_txt = new Texture;
	jugador_txt->loadFromFile("recursos/soldado2.png");
	jugador_sprite = new Sprite;
	jugador_sprite->setTexture(*jugador_txt);
	jugador_sprite->setPosition(400, 480);
	jugador_sprite->setScale(2.5,2.5);
	velocidad.x = 150;
	velocidad.y = -7;
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

	jugador_sprite->move(0, velocidad.y * tiempo_delta);
	
}

void Jugador::mov_derecha()
{
	jugador_sprite->move(velocidad.x * tiempo_delta,0);
}

void Jugador::mov_izquierda()
{
	jugador_sprite->move(velocidad.x * -1 * tiempo_delta, 0);
}

void Jugador::actualizar(Vector2f mira, RectangleShape limiteD, RectangleShape limiteI)
{
	//actualizo el tiempol
	tiempo_delta = Reloj.restart().asSeconds();
	//se debe poner los limites para que no caiga fuera del mapa.
	//actualizar gravedad
	if (jugador_sprite->getPosition().y > 480)
	{
		jugador_sprite->setPosition(jugador_sprite->getPosition().x, 480);
		velocidad.y = -7; 
	}
	if (jugador_sprite->getPosition().y < 480)
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

			jugador_sprite->setPosition(limiteD.getPosition().x , jugador_sprite->getPosition().y);

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

	
	//cout << jugador_sprite->getPosition().y << endl;
	//cout << velocidad.y << endl;
}

void Jugador::dar_vuelta(Vector2f mira)
{
	if (mira.x > jugador_sprite->getPosition().x)
	{

		jugador_sprite->setScale(2.5, 2.5);
		
		if (mira_izquierda == true)
		{
			jugador_sprite->setPosition(jugador_sprite->getPosition().x - jugador_sprite->getGlobalBounds().width, jugador_sprite->getPosition().y);

			mira_izquierda = false;
			mira_derecha = true;
		}
		
	}
	else
	{

		jugador_sprite->setScale(2.5*-1, 2.5);
		
		if (mira_derecha == true)
		{
		jugador_sprite->setPosition(jugador_sprite->getPosition().x + jugador_sprite->getGlobalBounds().width, jugador_sprite->getPosition().y);
		mira_derecha = false;
		mira_izquierda = true;
		}
		
	}
}
