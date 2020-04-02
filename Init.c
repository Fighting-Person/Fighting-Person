// Init.c

#include "MainHead.h"

#define TINY 4
#define SMALL 6
#define MEDIUM 8
#define LARGE 10

//#define BASE_ARMOR 10
#define BASE_ABILITY 0

#define STARTING_GOLD 10 * multdiemod(5,4,0)

// monsterdata 
struct MonsterData mdBat = {"Bat",TINY,12,1,-4,2,-1,10,BITE,0,0};
struct MonsterData mdFireBeetle = {"Fire Beetle",SMALL,13,1,-1,0,1,10,BITE6,0,0};
struct MonsterData mdGoblin = {"Goblin", SMALL, 15, 2,-1, 2, 0, 50, SCIMITAR/*,LEATHER,*/};
// add monster + enum

struct WeaponData wdFist = {"punches",2,0,0,"fist"};
struct WeaponData wdBite = {"bites",1,0,0}; 
struct WeaponData wdBite6 = {"bites", 6,0,0};
struct WeaponData wdDagger = {"stabs",4,30,1,"dagger"};
struct WeaponData wdScimitar = {"slashes", 6};
// add weapon + enum

struct ArmorData adNone = {"no armor",10,0,0};
struct ArmorData adLeather = {"leather armor", 11, 10, 10};
struct ArmorData adChainshirt = {"chain shirt", 13, 20, 50};
struct ArmorData adChainmail = {"chain mail", 16, 55, 75};
// add Armor + enum

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
void LoadArmorArray(void){
	pArmor[NONE] = &adNone;
	pArmor[LEATHER] = &adLeather;
	pArmor[CHAIN_SHIRT] = &adChainshirt;
	pArmor[CHAIN_MAIL] = &adChainmail;
	// add Armor array
}
// Generate Char
void DoAC(){
	player.ac = player.Wearing->ac + player.ability[dex];
}
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
	player.hp.max = player.hp.current = player.size /*+ player.ability[con]*/;
	player.xp = 0;
	player.gp = STARTING_GOLD;
	player.Wielding = pWeapon[FIST];
	player.inven.WeaponTotal = 1;
	player.inven.Weapon = calloc(player.inven.WeaponTotal,sizeof(int));
	player.inven.Weapon[(player.inven.WeaponTotal-1)] = FIST;
	player.Wearing = pArmor[NONE];
	DoAC();
	return;
}

//end
