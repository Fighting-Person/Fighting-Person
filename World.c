// world.c
#include "MainHead.h"

#define LOCATION matrix[x][y]
#define ENCOUNTER_RATE 33

// toc
void FillLocation(struct LocationType*,int ,int);
void printboundary(string);
bool InBounds(string, coordinates);
bool SaleOK(string , int );

// LocationType {string name, int encounterrate, int move, int zmode (camp,town,home)}
struct LocationType woods = {"Woods", ENCOUNTER_RATE, 1, CAMP};
struct LocationType town = {"Town", 0, 1, TOWN};
struct LocationType home = {"Home",0,1,HOME};
struct LocationType shop = {"Shop",0,1,TOWN};
// in world.c, add weaponmaster, armormaster, adventuremaster

void FillLocation(struct LocationType* fill, int x, int y){
	LOCATION.description = fill->description;
	LOCATION.EncounterRate = fill->EncounterRate;
	LOCATION.move = fill->move;
	LOCATION.zmode = fill->zmode;
	return; 
}
void buildworld(){
	// fill woods for y = 3 - 5
	for(int x=0;x<worldsize;x++){
		for(int y=3;y<worldsize;y++){
			FillLocation(&woods,x,y);
		}
	}
	// fill town
	for(int x=0;x<worldsize;x++){
		for(int y=0;y<3;y++){
			FillLocation(&town,x,y);		
		}
	}
	// home
	FillLocation(&home,0,0);
	//shop - for better to fight beetle with
	FillLocation(&shop,1,0);
	return;
}

void printLocationShort(){
	printf("%s.",matrix[location.x][location.y].description);
	nl();
}
void printboundary(string direction){
	printf("You can't go further %s.",direction);
	nl();
}
bool InBounds(string direction, coordinates supposed){
	if (supposed.x == worldsize || 
		supposed.y == worldsize || 
			supposed.x < 0 || supposed.y < 0){
		return false;
	}
	return true;
}
void Move(){
	string direction;
	coordinates new = {0,0};
	switch(entry){
		case 'u': new.y = 1; direction = "north"; break;
		case 'v': new.y = -1; direction = "south"; break;
		case 'f': new.x = -1; direction = "west"; break;
		case 'j': new.x = 1; direction = "east"; break;
	}

	// check world boundary 
	coordinates supposed = {0,0};
	supposed.x = location.x + new.x;
	supposed.y = location.y + new.y;
	if (!InBounds(direction, supposed)){
		printboundary(direction);
		return;
	}

	location.y += new.y ;
	location.x += new.x;

	printLocationShort();
	
	// if 1d100 falls within encounter rate
	if ((rollmod(100,0)) <= matrix[location.x][location.y].EncounterRate)
		Encounter(); //Encounter.c (good luck)

	return;
}
bool SaleOK(string name, int price){
	printf("Buy %s?",name);
	in();
	if (entry == 'y'){
		if (player.gp < price){
			printpause("Insufficient funds.");
			return false;
		}
		player.gp -= price;
		return true;
	}
	return false;
}
void Shop(){
	// check if at shop location
	if  ( !(location.x == 1 && location.y == 0) )
		return;
	printpause("Welcome to the shop. :)");
	int ItemNumber = 1;
	// do weapons
	int WeaponList[] = {DAGGER};
	printf("#%i %s - %i gp",ItemNumber,pWeapon[WeaponList[0]]->name,pWeapon[WeaponList[0]]->price);
	nl();
	ItemNumber++;
	// do armor
	int ArmorList[] = {LEATHER, CHAIN_SHIRT, CHAIN_MAIL};
	int loop = sizeof(ArmorList)/sizeof(ArmorList[0]);
	for (int x = 0; x < loop; x++){
		printf("#%i %s - %i gp",ItemNumber,pArmor[ArmorList[x]]->name,pArmor[ArmorList[x]]->price);
		nl();
		ItemNumber++;
	}
	in();
	//sale:
		printpause("Which?");
		if (entry == '1'){
			//if (SaleOK(pWeapon[WeaponList[0]]->name,pWeapon[WeaponList[0]]->price))
				player.inven.WeaponTotal++;
				player.inven.Weapon = realloc(player.inven.Weapon,player.inven.WeaponTotal);
				player.inven.Weapon[(player.inven.WeaponTotal-1)] = WeaponList[0];
				player.Wielding = pWeapon[player.inven.Weapon[(player.inven.WeaponTotal-1)]]; //whew

				printf("You arm yourself with %s.",player.Wielding->name);
				nl();
			}

		
}

//end
