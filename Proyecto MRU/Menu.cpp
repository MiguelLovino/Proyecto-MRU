#include "Menu.h"

Menu::Menu()
{
	//NOTA TILIZAR EVENTOS BUFFERED PARA EL MENU.
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
	texto_juego_fase->setFillColor(Color::Black);
	texto_juego_fase->setPosition(400, 5);
	texto_juego_fase->setCharacterSize(25);

	texto_juego_puntaje = new Text;
	texto_juego_puntaje->setFont(*fuente_txt);
	texto_juego_puntaje->setString("Puntaje");
	texto_juego_puntaje->setFillColor(Color::Black);
	texto_juego_puntaje->setPosition(650, 5);
	texto_juego_puntaje->setCharacterSize(25);


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
	
	//sonido correspondientes a los menus.
	
	buffer_menu.loadFromFile("recursos/Sonido/sonido menu.ogg");
	sonido_menu.setBuffer(buffer_menu);
}

void Menu::inicio_actualizar(Mira *mira,Vector2f mouserposition, RenderWindow* pWnd, Event &eventito)
{

	if (pantalla_menu == true)
	{
		
		if (eventito.type == eventito.MouseButtonPressed && eventito.mouseButton.button == Mouse::Left)
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
			if (rep_jugar == true)
			{
				sonido_menu.play();
				rep_jugar = false;
			}
		}
		else
		{
			texto_inicio->setFillColor(Color::White);
			rep_jugar = true;
		}
		if (mira->get_sprite().getGlobalBounds().intersects(texo_salir->getGlobalBounds()))
		{
			texo_salir->setFillColor(Color::Black);
			if (rep_salir == true)
			{
				sonido_menu.play();
				rep_salir = false;
			}
		}
		else
		{
			texo_salir->setFillColor(Color::White);
			rep_salir = true;
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

void Menu::fin_actualizar(Mira* mira, Vector2f mouserposition, RenderWindow* pWnd, Event &eventito)
{
	
	if (pantalla_fin == true)
	{
		

		if (eventito.type == eventito.MouseButtonReleased && eventito.mouseButton.button == Mouse::Left)
		{
			
			if (mira->get_sprite().getGlobalBounds().intersects(texo_salir->getGlobalBounds()))
			{
				pWnd->close();
			}
		}

		mira->set_pos_mira(mouserposition);

		if (mira->get_sprite().getGlobalBounds().intersects(texto_fin->getGlobalBounds()))
		{
			texto_fin->setFillColor(Color::Black);
			//ejecutar sonido
			if (rep_reiniciar == true)
			{
			sonido_menu.play();
			rep_reiniciar = false;
			}
			
		}
		else
		{
			texto_fin->setFillColor(Color::White);
			rep_reiniciar = true;
		}
		if (mira->get_sprite().getGlobalBounds().intersects(texo_salir->getGlobalBounds()))
		{
			texo_salir->setFillColor(Color::Black);
			//ejecutar sonido
			if (rep_salir == true)
			{
				sonido_menu.play();
				rep_salir = false;
			}
		}
		else
		{
			texo_salir->setFillColor(Color::White);
			rep_salir = true;
		}
		if (eventito.type == eventito.MouseButtonReleased && eventito.mouseButton.button == Mouse::Left)
		{
			if (mira->get_sprite().getGlobalBounds().intersects(texto_fin->getGlobalBounds()))
			{

				//cambiar de pantallla
				pantalla_menu = true;
				pantalla_fin = false;
				sonido_menu.play();
				cout << "se produce el evento de soltar el boton" << endl;


				//agrego delay para que que no colicione con la otra opcion rapidamente
			 //  sleep(milliseconds(250));

			}
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


void Menu::menu_juego_actualizar(int vida, int puntaje, int fase)
{
	//agregar puntaje
	texto_juego_vida->setString("vida: " + to_string(vida));
	texto_juego_puntaje->setString("puntaje " + to_string(puntaje));

	
}

void Menu::dibujar_menu_juego(RenderWindow* pWnd, Pantalla* pantalla_fondo, Mira* Mira_cursor)
{
	if (pantalla_juego == true)
	{
		pWnd->draw(*texto_juego_vida);
		pWnd->draw(*texto_juego_puntaje);
		pWnd->draw(*texto_juego_fase);
	}
}
