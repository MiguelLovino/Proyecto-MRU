#include "Barril.h"

Barril::Barril(float vel,int ancho, int alto)
{
	barril_explosivo = new CircleShape;
	barril_txt = new Texture;
	barril_txt->loadFromFile("recursos/barril.png");
	barril_explosivo->setRadius(25);
	barril_explosivo->setTexture(barril_txt);
	barril_explosivo->setOrigin(barril_explosivo->getRadius(), barril_explosivo->getRadius());
	aceleracion_x = vel;
	int tx_b = barril_explosivo->getGlobalBounds().height;
	if (pos_inicial == 0)
	{
		barril_explosivo->setPosition(0, alto - barril_explosivo->getRadius());
	}
	else
	{
		barril_explosivo->setPosition(ancho, alto - barril_explosivo->getRadius());
		barril_explosivo->setFillColor(Color::Green);
		velocidad_x *= -1;
		aceleracion_x *= -1;
	}

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
	barril_explosivo->rotate(1 * velocidad_x / 20);
}


