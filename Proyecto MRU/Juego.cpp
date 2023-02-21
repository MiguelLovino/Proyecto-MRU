#include "Juego.h"


Juego::Juego(int alto, int ancho, string titulo)

{
	
	pWnd = new RenderWindow(VideoMode(pantalla_ancho, pantalla_alto), titulo);
	
	pantalla_fondo = new Pantalla(pantalla_ancho, pantalla_alto);
	bombardero = new Avion(pantalla_ancho);
	Mira_cursor = new Mira;
	menus = new Menu;
	reloj = new Clock;
	tiempo1 = new Time;

	pWnd->setFramerateLimit(60);
	pWnd->setMouseCursorVisible(false);
	pWnd->setMouseCursorGrabbed(true);
	soldado = new Jugador(pantalla_ancho, pantalla_alto);

	//rectangulos de pruebas
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

	zona_disparoRECTrecsize.x = 80;
	zona_disparoRECTrecsize.y = 5;
	zona_disparoRECT->setSize(zona_disparoRECTrecsize);
	limite_ancho_derecha.setSize(Vector2f(1, (float)pantalla_alto));
	limite_ancho_derecha.setPosition((float)pantalla_ancho, 0);
	limite_ancho_izquierda.setSize(Vector2f(1, (float)pantalla_alto));
	//sonidos
	buffer_explo.loadFromFile("recursos/Sonido/explota bomba2.ogg");
	sound_explo.setBuffer(buffer_explo);
	sound_explo.setVolume(25);
	//gameover
	buffer_vida_menos.loadFromFile("recursos/Sonido/game over2.wav");
	sound_vida_menos.setBuffer(buffer_vida_menos);


}
void Juego::ProcessEvent(Event& evt)
{


	//eventos de teclado, etc

	if (evt.type == evt.Closed)
	{
		pWnd->close();

	}
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		pWnd->close();
	}

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
		//** DIBUJAR ACA LAS COSAS QUE NECESITO ESCONDER (para testing) **//

		pWnd->draw(pantalla_fondo->get_sprite_fondoPantalla()); //dibujo pantalla
	
		pWnd->draw(*zona_disparoRECT);
		pWnd->draw(*soldadoRECT);
		pWnd->draw(soldado->get_colider());
		pWnd->draw(*avionRECT);

		//************************************************//

		pWnd->draw(bombardero->get_sprite_avion()); //avion
		//dibujo barriles
		dibujar_vectores(barril_explosivo);
		//dibujo bombas
		dibujar_vectores(pelotas);
		//dibujo proyectiles
		dibujar_vectores(proyectiles_en_juego);
		pWnd->draw(soldado->get_sprite());
		pWnd->draw(Mira_cursor->get_sprite()); //dibujo la mira
		

	}
	//MENUS DE PANTALLA DE JUEGO
	menus->dibujar_menu_juego(pWnd, pantalla_fondo, Mira_cursor);

}

