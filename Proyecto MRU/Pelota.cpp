#include  "Pelota.h"

Pelota::Pelota(Vector2f mouse_pos, float velocidad_avion)
{
	
	reloj_interno = new Clock;
	pelota_texture = new Texture;
	pelota_texture->loadFromFile("recursos/bomba.png");

	pelote_sprite = new Sprite;
	pelote_sprite->setTexture(*pelota_texture);
	pelote_sprite->setScale(0.3f,0.3f);

	pelote_sprite->setColor(Color(rand()% 255 + 1, rand() % 255 + 1, rand() % 255 + 1));

	//pos inicial
	pelote_sprite->setPosition(mouse_pos);

	//velocidad
	velocidad.x = RandomNumber(-50, 50);// <- random flotante entre negativo y positivo.
	velocidad.y = 25;
	//aceleracion
	aceleracion.x = 15;
	aceleracion.y = 15;

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
	//reproducir el sonido de explocion
	delete reloj_interno;
	delete pelota_texture;
	delete pelote_sprite;
}

void Pelota::actualizar()
{
	
	tiempo_delta = reloj_interno->restart().asSeconds();

		//tiempo_interno = 0.20f;
	// formula de la velocidad v = a * t  (para que sea variada ) MRUV
	velocidad.x += aceleracion.x * tiempo_delta;
	velocidad.y += aceleracion.y * tiempo_delta;

	//formula MRU  
	pelote_sprite->setPosition(pelote_sprite->getPosition().x + velocidad.x * tiempo_delta, pelote_sprite->getPosition().y + velocidad.y * tiempo_delta );

	//rebote();
	
}

void Pelota::rebote()
{

	if (pelote_sprite->getPosition().y >= 600 - pelote_sprite->getGlobalBounds().height) // SI TOCA EL SUELO
	{
		pelote_sprite->setPosition(pelote_sprite->getPosition().x , 600 -pelote_sprite->getGlobalBounds().height); //NO LO TRASPASA
		velocidad.y = -5 / (tiempo_interno); // LO IMPULSA HACIA ARRIBA(REBOTA)
		if (tiempo_interno > 2.25f) //FRENO LA BOMBA
		{
			velocidad.x = 0;
		}
		

	}

}






