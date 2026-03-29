#include "header.h"

/**
 * Loads initial team and game data from text files at startup
 * @param team        Array of team structures to store team and player data
 * @param record      Array of record structures to store game history and specific details about those games
 * @param game_count  Pointer to an integer that will store total number of games loaded
 */
void loadInitialData(teams team[], recs record[], int* game_count){
	FILE *fp;
	fp = fopen("league_data.txt", "r");
	if(fp != NULL){
		int i, k;
		for(i = 0; i < MAX_TEAMS; i++){
			fscanf(fp, "%s %d %d", team[i].tName, &team[i].win, &team[i].loss);
			for(k = 0; k < MAX_PLAYERS; k++){
				fscanf(fp, "%s %d %d %d %d %f %f %f %d", team[i].player[k].lName, &team[i].player[k].jNum, &team[i].player[k].stat.tPts,
				&team[i].player[k].stat.tReb, &team[i].player[k].stat.tAst, &team[i].player[k].stat.aPts,
				&team[i].player[k].stat.aReb, &team[i].player[k].stat.aAst, &team[i].player[k].stat.gPlayed);
			}
		}
		fclose(fp);		
	}
	else{
		printf("File not found!\n");
	}
		
	
	FILE *fp2;
	fp2 = fopen("history.txt", "r");
	if(fp2 != NULL){
		int x = 0;
		while(fscanf(fp2, "%d %s %s %d %d", &record[x].gID, record[x].ht, record[x].vt, &record[x].htfScore, &record[x].vtfScore) == 5){
			record[x].htIndex = -1;
			record[x].vtIndex = -1;
			for(int i = 0; i < MAX_TEAMS; i++){
				if(strcmp(record[x].ht, team[i].tName) == 0){
					record[x].htIndex = i;
				}
				if(strcmp(record[x].vt, team[i].tName) == 0){
					record[x].vtIndex = i;
				}
			} 		
			x++;
		}
		*game_count = x;
		fclose(fp2);
	}
	else{
		printf("File not found!\n");
	}
	
	
	FILE *fp3;
	fp3 = fopen("box_scores.txt", "r");
	if(fp3 != NULL){
		int a;
		char b[30]; //holds data that we dont want to store in our records structs
		char c[30]; //holds data that we dont want to store in our records structs
		for(int j = 0; j < *game_count; j++){
			for(int k = 0; k < MAX_PLAYERS * 2; k++){
				if(k<5){
					fscanf(fp3, "%d %s %s %d %d %d", &a, b, c, &record[j].hpPts[k], &record[j].hpReb[k], &record[j].hpAst[k]);
				}
				else{
					fscanf(fp3, "%d %s %s %d %d %d", &a, b, c, &record[j].vpPts[k-5], &record[j].vpReb[k-5], &record[j].vpAst[k-5]);	
				}
			}	
		}
		fclose(fp3);
	}
	else{
		printf("File not found!\n");
	}
	
}

/**
 * Updates and appends data to the text files right after every new game is generated
 * @param team        Array of team structures that stores team and player data
 * @param record      Array of record structures that stores game history and specific details about those games
 * @param game_count  Pointer to an integer that that stores total number of games loaded
 */
