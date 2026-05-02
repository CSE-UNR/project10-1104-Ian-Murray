//Author: Ian Murray
//date: 4/27/26
//purpose: wordle

#include <stdio.h>
#include <stdbool.h>

void getWord(char word[6]);
void displayGame(char guessList[6][6], int totalGuesses, char goalWord[]);
void fitsGame(char input[]);
void makeLowerCase(char input[]);
bool checkWin(char input[], char goalWord[]);
void printWinMessage(int totalGuesses);

int main(){
	char goalWord[6];
	char userInput[100];
	bool win =false;
	int totalGuesses=1;
	char guessList[6][6];
	
	getWord(goalWord);

	while(totalGuesses<7){
		if(totalGuesses<=6){
			printf("Guess %d! Enter your guess: ", totalGuesses);
			scanf("%s", userInput);
		}
		else{
			printf("FINAL GUESS: ");
			scanf("%s", userInput);
		}
		
		fitsGame(userInput);
		makeLowerCase(userInput);
		win=checkWin(userInput, goalWord);
		
		if(win){
			printWinMessage(totalGuesses);
			break;
		}
		
		for(int i = 0; i < 5; i++) {
			guessList[totalGuesses - 1][i] = userInput[i];
		}
		
		displayGame(guessList, totalGuesses, goalWord);
		totalGuesses++;
	}
	
	return 0;
}

void getWord(char word[6]){
	FILE *fchosenWord = fopen("mystery.txt", "r");
	
	if(fchosenWord== NULL){
		word[0]='w';
		word[1]='o';
		word[2]='r';
		word[3]='d';
		word[4]='s';
		word[5]='\0';
	}
	else{
		fscanf(fchosenWord, " %5s", word);
		fclose(fchosenWord);
	}
}

void fitsGame(char input[]){
	int length =0;
	bool repeat=false;
	
	while(!repeat){
		while (input[length] != '\0'){
			length++;
		}
		
		if (length!=5){
			printf("your guess must be 5 letters long\n");
		}
		else{
			repeat=true;
		}
		
		for(int i=0; i<5; i++){
			if(!((input[i]>= 'a' && input[i]<='z') || (input[i]>= 'A' && input[i]<='Z'))){
				printf("your guess must be 5 LETTERS long\n");
				repeat=false;
				break;
			}
		}
		
		if(!repeat){
			printf("Please try again: ");
			scanf(" %s", input);
		}
	}
}

void makeLowerCase(char input[]){
	for (int j=0; j<5; j++){
		if(input[j]>='A'&& input[j]<='Z'){
			input[j]= input[j]+32;
		}
	}
}

bool checkWin(char input[], char goalWord[]){
	for(int i=0; i<5; i++){
		if(input[i] != goalWord[i]){
			return false;
		}
	}
	return true;
}

void displayGame(char guessList[6][6], int totalGuesses, char goalWord[]){
	printf("================================\n");

	for (int i = 0; i < totalGuesses; i++) {
        
		for (int j = 0; j < 5; j++) {
		    if (guessList[i][j] == goalWord[j]) {
		        printf("%c", guessList[i][j] - 32);
		    } 
		    else {
		        printf("%c", guessList[i][j]);
		    }
		}
		
		printf("\n");

		for (int j = 0; j < 5; j++) {
		    bool foundElsewhere = false;
		    if (guessList[i][j] != goalWord[j]) {
		        for (int k = 0; k < 5; k++) {
		            if (guessList[i][j] == goalWord[k]) {
		                foundElsewhere = true;
		                break; 
		            }
		        }
		    }

		    if (foundElsewhere) {
		        printf("^");
		    } 
		    else {
		        printf(" ");
		    }
		}
		printf("\n");
	}
}

void printWinMessage(int totalGuesses){
	if(totalGuesses<6){
		printf("================================\n");
		printf("                SOUND\n");
		printf("        You won in %d guesses!\n", totalGuesses);
	}
	else{
		printf("                SOUND\n");
	}
		
	if(totalGuesses==1){
		printf("                GOATED!\n");
	}
	else if(totalGuesses<=3 ){
		printf("                Amazing\n!");
	}
	else if(totalGuesses<=5){
		printf("                Nice!\n");
	}
}

