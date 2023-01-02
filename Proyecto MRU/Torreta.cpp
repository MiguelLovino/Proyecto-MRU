#include "Torreta.h"

Torreta::Torreta()
{

	texture_torreta = new Texture;
	reloj = new Clock;
	
	if (!texture_torreta->loadFromFile("recursos/torreta.png"))
	{
		cout << " no se pudo cargar la textura" << endl;
	}

	//sprite_torreta = new Sprite;
	sprite_torreta.setTexture(*texture_torreta);

	sprite_torreta.setOrigin(25, 150);
	sprite_torreta.setPosition(400,750 - sprite_torreta.getGlobalBounds().height);

	
}

void Torreta::actualizar(RenderWindow* pWnd)
{
	tiempo1 = reloj->getElapsedTime().asSeconds();

	if (proyectil_torreta.size() > 0) //dibujo los proyectiles
	{
		for (int i = 0; i < proyectil_torreta.size(); i++)
		{
			pWnd->draw(proyectil_torreta[i]->get_sprite());
		}
	}
	
	//actualizo los proyectiles
	if (proyectil_torreta.size() >= 0)
	{
		for (int i = 0; i < proyectil_torreta.size(); i++)
		{
			proyectil_torreta[i]->actualizar(sprite_torreta.getRotation());
		}
	}
	




	disparar_proyectiles(sprite_torreta.getPosition(), sprite_torreta.getRotation());
}
void Torreta::rota_derecha()
{
	sprite_torreta.rotate(1);
}

void Torreta::rota_izquierda()
{
	sprite_torreta.rotate(-1);
}

void Torreta::disparar_proyectiles(Vector2f pos_bocacha, float rotacion)
{
	if (tiempo1 > tiempo2 + 0.15f)
	{
		//cout << "se dibuja una bala" << endl;
		//cout << sprite_torreta.getRotation() << endl;
		tiempo2 = tiempo1;
		proyectil_torreta.push_back(new Proyectil(pos_bocacha, rotacion));
	}
}