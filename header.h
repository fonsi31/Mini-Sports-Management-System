#ifndef PROJECT_STRUCTS_H
#define PROJECT_STRUCTS_H

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
	char lName[30];
	int jNum;
	stats stat;
} players;

typedef struct{
	char tName[30];
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

void loadInitialData(teams team[], recs record[], int* game_count);
void update(teams team[], recs record[], int* game_count);
void simulateGame(teams team[], recs record[], int* game_count);
void standings(teams team[]);
void team_stats(teams team[]);
void player_stats(teams team[]);
void history(recs record[], int count);
void mvp_race(teams team[]);
void h2h(recs record[], teams team[], int game_count);
void box_scores(recs record[], teams team[], int game_count);
void sort_teams_float(teams ranking[], float averages[], int count);
void sort_teams_str(teams ranking[], int count);
void sort_player(player_rank ranking[], int mode, int count);

#endif
