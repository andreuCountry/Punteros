#include <stdio.h>
#include <stdlib.h>
#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <esat/time.h>
#include <conio.h>
#include <time.h>

enum Direction {
    UR,
    UL,
    DR,
    DL
};

struct Coordenate {
    int x, y;
};

struct TBall {
    Coordenate coordenate;
    esat::SpriteHandle sprite;
    int speed;
    Direction direction;
};

// You know what i mean 
unsigned char si = 0, fps=25; //Control de frames por segundo
double current_time, last_time;
int windowX, windowY, numberFigures = 0;
int container = 0;


TBall* ballData = nullptr;

esat::SpriteHandle sprite1, sprite2, blue, green;

void GenerateSeed() {
    srand(time(NULL));
}

Direction ChooseDirection() {

    int number = rand()%3;

    Direction direction;

    switch (number) {
        case 0:
            direction = UR;
        break;
        case 1:
            direction = UL;
        break;
        case 2:
            direction = DR;
        break;
        case 3:
            direction = DL;
        break;
    }

    return direction;
}

void InitSprites() {

    sprite1 = esat::SpriteFromFile("./Recursos/Imagenes/Sprites/bola1.png");
    sprite2 = esat::SpriteFromFile("./Recursos/Imagenes/Sprites/bola2.png");
    blue = esat::SpriteFromFile("./Recursos/Imagenes/Sprites/azul.png");
    green = esat::SpriteFromFile("./Recursos/Imagenes/Sprites/verde.png");

    for (int i = 0; i < numberFigures; i++) {
        (ballData + i)->coordenate = {rand()%windowX, rand()%windowY};
        (ballData + i)->sprite = sprite1;
        (ballData + i)->speed = rand()%15 + 1;
        (ballData + i)->direction = ChooseDirection();
    }
}

void InitMemory() {
    ballData = (TBall*) realloc(ballData, (numberFigures)*sizeof(TBall));
}

bool CheckBorders(TBall ball) {
    
    // use sprite weight and height and coordenate
    Coordenate ballCoordenate = ball->coordenate;

    if (ballCoordenate.x > windowX) {

    }
}

void AddMovement(TBall ball) {

    bool cross = CheckBorders(ball);
}

void Draw() {

    esat::SpriteHandle color;
    container++;

    for (int i = 0; i < numberFigures; i++) {

        if (i % 2 == 0) {
            color = green;
        } else {
            color = blue;
        }

        if (container == 30) {
            if ((ballData + i)->sprite == sprite1) {
                (ballData + i)->sprite = sprite2;
            } else {
                (ballData + i)->sprite = sprite1;
            }
        }
        
        AddMovement((ballData + i));

        esat::DrawSprite(color, (ballData + i)->coordenate.x, (ballData + i)->coordenate.y);
        esat::DrawSprite((ballData + i)->sprite, (ballData + i)->coordenate.x, (ballData + i)->coordenate.y);
    }

    if (container == 30) {
        container = 0;
    }

}

int esat::main(int argc, char **argv) {

    GenerateSeed();

    if (argc == 4) {
        windowX = atoi(*(argv+1));
        windowY = atoi(*(argv+2));
        numberFigures = atoi(*(argv+3));
    }
    
	esat::WindowInit(windowX, windowY);
	WindowSetMouseVisibility(true);

    InitMemory();

    InitSprites();

    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	last_time = esat::Time(); 
            
    	esat::DrawBegin();

    	esat::DrawClear(0, 0, 0);

        Draw();
        AddMovement();

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
