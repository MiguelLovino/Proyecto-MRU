#include "Avion.h"

Avion::Avion()
{
	
	//reloj
	reloj = new Clock;
	
	//texturas y sprite;
	texture_avion = new Texture;
	texture_avion->loadFromFile("recursos/avion.png");

	sprite_avion = new Sprite;
	sprite_avion->setTexture(*texture_avion);

	sprite_avion->setPosition(800 , 0);
	//sprite_avion->setScale(5, 5);



	//vectores de movimiento

	velocidad.x = -1;
	velocidad.y = 0;

	aceleracion.x = 0;
	aceleracion.y = 0;

}

void Avion::actualizar()
{
	//tiempo1 = reloj->getElapsedTime().asSeconds();

	tiempo1 = 3.20f;

	//MRUV

	// v = a * t;

	//velocidad.x = aceleracion.x * tiempo1;
	//velocidad.y = aceleracion.y * tiempo1;

	//MRU

	//p = pa + v * t

	sprite_avion->setPosition(sprite_avion->getPosition() + (velocidad*tiempo1) );
	de_lado_a_lado();
	posision_disparo();
}

void Avion::de_lado_a_lado()
{
		//cout << sprite_avion->getPosition().x << endl;

	if (sprite_avion->getPosition().x <= 0 - sprite_avion->getGlobalBounds().width)
	{
		velocidad.x = 1;
		sprite_avion->setScale(-1, 1); //dar vuelta la imagen
	}
	if (sprite_avion->getPosition().x >= 800 + sprite_avion->getGlobalBounds().width)
	{
		velocidad.x = -1;
		sprite_avion->setScale(1, 1);
	}
	

}

bool Avion::posision_disparo()
{
	if (sprite_avion->getPosition().x > 0 && sprite_avion->getPosition().x < 800)
	{
		//cout << "esta en posicion de disparo" << endl;
		return true;
	}
	else
	{
		return false;
	}






}