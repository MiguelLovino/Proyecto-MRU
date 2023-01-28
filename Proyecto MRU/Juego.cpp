#include "Juego.h"


Juego::Juego(int alto, int ancho, string titulo)
	
{
	pWnd = new RenderWindow(VideoMode(alto,ancho),titulo);
	pantalla_fondo = new Pantalla;
	bombardero = new Avion;
	Mira_cursor = new Mira;
	menus = new Menu;
	reloj = new Clock;
	tiempo1 = new Time;
	pWnd->setFramerateLimit(60);
	pWnd->setMouseCursorVisible(false);
	soldado = new Jugador;
	//rectangulos de pruebas, borrar al finalizar.
	soldadoRECT = new RectangleShape;
	soldadoRECT->setFillColor(Color::Red);
	Vector2f soldadorecsize;
	soldadorecsize.x = 5;
	soldadorecsize.y = 5;
	soldadoRECT->setSize(soldadorecsize);

	avionRECT = new RectangleShape;
	avionRECT->setFillColor(Color::Red);
	Vector2f avionRECTrecsize;
	avionRECTrecsize.x = 5;
	avionRECTrecsize.y = 5;
	avionRECT->setSize(avionRECTrecsize);

	zona_disparoRECT = new RectangleShape;
	zona_disparoRECT->setFillColor(Color::Green);
	Vector2f zona_disparoRECTrecsize;
	zona_disparoRECTrecsize.x = 400;
	zona_disparoRECTrecsize.y = 100;
	zona_disparoRECT->setSize(zona_disparoRECTrecsize);


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

	/*
	if (Mouse::isButtonPressed(Mouse::Middle) && pantalla_menu == false)
	{
		pantalla_juego = false;
		pantalla_fin = true;
	}
	*/
	

}

void Juego::DrawGame()
{
	//PANTALLA DE INICIO
	menus->dibujar_inicio(pWnd, pantalla_fondo, Mira_cursor);
	//PANTALLA DE FIN
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
	
	
	pWnd->draw(soldado->get_sprite());
	pWnd->draw(Mira_cursor->get_sprite()); //dibujo la mira
	pWnd->draw(*soldadoRECT);
	pWnd->draw(*zona_disparoRECT);
	pWnd->draw(*avionRECT);
	
	}
	//MENUS DE PANTALLA DE JUEGO
	menus->dibujar_menu_juego(pWnd, pantalla_fondo, Mira_cursor);
}

