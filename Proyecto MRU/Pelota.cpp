#include  "Pelota.h"

Pelota::Pelota(Vector2f mouse_pos, float velocidad_avion, int aceleracion_bomba)
{

	reloj_interno = new Clock;
	pelota_texture = new Texture;
	pelota_texture->loadFromFile("recursos/bomba.png");

	pelote_sprite = new Sprite;
	pelote_sprite->setTexture(*pelota_texture);
	pelote_sprite->setScale(0.3f, 0.3f);

	pelote_sprite->setColor(Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));

	//pos inicial
	pelote_sprite->setPosition(mouse_pos);

	//velocidad
	velocidad.x = RandomNumber(-50, 50);// <- random flotante entre negativo y positivo.
	velocidad.y = 25;
	//aceleracion
	aceleracion.x = 15;
	aceleracion.y = aceleracion_bomba;

	if (velocidad_avion == -1)
	{
		pelote_sprite->setRotation(velocidad_avion - 34); //ROTO EL SPRITE

	}
	if (velocidad_avion == 1)
	{

		pelote_sprite->setRotation(velocidad_avion + 34);

	}

}

Pelota::~Pelota()
{
	delete reloj_interno;
	delete pelota_texture;
	delete pelote_sprite;
}

void Pelota::actualizar(RectangleShape limite_D, RectangleShape limite_i)
{

	tiempo_delta = reloj_interno->restart().asSeconds();
	velocidad.x += aceleracion.x * tiempo_delta;
	velocidad.y += aceleracion.y * tiempo_delta;
	pelote_sprite->setPosition(pelote_sprite->getPosition().x + velocidad.x * tiempo_delta, pelote_sprite->getPosition().y + velocidad.y * tiempo_delta);
	rebote(limite_D, limite_i);

}

void Pelota::rebote(RectangleShape limite_D, RectangleShape limite_i)
{

	if (pelote_sprite->getGlobalBounds().intersects(limite_D.getGlobalBounds()) ||
		pelote_sprite->getGlobalBounds().intersects(limite_i.getGlobalBounds())) // SI TOCA EL SUELO
	{
		velocidad.x *= -1;
	}

}






