// Init.c

#include "MainHead.h"

#define TINY 4
#define SMALL 6
#define MEDIUM 8
#define LARGE 10

#define BASE_ARMOR 10
#define BASE_ABILITY 0

#define STARTING_GOLD 10 * multdiemod(5,4,0)

struct MonsterData mdBat = {"Bat",TINY,12,1,-4,2,-1,10,BITE};
struct MonsterData mdFireBeetle = {"Fire Beetle",SMALL,13,1,-1,0,1,10,BITE6};
struct MonsterData mdGoblin = {"Goblin", SMALL, 15, 2,-1, 2, 0, 50, SCIMITAR};
// add monster + enum

struct WeaponData wdFist = {"punches",2,0,0,"fist"};
struct WeaponData wdBite = {"bites",1,0,0}; 
struct WeaponData wdBite6 = {"bites", 6,0,0};
struct WeaponData wdDagger = {"stabs",4,30,1,"dagger"};
struct WeaponData wdScimitar = {"slashes", 6};
// add weapon + enum

void LoadWeaponArray(void){
	pWeapon[FIST] = &wdFist;
	pWeapon[BITE] = &wdBite;
	pWeapon[BITE6] = &wdBite6;
	pWeapon[DAGGER] = &wdDagger;
	pWeapon[SCIMITAR] = &wdScimitar;
	// add weapon array
	}
void LoadMonsterArray(void){
	pMonster[BAT] = &mdBat;
	pMonster[FIRE_BEETLE] = &mdFireBeetle;
	pMonster[GOBLIN] = &mdGoblin;
	// add monster array
	}

// Generate Char
/*void rollprimary(){
	// (4d6 - lowest) new school (low dex makes game annoying)
	const int NUM_DICE = 4;
	int die[NUM_DICE], result[NUM_DICE];
	int x,y;
	for (x=0;x<NUM_ABILITY;x++){
		//player.ability[x].score = multdiemod(3,6,0);
		for (y=0;y<NUM_DICE;y++){
			die[y] = rollmod(6,0);
			} // 4 die rolled
		
		result[0] = die[0]+die[1]+die[2];
		result[1] = die[0]+die[1]+die[3];
		result[2] = die[0]+die[2]+die[3];
		result[3] = die[1]+die[2]+die[3];
		for(int z=0;z<NUM_DICE;z++){
			printf("set %i result %i",z,result[z]);
			nl();
			}
		if ((result[0] >= result[1]) && (result[0] >= result[2]) && (result[0] >= result[3])){
			player.ability[x].score = result[0];
			continue;
			}
		if ((result[1] >= result[0]) && (result[1] >= result[2]) && (result[1] >= result[3])){
			player.ability[x].score = result[1];
			continue;
			} // 1
		if ((result[2] >= result[0]) && (result[2] >= result[1]) && (result[2] >= result[3])){
			player.ability[x].score = result[2];
			continue;
			} // 2
		if ((result[3] >= result[0]) && (result[3] >= result[1]) && (result[3] >= result[2])){
			player.ability[x].score = result[3];
			continue;
			} // 3
		} // end x
		//if (player.ability[dex].score < 9)
		//player.ability[dex].score = 9;

		
	} // end fx
int getbonus(int stat){
	int bonus=0;
	switch(stat){
		case 1:
			bonus = -5;
			break;
		case 2: case 3:
			bonus = -4;
			break;
		case 4: case 5:
			bonus = -3;
			break;
		case 6: case 7:
			bonus = -2;
			break;
		case 8: case 9:
			bonus = -1;
			break;
		case 10: case 11:
			bonus = 0;
			break;
		case 12:
			bonus = 1;
			break;
		case 13: case 14:
			bonus = 2;
			break;
		case 15:	case 16:
			bonus = 3;
			break;
		case 17: case 18:
			bonus = 4;
			break;
		default:
		if ( stat < 3 || stat > 18)
			printpause("stat value out of expected range.");
		
			}
	return bonus;
	}
//void primarynamemod(sheet* who){ 
	
	for (int x=0;x<NUM_ABILITY;x++){
		who->ability[x].mod = getbonus(who->ability[x].score);
		who->ability[x].name = name[x];
	
		}
	return;
	}*/
void buildplayer(){ // from main()
	player.alive = true;
	player.name = "Player";
	player.size = MEDIUM;
	player.level = 1;
	//rollprimary();
	for ( int x =0;x<NUM_ABILITY;x++){
		player.ability[x] = BASE_ABILITY;
	} 
	//primarynamemod(&player);
	player.AC = atleast(0, (BASE_ARMOR + player.ability[dex]));
	player.hp.max = player.hp.current = player.size + player.ability[con];
	player.xp = 0;
	player.gp = STARTING_GOLD;
	player.Wielding = pWeapon[FIST];
	player.inven.WeaponTotal = 1;
	player.inven.Weapon = calloc(player.inven.WeaponTotal,sizeof(int));
	player.inven.Weapon[(player.inven.WeaponTotal-1)] = FIST;
	return;
	}

//end
