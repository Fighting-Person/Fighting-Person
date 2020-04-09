//main.c
#include "MainHead.h"

// toc
// see MainHead.h

int main(){
		srand(time(0));
		printpause("Hello. :]");
		buildworld();
		LoadWeaponArray();
		LoadMonsterArray();
		LoadArmorArray();
		LoadItemArray();
	restart:
		buildplayer();
		location.x=location.y=0;
		printLocationShort();
		gameloop = true;
		int new;
		do{
			printpause("*");
			switch(entry) {
				case 's': //status
					playerstatus();
					continue;
				case 'a': //attack
					printprompt("Nothing here to attack.");
					continue;
				case 'q': //quit
					gameloop = false;
					break;
				case 'l': //look
					printLocationShort();
					continue;
				case 'u': // 0301
				case 'v': 
				case 'f': 
				case 'j':
					Move();
					if (!player.alive){
						printpause("Restart?");
						if (entry == 'y')
							goto restart;
					}
					continue;
				case 'p': // show primary stats
					showprimary();
					continue;
				case 'r': // restart
					printprompt("Restarted.");
					goto restart;
				case 'h': // show hp
					printHP();
					continue;
				case 'e':
					ReportEquipment();
					continue;
				case 'z': //sleep.
					if (AT.zmode == HOME){
						printpause("You sleep.");	
						player.hp.current = player.hp.max;
						printHP();
					}		
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
					continue;
				case 'b': // buy (from shop)
					Shop();
					continue;
				case 'i':
					ReportInventory();
					continue;
				case '`': //cheat
					new = ITEM_DAGGER;
					AddToInventory(new);
					CalcWield(pItem[new]);
					new = ITEM_CHAINMAIL;
					AddToInventory(new);
					CalcWear(pItem[new]);
					continue;
				}
		} while (gameloop && player.alive); // end switch

	return 0;
}	
// end main

void in(){
	gets(buffer);
	entry = buffer[0];
	return;
}
void nl(){
	printf("\n");
}
void printpause(string line){
	printf("%s", line);
	in();
	return;
}
void printprompt(string line){
	printf("%s\n",line);
	return;
}
void playerstatus(){
	printf("Level %i",player.level);
	nl();
	printf("HP %i/%i", player.hp.current,player.hp.max); 
	nl();
	printf("GP %i",player.gp); 
	nl();
	printf("XP %i",player.xp); 
	nl();
	printf("AC %i", player.ac);
	nl();
	return;
}
void showprimary(){
	string name[]={"Strength","Dexterity","Constitution"};
	for (int x=0;x<NUM_ABILITY;x++){
		printf("%s %i",name[x],player.ability[x]); // to fix
		nl();
	}
	return;
}
void printcoordinates(void){
	printf("%s. %i, %i",matrix[location.x][location.y].description,location.x,location.y);
	nl();
}
void printHP(){
	printf("%i/%i hp",player.hp.current,player.hp.max);
	nl();
	return;
}
void ReportEquipment(void){
	printf("Wielding %s", player.Wielding->name);
	nl();
	printf("Wearing %s", player.Wearing->name);
	nl();
	printf("Carrying %s",player.Carrying->name);
	nl();
}
void ReportInventory(void){
	for(int x =1; x < player.InventoryTotal+1; x++){
		printf("%s", pItem[player.Inventory[x]]->name);
		nl();
	}
}
void AddToInventory(int new){
	player.Inventory = realloc(player.Inventory,++player.InventoryTotal);
	player.Inventory[player.InventoryTotal] = new;
}
//end