void update(teams team[], recs record[], int* game_count){
	FILE *fp;
	fp = fopen("league_data.txt", "w");
	if(fp != NULL){
		for(int i = 0; i < MAX_TEAMS; i++){
			fprintf(fp, "%s %d %d\n", team[i].tName, team[i].win, team[i].loss);
			for(int k = 0; k < MAX_PLAYERS; k++){
				fprintf(fp, "%s %d %d %d %d %f %f %f %d\n", team[i].player[k].lName, team[i].player[k].jNum, team[i].player[k].stat.tPts,
				team[i].player[k].stat.tReb, team[i].player[k].stat.tAst, team[i].player[k].stat.aPts,
				team[i].player[k].stat.aReb, team[i].player[k].stat.aAst, team[i].player[k].stat.gPlayed);
			}
		}
		fclose(fp);
	}
	else{
		printf("File not found!\n");
	}
	

	FILE *fp2;
	fp2 = fopen("history.txt", "a");
	if(fp2 != NULL){
		fprintf(fp2, "%d %s %s %d %d\n", record[*game_count].gID,
		record[*game_count].ht, record[*game_count].vt,
		record[*game_count].htfScore, record[*game_count].vtfScore);
		fclose(fp2);
	}
	else{
		printf("File not found!\n");
	}
	
	
	FILE *fp3;
	fp3 = fopen("box_scores.txt", "a");
	if(fp3 != NULL){
		for(int j = 0; j < MAX_PLAYERS * 2; j++){
			if(j < MAX_PLAYERS){
				fprintf(fp3, "%d %s %s %d %d %d\n", record[*game_count].gID, record[*game_count].ht,
				team[record[*game_count].htIndex].player[j%5].lName, record[*game_count].hpPts[j%5], record[*game_count].hpReb[j%5], record[*game_count].hpAst[j%5]);
			}
			else{
				fprintf(fp3, "%d %s %s %d %d %d\n", record[*game_count].gID, record[*game_count].vt,
				team[record[*game_count].vtIndex].player[j%5].lName, record[*game_count].vpPts[j%5], record[*game_count].vpReb[j%5], record[*game_count].vpAst[j%5]);	
			}
		}
		fclose(fp3);
	}
	else{
		printf("File not found!\n");
	}
}

/**
 * Simulates a new game between two selected teams.
 *
 * Allows the user to choose teams and select between manual stat entry
 * or randomized simulation. Updates team/player statistics and stores
 * the game result in the record array.
 *
 * @param team        Array of team structures storing team and player data
 * @param record      Array of record structures storing game history
 * @param game_count  Pointer to total number of games (used as index for new game)
 */
