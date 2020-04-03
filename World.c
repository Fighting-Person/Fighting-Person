// world.c
#include "MainHead.h"

#define LOCATION matrix[x][y]
#define ENCOUNTER_RATE 33

// toc
void FillLocation(struct LocationType*,int ,int);
void printboundary(string);
bool InBounds(string, coordinates);
int SaleOK(string , int );


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
int SaleOK(string name, int price){
	printf("Buy %s?",name);
	in();
	if (entry == 'y'){
		if (player.gp < price){
			printpause("Insufficient funds.");
			return 0;
		}
		player.gp -= price;
		return 1;
	}
	return 2;
}

void Shop(){
	
	// check if at shop location
	if  ( !(location.x == 1 && location.y == 0) )
		return;
	printpause("Welcome to the shop. :)");
	int list[] = {ITEM_DAGGER, ITEM_LEATHER, ITEM_CHAINSHIRT, ITEM_CHAINMAIL};
	int loop = sizeof(list)/sizeof(list[0]);
	int ItemNumber = 1;

	for (int x = 0; x < loop; x++){
		printf("#%i %s - %i gp",x+1, pItem[list[x]]->name ,pItem[list[x]]->value );
		nl();
		ItemNumber++;
	}
	
	/*in();
	int New;
	sale:
		printpause("Which?");
		switch (entry){
			case '1':
			case '2':
			case '3':
			case '4':
				switch (entry){
					case '1':
						switch(SaleOK(pWeapon[WeaponList[0]]->name,pWeapon[WeaponList[0]]->price)){
							case 0:
								goto sale;
							case 1:
								break;
							case 2:
								goto sale;
						}

						player.inven.WeaponTotal++;
						player.inven.Weapon = realloc(player.inven.Weapon,player.inven.WeaponTotal);
						player.inven.Weapon[(player.inven.WeaponTotal-1)] = WeaponList[0];
						player.Wielding = pWeapon[player.inven.Weapon[(player.inven.WeaponTotal-1)]]; //whew

						printf("You arm yourself with %s.",player.Wielding->name);
						nl();
						break; // weapon do
					case '2':
						New = ArmorList[0];
					case '3':
						New = ArmorList[1];
					case '4':
						New =  ArmorList[2];

						switch(SaleOK(pArmor[New]->name,pArmor[New]->price)){
							case 0:
								goto sale;
							case 1:
								break;
							case 2:
								return;
						}

						player.inven.ArmorTotal++;
						player.inven.Armor = realloc(player.inven.Armor,player.inven.ArmorTotal);

						player.inven.Armor[(player.inven.ArmorTotal-1)] = New;
						player.Wearing = pArmor[New]; //whew
						DoAC();

						printf("You wear %s.",player.Wearing->name);
						nl();
						break; // armor do
					} // switch 2
			default: // invalid selection 
				printpause("Come again.");
		} // switch 1 valid selection*/
} // shop()

//end
