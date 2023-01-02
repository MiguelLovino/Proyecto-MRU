#include "Caballero.h"

Caballero::Caballero()
{
	caballero_texture = new Texture;
	caballero_texture->loadFromFile("recursos/goku.png");

	caballero_sprite = new Sprite;
	caballero_sprite->setTexture(*caballero_texture);
	//caballero_sprite->setScale((float)0.3,(float)0.3);

	caballero_sprite->setPosition(0, 600 - caballero_sprite->getGlobalBounds().height);
	velocidad.x = 0;
	velocidad.y = 0;

	aceleracion.x = 0;
	aceleracion.y = 0;

	reloj = new Clock;
	tiempo1 = new Time;
	
}

void Caballero::actualizar_pos(float delta_t)

{
	delta_t = delta_t /= 10;
	velocidad.x += aceleracion.x * delta_t;
	velocidad.y  += aceleracion.y * delta_t; //gravedad


	caballero_sprite->setPosition(caballero_sprite->getPosition().x + velocidad.x * delta_t, caballero_sprite->getPosition().y + velocidad.y * delta_t);
	
	//pasar de un lado al otro.
	
	if (caballero_sprite->getPosition().x >= 800)
	{
		caballero_sprite->setPosition((0  - caballero_sprite->getGlobalBounds().width) , caballero_sprite->getPosition().y);
		// aumenta la velocidad cuando pasa de lado.
	
		
	}
	if (caballero_sprite->getPosition().x < (0 - caballero_sprite->getGlobalBounds().width))
	{
		caballero_sprite->setPosition(800 , caballero_sprite->getPosition().y);
		// aumenta la velocidad cuando pasa de lado.


	}
	
	/*  gravedad
 	if (caballero_sprite->getPosition().y >= (600 - caballero_sprite->getGlobalBounds().height))
	{
		caballero_sprite->setPosition(caballero_sprite->getPosition().x, 600 - caballero_sprite->getGlobalBounds().height);
	}
	
	*/




}

void Caballero::set_velocidad_x(float vel)
{
	aceleracion.x = vel;
}

void Caballero::set_aceleracion_Yy(float acel)
{
	aceleracion.y = acel;
}