void simulateGame(teams team[], recs record[], int* game_count){
	system("cls");
	printf("*** THE TIP-OFF: SELECT THE TEAMS ***\n");
	int i, home, away, mode, hfs = 0, vfs = 0;
	int hPts[5], hReb[5], hAst[5];
	int vPts[5], vReb[5], vAst[5];
	
	for(i = 0; i < MAX_TEAMS; i++){
		printf("[%d] %s\n", i, team[i].tName);
	}
	
	printf("Home Index: ");
	scanf("%d", &home);
	printf("Away Index: ");
	scanf("%d", &away);
	if(home == away || home > 3 || home < 0 || away > 3 || away < 0){
		printf("[!] Technical Foul: Invalid Selection!\n");
	}
	
	else{
		record[*game_count].htIndex = home;
		record[*game_count].vtIndex = away;
		
		printf("CHOOSE MODE:\n");
		printf("[1] MANUAL ENTRY (BOX SCORE)\n");
		printf("[2] QUICK SIM (Randomized)\n");
		printf("Selection: ");
		scanf("%d", &mode);
		
		printf("\n>>> THE WHISTLE BLOWS: %s VS %s <<<\n", team[home].tName, team[away].tName);
		if(mode == 1){
			for(int k = 0; k < MAX_PLAYERS; k++){
				printf("%s (Pts Reb Ast): ", team[home].player[k].lName);
				scanf("%d %d %d", &hPts[k], &hReb[k], &hAst[k]);
				team[home].player[k].stat.tPts += hPts[k];
				hfs += hPts[k];
				team[home].player[k].stat.tReb += hReb[k];
				team[home].player[k].stat.tAst += hAst[k];
				team[home].player[k].stat.gPlayed++;
				record[*game_count].hpPts[k] = hPts[k];
				record[*game_count].hpReb[k] = hReb[k];
				record[*game_count].hpAst[k] = hAst[k];
			}
			printf("\n");
			
			for(int j = 0; j < MAX_PLAYERS; j++){
				printf("%s (Pts Reb Ast): ", team[away].player[j].lName);
				scanf("%d %d %d", &vPts[j], &vReb[j], &vAst[j]);
				team[away].player[j].stat.tPts += vPts[j];
				vfs += vPts[j];
				team[away].player[j].stat.tReb += vReb[j];
				team[away].player[j].stat.tAst += vAst[j];		
				team[away].player[j].stat.gPlayed++;
				record[*game_count].vpPts[j] = vPts[j];
				record[*game_count].vpReb[j] = vReb[j];
				record[*game_count].vpAst[j] = vAst[j];			
			}
		}
		else{
			for(int x = 0; x < MAX_PLAYERS; x++){
				hPts[x] = (rand() % 31 + rand() % 4);
				if(hPts[x] > 30)
					hPts[x] = 30;
				team[home].player[x].stat.tPts += hPts[x];
				hfs += hPts[x];
				hReb[x] = rand() % 16;
				team[home].player[x].stat.tReb += hReb[x];
				hAst[x] = rand() % 11;
				team[home].player[x].stat.tAst += hAst[x];
				record[*game_count].hpPts[x] = hPts[x];
				record[*game_count].hpReb[x] = hReb[x];
				record[*game_count].hpAst[x] = hAst[x];
				
				vPts[x] = rand() % 31;
				team[away].player[x].stat.tPts += vPts[x];
				vfs += vPts[x];
				vReb[x] = rand() % 16;
				team[away].player[x].stat.tReb += vReb[x];
				vAst[x] = rand() % 11;
				team[away].player[x].stat.tAst += vAst[x];	
				record[*game_count].vpPts[x] = vPts[x];
				record[*game_count].vpReb[x] = vReb[x];
				record[*game_count].vpAst[x] = vAst[x];	
					
				team[home].player[x].stat.gPlayed++;
				team[away].player[x].stat.gPlayed++;
			}
			for(int y = 0; y < MAX_PLAYERS; y++){
				printf("%s: %d Pts, %d Reb, %d Ast\n", team[home].player[y].lName, hPts[y], hReb[y], hAst[y]);
			}
			printf("\n");
			for(int z = 0; z < MAX_PLAYERS; z++){
				printf("%s: %d Pts, %d Reb, %d Ast\n", team[away].player[z].lName, vPts[z], vReb[z], vAst[z]);
			}
		}
		
		for(int b = 0; b < MAX_PLAYERS; b++){
			team[home].player[b].stat.aPts = (team[home].player[b].stat.aPts * (team[home].player[b].stat.gPlayed - 1) + hPts[b]) * 1.0 / team[home].player[b].stat.gPlayed;
			team[home].player[b].stat.aReb = (team[home].player[b].stat.aReb * (team[home].player[b].stat.gPlayed - 1) + hReb[b]) * 1.0 / team[home].player[b].stat.gPlayed;
			team[home].player[b].stat.aAst = (team[home].player[b].stat.aAst * (team[home].player[b].stat.gPlayed - 1) + hAst[b]) * 1.0 / team[home].player[b].stat.gPlayed;
	
			team[away].player[b].stat.aPts = (team[away].player[b].stat.aPts * (team[away].player[b].stat.gPlayed - 1) + vPts[b]) * 1.0 / team[away].player[b].stat.gPlayed;
			team[away].player[b].stat.aReb = (team[away].player[b].stat.aReb * (team[away].player[b].stat.gPlayed - 1) + vReb[b]) * 1.0 / team[away].player[b].stat.gPlayed;
			team[away].player[b].stat.aAst = (team[away].player[b].stat.aAst * (team[away].player[b].stat.gPlayed - 1) + vAst[b]) * 1.0 / team[away].player[b].stat.gPlayed;			
		}
		printf("\n--- FINAL BUZZER: %d - %d ---\n", hfs, vfs);
		if(hfs > vfs){
			team[home].win++;
			team[away].loss++;
			printf("%s Victory!\n", team[home].tName);
		}
		else{
			team[away].win++;
			team[home].loss++;
			printf("%s Victory!\n", team[away].tName);
		}
		printf("\n");
	
		record[*game_count].gID = (*game_count) + 1;
		strcpy(record[*game_count].ht, team[home].tName);
		strcpy(record[*game_count].vt, team[away].tName);
		record[*game_count].htfScore = hfs;
		record[*game_count].vtfScore = vfs;
		update(team, record, game_count);
		(*game_count)++;
	}
	system("pause");
}

