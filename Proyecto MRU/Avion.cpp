#include "Avion.h"

Avion::Avion(int ancho)
{

	//reloj
	reloj = new Clock;

	//texturas y sprite;
	texture_avion = new Texture;
	texture_avion->loadFromFile("recursos/avion.png");
	sprite_avion = new Sprite;
	sprite_avion->setTexture(*texture_avion);
	sprite_avion->setPosition(ancho, -20);

	velocidad.x = -1;
	velocidad.y = 0;

	aceleracion.x = 0;
	aceleracion.y = 0;

	//avion en pantalla
	avion_en_pantalla.setSize(Vector2f(800, 300));
	avion_en_pantalla.setPosition(0, 0);

	//sonidos
	buffer_avion.loadFromFile("recursos/Sonido/avion2.wav");
	sound_avion.setBuffer(buffer_avion);
	sound_avion.setVolume(50);
}


void Avion::actualizar(RectangleShape zona_disparo, bool start)
{

	tiempo1 = 3.20f;
	sprite_avion->setPosition(sprite_avion->getPosition() + (velocidad * tiempo1));
	de_lado_a_lado(start);
	posision_disparo(zona_disparo);
	reproducir_sonido_avion();

}

void Avion::de_lado_a_lado(bool start)
{

	if (sprite_avion->getPosition().x <= 0 - sprite_avion->getGlobalBounds().width)
	{
		velocidad.x = 0;
		sprite_avion->setScale(-1, 1); //dar vuelta la imagen

		if (start == false)
		{

		velocidad.x = 1;

		}

	}

	if (sprite_avion->getPosition().x >= 1270 + sprite_avion->getGlobalBounds().width)
	{
		velocidad.x = 0;
		sprite_avion->setScale(1, 1);

		if (start == false)
		{
			velocidad.x = -1;
		}
	}


}

void Avion::reset_avion()
{
	//vuelvo el avion a su posicion original
	sprite_avion->setPosition(802, -20);
	sprite_avion->setScale(1, 1);
	velocidad.x = -1;
}

bool Avion::posision_disparo(RectangleShape zona_disparo)
{
	// tiene que intersectar con el rectangulo verde
	if (sprite_avion->getGlobalBounds().intersects(zona_disparo.getGlobalBounds()))
	{
		return true;
	}
	else
	{
		return false;
	}
	

}

void Avion::reproducir_sonido_avion()
{
	//si, el avion se encuentra "adentro de la pantalla" (intercept?), se reproduce el sonido.
	//si no, se para el sonido y se actualiza el boleano.
	if (sprite_avion->getGlobalBounds().intersects(avion_en_pantalla.getGlobalBounds()))
	{
		if (rep_avion == true)
		{

			sound_avion.play();
			sound_avion.setPlayingOffset(seconds(15));
			rep_avion = false;
		}

	}
	else
	{
		sound_avion.stop();
		rep_avion = true;
	}
}
