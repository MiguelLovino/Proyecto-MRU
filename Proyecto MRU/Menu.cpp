#include "Menu.h"

Menu::Menu()
{
	//NOTA TILIZAR EVENTOS BUFFERED PARA EL MENU.
	//Textos correspondiente a la parte del menu INICIO
	fuente_txt = new Font;
	fuente_txt->loadFromFile("recursos/Ss.ttf");

	reloj_principal = new Clock;

	vida_txt = new Texture;
	for (int i = 0; i < 5; i++)
	{
		vida_spr[i] = new Sprite;
	}
	vida_txt->loadFromFile("recursos/corazon.png");

	for (int i = 0; i < 5; i++)
	{
		vida_spr[i]->setTexture(*vida_txt);
	
	}

	texto_inicio = new Text;
	texto_inicio->setFont(*fuente_txt);
	texto_inicio->setString("JUGAR");
	texto_inicio->setPosition(100, 200);
	texto_inicio->setCharacterSize(50);
	texto_inicio->setOutlineThickness(5.f);
	texto_inicio->setOutlineColor(Color::Blue);
	nombre_juego = new Text;
	nombre_juego->setFont(*fuente_txt);
	nombre_juego->setString("BOMBER SHOOTER");
	nombre_juego->setPosition(400, 100);
	nombre_juego->setCharacterSize(50);
	nombre_juego->setFillColor(Color::Black);
	nombre_juego->setOutlineThickness(5.0f);
	nombre_juego->setOutlineColor(Color::White);

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
	puntaje_final = new Text;
	texto_fin->setFont(*fuente_txt);
	texto_fin->setString("REINICIAR");
	texto_fin->setPosition(300, 200);
	texto_fin->setCharacterSize(50);
	texto_fin->setOutlineThickness(5.f);
	texto_fin->setOutlineColor(Color::Blue);
	puntaje_final->setFillColor(Color::Black);
	puntaje_final->setFont(*fuente_txt);
	puntaje_final->setPosition(50, 650);
	puntaje_final->setCharacterSize(50);
	
	//texto correspondiente a SALIR
	texo_salir = new Text;
	texo_salir->setFont(*fuente_txt);
	texo_salir->setString("SALIR");
	texo_salir->setPosition(100, 300);
	texo_salir->setCharacterSize(50);
	texo_salir->setOutlineThickness(5.f);
	texo_salir->setOutlineColor(Color::Blue);

	//tutorial
	tutorial = new Text;
	tutorial->setFont(*fuente_txt);
	tutorial->setString("TUTORIAL");
	tutorial->setPosition(100, 400);
	tutorial->setCharacterSize(50);
	tutorial->setOutlineThickness(5.f);
	tutorial->setOutlineColor(Color::Blue);

	tutorial_txt.loadFromFile("recursos/tutorial.png");
	tutorial_spr.setTexture(tutorial_txt);
	tutorial_spr.setPosition(20, 50);

	

	//sonido correspondientes a los menus.

	buffer_menu.loadFromFile("recursos/Sonido/sonido menu.wav");
	sonido_menu.setBuffer(buffer_menu);
	sonido_menu.setVolume(35);

	Buffer_menu_loop.loadFromFile("recursos/Sonido/menu song.wav");
	sonido_menu_loop.setBuffer(Buffer_menu_loop);

	batalla_buffer.loadFromFile("recursos/Sonido/battle song.ogg");
	batalla_sound.setBuffer(batalla_buffer);

	//sonido mune-unmuted
	unmute_txt = new Texture;
	unmute_txt->loadFromFile("recursos/mute2.png");
	mute_txt = new Texture;
	mute_spr = new Sprite;
	mute_txt->loadFromFile("recursos/unmuted.png");
	mute_spr->setTexture(*mute_txt);
	mute_spr->setPosition(1150, 50);
	
}

