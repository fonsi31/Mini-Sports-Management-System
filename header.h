#ifndef PROJECT_STRUCTS_H
#define PROJECT_STRUCTS_H

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#define HOME_ADVANTAGE 3
#define MAX_TEAMS 4
#define MAX_PLAYERS 5

/**
 * Used to temporarily hold players data for sorting to avoid modifying the main players struct
*/
typedef struct {
    char tName[30];
    float avg_pts;
    float avg_reb;
    float avg_ast;
    int win;
    int loss;
} team_rank;

typedef struct{
    char pName[30]; //player name
    char tName[30]; //team name of the player
    float avg_pts;
    float avg_reb;
    float avg_ast;
	float sp; //stat points;
}player_rank;

/**
 * Stats of a single player
*/
typedef struct{
	int gPlayed; //games played of a single player
	
	int tPts; //total points
	int tReb; // total rebounds
	int tAst; // total assists
	
	float aPts; //aerage points
	float aReb; // average rebounds
	float aAst; //average assists
}stats;

typedef struct{
	char lName[30]; //player name
	int jNum;// jersey number
	stats stat;
} players;

typedef struct{
	char tName[30]; //team name
	int win;
	int loss;
	players player[5];
}teams;

/**
 * Stores records/details of a game
*/
typedef struct{
	int gID;
	char ht[30]; //home team name
	char vt[30]; //away/visiting team name
	
	int htIndex; //home team index
	int vtIndex; //away/visiting team index
	
	int htfScore; //home team final score
	int vtfScore; //away/visiting team final score
	
	int hpPts[5]; //home player points
	int vpPts[5]; //away/visiting player points
	
	int hpReb[5]; //home player rebounds
	int vpReb[5]; //away/visiting player rebounds
	
	int hpAst[5]; //home players assists
	int vpAst[5]; //away/visiting player assists
}recs;

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
void sort_team(team_rank arr[], int mode, int count);
void sort_player(player_rank ranking[], int mode, int count);

#endif