void Juego::UpdateGame()
{
	mouserposition.x = (float)Mouse::getPosition(*pWnd).x;
	mouserposition.y = (float)Mouse::getPosition(*pWnd).y;
	
	Mira_cursor->set_pos_mira(mouserposition);

	//MENU
	//pantalla menu
	menus->inicio_actualizar(Mira_cursor, mouserposition, pWnd, evt);

	//pantalla del menu de juego
	menus->menu_juego_actualizar(vida, puntaje, fase);

	//pantalla  de fin
	menus->fin_actualizar(Mira_cursor, mouserposition, pWnd, evt, puntaje_fina);

	//ventana de disparo de bombas
	zona_disparoRECT->setSize(zona_disparoRECTrecsize);

	//*************************GAMEPLAY SCREEN*************************************
	// 
	//reloj
	tiempo2 = reloj->getElapsedTime().asSeconds();

	if (menus->get_pantalla_juego() == true)
	{
		//EVENTOS
		//DISPARAR
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			soldado->disparar_proyectiles(proyectil_pos_de_disparo,mouserposition,tiempo2,tiempo4,proyectiles_en_juego); //crea los proyectilesproyectiles

		}
		//MOVIMIENTOS
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			soldado->mov_derecha();

		}
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			soldado->mov_izquierda();

		}
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			soldado->saltar();

		}

		

		//disparar proyectiles (los crea)

		proyectil_pos_de_disparo.x = soldadoRECT->getPosition().x;
		proyectil_pos_de_disparo.y = soldadoRECT->getPosition().y;

		//personaje
		soldado->actualizar(Mira_cursor->get_sprite().getPosition(), limite_ancho_derecha, limite_ancho_izquierda, pantalla_ancho, pantalla_alto);

		//actualizar pos a donde mira.
		if (Mira_cursor->get_sprite().getPosition().x > soldado->get_sprite().getPosition().x)
		{
			soldadoRECT->setPosition(soldado->get_sprite().getPosition().x + 23, soldado->get_sprite().getPosition().y);

		}
		else
		{
			soldadoRECT->setPosition(soldado->get_sprite().getPosition().x + 30 * -1, soldado->get_sprite().getPosition().y);
		}

		avionRECT->setPosition(bombardero->get_sprite_avion().getPosition().x, bombardero->get_sprite_avion().getPosition().y);


		//disparar proyectiles actualizar
		if (proyectiles_en_juego.size() >= 0)
		{

			for (int i = 0; i < proyectiles_en_juego.size(); i++)
			{
				proyectiles_en_juego[i]->actualizar();
			}
		}
		//zona de disparo
		zona_disparoRECT->setPosition(pantalla_ancho / 2 - zona_disparoRECT->getGlobalBounds().width / 2, 50);
		//actualizar avion
		bombardero->actualizar(*zona_disparoRECT);

		//actualizar bombas
		if (pelotas.size() >= 0)
		{
			for (int i = 0; i < pelotas.size(); i++)
			{
				pelotas[i]->actualizar(limite_ancho_derecha, limite_ancho_izquierda);
			}
		}

		//actualizar barriles
		if (barril_explosivo.size() >= 0)
		{
			for (int i = 0; i < barril_explosivo.size(); i++)
			{
				barril_explosivo[i]->actualizar();

				acercamiento = (int)(soldado->get_sprite().getPosition().x - barril_explosivo[i]->get_sprite().getPosition().x);


			}
		}

		//posiciones y estados

		//actualizo el sprite del avion cuando llega al final de la pantalla

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
			tiempo3 = tiempo2 + 0.50f;
			if (bombardero->posision_disparo(*zona_disparoRECT) == true && cant_bombas < max_bombas)
			{
				pelotas.push_back(new Bomba(bombaposition, bombardero->get_velocidad_avion_X(), aceleracion_bomba));
				cant_bombas++;
			}
		}

		if (tiempo2 > tiempo_barril_explosivo)
		{
			tiempo_barril_explosivo = tiempo2 + 1.25f;
			if (bombardero->posision_disparo(*zona_disparoRECT) == true && cant_barriles < max_barriles)
				barril_explosivo.push_back(new Barril(velocidad_barril,pantalla_ancho,pantalla_alto));
			cant_barriles++;
		}

		//tirar barriles
		velocidad_de_las_bombas();

		//***************reset cargador de bombas***********************//
		//se resetean las bombas y los barriles cuando el avion se encuentra en un punto ciego, entre los bordes y la ventana de disparo.
		if (bombardero->get_sprite_avion().getGlobalBounds().intersects(limite_ancho_derecha.getGlobalBounds()) ||
			bombardero->get_sprite_avion().getGlobalBounds().intersects(limite_ancho_izquierda.getGlobalBounds()) &&
			!bombardero->get_sprite_avion().getGlobalBounds().intersects(zona_disparoRECT->getGlobalBounds()))
		{
			cant_bombas = 0;
			//tambien reseteo los barriles.
			cant_barriles = 0;
		}




		//*************************GAMEOVER*************************************
		if (vida <= 0)
		{
			sound_vida_menos.play();
			puntaje_fina = puntaje;
			Game_over = true;
		}

		//*************************GAME RESET*************************************

		resetear_juego();

	}
}

