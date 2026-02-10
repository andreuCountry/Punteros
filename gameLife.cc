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
int windowX = 800, windowY = 800, filas;
char* born = nullptr;
char* dead = nullptr;

struct Color {
	int R, G, B;
};

struct TCelula {
	esat::Vec2 initialPosition;
	esat::Vec2 lastPosition;
	bool IsAlive = false;
	Color color;
};

TCelula* celulaData = nullptr;

void GenerateSeed() {
    srand(time(NULL));
}

void TakeBornDead(char* argv) {

	born = (char*) malloc((3)*sizeof(char));
	dead = (char*) malloc((3)*sizeof(char));

	bool isDead = false;

	for (int i = 0; i < 7; i++) {

		if (*(argv+i) != '/' && !isDead) {
			*(born+i) = *(argv+i);
		} else {
			isDead = true;
		}

		if (isDead && i < 6) {
			int j = 0;
			*(dead+j) = *(argv+i+1);
			j++;
		}
	}
}

void InitMemory() {
	filas = filas * filas;
	celulaData = (TCelula*) malloc(filas*sizeof(TCelula));
}

void DrawBox(esat::Vec2 initialPosition, esat::Vec2 lastPosition, bool isAlive) {
	float rect[10] = {
        initialPosition.x, initialPosition.y,
        lastPosition.x, initialPosition.y,
        lastPosition.x, lastPosition.y,
        initialPosition.x, lastPosition.y,
        initialPosition.x, initialPosition.y
    };

	if (isAlive) {
		esat::DrawSetStrokeColor(255, 0, 0, 0);
    	esat::DrawSetFillColor(255, 0, 0, 0);
    	esat::DrawSolidPath(rect, 5);
	} else {
		esat::DrawSetStrokeColor(255, 0, 0, 0);
    	esat::DrawSetFillColor(0, 0, 0, 0);
    	esat::DrawSolidPath(rect, 5);
	}
}

void InitMap() {
	float coordenateX = 0.0f;
	float coordenateY = windowY / filas;
	for (int i = 0; i < filas; i++) {
		int random = rand()%1;

		if (random == 1) {
			(celulaData+i)->IsAlive = true;
			(celulaData+i)->color = {255, 0, 0};
		}

		if (coordenateX + (windowX / filas) < 800) {
			(celulaData+i)->initialPosition = {coordenateX, coordenateY};
			(celulaData+i)->lastPosition = {coordenateX + (windowX / filas), coordenateY};
			coordenateX += windowX / filas;
			DrawBox((celulaData+i)->initialPosition, (celulaData+i)->lastPosition, (celulaData+i)->IsAlive);
		} else {
			coordenateX = 0;
			coordenateY += windowY / filas;
		}
	}


}

int esat::main(int argc, char **argv) {

    GenerateSeed();
	
	if (argc == 3) {
    	fgets(*(argv+1), 8, stdin);
        filas = atoi(*(argv+2));
    }

	TakeBornDead(*(argv+1));
	InitMemory();

	esat::WindowInit(windowX, windowY);
	WindowSetMouseVisibility(true);

    // Init parts

    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	last_time = esat::Time(); 
            
    	esat::DrawBegin();

    	esat::DrawClear(0, 0, 0);

		InitMap();

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
