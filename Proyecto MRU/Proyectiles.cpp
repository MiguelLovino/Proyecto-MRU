#include "Proyectiles.h"

Proyectil::Proyectil(Vector2f pos_bocacha, Vector2f mira, Jugador* soldado)
{
	texture_proyectil = new Texture;
	texture_proyectil->loadFromFile("recursos/proyectil2.png");
	sprite_proyectil = new Sprite;
	sprite_proyectil->setColor(Color::Red);
	sprite_proyectil->setTexture(*texture_proyectil);
	sprite_proyectil->setPosition(pos_bocacha);
	sprite_proyectil->setScale(0.5, 0.5);
	direction = (mira - soldado->get_sprite().getPosition());
	reloj = new Clock;
	//Sonido
	//el sonido se ejecuta cuando el proyectil sale disparado.
	buffer_proyectil.loadFromFile("recursos/Sonido/proyectil.wav");
	sound_proyectil.setBuffer(buffer_proyectil);
	sound_proyectil.setVolume(20);
	sound_proyectil.play();
	//posicion
	
}

Proyectil::~Proyectil()
{
	delete reloj;
	delete sprite_proyectil;
	delete texture_proyectil;
}

void Proyectil::actualizar()
{	
	longitud = sqrt(direction.x * direction.x + direction.y * direction.y);
	direction.x = direction.x / longitud;
	direction.y = direction.y / longitud;
	tiempodelta = reloj->restart().asSeconds();
	sprite_proyectil->move(direction  *  (tiempodelta * velocidad_proyectil));

}

