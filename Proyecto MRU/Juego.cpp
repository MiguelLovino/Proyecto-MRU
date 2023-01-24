#include "Juego.h"


Juego::Juego(int alto, int ancho, string titulo)
	
{
	pWnd = new RenderWindow(VideoMode(alto,ancho),titulo);
	jugador = new Caballero;
	pantalla_fondo = new Pantalla;
	bombardero = new Avion;
	Mira_cursor = new Mira;
	torretaaire = new Torreta;
	menus = new Menu;
	//proyectil_torretaaire = new Proyectil;
	//pelotita = new Pelota;
	reloj = new Clock;
	tiempo1 = new Time;
	pWnd->setFramerateLimit(60);
	pWnd->setMouseCursorVisible(false);
	//pWnd->setKeyRepeatEnabled(false);
	
	
	
}
void Juego::ProcessEvent(Event& evt)
{
	//eventos de mouse
	mouserposition.x = (float)Mouse::getPosition(*pWnd).x;
	mouserposition.y = (float)Mouse::getPosition(*pWnd).y;

	


	//eventos de teclado, etc

	if (evt.type == evt.Closed)
	{
		pWnd->close();
	}
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		pWnd->close();
	}

	//teclado letra D
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		torretaaire->rota_derecha();
		//cout << "funciona la D" << endl;
	}
	if (Keyboard::isKeyPressed(Keyboard::A))
		torretaaire->rota_izquierda();
	{
		//jugador->set_velocidad_x(-0.1);
		
	}
	
	
	/*
	if (Mouse::isButtonPressed(Mouse::Middle) && pantalla_menu == false)
	{
		pantalla_juego = false;
		pantalla_fin = true;
	}
	*/
	
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		if (pelotas.size() >= 0)
		{

			for (int i = 0; i < pelotas.size(); i++)
			{

				if (Mira_cursor->get_sprite().getGlobalBounds().intersects(pelotas[i]->get_sprite().getGlobalBounds()))
				{
					pelotas.erase(pelotas.begin() + i);

				}

			}

		}
		
	}

}

void Juego::DrawGame()
{
	//PANTALLA DE INICIO
	menus->dibujar_inicio(pWnd, pantalla_fondo, Mira_cursor);
	menus->dibujar_fin(pWnd, pantalla_fondo, Mira_cursor);
	
	
	//PANTALLA DEL JUEGO
	
	if (menus->get_pantalla_juego() == true)
	{

	pWnd->draw(pantalla_fondo->get_sprite_fondoPantalla()); //dibujo pantalla
	pWnd->draw(bombardero->get_sprite_avion()); //avion

	if (pelotas.size() > 0) //dibujo las bombas
	{
		for (int i = 0; i < pelotas.size(); i++)
		{
			pWnd->draw(pelotas[i]->get_sprite());
		}
	}
	if (proyectil_torretaDOS.size() > 0) //dibujo los proyectiles
	{
		for (int i = 0; i < proyectil_torretaDOS.size(); i++)
		{
			pWnd->draw(proyectil_torretaDOS[i]->get_sprite());
		}
	}
	
	pWnd->draw(torretaaire->get_sprite_torreta()); //torreta
	pWnd->draw(Mira_cursor->get_sprite()); //dibujo la mira
	
	
	}
	
	menus->dibujar_menu_juego(pWnd, pantalla_fondo, Mira_cursor);
}