/**
 * Computes the win rate of each team and displays rankings in descending order.
 *
 * Calculates win rate as wins / (wins + losses). Teams with no games played
 * are assigned a win rate of 0. Rankings are determined using a separate
 * array without modifying the original team order.
 *
 * @param team  Array of team structures storing team and player data
 */
void standings(teams team[]){
	system("cls");
	float winrate[4];
	teams ranking[4];
	for (int i = 0; i < MAX_TEAMS; i++){
		ranking[i] = team[i];
		if(team[i].win + team[i].loss == 0){
			winrate[i] = 0;
		}
		else{
			winrate[i] = team[i].win * 1.0 / (team[i].win + team[i].loss);	
		}	
	}
	for(int j = 0; j < MAX_TEAMS-1; j++){//sorts winrate
		int min = j;
		for(int k = j+1; k < MAX_TEAMS; k++){
			if(winrate[k] > winrate[min]){
				min = k;
			}
		}
		if(min != j){
			float temp = winrate[j];
			winrate[j] = winrate[min];
			winrate[min] = temp;
			
			teams temp1 = ranking[j];
			ranking[j] = ranking[min];
			ranking[min] = temp1;
		}
	}
	printf("=====================================================\n");
	printf("                    TEAM STANDINGS                   \n");
	printf("=====================================================\n");
	printf("+-------+-----------------+-------+-------+---------+\n");
	printf("| RANK  | TEAM            | WINS  | LOSS  | WIN %%   |\n");
	printf("+-------+-----------------+-------+-------+---------+\n");
	for(int x = 0; x < MAX_TEAMS; x++){
		printf("| %-6d| %-16s| %-6d| %-6d| %-6.1f%% |\n", x+1, ranking[x].tName, ranking[x].win, ranking[x].loss, winrate[x] * 100);
	}
	printf("+-------+-----------------+-------+-------+---------+\n");
	system("pause");
}

/**
 * Computes team averages for points, rebounds, and assists.
 *
 * Aggregates player statistics to calculate team averages, then displays
 * rankings in descending order based on a user-selected category
 * (points, rebounds, assists, or alphabetical order).
 *
 * @param team  Array of team structures storing team and player data
 */
void team_stats(teams team[]){
	system("cls");
	int choice;
	printf("FILTER: [1]Pts [2]Reb [3]Ast [4]Alpha: ");
	scanf("%d", &choice);
	printf("\n");
	printf("=================================================\n");
	printf("               TEAM SCOUTING REPORT              \n");
	printf("=================================================\n");
	printf("+-----------------+---------+---------+---------+\n");
	printf("| TEAM            | AVG PTS | AVG REB | AVG AST |\n");
	printf("+-----------------+---------+---------+---------+\n");
	
	team_rank ranking[4];
	for (int i = 0; i < MAX_TEAMS; i++){
		strcpy(ranking[i].tName, team[i].tName);
		ranking[i].avg_pts = 0;
    	ranking[i].avg_reb = 0;
    	ranking[i].avg_ast = 0;
		for(int k = 0; k < MAX_PLAYERS; k++){
			ranking[i].avg_pts += team[i].player[k].stat.aPts;
			ranking[i].avg_reb += team[i].player[k].stat.aReb;
			ranking[i].avg_ast += team[i].player[k].stat.aAst;
		}
	}	
	
	switch(choice){
		case 1:
			sort_team(ranking, 1, MAX_TEAMS);
			break;
		case 2:
			sort_team(ranking, 2, MAX_TEAMS);
			break;
		case 3:
			sort_team(ranking, 3, MAX_TEAMS);
			break;
		default:
			sort_team(ranking, 4,  MAX_TEAMS);
			break;
	}
	
	for(int j = 0; j < MAX_TEAMS; j++){
		printf("| %-16s|%8.2f |%8.2f |%8.2f |\n", ranking[j].tName, ranking[j].avg_pts, ranking[j].avg_reb, ranking[j].avg_ast);
	}
	printf("+-----------------+---------+---------+---------+\n");
	system("pause");
}

