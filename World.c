// world.c
#include "MainHead.h"

#define LOCATION matrix[x][y]
#define ENCOUNTER_RATE 33

// toc
void FillLocation(struct LocationType*,int ,int);
void printboundary(string);
bool InBounds(string, coordinates);
bool SaleOK( int );


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
void buildworld(void){
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

void printLocationShort(void){
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
void Move(void){
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
bool SaleOK(int item){
	printf("Buy %s?",pItem[item]->name);
	in();
	if (entry == 'y'){
		if (player.gp < pItem[item]->value){
			printpause("Insufficient funds.");
			return 0; 
		}
		player.gp -= pItem[item]->value;
		return 1;
	}
	return 0;
}

void Shop(void){
	// check if at shop location
	if  ( !(location.x == 1 && location.y == 0) )
		return;
	printpause("Welcome to the shop. :)");

	int list[] = {ITEM_DAGGER, ITEM_LEATHER, ITEM_CHAINSHIRT, ITEM_CHAINMAIL};

	int loop = sizeof(list)/sizeof(list[0]);
	int ItemNumber = 1;
	for (int x = 0; x < loop; x++){
		printf("#%i %s - %i gp",ItemNumber, pItem[list[x]]->name ,pItem[list[x]]->value );
		nl();
		ItemNumber++;
	}

	printpause("Which?");
	int selected=0;
	switch(entry){
		case 49: selected = list[0]; break;
		case 50: selected = list[1]; break;
		case 51: selected = list[2]; break;
		case 52: selected = list[3]; break;
		default: printpause("Invalid.");
	}

	if (!selected)
		return;
	if(!SaleOK(selected))
		return;

	AddToInventory(selected);

	switch(pItem[selected]->genus){
		case WEAPON:
			printpause("Wield?");
			if (entry == 'y'){
				CalcWield(pItem[selected]);
			}
			break;
		case ARMOR:
		printpause("Wear?");
			if (entry == 'y'){
				CalcWear(pItem[selected]);
			}
			break;
	} // end wield/wear

} // shop()

//end