void Juego::UpdateGame()
{
	//MENU
	//pantalla menu
	menus->inicio_actualizar(Mira_cursor, mouserposition, pWnd, evt);
	//pantalla del menu de juego
	menus->menu_juego_actualizar(vida,puntaje,fase);
	//pantalla  de fin
	menus->fin_actualizar(Mira_cursor, mouserposition, pWnd, evt);
	//DISPARAR
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		disparar_proyectiles(proyectil_pos_de_disparo, 0); //crea los proyectilesproyectiles

	}
	//MOVIMIENTOS
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		soldado->mov_derecha();
		//cout << "funciona la D" << endl;
	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		soldado->mov_izquierda();
		//cout << "funciona la D" << endl;
	}
	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		soldado->saltar();
		//cout << "funciona la D" << endl;
	}

	//pantalla juego
	if (menus->get_pantalla_juego() == true)
	{
	//reloj
	tiempo2 = reloj->getElapsedTime().asSeconds();

	//mira
	Mira_cursor->set_pos_mira(mouserposition);

	//disparar proyectiles (los crea)
	proyectil_pos_de_disparo.x = soldadoRECT->getPosition().x;
	proyectil_pos_de_disparo.y = soldadoRECT->getPosition().y;

	

	//personaje
	soldado->actualizar();

	//RECTANGULOS DE PRUEBA ACTUALIZAR POS
	soldadoRECT->setPosition(soldado->get_sprite().getPosition().x, soldado->get_sprite().getPosition().y);
	avionRECT->setPosition(bombardero->get_sprite_avion().getPosition().x, bombardero->get_sprite_avion().getPosition().y);
	zona_disparoRECT->setPosition(200, 0);

	//disparar proyectiles actualizar
	if (proyectil_torretaDOS.size() >= 0)
	{

		for (int i = 0; i < proyectil_torretaDOS.size(); i++)
		{
			proyectil_torretaDOS[i]->actualizar(0);
		}
	}

	//actualizar avion
	bombardero->actualizar();
	
	//actualizar bombas
	if (pelotas.size() >= 0)
	{
		for (int i = 0; i < pelotas.size(); i++)
		{
		pelotas[i]->actualizar();
		}
	}
	

	//posiciones y estados
	// 
	//NOTA : SE PUEDE HACER UN RECT PARA MANEJAR EL AREA DE LANZAMIENTO Y ASI SERIA MAS FACIL MODIFICAR SU ESPACIO MIENTRAS SE AUMENTA EL NIVEL.

	if (bombardero->get_sprite_avion().getScale().x == 1) //cambio de trayectoria del avion.
	{
	bombaposition.x = bombardero->get_sprite_avion().getPosition().x + (bombardero->get_sprite_avion().getGlobalBounds().width / 2);

	}
	if (bombardero->get_sprite_avion().getScale().x == -1)
	{
		bombaposition.x = bombardero->get_sprite_avion().getPosition().x - (bombardero->get_sprite_avion().getGlobalBounds().width / 2);
	}

	bombaposition.y = bombardero->get_sprite_avion().getPosition().y + 134;

	//tirar bombas
	if (tiempo2 > tiempo3)
	{
		tiempo3 = tiempo2 + 0.25f;
		if (bombardero->posision_disparo() == true)
		{
			pelotas.push_back(new Pelota(bombaposition, bombardero->get_velocidad_avion_X()));
		}
	}
	
	//CONDICION DE GAME OVER
	if (vida <= 0)
	{
		Game_over = true;
	}
	
	//RESETEO EL JUEGO cuando pierdo.
	resetear_juego();
	
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
					puntaje += 10;
					delete proyectil_torretaDOS[j];
					proyectil_torretaDOS.erase(proyectil_torretaDOS.begin() + j);
					delete pelotas[i];
					pelotas.erase(pelotas.begin() + i);
					break;
				}
			}
		}
	}
	// destruir proyectiles que pasen el eje y = 0;
	/*
	*/
	if (proyectil_torretaDOS.size() >= 0)
	{
		
		for (int i = 0; i < proyectil_torretaDOS.size(); i++)
		{
			if (proyectil_torretaDOS[i]->get_sprite().getPosition().y < 50)
			{
				//para no hacer 
				delete proyectil_torretaDOS[i]; 
				proyectil_torretaDOS.erase(proyectil_torretaDOS.begin() + i);
				break;
			}
		}

	}

	// destuir bombas que pasen el eje y = 600;
	if (pelotas.size() >= 0)
	{
		for (int i = 0; i < pelotas.size(); i++)

		{
			if (pelotas[i]->get_sprite().getPosition().y > 575)
			{
				delete pelotas[i];
				pelotas.erase(pelotas.begin() + i);

				vida--;
				break;
				//break;
			}

		}

	}
	
	}
}


void Juego::Go()
{
	
	//objeto para recibir eventos
	
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

		proyectil_torretaDOS.push_back(new Proyectil(pos_bocacha, rotacion, mouserposition, soldado));
		

	}
		//cout << "se dibuja una bala" << endl;
		//cout << sprite_torreta.getRotation() << endl;
		//tiempo2 = tiempo1;
	
}

void Juego::prueba_en_consola()
{
	//colocar aqui adentro todo los cout.
	//cout << torretaaire->get_sprite_torreta().getOrigin().y << endl;
	//cout << bombardero->get_sprite_avion().getPosition().x << endl;

}

void Juego::resetear_juego()
{
	if (Game_over == true)
	{
	vida = 5;
	puntaje = 0;
	fase = 1;
	pelotas.clear();
	for (auto it = pelotas.begin(); it != pelotas.end(); it++)
	{
		delete* it;
	}
	for (auto it = proyectil_torretaDOS.begin(); it != proyectil_torretaDOS.end(); it++)
	{
		delete* it;
	}
	proyectil_torretaDOS.clear();
	bombardero->reset_avion();
	Game_over = false;
	menus->set_pantalla_juego(false);
	menus->set_pantalla_fin(true);
	}
}

Juego::~Juego()
{
	delete pWnd;
	delete pantalla_fondo;
	delete bombardero;
	delete Mira_cursor;
	delete menus;
	delete reloj;
	delete tiempo1;
	delete soldado;
	for (auto it = pelotas.begin(); it != pelotas.end(); it++)
	{
		delete* it;
	}
	pelotas.clear();
	for (auto it = proyectil_torretaDOS.begin(); it != proyectil_torretaDOS.end(); it++)
	{
		delete* it;
	}
	proyectil_torretaDOS.clear();
}