/**
 * Displays player rankings across the league based on a selected category.
 *
 * Aggregates all players from every team into a single array, then sorts
 * them in descending order based on the chosen metric (points, rebounds,
 * assists, or alphabetical order).
 *
 * @param team  Array of team structures storing team and player data
 */
void player_stats(teams team[]){
	system("cls");
	int choice;
	printf("FILTER: [1]Pts [2]Reb [3]Ast [4]Alpha: ");
	scanf("%d", &choice);
	player_rank ranking[20];
	int count = MAX_PLAYERS; //determines how many rows will be displayed
	for(int i = 0; i < MAX_TEAMS * MAX_PLAYERS; i++){
		strcpy(ranking[i].pName, team[i/5].player[i%5].lName);
		strcpy(ranking[i].tName, team[i/5].tName);
		ranking[i].avg_pts = team[i/5].player[i%5].stat.aPts;
		ranking[i].avg_reb = team[i/5].player[i%5].stat.aReb;
		ranking[i].avg_ast = team[i/5].player[i%5].stat.aAst;
	}	
	switch(choice){
		case 1:
			sort_player(ranking, 1, 20);
			break;
		case 2:
			sort_player(ranking, 2, 20);
			break;
		case 3:
			sort_player(ranking, 3, 20);
			break;
		default:
			sort_player(ranking, 4, 20);
			count = MAX_PLAYERS * MAX_TEAMS;
			break;
	}	
	printf("==============================================\n");
	printf("               ACE PLAYER DATA                \n");
	printf("==============================================\n");
	printf("+----------+---------+-------+-------+-------+\n");
	printf("| PLAYER   | TEAM    | PTS   | REB   | AST   |\n");
	for(int j = 0; j < count; j++){
		printf("+----------+---------+-------+-------+-------+\n");
		printf("| %-9s| %-8s| %-6.1f| %-6.1f| %-6.1f|\n", ranking[j].pName, ranking[j].tName, ranking[j].avg_pts, ranking[j].avg_reb, ranking[j].avg_ast);
	}
	printf("+----------+---------+-------+-------+-------+\n");
	system("pause");
}

/**
 * Displays all recorded games and their results.
 *
 * Iterates through the record array and prints game details,
 * including teams, final scores, and winners.
 *
 * @param record  Array of record structures storing game details
 * @param count   Total number of games recorded
 */
void history(recs record[], int count){
	system("cls");
	printf("==================================================\n");
	printf("                   GAME HISTORY                   \n");
	printf("==================================================\n");
	printf("+----+---------+---------+-------------+---------+\n");
	printf("| ID | HOME    | AWAY    | FINAL SCORE | WINNER  |\n");
	char wName[30];
	for(int i = 0; i < count; i++){
		printf("+----+---------+---------+-------------+---------+\n");
		if(record[i].htfScore > record[i].vtfScore){
			strcpy(wName, record[i].ht);
		}
		else{
			strcpy(wName, record[i].vt);
		}
		printf("| %-3d| %-8s| %-8s|%5d - %-5d| %-8s|\n", record[i].gID, record[i].ht, record[i].vt, record[i].htfScore, record[i].vtfScore, wName);
	}
	printf("+----+---------+---------+-------------+---------+\n");
}

/**
 * Displays MVP rankings based on a weighted performance score.
 *
 * Aggregates all players into a single array and computes a score (SP)
 * using weighted contributions from points, rebounds, and assists.
 * Players are then ranked in descending order based on this score.
 *
 * @param team  Array of team structures storing team and player data
 */
void mvp_race(teams team[]){
	system("cls");
	player_rank ranking[20];
	for(int i = 0; i < 20; i++){
		strcpy(ranking[i].pName, team[i/5].player[i%5].lName);
		strcpy(ranking[i].tName, team[i/5].tName);
		ranking[i].sp = (team[i/5].player[i%5].stat.aPts * 10.0) + (team[i/5].player[i%5].stat.aReb * 5.0) + (team[i/5].player[i%5].stat.aAst * 3.0);
	}
	sort_player(ranking, 5, 20);
	printf("================================================\n");
	printf("                    MVP RACE                    \n");
	printf("================================================\n");
	printf("+------+----------+---------+------------------+\n");
	printf("| RANK | PLAYER   | TEAM    | STAT POINTS (SP) |\n");
	for(int j = 0; j < MAX_PLAYERS; j++){
		printf("+------+----------+---------+------------------+\n");
		printf("| %-5d| %-9s| %-8s| %-17.2f|\n", j+1, ranking[j].pName, ranking[j].tName, ranking[j].sp);
	}
	printf("+------+----------+---------+------------------+\n");
	system("pause");
}

