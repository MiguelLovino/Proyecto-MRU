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

	sprite_avion->setPosition(801 , 50);
	//sprite_avion->setScale(5, 5);

	//vectores de movimiento

	velocidad.x = -1;
	velocidad.y = 0;

	aceleracion.x = 0;
	aceleracion.y = 0;

	//avion en pantalla
	avion_en_pantalla.setSize(Vector2f(800,300));
	avion_en_pantalla.setPosition(0, 0);



	//sonidos
	buffer_avion.loadFromFile("recursos/Sonido/avion2.wav");
	sound_avion.setBuffer(buffer_avion);
	sound_avion.setVolume(50);
}


void Avion::actualizar()
{
	//CONTROLARRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
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
	reproducir_sonido_avion();
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

void Avion::reset_avion()
{
	//vuelvo el avion a su posicion original
	sprite_avion->setPosition(802, 50);
	sprite_avion->setScale(1, 1);
	velocidad.x = -1;
}

bool Avion::posision_disparo()
{
	if (sprite_avion->getPosition().x > 350 && sprite_avion->getPosition().x < 500)
	{
		//cout << "esta en posicion de disparo" << endl;
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
