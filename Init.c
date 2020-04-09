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

struct WeaponData wdFist = {"punches",2};
struct WeaponData wdBite = {"bites",1}; 
struct WeaponData wdBite6 = {"bites", 6};
struct WeaponData wdDagger = {"stabs",4};
struct WeaponData wdScimitar = {"slashes", 6};
// add weapon + enum

/*struct ArmorData adClothes = {10}; // "clothes"
struct ArmorData adLeather = {11};
struct ArmorData adChainshirt = {13};
struct ArmorData adChainmail = {16};
// add Armor + enum*/

struct ItemData idNone = {"nothing",0,0,0};
struct ItemData idDagger = {"dagger", 30, 1, WEAPON, DAGGER};
struct ItemData idLeather = {"leather armor", 10, 10, ARMOR, LEATHER};
struct ItemData idChainshirt = {"chain shirt", 50, 20, ARMOR, CHAINSHIRT};
struct ItemData idChainmail = {"chain mail", 75, 55, ARMOR, CHAINMAIL};
struct ItemData idShield = {"shield", 0,0,SHIELD,0};

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
	/*pArmor[CLOTHES] = &adClothes;
	pArmor[LEATHER] = &adLeather;
	pArmor[CHAINSHIRT] = &adChainshirt;
	pArmor[CHAINMAIL] = &adChainmail;
	// add Armor array*/
	armor_ac[CLOTHES] = 10;
	armor_ac[LEATHER] = 11;
	armor_ac[CHAINSHIRT] = 13;
	armor_ac[CHAINMAIL] = 16;
} //ArmorArray
void LoadItemArray(void){
	pItem[ITEM_NONE] = &idNone;
	pItem[ITEM_DAGGER] = &idDagger;	
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

	printpause("Error - Carry.");
}
void buildplayer(){ // from main()
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

	player.Wielding = &idNone;
	player.Weapon = pWeapon[FIST];

	player.Wearing = &idNone;
	player.Armor = CLOTHES;

	player.ac = armor_ac[player.Armor] + player.ability[dex];

	AddToInventory(ITEM_SHIELD);
	player.Carrying = pItem[ITEM_SHIELD];
	player.ac += SHIELD_AC;
}

//end
