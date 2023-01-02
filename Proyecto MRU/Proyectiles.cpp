#include "Proyectiles.h"

Proyectil::Proyectil(Vector2f pos_bocacha, float rotacion)
{
	texture_proyectil = new Texture;
	texture_proyectil->loadFromFile("recursos/proyectil.png");
	sprite_proyectil = new Sprite;
	sprite_proyectil->setTexture(*texture_proyectil);
	sprite_proyectil->setPosition(pos_bocacha);
	sprite_proyectil->setRotation(rotacion);

	reloj = new Clock;


	velocidad.x = 0;
	velocidad.y = -10;
	
	if (rotacion > 180 && rotacion < 360)
	{
		//cout << "resta activa" << endl;
		aceleracion.x = (rotacion - 360) / 5;
	}
	else
	{

		aceleracion.x = rotacion / 4;
	}
	aceleracion.y = -5;
	
}

void Proyectil::actualizar(float rotacion)
{
	
	tiempodelta = reloj->getElapsedTime().asSeconds();
	//aceleracion.x = rotacion;
	
	velocidad.x = aceleracion.x * tiempodelta;
	
	// p = pa + v * t
	// v = v + a *t
	sprite_proyectil->setPosition(sprite_proyectil->getPosition().x + velocidad.x, sprite_proyectil->getPosition().y + velocidad.y * tiempodelta);

}