void Juego::UpdateGame()
{
	//pantalla menu
	menus->inicio_actualizar(Mira_cursor, mouserposition, pWnd);
	//pantalla del menu de juego
	menus->menu_juego_actualizar(vida);
	//pantalla  de fin
	menus->fin_actualizar(Mira_cursor, mouserposition, pWnd);
	

	//pantalla juego
	if (menus->get_pantalla_juego() == true)
	{
	//reloj
	tiempo2 = reloj->getElapsedTime().asSeconds();

	//mira
	Mira_cursor->set_pos_mira(mouserposition);

	//disparar proyectiles (los crea)
	proyectil_pos_de_disparo.x = torretaaire->get_sprite_torreta().getPosition().x -11 + torretaaire->get_sprite_torreta().getRotation();
	proyectil_pos_de_disparo.y = torretaaire->get_sprite_torreta().getPosition().y -100 + torretaaire->get_sprite_torreta().getRotation();

	disparar_proyectiles(proyectil_pos_de_disparo, torretaaire->get_sprite_torreta().getRotation()); //disparar proyectiles

	//disparar proyectiles actualizar
	if (proyectil_torretaDOS.size() >= 0)
	{

		for (int i = 0; i < proyectil_torretaDOS.size(); i++)
		{
			proyectil_torretaDOS[i]->actualizar(torretaaire->get_sprite_torreta().getRotation());
		}
	}

	//actualizar avion
	bombardero->actualizar();
	
	

	//actualizar bombas
	if (pelotas.size() >= 0)
	{
		for (int i = 1; i < pelotas.size(); i++)
		{
		pelotas[i]->actualizar();
		}
	}
	
	
	//destruir bombas si chochan el suelo
	if (pelotas.size() >= 0)
	{

		for (int i = 0; i < pelotas.size(); i++)

		{
			

			if (pelotas[i]->get_sprite().getPosition().y > 300)
			{
				pelotas.erase(pelotas.begin()+i);
				vida--;
				
				//break;
			}
				
		}

	}
	
	//destruir bombas 2;


	//posiciones y estados
	// 
	if (bombardero->get_sprite_avion().getScale().x == 1) //cambio de trayectoria del avion.
	{
	bombaposition.x = bombardero->get_sprite_avion().getPosition().x + (bombardero->get_sprite_avion().getGlobalBounds().width / 2);

	}
	if (bombardero->get_sprite_avion().getScale().x == -1)
	{
		bombaposition.x = bombardero->get_sprite_avion().getPosition().x - (bombardero->get_sprite_avion().getGlobalBounds().width / 2);
	}

	bombaposition.y = bombardero->get_sprite_avion().getPosition().y + 134;

	//tirar bombas //CONTROLAR AQUI la bomba que queda suelta al incio.
	if (tiempo2 > tiempo3)
	{
		tiempo3 = tiempo2 + 0.25f;
		if (bombardero->posision_disparo() == true)
		{
			pelotas.push_back(new Pelota(bombaposition, bombardero->get_velocidad_avion_X()));
		}
	}

	//actualizar torreta
	if (vida <= 0)
	{
		Game_over = true;
	}
	

	//actualizo la condicion de perdida.
	if (Game_over == true)
	{
		resetear_juego();
		menus->set_pantalla_juego(false);
		menus->set_pantalla_fin(true);


	}
	}
}

void Juego::ProcessCollisions()
{
	if (menus->get_pantalla_juego() == true)
	{

	
	//coliciones
	//colicion de bombas con proyectiles.
	if (pelotas.size() >= 0 && proyectil_torretaDOS.size() >= 0)
	{

		for (int i = 0; i < pelotas.size(); i++)
		{
			for (int j = 0; j < proyectil_torretaDOS.size(); j++)
			{
				if (proyectil_torretaDOS[j]->get_sprite().getGlobalBounds().intersects(pelotas[i]->get_sprite().getGlobalBounds()))
				{
					//cout << "se produjo colicion" << endl;
				proyectil_torretaDOS.erase(proyectil_torretaDOS.begin() + j);
					pelotas.erase(pelotas.begin() + i);
					break;
				}
			}
		}
	}
	// destruir proyectiles que pasen el eje y = 0;

	if (proyectil_torretaDOS.size() >= 0)
	{
		
		for (int i = 0; i < proyectil_torretaDOS.size(); i++)
		{
			if (proyectil_torretaDOS[i]->get_sprite().getPosition().y < 50)
			{
				proyectil_torretaDOS.erase(proyectil_torretaDOS.begin() + i);
			}
		}

	}

	// destuir bombas que pasen el eje y = 600;
	if (pelotas.size() >= 0)
	{
		for (int i = 0; i < pelotas.size(); i++)
		{
			if (pelotas[i]->get_sprite().getPosition().y > 500)
			{
				pelotas.erase(pelotas.begin() + i);
			}
		}
	}
	
	}
}

Juego::~Juego(void)
{
	
}

void Juego::Go()
{
	
	//objeto para recibir eventos
	Event evt;
	while (pWnd->isOpen()) {
		//procesar eventos
		while (pWnd->pollEvent(evt))
		

		
			ProcessEvent(evt);
		//MENU DE PANTALLA AQUI.
		//procesar colisiones
		ProcessCollisions();
		//actualizar estados de objetos
		UpdateGame();
		pWnd->clear();
		DrawGame();
		prueba_en_consola();
		//MENU DE FIN DEL JUEGO AQUI
		pWnd->display();
		
	}
}

void Juego::disparar_proyectiles(Vector2f pos_bocacha, float rotacion)
{
	 


	if (tiempo2 > tiempo4 + 0.10)
	{
		tiempo4 = tiempo2;

		// MODIFICAR  ESTA PARTE PARA QUE EL PROYECTIL SALGA DESDE LA BOCACHA.

		proyectil_torretaDOS.push_back(new Proyectil(pos_bocacha, rotacion));

	}
		//cout << "se dibuja una bala" << endl;
		//cout << sprite_torreta.getRotation() << endl;
		//tiempo2 = tiempo1;
	
}

void Juego::prueba_en_consola()
{
	//colocar aqui adentro todo los cout.
	//cout << torretaaire->get_sprite_torreta().getOrigin().y << endl;
	cout << bombardero->get_sprite_avion().getPosition().x << endl;

}

void Juego::resetear_juego()
{
	vida = 5;
	puntaje = 0;
	fase = 1;
	pelotas.clear();
	proyectil_torretaDOS.clear();
	bombardero->reset_avion();
	Game_over = false;
}