/**
 * Displays head-to-head results between two selected teams.
 * Instead of scanning the history file repeatedly, the file is scanned once at startup and data from the text file is stored in a struct array which gets updated
   along with the text file after every new game is generated.
 * @param team        Array of team structures storing team and player data
 * @param record      Array of record structures storing game history
 * @param game_count  Pointer to total number of games (used as index for new game)
*/
void h2h(recs record[], teams team[], int game_count){
	system("cls");
	int i1, i2, win1=0, win2=0, count = 0;
	int i3[100]; //stores indexes in records where the 2 teams fought
	printf("*** SELECT TEAMS FOR H2H ANALYSIS ***\n");
	printf("[0] Shohoku\n[1] Kainan\n[2] Ryonan\n[3] Shoyo\n");
	printf("\n");
	printf("Select First Team Index: ");
	scanf("%d", &i1);
	printf("Select Second Team Index: ");
	scanf("%d", &i2);
	if(i1 == i2 || i1 >= MAX_TEAMS || i1 < 0 || i2 >= MAX_TEAMS || i2 < 0){
		printf("[!] Invalid Selection!\n");
	}
	else{
		printf("\n");
		for(int i = 0; i < game_count; i++){
			if((i1 == record[i].htIndex || i1 == record[i].vtIndex) && (i2 == record[i].htIndex || i2 == record[i].vtIndex)){
				i3[count] = i;
				count++;
			}
		}
		printf("       --- %s VS %s HISTORY ---\n", team[i1].tName, team[i2].tName);
		printf("+----+-------------+-------------+-------------+\n");
		printf("| ID | HOME        | AWAY        | SCORE       |\n");
		printf("+----+-------------+-------------+-------------+\n");
		for(int j = 0; j < count; j++){
			if((i1 == record[i3[j]].htIndex && record[i3[j]].htfScore > record[i3[j]].vtfScore)||
			(i1 == record[i3[j]].vtIndex && record[i3[j]].vtfScore > record[i3[j]].htfScore)){
				win1++;
			}
			else{
				win2++;
			}
			printf("| %-3d| %-12s| %-12s|%5d - %-5d|\n", record[i3[j]].gID, record[i3[j]].ht, record[i3[j]].vt, record[i3[j]].htfScore, record[i3[j]].vtfScore);
		}
		printf("+----+-------------+-------------+-------------+\n");
		printf("\n");
		printf("SUMMARY:\n");
		printf(" %-9sWins: %d\n", team[i1].tName, win1);
		printf(" %-9sWins: %d\n", team[i2].tName, win2);
	}
	system("pause");
}

