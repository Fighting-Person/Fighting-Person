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
enum weapons {FIST, BITE, BITE6, DAGGER, SCIMITAR, W_ENUMSIZE};
enum monsters {BAT,FIRE_BEETLE,GOBLIN, M_ENUMSIZE};
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
};

struct WeaponData {
	string verb;
	int damage; // 1x die
	int price; // gp
	int weight; // lbs
	string name;
};

struct ArmourData{
	string name;
	int ac;
	int weight;
	int price;
}; // armourdata

typedef struct { //sheet
	struct {
		int max;
		int current;
		} hp;
	int ability[NUM_ABILITY];
	int initiative;
	string name;
	int AC;
	int xp;
	int level;
	int gp;
	int size;
	bool alive;
	struct { //inv
		int* Weapon;
		int WeaponTotal;
		int* Armour;
		int ArmourTotal;
		int* Shield;
		int ShieldTotal;
		} inven;
	struct WeaponData* Wielding;
	//struct ArmourData* Wearing;
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

// toc
void in(void);
void printpause(string);
void nl(void);	//0308
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
void showprimary(void); // 0302
int multdiemod(int,int,int); //0304
void playerstatus(void); 
void printcoordinates(void); //0316
void printHP(void); // 0319

// Init.h
void buildplayer(void); // 0229
void LoadWeaponArray(void); //0322
void LoadMonsterArray(void); //0322

// globals

char buffer[150];
char entry;

coordinates location;
struct LocationType matrix[worldsize][worldsize]; // 03/14

struct WeaponData *pWeapon[W_ENUMSIZE];
struct MonsterData *pMonster[M_ENUMSIZE];

sheet player;

bool gameloop; // shared by encounter-loop (for hard quitting)

//end
