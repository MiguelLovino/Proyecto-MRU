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
		pWnd->draw(*zona_disparoRECT);
		pWnd->draw(*soldadoRECT);
		pWnd->draw(soldado->get_colider());
		pWnd->draw(*avionRECT);

		pWnd->draw(pantalla_fondo->get_sprite_fondoPantalla()); //dibujo pantalla
	

		//************************************************//

		pWnd->draw(bombardero->get_sprite_avion()); //avion
		//dibujo barriles
		dibujar_vectores(barril_explosivo);
		//dibujo bombas
		dibujar_vectores(bombas);
		dibujar_vectores(granada_de_mano);
		//dibujo proyectiles
		dibujar_vectores(proyectiles_en_juego);
		pWnd->draw(soldado->get_sprite());
		pWnd->draw(Mira_cursor->get_sprite()); //dibujo la mira
		

	}
	//MENUS DE PANTALLA DE JUEGO
	menus->dibujar_menu_juego(pWnd, pantalla_fondo, Mira_cursor, vida);

}

void Juego::UpdateGame()
{
	//actualizo la pos de la mira
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
			//crea los proyectilesproyectiles
			soldado->disparar_proyectiles(proyectil_pos_de_disparo,mouserposition,tiempo2,tiempo4,proyectiles_en_juego); 

		}
		if (Keyboard::isKeyPressed(Keyboard::R))
		{
			soldado->tirar_granadas(proyectil_pos_de_disparo, mouserposition,tiempo2, tiempo5, granada_de_mano);
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

		proyectil_pos_de_disparo.x = soldadoRECT->getPosition().x;
		proyectil_pos_de_disparo.y = soldadoRECT->getPosition().y;

		//actualizo personaje
		soldado->actualizar(Mira_cursor->get_sprite().getPosition(), limite_ancho_derecha, limite_ancho_izquierda, pantalla_ancho, pantalla_alto);

		//actualizo la posicion del sprite segun donde "apunte"
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
		bombardero->actualizar(*zona_disparoRECT, bombas_en_pantalla());

		//actualizar bombas
		if (bombas.size() >= 0)
		{
			for (int i = 0; i < bombas.size(); i++)
			{
				bombas[i]->actualizar(limite_ancho_derecha, limite_ancho_izquierda);
			}
		}

		//actualizar barriles
		if (barril_explosivo.size() >= 0)
		{
			for (int i = 0; i < barril_explosivo.size(); i++)
			{
				barril_explosivo[i]->actualizar();
				//acercamiento = (int)(soldado->get_sprite().getPosition().x - barril_explosivo[i]->get_sprite().getPosition().x);
			}
		}

		//actualizar granadas
		if (granada_de_mano.size() >= 0)
		{
			for (int i = 0; i < granada_de_mano.size(); i++)
			{
				granada_de_mano[i]->actualizar();
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
				bombas.push_back(new Bomba(bombaposition, bombardero->get_velocidad_avion_X(), aceleracion_bomba));
				cant_bombas++;
			}
		}

		//tirar barriles
		if (tiempo2 > tiempo_barril_explosivo)
		{
			tiempo_barril_explosivo = tiempo2 + 1.25f;
			if (bombardero->posision_disparo(*zona_disparoRECT) == true && cant_barriles < max_barriles)
				barril_explosivo.push_back(new Barril(velocidad_barril,pantalla_ancho,pantalla_alto));
			cant_barriles++;
		}
		
		//actualizo la dificultad del juego
		dificultad_de_juego();

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
							//********************COLICIONES**********************//
		//colicion de bombas con proyectiles.
		colicion_de_objetos(bombas, proyectiles_en_juego);

		//colicion barriles con proyectil
		colicion_de_objetos(barril_explosivo, proyectiles_en_juego);

		//colicion de granada con barriles
		colicion_de_objetos(barril_explosivo, granada_de_mano);

		//colicion de granadas con los bordes de la pantalla.
		colicion_de_objeto_con_pantalla(granada_de_mano);

		//colicion de proyectiles con los bordes de la pantalla.
		colicion_de_objeto_con_pantalla(proyectiles_en_juego);

		//colicion de los barriles con los bordes de la pantalla.
		colicion_de_objeto_con_pantalla(barril_explosivo);

		//colicion de barril con personaje (SE PIERDEN VIDAS)
		if (barril_explosivo.size() > 0)
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
		if (bombas.size() > 0)
		{
			for (int i = 0; i < bombas.size(); i++)
			{
				if (bombas[i]->get_sprite().getPosition().y > pantalla_alto - bombas[i]->get_sprite().getGlobalBounds().height) //CHECKEAR LA DISTANCIA
				{
					sound_explo.play();
					delete bombas[i];
					bombas.erase(bombas.begin() + i);
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
		//procesar colisiones
		ProcessCollisions();
		//actualizar estados de objetos
		UpdateGame();
		pWnd->clear();
		//dibujo
		DrawGame();
		prueba_en_consola();
		pWnd->display();

	}
}


bool Juego::bombas_en_pantalla()
{
	if (bombas.size() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Juego::dificultad_de_juego()
{
	//************************************actualizar nivel**********************//
	if (puntaje >= 60 && puntaje < 100 && bombas_en_pantalla() == false)
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
}



void Juego::resetear_juego()
{
	if (Game_over == true)
	{
		vida = 5;
		puntaje = 0;
		fase = 1;
		borrar_vectores(bombas);
		bombas.clear();
		borrar_vectores(proyectiles_en_juego);
		proyectiles_en_juego.clear();
		borrar_vectores(barril_explosivo);
		barril_explosivo.clear();
		borrar_vectores(granada_de_mano);
		granada_de_mano.clear();
		bombardero->reset_avion(pantalla_ancho);
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
	borrar_vectores(bombas);
	bombas.clear();
	borrar_vectores(proyectiles_en_juego);
	proyectiles_en_juego.clear();
	borrar_vectores(barril_explosivo);
	barril_explosivo.clear();
	borrar_vectores(granada_de_mano);
	granada_de_mano.clear();
}