/**
 * Displays the box scores in a recorded game selected via input of game ID.
 * Instead of scanning the box score file repeatedly, the file is scanned once at startup and data from the txt file is stored in a struct array which gets updated
   along with the txt file after every new game is generated.
 * @param team        Array of team structures storing team and player data
 * @param record      Array of record structures storing game history
 * @param game_count  Pointer to total number of games (used as index for new game)
*/
void box_scores(recs record[], teams team[], int game_count){
	system("cls");
	history(record, game_count);
	int gID;
	int found = 0;
	printf("Enter GAME ID to look up: ");
	scanf("%d", &gID);
	
	for(int i = 0; i < game_count; i++){
		if(gID == record[i].gID){
			system("cls");
			found = 1;
			int rSum = 0, aSum = 0;
			printf("--- BOX SCORE: GAME #%-2d---\n", gID);
			printf("%s (%d) vs %s (%d)\n", record[i].ht, record[i].htfScore, record[i].vt, record[i].vtfScore);
			printf("\n");
			printf("+-----------------+-----+-----+-----+\n");
			printf("| %-16s| PTS | REB | AST |\n", record[i].ht);
			printf("+-----------------+-----+-----+-----+\n");
			for(int j = 0; j < 5; j++){
				printf("| %-16s| %-4d| %-4d| %-4d|\n", team[record[i].htIndex].player[j].lName, record[i].hpPts[j], record[i].hpReb[j], record[i].hpAst[j]);
				rSum += record[i].hpReb[j];
				aSum += record[i].hpAst[j];
			}
			printf("+-----------------+-----+-----+-----+\n");
			printf("| TEAM TOTALS     | %-4d| %-4d| %-4d|\n", record[i].htfScore, rSum, aSum);
			printf("+-----------------+-----+-----+-----+\n");
			printf("\n");
			
			rSum = 0;
			aSum = 0;
			printf("+-----------------+-----+-----+-----+\n");
			printf("| %-16s| PTS | REB | AST |\n", record[i].vt);
			printf("+-----------------+-----+-----+-----+\n");
			for(int k = 0; k < 5; k++){
				printf("| %-16s| %-4d| %-4d| %-4d|\n", team[record[i].vtIndex].player[k].lName, record[i].vpPts[k], record[i].vpReb[k], record[i].vpAst[k]);
				rSum += record[i].vpReb[k];
				aSum += record[i].vpAst[k];
			}
			printf("+-----------------+-----+-----+-----+\n");
			printf("| TEAM TOTALS     | %-4d| %-4d| %-4d|\n", record[i].vtfScore, rSum, aSum);
			printf("+-----------------+-----+-----+-----+\n");
			printf("\n");
		}
	}
	if(!found){
		printf("[!] Record for Game ID %d not found.\n", gID);
	}
	system("pause");
}

/**
 * Sorts teams in descending order based on a selected statistic.
 *
 * Uses a comparison-based sorting algorithm to reorder the array
 * according to the specified mode:
 *   1 - points
 *   2 - rebounds
 *   3 - assists
 *   4 - alphabetical order (team name)
 *
 * @param arr    Array of team_rank structures to be sorted
 * @param mode   Sorting criterion (see modes above)
 * @param count  Number of teams in the array
 */
void sort_team(team_rank arr[], int mode, int count){
    for(int i = 0; i < count-1; i++){
        for(int j = i+1; j < count; j++){
            int swap = 0;

            if(mode == 1 && arr[j].avg_pts > arr[i].avg_pts) swap = 1;
            else if(mode == 2 && arr[j].avg_reb > arr[i].avg_reb) swap = 1;
            else if(mode == 3 && arr[j].avg_ast > arr[i].avg_ast) swap = 1;
            else if(mode == 4 && strcmp(arr[j].tName, arr[i].tName) < 0) swap = 1;

            if(swap){
                team_rank temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

/**
 * Sorts players in descending order based on a selected statistic.
 *
 * Uses a comparison-based sorting algorithm to reorder the array
 * according to the specified mode:
 *   1 - points
 *   2 - rebounds
 *   3 - assists
 *   4 - alphabetical order (player name)
 *
 * @param ranking  Array of player_rank structures to be sorted
 * @param mode     Sorting criterion (see modes above)
 * @param count    Number of players in the array
 */
void sort_player(player_rank ranking[], int mode, int count){
	int swap;
	player_rank temp;
	for(int i = 0; i < count-1; i++){
		for(int j = i+1; j < count; j++){
			swap = 0;
			if(mode == 1 && ranking[j].avg_pts > ranking[i].avg_pts)
				swap = 1;
			else if(mode == 2 && ranking[j].avg_reb > ranking[i].avg_reb)
				swap = 1;
			else if(mode == 3 && ranking[j].avg_ast > ranking[i].avg_ast)
				swap = 1;
			else if(mode == 4 && strcmp(ranking[j].pName, ranking[i].pName) < 0)
				swap = 1;
			else if(mode == 5 && ranking[j].sp > ranking[i].sp)
				swap = 1;
				
			if(swap){
				temp = ranking[i];
				ranking[i] = ranking[j];
				ranking[j] = temp;
			}
		}
	}
}
