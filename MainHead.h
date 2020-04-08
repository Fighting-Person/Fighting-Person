//MainHead.h
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define worldsize 6 //0314
#define AT matrix[location.x][location.y]
// define end

enum abilities {str,dex,con, NUM_ABILITY};
enum ztype {CAMP, TOWN, HOME};

// enum end

typedef const char* string;

// data structs
struct MonsterData {
	string name;
	int size;
	int ac;
	int level;
	int str;
	int dex;
	int con;
	int xp;
	int weapon;
int armor;
	int shield;
}; // monster

struct WeaponData {
	string verb;
	int damage; // 1x die
}; // weapon

struct ArmorData{
	int ac;
}; // armor

struct ShieldData{
string name;
int ac;
int weight;
int price;
}; // ShieldData

struct ItemData{ // for shops & inventory
	string name;
	int value;
	int weight;
	char genus;
	int species;
} ; // item

typedef struct { //sheet
	string name;
	bool alive;
	struct {
		int max;
		int current;
		} hp;
	int ability[NUM_ABILITY];
	int size;
	int ac;
	int xp;
	int level;
	int gp;
	int initiative;
	int* Inventory;
	int InventoryTotal;
	struct ItemData* Wielding;
	struct ItemData* Wearing;
	struct ItemData* Carrying;
	struct WeaponData* Weapon;	
	struct ArmorData* Armor;
	struct ShieldData* Shield;
} sheet;

struct LocationType {
	string description;
	int EncounterRate;
	bool move;
	char zmode; // 0313
} ; // locationdata

typedef struct {
	int x;
	int y;
} coordinates;

// end struct

// toc
void in(void);
void printpause(string);
void showprimary(void); // 0302
void nl(void);	//0308
void playerstatus(void); 
void printcoordinates(void); //0316
void printHP(void); // 0319
void ReportEquipment(void); //0326
void CalcWield(struct ItemData*); //040x
void CalcWear(struct ItemData*); //040x
void ReportInventory(void); //0408
void AddToInventory(int); //0408

// World.h
void buildworld(void); //0306
void Move(void); //0309
void printLocationShort(void); //0322
void Shop(void); //0322

// Encounter.h
int rollmod(int,int);
void Encounter(void); 
void rollprimary(void); 
//void primarynamemod(sheet* );
int atleast(int,int);
void printprompt(string); // 0301
int multdiemod(int,int,int); //0304

// Init.h
void buildplayer(void); // 0229
void LoadWeaponArray(void); //0322
void LoadMonsterArray(void); //0322
void LoadArmorArray(void); //0331
void LoadItemArray(void); //0403

// globals

char buffer[150];
char entry;

coordinates location;
struct LocationType matrix[worldsize][worldsize];

// enum data
enum weapons {FIST, BITE, BITE6, DAGGER, SCIMITAR, W_ENUMSIZE};
enum monsters {BAT,FIRE_BEETLE,GOBLIN, M_ENUMSIZE};
enum armor {CLOTHES, LEATHER, CHAINSHIRT, CHAINMAIL, A_ENUMSIZE};
enum items {ITEM_NONE, ITEM_DAGGER, ITEM_LEATHER, ITEM_CHAINSHIRT, ITEM_CHAINMAIL, I_ENUMSIZE};
enum ItemGenus {WEAPON, ARMOR, SHIELD};

// struct arrays data
struct WeaponData *pWeapon[W_ENUMSIZE];
struct MonsterData *pMonster[M_ENUMSIZE];
struct ArmorData *pArmor[A_ENUMSIZE];
struct ItemData *pItem[I_ENUMSIZE];

sheet player;

bool gameloop; // shared by encounter-loop (for hard quitting)

//end
