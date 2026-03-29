#include "definitions.c"
#include "header.h"

/**
 * Description      : Basketball League Simulator that manages teams, players,
 *                    and game records. The program supports game simulation
 *                    (manual or randomized), team standings, player statistics,
 *                    MVP ranking, head-to-head analysis, and box score viewing.
 *                    Data is persistently stored and retrieved from text files.
 *
 * Author/s         : Cauilan, Alfonso
 *                    Abad, Davian
 *
 * Section          : S15B
 *
 * Last Modified    : March 29, 2026
 *
 * Acknowledgements :
 *                    - Course materials and lectures
 */
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
		printf(" [4] ACE PLAYER DATA (PLAYER STATS)\n");
		printf(" [5] TOURNAMENT SCOREBOOK (HISTORY)\n");
		printf(" [6] MVP RACE CANDIDATES\n");
		printf(" [7] RIVALRY CHECK (HEAD-TO-HEAD)\n");
		printf(" [8] VIEW BOX SCORE\n");
		printf(" [9] LEAVE THE COURT (EXIT)\n");
		printf("==========================================\n");
		printf("ENTER CHOICE: ");
		int input = scanf("%d", &choice);
		
		if(input != 1 || choice < 1 || choice > 9){
			printf("Invalid Input!\n");
			while(getchar() != '\n'); //clears input buffer 
			system("pause");
		}
		
		else{
			switch (choice){
				case 1:
					simulateGame(team, record, &game_count);
					break;
					
				case 2:
					standings(team);
					break;
					
				case 3:
					team_stats(team);
					break;
					
				case 4:
					player_stats(team);
					break;
					
				case 5:
					history(record, game_count);
					system("pause");
					break;
					
				case 6:
					mvp_race(team);
					break;
					
				case 7:
					h2h(record, team, game_count);
					break;
					
				case 8:
					box_scores(record, team, game_count);
					break;
					
				case 9:
					exit = 1;
					break;
					
				default:
					system("pause");
					break;
			}
		}
	}while(!exit);

	return 0;
}

/**
* This is to certify that this project is my/our own work, based on my/our personal
* efforts in studying and applying the concepts learned. I/We have constructed the
* functions and their respective algorithms and corresponding code by myself/ourselves.
* The program was run, tested, and debugged by my/our own efforts. I/We further certify
* that I/we have not copied in part or whole or otherwise plagiarized the work of
* other students and/or persons.
*
* Cauilan, Alfonso S. 12504513
* Abad, Davian
*/
