#include  "Bomba.h"

Bomba::Bomba(Vector2f mouse_pos, float velocidad_avion, int aceleracion_bomba)
{

	reloj_interno = new Clock;
	bomba_texture = new Texture;
	bomba_texture->loadFromFile("recursos/bomba.png");

	bomba_sprite = new Sprite;
	bomba_sprite->setTexture(*bomba_texture);
	bomba_sprite->setScale(0.3f, 0.3f);

	//pos inicial
	bomba_sprite->setPosition(mouse_pos);

	//velocidad
	velocidad.x = RandomNumber(-50, 50);// <- random flotante entre negativo y positivo.
	velocidad.y = 25;
	//aceleracion
	aceleracion.x = 15;
	aceleracion.y = aceleracion_bomba;

	if (velocidad_avion == -1)
	{
		bomba_sprite->setRotation(velocidad_avion - 34); //ROTO EL SPRITE

	}
	if (velocidad_avion == 1)
	{

		bomba_sprite->setRotation(velocidad_avion + 34);

	}

}

Bomba::~Bomba()
{
	delete reloj_interno;
	delete bomba_texture;
	delete bomba_sprite;
}

void Bomba::actualizar(RectangleShape limite_D, RectangleShape limite_i)
{

	tiempo_delta = reloj_interno->restart().asSeconds();
	velocidad.x += aceleracion.x * tiempo_delta;
	velocidad.y += aceleracion.y * tiempo_delta;
	bomba_sprite->setPosition(bomba_sprite->getPosition().x + velocidad.x * tiempo_delta, bomba_sprite->getPosition().y + velocidad.y * tiempo_delta);
	rebote(limite_D, limite_i);

}

void Bomba::rebote(RectangleShape limite_D, RectangleShape limite_i)
{

	if (bomba_sprite->getGlobalBounds().intersects(limite_D.getGlobalBounds()) ||
		bomba_sprite->getGlobalBounds().intersects(limite_i.getGlobalBounds())) // SI TOCA EL SUELO
	{
		velocidad.x *= -1;
	}

}






