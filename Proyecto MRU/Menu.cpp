#include "Menu.h"

Menu::Menu()
{

	//Textos correspondiente a la parte del menu INICIO
	fuente_txt = new Font;
	fuente_txt->loadFromFile("recursos/Ss.ttf");

	texto_inicio = new Text;
	texto_inicio->setFont(*fuente_txt);
	texto_inicio->setString("JUGAR");
	texto_inicio->setPosition(300, 200);
	texto_inicio->setCharacterSize(50);

	//textos correspondiente a la parte del juego
	texto_juego_vida = new Text;
	texto_juego_vida->setFont(*fuente_txt);
	texto_juego_vida->setString("vidas");
	texto_juego_vida->setFillColor(Color::Black);
	texto_juego_vida->setPosition(10, 5);
	texto_juego_vida->setCharacterSize(25);
	
	texto_juego_fase = new Text;
	texto_juego_fase->setFont(*fuente_txt);
	texto_juego_fase->setString("fase");

	texto_juego_puntaje = new Text;
	texto_juego_puntaje->setFont(*fuente_txt);
	texto_juego_puntaje->setString("Puntaje");



	//texto correspondiente a la parte del menu FIN
	texto_fin = new Text;
	texto_fin->setFont(*fuente_txt);
	texto_fin->setString("REINICIAR");
	texto_fin->setPosition(300, 200);
	texto_fin->setCharacterSize(50);

	//texto correspondiente a SALIR
	texo_salir = new Text;
	texo_salir->setFont(*fuente_txt);
	texo_salir->setString("SALIR");
	texo_salir->setPosition(300, 300);
	texo_salir->setCharacterSize(50);
	
}

void Menu::inicio_actualizar(Mira *mira,Vector2f mouserposition, RenderWindow* pWnd)
{

	if (pantalla_menu == true)
	{
		
		if (Mouse::isButtonPressed(Mouse::Left))
		{

			if (mira->get_sprite().getGlobalBounds().intersects(texto_inicio->getGlobalBounds()))
			{
				pantalla_juego = true;
				pantalla_menu = false;
				sleep(milliseconds(250));
				
			}
			if (mira->get_sprite().getGlobalBounds().intersects(texo_salir->getGlobalBounds()))
			{
				pWnd->close();
			}
		}
		mira->set_pos_mira(mouserposition);
		if (mira->get_sprite().getGlobalBounds().intersects(texto_inicio->getGlobalBounds()))
		{
			texto_inicio->setFillColor(Color::Black);
		}
		else
		{
			texto_inicio->setFillColor(Color::White);
		}
		if (mira->get_sprite().getGlobalBounds().intersects(texo_salir->getGlobalBounds()))
		{
			texo_salir->setFillColor(Color::Black);
		}
		else
		{
			texo_salir->setFillColor(Color::White);
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
		pWnd->draw(*texo_salir);
		pWnd->draw(Mira_cursor->get_sprite()); //dibujo la mira
	}
}

void Menu::fin_actualizar(Mira* mira, Vector2f mouserposition, RenderWindow* pWnd)
{
	
	if (pantalla_fin == true)
	{
		
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (mira->get_sprite().getGlobalBounds().intersects(texto_fin->getGlobalBounds()))
			{
				
				pantalla_menu = true;
				pantalla_fin = false;
				cout << "se produce el evento de soltar el boton" << endl;
				
				//agrego delay para que que no colicione con la otra opcion rapidamente
			   sleep(milliseconds(250));
				
			}
			if (mira->get_sprite().getGlobalBounds().intersects(texo_salir->getGlobalBounds()))
			{
				pWnd->close();
			}
		}
		mira->set_pos_mira(mouserposition);
		if (mira->get_sprite().getGlobalBounds().intersects(texto_fin->getGlobalBounds()))
		{
			texto_fin->setFillColor(Color::Black);
		}
		else
		{
			texto_fin->setFillColor(Color::White);
		}
		if (mira->get_sprite().getGlobalBounds().intersects(texo_salir->getGlobalBounds()))
		{
			texo_salir->setFillColor(Color::Black);
		}
		else
		{
			texo_salir->setFillColor(Color::White);
		}
		
	}
	

}

void Menu::dibujar_fin(RenderWindow* pWnd, Pantalla* pantalla_fondo, Mira* Mira_cursor)
{
	if (pantalla_fin == true)
	{
		pWnd->draw(pantalla_fondo->get_sprite_fondoPantalla());
		pWnd->draw(*texto_fin);
		pWnd->draw(*texo_salir);
		pWnd->draw(Mira_cursor->get_sprite());
	}
	


}


void Menu::menu_juego_actualizar(int vida)
{
	texto_juego_vida->setString("vida: " + to_string(vida));
	
}

void Menu::dibujar_menu_juego(RenderWindow* pWnd, Pantalla* pantalla_fondo, Mira* Mira_cursor)
{
	if (pantalla_juego == true)
	{
		pWnd->draw(*texto_juego_vida);
	}
}
