// Encounter.c

#include "MainHead.h"

#define HALF .5
#define QUARTER .25

bool encounter;

// toc
void Combat(sheet*,sheet*);
void initiative();
void Attack(sheet*, sheet*);
void buildabear(struct MonsterData*, sheet*); //0303
int getbonus(int);
bool escape(sheet*);
bool DetermineDefeat(sheet *);
void ShowOpponentStatus(sheet*); //0327

// fx
int rollmod(int die, int mod){
	int a = (rand() % die) + 1 + mod;
	return a;
	}
int multdiemod(int multiple,int die,int mod){
	int result = 0;
	for (int b=0;b<multiple;b++){
		result += rollmod(die,mod);
		}
	return result;
	}
int atleast(int minimum, int result){
	if (result < minimum)
		return minimum;
	return result;
	}
void Attack(sheet *attacker, sheet *defender){ // called from Combat()
	int attack = rollmod(20, attacker->ability[dex]);
	if (attack <= defender->ac){
		printf("%s misses!",attacker->name);
		in();
		return;
		}
	int damage = atleast(0,rollmod(attacker->Weapon->damage, attacker->ability[str]));
	printf("%s %s %s for %i damage!", 
		attacker->name, attacker->Weapon->verb, defender->name, damage);
	in();
	defender->hp.current -= damage;
	if (defender->hp.current <= 0){
		encounter = false;
		printf("%s is killed.",defender->name);
		in();
		defender->alive = false;
		return;
		}
	return;
	}
bool DetermineDefeat(sheet *opponent){
	if (!opponent->alive){
		player.xp += opponent->xp;
		printf("You gain %i experience.",opponent->xp);
		in();
		return true;
		}
	if (!player.alive){
		return true;
		}
	return false;
}
void initiative (sheet* who){
	who->initiative = rollmod(20,who->ability[dex]);
	return;
}
void Combat(sheet* player, sheet* opponent){ // called from EncounterLoop ('a')
	sheet *attacker, *defender;
	roll:
		initiative(player);
		initiative(opponent);
		if (player->initiative == opponent->initiative)
			goto roll;
	if (player->initiative > opponent->initiative){
		attacker = player;
		defender = opponent;
		}
	else{
		attacker = opponent;
		defender = player;
		}
	Attack(attacker, defender);
	if(DetermineDefeat(opponent))
		return;
	// if no one is killed..
	Attack(defender, attacker); 
	DetermineDefeat(opponent);
	return;
}
void buildabear(struct MonsterData *fill, sheet* opponent){ // called from Encounter()
	opponent->name = fill->name;
	opponent->size = fill->size;
	opponent->ac = fill->ac;
	opponent->level = fill->level;
	opponent->ability[str] = fill->str;
	opponent->ability[dex] = fill->dex;
	opponent->ability[con] = fill->con;
	opponent->hp.max = opponent->hp.current = 
		atleast(1, (multdiemod(opponent->level,
		opponent->size,opponent->ability[con])));
	opponent->Weapon = pWeapon[fill->weapon];
	opponent->xp = fill->xp;
	opponent->alive = true;
}
bool escape(sheet* opponent){
	int b = rollmod(20,player.ability[dex]);
	int c = rollmod(20,opponent->ability[dex]);
	if (b > c) 
		return true;
	return false;
}
void Encounter(){ // called from Move()

	sheet opponent;

	// determine monster
	int roll = rollmod(M_ENUMSIZE, 0) - 1;
	// define
	buildabear(pMonster[roll],&opponent);

	encounter = true;
	printf("Encounter %s!", opponent.name);
	do{
		printpause("*");
		switch (entry){
			case 's': // status
				playerstatus();
				continue;
			case 'a': // attack
				Combat(&player, &opponent);
				continue;
			case 'q': // quit
				encounter = false;
				gameloop = false;
				break;
			case 'l': // look
				ShowOpponentStatus(&opponent);	
				continue;
			case 'u': // 0301
			case 'v': 
			case 'f': 
			case 'j':
				printprompt("You're currently in an encounter.");
				continue;
			case 'p': // show primary stats
				showprimary();
				continue;
			case 'r': // restart
				break;
			case 'h': // show hp
				printHP();
				continue;
			case 'e':
				if(escape(&opponent)){
					encounter = false;
					printprompt("You escaped!");
					continue;
				}
				printpause("Failed to escape!");
				Attack(&opponent,&player);
				continue;
			case 'z': //sleep. 0=no, 1=ok, 2=camp 
				printprompt("There's no sleeping in fantasy combat!");
				continue;
			case 'x': // show xp
				printf("%i xp",player.xp);
				nl();
				continue;
			case 'g': // show gp
				printf("%i gold pieces",player.gp);
				nl();
				continue;
			case 'w': // where? //0315
				printcoordinates();
			}
		} while (encounter);
	return; // fx
}
void ShowOpponentStatus(sheet* opponent){
	int now, max,half,quarter;
	now = opponent->hp.current;
	max = opponent->hp.max;
	half = HALF * max;
	quarter = QUARTER * max;
	if (now == max)
		printf("%s looks unhurt.", opponent->name);	
	if ( now < max && now > half)
		printf("%s looks slightly hurt.",opponent->name);
	if (now <= half && now > quarter)
		printf("%s looks somewhat hurt.",opponent->name);
	if (now <= quarter)
		printf("%s looks hurt.", opponent->name);
	nl();
}
//end
