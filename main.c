#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#define HOME_ADVANTAGE 3


typedef struct{
    char pName[30];
    char tName[30];
    float avg_pts;
    float avg_reb;
    float avg_ast;
	float sp;
}player_rank;

typedef struct{
	int gPlayed;
	
	int tPts;
	int tReb;
	int tAst;
	
	float aPts;
	float aReb;
	float aAst;
}stats;

typedef struct{
	char[30] lName;
	int jNum;
	stats stat;
} players;

typedef struct{
	char[30] tName;
	int win;
	int loss;
	players player[5];
}teams;

typedef struct{
	int gID;
	char ht[30];
	char vt[30];
	
	int htIndex;
	int vtIndex;
	
	int htfScore;
	int vtfScore;
	
	int hpPts[5];
	int vpPts[5];
	
	int hpReb[5];
	int vpReb[5];
	
	int hpAst[5];
	int vpAst[5];
}recs;

typedef char string[30];

int main() {
	teams team[4];
	recs record[100];
	srand(time(NULL));
	int game_count =  0;   
	loadInitialData(team, record, &game_count);
	int exit = 0;
	int choice;	

	do{
		system("cls");
		
		printf("==========================================\n");
		printf("    KANAGAWA PREFECTURAL CHAMPIONSHIP     \n");
		printf("==========================================\n");
		printf(" [1] THE TIP-OFF (SIMULATE GAME)\n");
		printf(" [2] THE ROAD TO NATIONALS (STANDINGS)\n");
		printf(" [3] TEAM SCOUTING REPORT (AVERAGES)\n");  
		printf("ENTER CHOICE: ");
		
		if(scanf("%d", &choice) != 1){
			
		}
		
		switch (choice){
			case 1:
				simulateGame(team, record, &game_count);
				break;
			case 2:
				
			case 3:
				
			case 4:
				
			case 5:
				
			case 6:
			
			case 7:
				
			case 8:
				
			case 9:
				exit = 1;
				break;
			default:
				system("pause");
				break;
		}
		
	}while(!exit);

	return 0;
}











