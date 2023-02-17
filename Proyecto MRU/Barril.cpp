#include "Barril.h"

Barril::Barril(float vel)
{
	barril_explosivo = new CircleShape;
	barril_txt = new Texture;
	barril_txt->loadFromFile("recursos/barril.png");
	barril_explosivo->setRadius(25);
	barril_explosivo->setTexture(barril_txt);
	aceleracion_x = vel;
	//pos_inicial = ; // 0 = izquierda, 1 = derecha
	if (pos_inicial == 0)
	{
	barril_explosivo->setPosition(0, 560);
	}
	else
	{
	barril_explosivo->setPosition(775, 560);
	barril_explosivo->setFillColor(Color::Green);
	velocidad_x *= -1;
	aceleracion_x *= -1;
	}
	
	barril_explosivo->setOrigin(barril_explosivo->getRadius(), barril_explosivo->getRadius());
}

Barril::~Barril()
{
	delete barril_explosivo;
	delete barril_txt;
}

void Barril::actualizar()
{
	tiempo_delta = Reloj.restart().asSeconds();
	velocidad_x += aceleracion_x * tiempo_delta;
	if (pos_inicial == 0)
	{
	barril_explosivo->move(velocidad_x * tiempo_delta, 0);
	}
	else
	{
	barril_explosivo->move(velocidad_x * tiempo_delta, 0);
	}
	barril_explosivo->rotate(1 * velocidad_x /20);
}
