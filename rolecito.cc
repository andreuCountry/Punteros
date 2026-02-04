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

struct CharacterPool {
    int constitution, strenght, charism, inteligence, knowledge, faith;
};

struct Skills {
    int talkative, combat, hide, stealth, health, fatigue, jump, mana;
};

void PrepareFile() {
    f = fopen("files/model.dat", "r+b");

    // Add all features to send

    fclose(f);
}

void AskBasic() {

}

void AskCharacterPool() {

}

void AskSkills() {

}

bool ValidateOption(int option) {
    if (option < 1 || option > 2) {
        return false;
    }

    return true;
}

void AskWhatToDo() {
    
    int option;

    printf("We have a preliminar version, what do you want to do? \n");
    printf("1 -- Check model \n");
    printf("2 -- Modify information \n");
    printf("Option 1 or 2? ");
    scanf("%d", &option);

    if (!ValidateOption(option)) {
        printf("\n \n");
        printf("This option doesn't exist.");
        printf("\n");

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