void Juego::ProcessCollisions()
{

	//****************GAME MENU***************************************//
	if (menus->get_pantalla_juego() == true)
	{
		//coliciones
		//colicion de bombas con proyectiles.
		if (pelotas.size() >= 0 && proyectiles_en_juego.size() >= 0)
		{

			for (int i = 0; i < pelotas.size(); i++)
			{
				for (int j = 0; j < proyectiles_en_juego.size(); j++)
				{
					if (proyectiles_en_juego[j]->get_sprite().getGlobalBounds().intersects(pelotas[i]->get_sprite().getGlobalBounds()))
					{
						//cout << "se produjo colicion" << endl;
						puntaje += 10;
						delete proyectiles_en_juego[j];
						proyectiles_en_juego.erase(proyectiles_en_juego.begin() + j);
						sound_explo.play();
						delete pelotas[i];
						pelotas.erase(pelotas.begin() + i);
						break;
					}
				}
			}
		}

		//colicion barriles con proyectil

		if (barril_explosivo.size() >= 0 && proyectiles_en_juego.size() >= 0)
		{

			for (int i = 0; i < barril_explosivo.size(); i++)
			{
				for (int j = 0; j < proyectiles_en_juego.size(); j++)
				{
					if (proyectiles_en_juego[j]->get_sprite().getGlobalBounds().intersects(barril_explosivo[i]->get_sprite().getGlobalBounds()))
					{
						//cout << "se produjo colicion" << endl;
						puntaje += 10;
						delete proyectiles_en_juego[j];
						proyectiles_en_juego.erase(proyectiles_en_juego.begin() + j);
						sound_explo.play();
						delete barril_explosivo[i];
						barril_explosivo.erase(barril_explosivo.begin() + i);
						break;
					}
				}
			}
		}

		//colicion de proyectiles con los bordes de la pantalla.
		if (proyectiles_en_juego.size() >= 0)
		{

			for (int i = 0; i < proyectiles_en_juego.size(); i++)
			{
				int y = (int)proyectiles_en_juego[i]->get_sprite().getPosition().y;
				int x = (int)proyectiles_en_juego[i]->get_sprite().getPosition().x;

				if (y < 50 || y > pantalla_alto || x < 20 || x > pantalla_ancho)
				{
					delete proyectiles_en_juego[i];
					proyectiles_en_juego.erase(proyectiles_en_juego.begin() + i);
					break;
				}
			}
		}

		//colicion de los barriles con los bordes de la pantalla.
		if (barril_explosivo.size() >= 0)
		{
			for (int i = 0; i < barril_explosivo.size(); i++)
			{
				if (barril_explosivo[i]->get_sprite().getGlobalBounds().intersects(limite_ancho_izquierda.getGlobalBounds()) &&
					barril_explosivo[i]->get_sprite().getFillColor() == Color::Green)
				{
					delete barril_explosivo[i];
					barril_explosivo.erase(barril_explosivo.begin() + i);
					break;
				}
				if (barril_explosivo[i]->get_sprite().getGlobalBounds().intersects(limite_ancho_derecha.getGlobalBounds()) &&
					barril_explosivo[i]->get_sprite().getFillColor() != Color::Green)
				{
					delete barril_explosivo[i];
					barril_explosivo.erase(barril_explosivo.begin() + i);
					break;
				}
			}
		}

		//colicion de barril con personaje;
		if (barril_explosivo.size() >= 0)
		{
			for (int i = 0; i < barril_explosivo.size(); i++)
			{
				if (barril_explosivo[i]->get_sprite().getGlobalBounds().intersects(soldado->get_colider().getGlobalBounds()))
				{
					delete barril_explosivo[i];
					barril_explosivo.erase(barril_explosivo.begin() + i);
					vida--;
					soldado->reprodicir_dolor();
					break;
				}

			}
		}

		//colicion de bombas con el suelo (SE PIERDEN VIDAS)
		if (pelotas.size() >= 0)
		{
			for (int i = 0; i < pelotas.size(); i++)

			{
				if (pelotas[i]->get_sprite().getPosition().y > pantalla_alto - pelotas[i]->get_sprite().getGlobalBounds().height) //CHECKEAR LA DISTANCIA
				{
					sound_explo.play();
					delete pelotas[i];
					pelotas.erase(pelotas.begin() + i);
					//SONIDO DE PERDIDA DE VIDA
					vida--;
					break;
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


bool Juego::bombas_en_pantalla()
{
	if (pelotas.size() > 0)
	{

		return true;
	}
	else
	{

		return false;
	}
}

void Juego::velocidad_de_las_bombas() //CAMBIAR NOMBRE A DIFICULTAD
{
	//************************************actualizar nivel**********************//
	if (puntaje >= 60 && puntaje < 100 && bombas_en_pantalla() == false) //AGREGAR BARRILES EN PANTALLA?
	{
		max_bombas = 5;
		max_barriles = 3;
		zona_disparoRECTrecsize.x = 160;
		zona_disparoRECT->setSize(zona_disparoRECTrecsize);
		aceleracion_bomba = 40;
		velocidad_barril = 10;

	}
	if (puntaje >= 100 && puntaje < 180 && bombas_en_pantalla() == false)
	{
		max_bombas = 7;
		max_barriles = 4;
		zona_disparoRECTrecsize.x = 240;
		zona_disparoRECT->setSize(zona_disparoRECTrecsize);
		aceleracion_bomba = 50;
		velocidad_barril = 15;
	}
	if (puntaje >= 180 && puntaje < 250 && bombas_en_pantalla() == false)
	{
		max_bombas = 9;
		max_barriles = 5;
		zona_disparoRECTrecsize.x = 320;
		zona_disparoRECT->setSize(zona_disparoRECTrecsize);
		aceleracion_bomba = 60;
		velocidad_barril = 20;
	}
	if (puntaje >= 250 && puntaje < 420 && bombas_en_pantalla() == false)
	{
		max_bombas = 11;
		max_barriles = 6;
		zona_disparoRECTrecsize.x = 400;
		zona_disparoRECT->setSize(zona_disparoRECTrecsize);
		aceleracion_bomba = 70;
		velocidad_barril = 20;
	}
	if (puntaje >= 420 && puntaje < 600 && bombas_en_pantalla() == false)
	{
		max_bombas = 13;
		max_barriles = 6;
		zona_disparoRECTrecsize.x = 480;
		zona_disparoRECT->setSize(zona_disparoRECTrecsize);
		aceleracion_bomba = 80;
		velocidad_barril = 25;
	}
}

void Juego::prueba_en_consola()
{
	//colocar aqui adentro todo los cout.
	//cout << torretaaire->get_sprite_torreta().getOrigin().y << endl;
	//cout << bombardero->get_sprite_avion().getPosition().x << endl;
	//cout << soldado->get_sprite().getPosition().x << endl;
	//cout << Mira_cursor->get_sprite().getPosition().x << endl;
	//bombas_en_pantalla();
	//cout << acercamiento << endl;
	//cout << soldado->get_sprite().getGlobalBounds().width << endl;
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
		/*
		for (auto it = soldado->get_disparos().begin(); it != soldado->get_disparos().end(); it++)
		{
			delete* it;
		}
		soldado->get_disparos().clear();
		*/
		for (auto it = barril_explosivo.begin(); it != barril_explosivo.end(); it++)
		{
			delete* it;
		}
		barril_explosivo.clear();
		bombardero->reset_avion();
		soldado->reset(pantalla_ancho);
		Game_over = false;
		menus->set_pantalla_juego(false);
		menus->set_pantalla_fin(true);
		zona_disparoRECTrecsize.x = 80;
		max_bombas = 3;
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
	/*
	for (auto it = soldado->get_disparos().begin(); it != soldado->get_disparos().end(); it++)
	{
		delete* it;
	}
	
	soldado->get_disparos().clear();
	*/
	for (auto it = barril_explosivo.begin(); it != barril_explosivo.end(); it++)
	{
		delete* it;
	}
	barril_explosivo.clear();
}