void Menu::inicio_actualizar(Mira* mira, Vector2f mouserposition, RenderWindow* pWnd, Event& eventito)
{

	if (pantalla_menu == true)
	{
		if (menu_loop == true)
		{
			
			sonido_menu_loop.play();
			sonido_menu_loop.setLoop(true);
			menu_loop = false;
		}
		texo_salir->setPosition(100, 300);
		
		if (eventito.type == eventito.MouseButtonPressed && eventito.mouseButton.button == Mouse::Left)
		{

			if (mira->get_sprite().getGlobalBounds().intersects(texto_inicio->getGlobalBounds()))
			{
				pantalla_juego = true;
				batalla_loop = true;
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
		if (mira->get_sprite().getGlobalBounds().intersects(tutorial->getGlobalBounds()))
		{
			tutorial->setFillColor(Color::Black);
			if (rep_tutorial == true)
			{
				sonido_menu.play();
				rep_tutorial = false;
			}
			dibu_tutorial = true;
			

		}
		else
		{
			tutorial->setFillColor(Color::White);
			rep_tutorial = true;
			dibu_tutorial = false;

		}
		if (mira->get_sprite().getGlobalBounds().intersects(mute_spr->getGlobalBounds()))
		{
			mute_spr->setScale(1.1, 1.1);

				if (eventito.type == eventito.MouseButtonPressed && eventito.mouseButton.button == Mouse::Left && muteado == false)
				{
						mute_spr->setTexture(*unmute_txt);
						muteado = true;
						sonido_menu.pause();
						sonido_menu_loop.pause();
				}
		}
		else
		{
			mute_spr->setScale(1, 1);

		}

	}
	else
	{
		sonido_menu_loop.stop();
	}
	
}

void Menu::dibujar_inicio(RenderWindow* pWnd, Pantalla* pantalla_fondo, Mira* Mira_cursor)
{
	//PANTALLA DE INICIO

	if (pantalla_menu == true)
	{
		pWnd->draw(pantalla_fondo->get_sprite_fondoPantalla());
		if (dibu_tutorial == true)
		{

		pWnd->draw(tutorial_spr);

		}
		pWnd->draw(*mute_spr);
		pWnd->draw(*tutorial);
		pWnd->draw(*texto_inicio);
		pWnd->draw(*texo_salir);

		pWnd->draw(Mira_cursor->get_sprite()); //dibujo la mira
		pWnd->draw(*nombre_juego);
		animacion_nomre_juego(pantalla_fondo->get_sprite_fondoPantalla().getGlobalBounds().width);
	}
}

void Menu::menu_juego_actualizar(int vida, int puntaje, int fase)
{
	//agregar puntaje
	if (batalla_loop == true)
	{
		batalla_sound.play();
		batalla_sound.setLoop(true);
		batalla_loop = false;
	}
	//texto_juego_vida->setString("vida: " + to_string(vida));
	texto_juego_puntaje->setPosition(635 - texto_juego_puntaje->getGlobalBounds().width / 2, texto_juego_puntaje->getPosition().y);
	texto_juego_puntaje->setString("puntaje " + to_string(puntaje));
	
	for (int i = 0; i < 5; i++)
	{
		int espacio_entre_corazones = 5;
		int espaciador_inicial = 10 + (i * (espacio_entre_corazones + vida_spr[i]->getGlobalBounds().width));
		vida_spr[i]->setPosition(espaciador_inicial, 20);
	}


}

void Menu::dibujar_menu_juego(RenderWindow* pWnd, Pantalla* pantalla_fondo, Mira* Mira_cursor, int vida)
{
	if (pantalla_juego == true)
	{
		//pWnd->draw(*texto_juego_vida);
		
		pWnd->draw(*texto_juego_puntaje);
		
		for (int i = 0; i <	vida; i++)
		{
			pWnd->draw(*vida_spr[i]);
		}
		//pWnd->draw(*texto_juego_fase);
	}
}

void Menu::fin_actualizar(Mira* mira, Vector2f mouserposition, RenderWindow* pWnd, Event& eventito, int puntaje)
{

	if (pantalla_fin == true)
	{
		batalla_sound.stop();
		texto_fin->setPosition(pWnd->getSize().x / 2 - texto_fin->getGlobalBounds().width / 2, 200);
		texo_salir->setPosition(pWnd->getSize().x /2 - texo_salir->getGlobalBounds().width / 2, 300);
		puntaje_final->setPosition(pWnd->getSize().x / 2 - puntaje_final->getGlobalBounds().width / 2, 650);
		puntaje_final->setString("Puntaje final: " + to_string(puntaje));

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
				menu_loop = true;
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
				//cout << "se produce el evento de soltar el boton" << endl;


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
		pWnd->draw(*puntaje_final);
	}



}

void Menu::animacion_nomre_juego(int ancho)
{
	

	tiempo_principal = reloj_principal->getElapsedTime().asSeconds();

	if (tiempo_principal > retardo_principal)
	{
		if (nombre_juego->getCharacterSize() >= 50 && escala_dinamica == true)
		{

			nombre_juego->setCharacterSize(nombre_juego->getCharacterSize() + 1);
			if (nombre_juego->getCharacterSize() == 70)

			{
				escala_dinamica = false;
			}
		}

		if (nombre_juego->getCharacterSize() <= 70 && escala_dinamica == false)
		{
			nombre_juego->setCharacterSize(nombre_juego->getCharacterSize() - 1);
			if (nombre_juego->getCharacterSize() == 50)

			{
				escala_dinamica = true;
			}

		}

		reloj_principal->restart();
	}
	nombre_juego->setPosition(ancho / 2 - nombre_juego->getGlobalBounds().width / 2, nombre_juego->getPosition().y);
}
