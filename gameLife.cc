#include <stdio.h>
#include <stdlib.h>
#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <esat/time.h>
#include <conio.h>
#include <time.h>

unsigned char si = 0, fps=25; //Control de frames por segundo
double current_time, last_time;
int windowX = 800, windowY = 800, numberFilas;

struct Celula {
	esat::Vec2 coordenate;
	bool IsAlive;
};

void GenerateSeed() {
    srand(time(NULL));
}

int esat::main(int argc, char **argv) {

    GenerateSeed();
	
	if (argc == 3) {
        windowX = atoi(*(argv+1));
        numberFilas = atoi(*(argv+2));
    }

	esat::WindowInit(windowX, windowY);
	WindowSetMouseVisibility(true);

    // Init parts

    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	last_time = esat::Time(); 
            
    	esat::DrawBegin();

    	esat::DrawClear(0, 0, 0);



    	esat::DrawEnd();
    	//Control fps 
    	do{
    		current_time = esat::Time();
    	}while((current_time-last_time)<=1000.0/fps);
    	esat::WindowFrame();

		++si%=7;
    }
  
    esat::WindowDestroy();
    
    return 0;
    
}
