#include <iostream>
#include "Juego.h"



int main(int argc, char* argv[])
{
	
	srand((int)time(NULL));
	
	Juego jugar(800, 600, "BomberSHooter");
	jugar.Go();
	

	return 0;

}