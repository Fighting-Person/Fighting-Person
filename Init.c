// Init.c
// defines
// struct monsterdata weapon item
// array weapon monster armor item
// calcwield wear carry
// buildplayer

#include "MainHead.h"

#define TINY 4
#define SMALL 6
#define MEDIUM 8
#define LARGE 10

#define BASE_ABILITY 0
#define STARTING_GOLD 10 * multdiemod(5,4,0)

struct MonsterData 
	mdBat = {"Bat",TINY,12,1,-4,2,-1,10,BITE,0,0},
	mdFireBeetle = {"Fire Beetle",SMALL,13,1,-1,0,1,10,BITE6,0,0},
	mdGoblin = {"Goblin", SMALL, 15, 2,-1, 2, 0, 50, SCIMITAR/*,LEATHER,*/};
	// add monster + enum

struct WeaponData 
	wdFist = {"punches",2},
	wdBite = {"bites",1},
	wdBite6 = {"bites", 6},
	wdDagger = {"stabs",4},
	wdScimitar = {"slashes", 6},
	wdLongsword = {"slashes", 8};
	// add weapon + enum

struct ItemData 
	idNone = {"nothing",0,0,0},

	idDagger = {"dagger", 30, 1, WEAPON, DAGGER},
	idLongsword = {"longsword", 25, 0, WEAPON, LONGSWORD},

	idLeather = {"leather armor", 10, 10, ARMOR, LEATHER},
	idChainshirt = {"chain shirt", 50, 20, ARMOR, CHAINSHIRT},
	idChainmail = {"chain mail", 75, 55, ARMOR, CHAINMAIL},

	idShield = {"shield", 0,0,SHIELD,0};
	// add item

void LoadWeaponArray(void){
	pWeapon[FIST] = &wdFist;
	pWeapon[BITE] = &wdBite;
	pWeapon[BITE6] = &wdBite6;
	pWeapon[DAGGER] = &wdDagger;
	pWeapon[SCIMITAR] = &wdScimitar;
	pWeapon[LONGSWORD] = &wdLongsword;
	// add weapon array
}
void LoadMonsterArray(void){
	pMonster[BAT] = &mdBat;
	pMonster[FIRE_BEETLE] = &mdFireBeetle;
	pMonster[GOBLIN] = &mdGoblin;
	// add monster array
}
void LoadArmorArray(void){
	armor_ac[CLOTHES] = 10;
	armor_ac[LEATHER] = 11;
	armor_ac[CHAINSHIRT] = 13;
	armor_ac[CHAINMAIL] = 16;
} //ArmorArray
void LoadItemArray(void){
	pItem[ITEM_NONE] = &idNone;
	pItem[ITEM_DAGGER] = &idDagger;	
	pItem[ITEM_LONGSWORD] = &idLongsword;
	pItem[ITEM_LEATHER] = &idLeather;
	pItem[ITEM_CHAINSHIRT] = &idChainshirt;
	pItem[ITEM_CHAINMAIL] = &idChainmail;
	pItem[ITEM_SHIELD] = &idShield;
};
void CalcWear(struct ItemData* idArmor){
	player.Wearing = idArmor;

	player.Armor = armor_ac[idArmor->species];
	player.ac = player.Armor + player.ability[dex];

	printf("You don %s.",idArmor->name);
	nl();
}
void CalcWield(struct ItemData* idWeapon){ 
	player.Wielding = idWeapon;
	player.Weapon = pWeapon[idWeapon->species];

	printf("You arm yourself with %s.",idWeapon->name);
	nl();
}
void CalcCarry(int new){
	if (pItem[new]->genus == SHIELD){
		player.Carrying = pItem[ITEM_SHIELD];
		player.ac += SHIELD_AC;
		printf("You carry shield."); nl();
		return;
	}
}
void buildplayer(void){ // from main()
	player.alive = true;
	player.name = "Player";
	player.size = MEDIUM;
	player.level = 1;
	for ( int x =0;x<NUM_ABILITY;x++){
		player.ability[x] = BASE_ABILITY;
	} 
	player.hp.max = player.hp.current = player.size /*+ player.ability[con]*/;
	player.xp = 0;
	player.gp = STARTING_GOLD;

	player.InventoryTotal = 0;
	player.Inventory = calloc(1,sizeof(int)); //since don't know when 1st item will be added.
	player.Inventory[0] = ITEM_NONE; // 0

	player.Wielding = &idLongsword;
	player.Weapon = pWeapon[LONGSWORD];

	player.Wearing = &idChainmail;
	player.Armor = CHAINMAIL;

	player.ac = armor_ac[player.Armor] + player.ability[dex];

	AddToInventory(ITEM_SHIELD);
	player.Carrying = pItem[ITEM_SHIELD];
	player.ac += SHIELD_AC;
}

//end
