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
	velocidad.x = 0;// RandomNumber(-25, 25); <- random flotante entre negativo y positivo.
	velocidad.y = 0;
	//aceleracion
	aceleracion.x = 0;//(rand() % 4 + 1) + (rand() % 4 - 4); //rand de -3 a 3. <- random entero entre negativo y positivo
	aceleracion.y = cosf(tiempo_interno) / 50;//RandomNumber(0.10f, 2.0f);  //GRAVEDAD
	//rotacion

	if (velocidad_avion == -1)
	{
	pelote_sprite->setRotation(velocidad_avion - 34); //ROTO EL SPRITE
		velocidad.x = RandomNumber(-5, 5); //CAMBIO SU VELOCIDAD PARA SIMULAR LA INERCIA
	}
	if (velocidad_avion == 1)
	{
		pelote_sprite->setRotation(velocidad_avion + 34);
		velocidad.x = RandomNumber(-5, 5);
	}
	
}

void Pelota::actualizar()
{
	
		tiempo_interno = reloj_interno->getElapsedTime().asSeconds();

		//tiempo_interno = 0.20f;
	// formula de la velocidad v = a * t  (para que sea variada ) MRUV
	velocidad.x += aceleracion.x * tiempo_interno;
	velocidad.y += aceleracion.y * tiempo_interno;

	//formula MRU  
	pelote_sprite->setPosition(pelote_sprite->getPosition() + velocidad * (tiempo_interno / 4));

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






