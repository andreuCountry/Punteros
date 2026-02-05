#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

FILE *f;

struct BasicInfo {
    char name[15];
    char description[100];
    char culture[30];
};

const int numPoolValues = 6;

struct CharacterPool {
    int constitution, strenght, charism, intelligence, knowledge, faith;
};

struct Skills {
    int talkative, combat, hide, stealth, health, fatigue, jump, mana;
};

struct Character {
    BasicInfo basicInfo;
    CharacterPool pool;
    Skills skills;
};

Character character;

void GenerateSeed() {
    srand(time(NULL));
}

void PrepareFile() {
    f = fopen("files/model.dat", "r+b");

    // Add all features to send

    fclose(f);
}

void AskBasic() {

    printf("Name of your character: ");
    fgets(character.basicInfo.name, 15, stdin);

    printf("Short description of your character: ");
    fgets(character.basicInfo.description, 100, stdin);

    printf("Associated culture (Example: medieval knight, native refugee): ");
    fgets(character.basicInfo.culture, 30, stdin);
}

void CalculatePoolsFields(int pool, int num1, int num2, int num3) {

    switch (pool) {
        case 0:
            character.pool.constitution = num1 + num2 + num3;
        break;
        case 1:
            character.pool.strenght = num1 + num2 + num3;
        break;
        case 2:
            character.pool.charism = num1 + num2 + num3;
        break;
        case 3:
            character.pool.intelligence = num1 + num2 + num3;
        break;
        case 4:
            character.pool.knowledge = num1 + num2 + num3;
        break;
        case 5:
            character.pool.faith = num1 + num2 + num3;
        break;
    }
}

void printBasicInfo() {
    printf("Here it is your normal information: \n");
    printf("Name: %s", character.basicInfo.name);
    printf("Description: %s", character.basicInfo.description);
    printf("Culture: %s", character.basicInfo.culture);
    printf("\n");
}

void printPool() {
    printf("Here it is your pool of atributes: \n");
    printf("Constitution: %d \n", character.pool.constitution);
    printf("Strenght: %d \n", character.pool.strenght);
    printf("Charism: %d \n", character.pool.charism);
    printf("Intelligence: %d \n", character.pool.intelligence);
    printf("Knowledge: %d \n", character.pool.knowledge);
    printf("Faith: %d \n \n", character.pool.faith);
}

void AskCharacterPool() {
    GenerateSeed();

    printf("We are gonna use 'dados' to calcule your values... \n");

    for (int i = 0; i < numPoolValues; i++) {
        int num1 = rand()%5 + 1, num2 = rand()%5 + 1, num3 = rand()%5 + 1;

        CalculatePoolsFields(i, num1, num2, num3);
    }
    char response;
    printf("End, do you want to see it (Y/n)?");
    scanf("%c", &response);
    printf("\n");

    if (response == 'Y') {
        printPool();
    }
}

void AskSkills() {

}

void WhatSee() {
    
    int option;

    printf("1 -- See basic information \n");
    printf("2 -- Another think \n");
    printf("Option? ");
    scanf("%d \n \n", &option);

    switch (option) {
        case 1:
            printBasicInfo();
        break;
        case 2:
            printPool();
        break;
    }
}

void AskModifiers() {

}

void DeleteCharacter() {

}

void ValidateOption(int option) {
    
    switch (option) {
        case 1:
            WhatSee();
        break;
        case 2:
            AskModifiers();
        break;
        case 3:
            DeleteCharacter();
        break;
    }
}

void AskWhatToDo() {
    
    int option;

    printf("We have a preliminar version, what do you want to do? \n");
    printf("1 -- Check model \n");
    printf("2 -- Modify information \n");
    printf("3 -- Delete character \n");
    printf("4 -- Exit... \n");
    printf("Option ? ");
    scanf("%d", &option);

    ValidateOption(option);

    if (option >= 1 && option <= 3) {

        AskWhatToDo();
    }
}

int main() {

    // Call all feature to fix
    AskBasic();
    AskCharacterPool();
    AskSkills();

    AskWhatToDo();


    return 0;
}