// "Simple betting game"
// "Jack Queen King" - computer shuffles these cards
// player has to guess the position of the Queen.
// if he wins, he takes 3*bet
// if he loose, he looses the bet amount.
// Player has $100 initially 

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int cash = 100;

// =====1. Memory Leak=====
void Play(int bet) {
    char *C = (char*)malloc(3*sizeof(char));
    C[0] = 'J'; C[1] = 'Q'; C[2] = 'K'; 
    printf("Shuffling...");

    srand(time(NULL));
    int i;
    for(i = 0;i<5;i++) {
        int x = rand() % 3;
        int y = rand() % 3;
        int temp = C[x];
        C[x]=C[y];
        C[y]=temp;
    }
    int playersGuess;
    printf("What's the position of Queen - 1,2 or 3?");
    scanf("%d",&playersGuess);
    
    if(C[playersGuess - 1] == 'Q'){
        cash += 3*bet;
        printf("You win ! Result = %c%c%c Total cash = %d", C[0],C[1],C[2]);
    } else {
        cash -= bet;
        printf("You loose ! Result = %c%c%c Total cash = %d", C[0],C[1],C[2]);
    }
}

// =====2.Stack Overflow=====
void causeStackOverflow() {
    casueStackOverflow();
}
// =====3.Out of Memory=====
void causeOutofMemory() {
    while(1){
        void *p = malloc(100 * 1024 * 1024);
        if(p == NULL) {
            printf("Out of Memory!  malloc return NULL\n");
            break;
        }
    }
}

int main() {

    int choice;
    printf("===Memory Demo Error===\n");
    printf("1.Play game (Memory Leak)\n");
    printf("2.Casue Stack Overflow\n");
    printf("3.Cause of Memory\n");
    printf("Choose Option:  ");
    scanf("%d",&choice);

    if(choice == 1){
    int bet;
    printf("Welcome to the virtual Casino\n");
    printf("Total cash = $%d\n",cash);
    while(cash > 0) {
        printf("What's your bet? $");
        scanf("%d",&bet);
        if(bet == 0 || bet > cash) break;
        Play(bet);
        printf("\n**********************************\n");
    }
    } else if(choice == 2){
        casueStackOverflow();
    } else if(choice == 3){
        causeOutofMemory();
    } else {
        printf("Invalid choice!\n");
    }

}

