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
};

struct WeaponData {
	string verb;
	int damage; // 1x die
	int price; // gp
	int weight; // lbs
	string name;
};

struct ArmorData{
	string name;
	int ac;
	int weight;
	int price;
}; // Armordata

struct ShieldData{
string name;
int ac;
int weight;
int price;
}; // ShieldData

typedef struct { //sheet
	struct {
		int max;
		int current;
		} hp;
	int ability[NUM_ABILITY];
	int initiative;
	string name;
	int ac;
	int xp;
	int level;
	int gp;
	int size;
	bool alive;
	struct { //inv
		int* Weapon;
		int WeaponTotal;
		int* Armor;
		int ArmorTotal;
		int* Shield;
		int ShieldTotal;
		} inven;
	struct WeaponData* Wielding;
	struct ArmorData* Wearing;
struct ShieldData *LeftHand; // dunno
	} sheet;

struct LocationType {
	string description;
	int EncounterRate;
	bool move;
	char zmode; // 0313
} ;

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
void ReportInventory(void); //0326

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
void DoAC(void);

// globals

char buffer[150];
char entry;

coordinates location;
struct LocationType matrix[worldsize][worldsize]; // 03/14

enum weapons {FIST, BITE, BITE6, DAGGER, SCIMITAR, W_ENUMSIZE};
enum monsters {BAT,FIRE_BEETLE,GOBLIN, M_ENUMSIZE};
enum armor {NONE, LEATHER, CHAIN_SHIRT, CHAIN_MAIL, A_ENUMSIZE};

struct WeaponData *pWeapon[W_ENUMSIZE];
struct MonsterData *pMonster[M_ENUMSIZE];
struct ArmorData *pArmor[A_ENUMSIZE];

sheet player;

bool gameloop; // shared by encounter-loop (for hard quitting)

//end
