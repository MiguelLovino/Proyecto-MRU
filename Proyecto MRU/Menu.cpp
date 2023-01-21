#include "Menu.h"

Menu::Menu()
{

	//Textos correspondiente a la parte del menu INICIO
	fuente_txt = new Font;
	fuente_txt->loadFromFile("recursos/Ss.ttf");

	texto_inicio = new Text;
	texto_inicio->setFont(*fuente_txt);
	texto_inicio->setString("JUGAR");
	texto_inicio->setPosition(400, 200);
	texto_inicio->setCharacterSize(50);

	//textos correspondiente a la parte del juego
	texto_juego = new Text;
	texto_juego->setFont(*fuente_txt);
	texto_juego->setString("vidas");

	//texto correspondiente a la parte del menu FIN
	texto_fin = new Text;
	texto_fin->setFont(*fuente_txt);
	texto_fin->setString("REINICIAR");


}

void Menu::inicio_actualizar(Mira *mira,Vector2f mouserposition)
{
	if (pantalla_menu == true)
	{
		mira->set_pos_mira(mouserposition);
		if (mira->get_sprite().getGlobalBounds().intersects(texto_inicio->getGlobalBounds()))
		{
			texto_inicio->setFillColor(Color::Black);

		}
		else
		{
			texto_inicio->setFillColor(Color::White);

		}
	}
}

void Menu::dibujar_inicio(RenderWindow* pWnd, Pantalla* pantalla_fondo, Mira* Mira_cursor)
{
	//PANTALLA DE INICIO
	
	if (pantalla_menu == true)
	{
		pWnd->draw(pantalla_fondo->get_sprite_fondoPantalla());
		pWnd->draw(*texto_inicio);
		pWnd->draw(Mira_cursor->get_sprite()); //dibujo la mira
	}
}
