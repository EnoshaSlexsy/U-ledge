  //-----------------------------------------------------------------------------------------------------------------------------------------
//Libraries list v1.0	20.11 (1.0+)
//-----------------------------------------------------------------------------------------------------------------------------------------
#include <cstdio>
#include <ctime>
#include <fstream>
#include <io.h>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <windows.h>
using namespace std;
//-----------------------------------------------------------------------------------------------------------------------------------------
//Constants v1.0	20.11 (1.0+)
//-----------------------------------------------------------------------------------------------------------------------------------------
const int ABILITY_COUNT = 10;
const int ABILITY_PARAMETER_MAX = 4;
//-----------------------------------------------------------------------------------------------------------------------------------------
//Function v1.0		20.1 (1.0+)
//-----------------------------------------------------------------------------------------------------------------------------------------
void debug(){
	/*system("pause");*/
	cout << "Debag msg"; cin >> emptyChar;
}
void debug( string S ){
	cout << S; cin >> emptyChar;
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Console function v1.0		20.1 (1.0+)
//-----------------------------------------------------------------------------------------------------------------------------------------
class c_Console{
	private:

	public: 
		void positionSet( int PositionX, int PositionY ){
			COORD Screen;
			HANDLE hOuput = GetStdHandle( STD_OUTPUT_HANDLE );
			Screen.X = PositionX; Screen.Y = PositionY;
			SetConsoleCursorPosition( hOuput , Screen );
		}
		int selecter( int PositionX, int PositionY, int SelectCount ){
			int Position = 0;
			while( !GetAsyncKeyState( VK_RIGHT ) ){
				PositionSet( PositionX, PositionY + Position );
				cout << " ";
				if( GetAsyncKeyState( VK_UP ) ){
					Position = max(Position - 1, 0);
				}
				else if( GetAsyncKeyState( VK_DOWN ) ){
					Position = min( Position + 1, SelectCount - 1 );
				}
				PositionSet( PositionX, PositionY + Position );
				cout << ">";
				Sleep( 100 );
			}
			return Position + 1;
		}
} Console;
//-----------------------------------------------------------------------------------------------------------------------------------------
//Structures v1.0	20.11 (1.0+)
//	s_Hero v1.0		20.11 (1.0+)
//-----------------------------------------------------------------------------------------------------------------------------------------
typedef struct s_Ability{
//Global parameters
	string 	ActionType;
	string 	Description;
	string 	Name;
	string 	TriggerType[ ABILITY_PARAMETER_MAX ];
	int 	LevelMax;
	int 	ParameterCount;
	int 	Power[ ABILITY_LEVEL_MAX + 1 ][ PARAMETER_COUNT_MAX + 1 ];
	int 	CountdownMax;
//Battle parameters
	int 	Countdown;
	int 	LevelCurrent;
};
typedef struct s_Summon{
	string 	Name;
	int 	AttackPower;
	int 	Actionpoint = 0, ActionpointIncrease = 300;
	int 	Block;
	int 	HitpointMax, HitpointCurrent;
};
typedef struct s_Hero{
//Global parameters
	int 	Level;
	int 	HitpointMax;
	int 	AttackPower;
	int 	CriticalChance, CriticalPower;
	int 	AbilityLevel[ ABILITY_COUNT ];
//Battle parameters
	int 	HitpointCurrent;
	int 	AbilityCountdown[ABILITY_COUNT];
};
//-----------------------------------------------------------------------------------------------------------------------------------------
//Player class v1.0 - 20.1 (1.0+)
//-----------------------------------------------------------------------------------------------------------------------------------------
class c_Player{
	private:

	public:
		void getInfo( s_Hero HeroName ){

		}
		void loadHero( s_Hero HeroName ){
			HeroName.Level = 1;
			HeroName.HitpointMax = 100;
			HeroName.AttackPower = 10;
			HeroName.CriticalChance = 0;
			HeroName.CriticalPower = 120;
			for( int position = 0; position < ABILITY_COUNT; position++ ){
				HeroName.AbilityLevel[position] = 0;
			}
		}
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------
// Dat output @_@
//-----------------------------------------------------------------------------------------------------------------------------------------
class Output{
	private:
	
	public:

};
//--------------------------------------------------------------------------------------------------
//Global Function 		v0 
//trigger - 			v0
//	add description!
//abilityUse - 			v0
//hitSimple - 			v0
//damageDet - 			v0
//abilityUp - 			v0
//abilityUpAll -		v0
//timePassed -			inDev
//getAbilityCount -		v0
//-----DO-NOT-USE-----------------------------------------------------------------------------------
int trigger( string type, Player* self, Player* target, int abilityStat ){
	stringstream output;
	string Desc;
	if( type == "heal" ){
		output << abilityStat;
		Desc = type + " for " + output.str();
		log.push_back(Desc);
		self->stats.hero.hitpointCurrent += abilityStat;
	}
	if( type == "damage" ){
		output << abilityStat;
		Desc = type + " for " + output.str();
		log.push_back(Desc);
		target->stats.hero.hitpointCurrent -= abilityStat;
	}
	if( type == "criticalPower" ){
		self->stats.hero.criticalPower += abilityStat;
	}
	if( type == "criticalChance" ){
		self->stats.hero.criticalChance += abilityStat;
	}
	if( type == "hitpointSet" ){
		self->stats.hero.hitpointCurrent = abilityStat;
	}
}
//--------------------------------------------------------------------------------------------------
int abilityUse( Player* self, Player* target, int abilityId ){
	int c_parameter, abilityStat;
	switch( abilityId ){
		case 1:	//FromGrave type:Active
			if( self->stats.ability.countdown[ abilityId ] == 0 && self->stats.ability.level[ abilityId ] > 0 ){
				if( self->stats.hero.hitpointCurrent <= 0 ){
					output.abilityActive(self, target, abilityId);
					for( c_parameter = 1; c_parameter <= abilityMassive[abilityId].stats.parameterCount; c_parameter++ ){
						trigger(abilityMassive[abilityId].stats.triggerType[ c_parameter ],
								self, target,
								abilityMassive[abilityId].stats.power[ self->stats.ability.level[ abilityId ] ][ c_parameter ]);
					}
					self->stats.ability.countdown[ abilityId ] =abilityMassive[abilityId].stats.countdownMax;
					openImage(abilityMassive[abilityId].stats.name);
					Sleep(1000);	//Temp
					return 1;
				}
				else{
					return 0;
				}
			}
			return 0;
		case 2:	//Critical type:Passive
			for( c_parameter = 1; c_parameter <= abilityMassive[ abilityId ].stats.parameterCount; c_parameter++ ){
				abilityStat = abilityMassive[ abilityId ].stats.power[ self->stats.ability.level[ abilityId ] ][ c_parameter ];
				abilityStat -= abilityMassive[ abilityId ].stats.power[ self->stats.ability.level[ abilityId ] - 1 ][ c_parameter ];
				trigger(abilityMassive[ abilityId ].stats.triggerType[ c_parameter ],
						self,
						target,
						abilityStat);
			}
			return 1;
		case 3:	//LifeDraine type:Active
			if( self->stats.ability.countdown[ abilityId ] == 0 && self->stats.ability.level[ abilityId ] > 0 ){
				output.abilityActive( self, target, abilityId );
				for( c_parameter = 1; c_parameter <= abilityMassive[ abilityId ].stats.parameterCount; c_parameter++ ){
					trigger(abilityMassive[ abilityId ].stats.triggerType[ c_parameter ],
							self,
							target,
							abilityMassive[ abilityId ].stats.power[ self->stats.ability.level[ abilityId ]][ c_parameter ]);
				}
				self->stats.ability.countdown[ abilityId ] = abilityMassive[abilityId].stats.countdownMax;
				/*openImage(self->ability[abilityId].name);*/
				Sleep(500);	//Temp
				return 1;
			}
			else{
				return 0;
			}
	}
}
//--------------------------------------------------------------------------------------------------
int hitSimple( Player* self, Player* target ){
	if( chanceCount() <= self->stats.hero.criticalChance ){
		output.triggerActive( self, target, TRIGGER_ID_CRIT );
		return self->stats.hero.attackPower * ( 100 + self->stats.hero.criticalPower ) / 100;
	}
	return self->stats.hero.attackPower;
}
//--------------------------------------------------------------------------------------------------
void damageGet( Player* self, Player* target, int damage ){
	/*if(blockBuffTime){
		blockBuffTime--;
		damage = damage * (100 - block - blockBuff) / 100;
	}
	else{*/
		damage = damage * ( 100 - target->stats.hero.block ) / 100;
	/*}*/
	output.hit(self, target, damage);
	target->stats.hero.hitpointCurrent -= damage;
}
//--------------------------------------------------------------------------------------------------
void abilityUp( Player* self, Player* target, int abilityId ){
	if(self->stats.ability.level[ abilityId ] < abilityMassive[ abilityId ].stats.levelMax){
		self->stats.ability.level[ abilityId ]++;
		if(abilityMassive[abilityId].stats.actionType == "Passive"){
			abilityUse(self, target, abilityId);
		}
		/*return 1;*/
	}
	/*return 0;*/
}
//-----------------------------------------------------------------------------------------------------------------------------------------
void abilityUpAll(Player* self, Player* target ){
	int c_i, c_j;
	for( c_i = 1; c_i <= self->stats.ability.learn; c_i++ ){
		for(c_j = 1; c_j <= self->stats.ability.levelUp[ c_i ]; c_j++){
			abilityUp( self, target, self->stats.ability.id[ c_i ] );
		}
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------
void timePassed(int time, Player* player){
	int c_ability;
	/*bugFinder("In TP");*/
	for(c_ability = 1; c_ability < ABILITY_COUNT; c_ability++){
		player->stats.ability.countdown[ c_ability ] = max(player->stats.ability.countdown[ c_ability ] - time, 0);	
	}	
}
void timePassed(int time, Player* Players[], int playerCount){
	int c_ability, c_player;
	for(c_player = 1; c_player <= playerCount; c_player++){
		for(c_ability = 1; c_ability < ABILITY_COUNT; c_ability++){
			Players[ c_player ]->stats.ability.countdown[ c_ability ] =
				max(Players[ c_player ]->stats.ability.countdown[ c_ability ] - time, 0);	
		}	
	}	
}
//-----------------------------------------------------------------------------------------------------------------------------------------
int getAbilityCount(){
	string fileName = "abilities//AbInfo.us";
	int abilityCount;
	if(FileExists( fileName.c_str() )){
		ifstream fin( fileName.c_str() );
		fin >> abilityCount;
	}
	else{
		cout << "Already Writed Abilities:";
		cin >> abilityCount;
	}
	return abilityCount;
}
//-----------------------------------------------------------------------------------------------------------------------------------------
int actionpointCount(Player *Alive[], int playerAlive){
	int actionpointMax;
	int Attack, c_i;
	actionpointMax = Alive[1]->stats.hero.actionpoint;
	Attack = 1;
	for( c_i = 2; c_i <= playerAlive; c_i++ ){
		if(Alive[ c_i ]->stats.hero.actionpoint > actionpointMax){
			actionpointMax = Alive[ c_i ]->stats.hero.actionpoint;
			Attack = c_i;
		}
	}
	bugFinder("Ready for AP up");
	if(actionpointMax < 1000){
		do{
			bugFinder("Loop/");
			Sleep(1000);
			Alive[1]->stats.hero.actionpoint += Alive[1]->stats.hero.actionpointIncrease;
			actionpointMax = Alive[1]->stats.hero.actionpoint;
			Attack = 1;
			for( c_i = 2; c_i <= playerAlive; c_i++ ){
				Alive[ c_i ]->stats.hero.actionpoint += Alive[ c_i ]->stats.hero.actionpointIncrease;
				if(Alive[ c_i ]->stats.hero.actionpoint > actionpointMax){
					actionpointMax = Alive[ c_i ]->stats.hero.actionpoint;
					Attack = c_i;
				}
			}
		} while(actionpointMax < 1000);
	}
	return c_i;
}
//-----------------------------------------------------------------------------------------------------------------------------------------
void defAction(Player *self, Player *target){
	if(!abilityUse(self, target, 3)){
		damageGet(self, target, hitSimple(self, target));
	}
	abilityUse(target, self, 1);
	self->stats.hero.actionpoint -= 1000;
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Main function - 		v0
//PvP -					v0
//Deathmatch -			inDev
//-----------------------------------------------------------------------------------------------------------------------------------------
void PvP(Player* playerFirst, Player* playerSecond){
	Player *Attack, *Def;
	
	system("cls");
	output.all(playerFirst, playerSecond);
	
	while(playerFirst->stats.hero.hitpointCurrent > 0 && playerSecond->stats.hero.hitpointCurrent > 0){
		if(playerFirst->stats.hero.actionpoint < 1000 && playerSecond->stats.hero.actionpoint < 1000){
			playerFirst->stats.hero.actionpoint += playerFirst->stats.hero.actionpointIncrease;
			playerSecond->stats.hero.actionpoint += playerSecond->stats.hero.actionpointIncrease;
			/*bugFinder("Passed");*/
		}
		if(playerFirst->stats.hero.actionpoint >= playerSecond->stats.hero.actionpoint){
			Attack = playerFirst;
			Def = playerSecond;
		}
		else{
			Attack = playerSecond;
			Def = playerFirst;
		}
		if(!abilityUse(Attack, Def, 3)){
			damageGet(Attack, Def, hitSimple(Attack, Def));
		}
		Sleep(1000);				//WTF? GABE FIX IT!
		timePassed(1000, Attack);
		timePassed(1000, Def);
		abilityUse(Def, Attack, 1);
		Attack->stats.hero.actionpoint -= 1000;
		output.all(playerFirst, playerSecond);
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------
/*void chooseEnemy(Player[] Players, Player )
*/
void Deathmatch(Player Players[], int playerCount){
	int c_i, attackId, targetId;
	int playerAlive = 0;
	Player *attack, *target, *Alive[10], *PlayersList[10];
	
	system("cls");
	output.playerList(PlayersList, playerCount);
	bugFinder("Ready for loop");
	for( c_i = 1; c_i <= playerCount; c_i++){
		if( Players[ c_i ].stats.hero.hitpointCurrent > 0){
			playerAlive++;
			Alive[ playerAlive ] = &Players[ c_i ];
		}
		PlayersList[ c_i ] = &Players[ c_i ];
	}
	bugFinder("Out of loop");
	if(playerAlive > 0) do{
		attackId = actionpointCount(Alive, playerAlive);
		attack = Alive[ attackId ];
		bugFinder("Attack - " + attack->stats.hero.name);
		output.targetList(Alive, playerAlive, attack);
		cin >> targetId;
		if(targetId <= attackId){
			targetId++;
		}
		target = Alive[ targetId ];
		bugFinder("target - " + target->stats.hero.name);
		defAction(attack, target);
		timePassed(1000, Alive, playerAlive);
		output.playerList(PlayersList, playerCount);
	} while(playerAlive > 1);
}
//--------------------------------------------------------------------------------------------------
int main(/*int argc, char* argv[]*/){
	
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute( hConsoleHandle, 15 | BACKGROUND_INTENSITY );
	system("cls");
	
	int abilityCount = getAbilityCount(), mode, playerCount, c_i;
	
	for(c_i = 1; c_i <= abilityCount; c_i++){
		abilityMassive[c_i].readStats(c_i);
	}
	if( true ){
		output.MainMenu( MENU_POSITION_X, MENU_POSITION_Y );
		output.Frame( MENU_SIZE_X, MENU_SIZE_Y, MENU_POSITION_X, MENU_POSITION_Y );
		mode = console.Cursor( MENU_POSITION_X, MENU_POSITION_Y + 1, MENU_MODE_COUNT, '|' );
		
	}
	else{
	console.PositionSet( 30, 0 );
	cout << "Choose game mode*:";
	console.PositionSet( 10, 1 );
	cout << "1 - PvP (1x1)";
	console.PositionSet( 10, 2 );
	cout << "2 - DeathMatch (2+)**";
	console.PositionSet( 10, 3 );
	cout << "3 - Debug!";
	console.PositionSet( 0, 5 );
	cout << "*else (default) - Debug" << endl;
	cout << "**Currently in develop!" << endl;
	mode = console.Cursor( 10 - 1, 1, 3 );
	console.PositionSet(30, 10);	
	}

	if(mode == 1){
		Player Player1, Player2;
		Player *P1 = &Player1, *P2 = &Player2;
		system("cls");
		cout << "Load your heroes:" << endl << endl;
		Player1.readStats();
		Player1.abilityClean();
		Player2.readStats();
		Player2.abilityClean();
		/*Player1.abilityGetInfo(abilityMassive, abilityCount);
		Player2.abilityGetInfo(abilityMassive, abilityCount);*/
		abilityUpAll(P1, P2);
		abilityUpAll(P2, P1);
		output.all(P1, P2);
		PvP(P1, P2);
		system("cls");
		if(P1->stats.hero.hitpointCurrent > P2->stats.hero.hitpointCurrent){
			cout << P1->stats.hero.name << " win!";
		}
		else{
			cout << P2->stats.hero.name << " win!";
		}
	}
	else if(mode == 2){
		Player Players[10], playerReading;
		
		cout << "Players - ";
		cin >> playerCount;
		if(playerCount < 2 || playerCount > 6){
			cout << "reize to 3";
			playerCount = 3;
		}
		for(c_i = 1; c_i <= playerCount; c_i++){
			Players[ c_i ].readStats();
			Players[ c_i ].abilityClean();
			/*Players[ c_i ].abilityGetInfo(abilityMassive, abilityCount);*/
			abilityUpAll( &Players[ c_i ], &Players[ 0 ]);
		}
		Player* PA[ 10 ];
		/*PA = &Players;*/
		output.playerList(PA, playerCount);
		Deathmatch(Players, playerCount);
	}
	else{	//DEBUG ||~-~-~-~-~-~-~-~( =-= )~-~-~-~-~-~-~-~||
	}
	console.PositionSet( TRASH_POSITION_X, TRASH_POSITION_Y );
	return 0;
}
