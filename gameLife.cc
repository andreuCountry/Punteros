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
int windowX = 800, windowY = 800, filas, totalCeldas;
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
			int j = 0; *(dead+j) = *(argv+i+1); j++; 
		} 
	}
}

void InitMemory() {
	totalCeldas = filas * filas;
	celulaData = (TCelula*) malloc(totalCeldas*sizeof(TCelula));
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
    	esat::DrawSetFillColor(255, 0, 0, 255);
    	esat::DrawSolidPath(rect, 5);
	} else {
		esat::DrawSetStrokeColor(255, 0, 0, 0);
    	esat::DrawSetFillColor(0, 0, 0, 255);
    	esat::DrawSolidPath(rect, 5);
	}
}

void DrawAllCells() {
	for (int i = 0; i < totalCeldas; i++) {
		DrawBox((celulaData+i)->initialPosition, (celulaData+i)->lastPosition, (celulaData+i)->IsAlive);
	}
}

void InitMap() {
	float cellWidth = (float)windowX / filas;
    float cellHeight = (float)windowY / filas;
    float coordenateX = 0.0f;
    float coordenateY = 0.0f;

    for (int i = 0; i < totalCeldas; i++) {

        (celulaData + i)->initialPosition = {coordenateX, coordenateY};
        (celulaData + i)->lastPosition = {coordenateX + cellWidth, coordenateY + cellHeight};

        coordenateX += cellWidth;

        if (coordenateX >= windowX) {
            coordenateX = 0.0f;
            coordenateY += cellHeight;
        }
    }
}

void InitCells() {
 	for (int i = 0; i < totalCeldas; i++) {
    	(celulaData+i)->IsAlive = (rand() % 5 == 0);

		if ((celulaData+i)->IsAlive == 1) {
			(celulaData+i)->color = {255, 0, 0};
		}
  	}
}

int NumOfNeighboors(int position) {
	int neighboors = 0;

	int x = position % filas;
	int y = position / filas;

	for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) {
				continue;
			}

            int columnaX = x + dx;
            int columnaY = y + dy;

            if (columnaX >= 0 && columnaX < filas && columnaY >= 0 && columnaY < filas) {
                int vecinoIndex = columnaY * filas + columnaX;
                if ((celulaData + vecinoIndex)->IsAlive) {
                    neighboors++;
                }
            }
        }
    }

	return neighboors;
}

void UpdateToDie(TCelula* celula, int position) {
	int NumberOfNeighboors = NumOfNeighboors(position);

	// Logic

	if (dead[0] - '0' == NumberOfNeighboors ||
		dead[1] - '0' == NumberOfNeighboors ||
		dead[2] - '0' == NumberOfNeighboors) {

			celula->IsAlive = false;
	}
}

void UpdateGeneration() {
    bool* nextStage = (bool*) malloc(totalCeldas * sizeof(bool));

    for (int i = 0; i < totalCeldas; i++) {
        int neighbors = NumOfNeighboors(i);
        nextStage[i] = celulaData[i].IsAlive;

		// Si vive, tenemos max range de vecinos y minimo, sabiendo eso, le decimos que muere
        if (celulaData[i].IsAlive) {
            int minDead = dead[0] - '0';
            int maxDead = dead[1] - '0';
            if (neighbors < minDead || neighbors > maxDead) {
                nextStage[i] = false;
            }
        } else {
			// Si esta en rango de vivir, la mantenemos
            int minBorn = born[0] - '0';
            int maxBorn = born[1] - '0';
            if (neighbors >= minBorn && neighbors <= maxBorn) {
                nextStage[i] = true;
            }
        }
    }

    for (int i = 0; i < totalCeldas; i++) {
        celulaData[i].IsAlive = nextStage[i];
    }

    free(nextStage);
}



int esat::main(int argc, char **argv) {

    GenerateSeed();
	
	if (argc == 3) {
        filas = atoi(*(argv+2));
		TakeBornDead(*(argv+1));
    }

	InitMemory();

	esat::WindowInit(windowX, windowY);
	WindowSetMouseVisibility(true);

    // Init parts
	InitMap();
	InitCells();

    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	last_time = esat::Time(); 
            
    	esat::DrawBegin();

    	esat::DrawClear(0, 0, 0);

		DrawAllCells();
		UpdateGeneration();

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
