// CombatLoop.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <list>
#include <algorithm>

struct Encounter
{
	int EncounterId;
	int HealthPool;
	int BasicAttackDamage;
	bool IsCombatEncounter;
};

struct Player
{
	int HealthPool;
	int BasicAttackDamage;
	int CritChance;
	int ExtraHealing;
	std::list<std::string> Inventory;
	int StrengthBonus;
	int DefenseBonus;
};



void PlayerTurn(Player& p, Encounter& e, std::string name);
void EncounterTurn(Player& player, Encounter& encounter, std::string name);
int RandomEncounter();
void ShopTurn(Player& player);
void Dungeon();
void Forest();
void Tundra();
void Swamp();
void Desert();

void ChangeBiome(int biome);

Player player = {
		30,
		3,
		0,
		0,
		std::list<std::string>{},
		0,
		0
};


Encounter rat = {
			1,
			3,
			2,
			true
};
Encounter cow = {
			2,
			5,
			3,
			true
};
Encounter camel = {
			3,
			10,
			5,
			true
};
Encounter rival = {
4,
10,
8,
true
};
Encounter dragon = {
			5,
			20,
			15,
			true
};

int Biome = 0;

int main()
{
	
	std::cout << "Your adventure has begun!\n";

	while (player.HealthPool > 0)
	{
		std::cout << "You see you can head in any cardinal direction, North to the tundra, East to the swamp, South to the Desert or West to the Forest" << std::endl;
		std::cout << "1 = Tundra. 2 = Swamp. 3 = Desert. 4 = Forest." << std::endl;
		std::cin >> Biome;
		ChangeBiome(Biome);
	}
	
	std::cout << "Oh dear, you have died.";
}

void ChangeBiome(int biome)
{
	switch (biome)
	{
	case 1:
		Tundra();
		break;
	case 2:
		Swamp();
		break;
	case 3:
		Desert();
	case 4:
		Forest();
		break;
	default:
		break;
	}
}

/// <summary>
/// This could be simplified into Biome() function that has the type passed into it
/// </summary>
void Tundra() 
{
	int TundraChoice;
	std::cout << "You find yourself in the frigid tundra. What would you like to do here?" << std::endl;
	std::cout << "1: Rest and recuperate. 2: Investigate the tundra. 3: Change biome" << std::endl;
	std::cin >> TundraChoice;

	switch (TundraChoice)
	{
	case 1:
		player.HealthPool = 30;
		std::cout << "You take a moment to rest. (your health has been restored to full)" << std::endl;
		break;
	case 2:
		int investigateRoll = (1 + rand() % 100);
		if (investigateRoll > 89)
		{
			//Loot?
		}
		else if (10 < investigateRoll <= 89)
		{
			//standard encounter
		}
		else
		{
			//Discover the dungeon of this area
		}
		break;
	case 3:
		std::cout << "1 = Tundra. 2 = Swamp. 3 = Desert. 4 = Forest." << std::endl;
		std::cin >> Biome;
		ChangeBiome(Biome);
		break;
	default:
		break;
	}
}

/// <summary>
/// Needs to have difficulty of encounters increased, and have escape return player to current biome overworld - add loot?
/// </summary>
void Dungeon() 
{
	while (player.HealthPool > 0)
	{
		std::cout << "You make your way deeper into the dungeon." << std::endl;
		std::cout << std::endl;

		switch (RandomEncounter())
		{
		case 0:
			//Shop encounter           
			std::cout << "You stumble across a strange altar, pulsing in the dark. Atop it's black marble surface lies an amulet and a potion.\n";
			std::cout << "Rejuvination potion (Increases amount healed).  Berserker's Amulet (Adds 10% crit chance).\n";
			ShopTurn(player);
			break;
		case 1:
			if (rat.HealthPool <= 0)
			{
				rat.HealthPool = 3;
			}
			//Rat encounter           
			while (rat.HealthPool >= 1)
			{
				PlayerTurn(player, rat, "rat");
				if (rat.HealthPool <= 0)
				{
					std::cout << "You have slain the beast!" << std::endl;
					break;
				}
				else
				{
					EncounterTurn(player, rat, "rat");
					if (player.HealthPool <= 0)
						break;
				}
			}
			break;
		case 2:
			//Cow encounter
			if (cow.HealthPool <= 0)
			{
				cow.HealthPool = 5;
			}
			while (cow.HealthPool >= 1)
			{
				PlayerTurn(player, cow, "cow");
				if (cow.HealthPool <= 0)
				{
					std::cout << "You have slain the beast!" << std::endl;
					break;
				}
				else
				{
					EncounterTurn(player, cow, "cow");
					if (player.HealthPool <= 0)
						break;
				}
			}
			break;
		case 3:
			if (camel.HealthPool <= 0)
			{
				camel.HealthPool = 10;
			}
			//Angry camel encounter

			while (camel.HealthPool >= 1)
			{
				PlayerTurn(player, camel, "camel");
				if (camel.HealthPool <= 0)
				{
					std::cout << "You have slain the beast!" << std::endl;
					break;
				}
				else
				{
					EncounterTurn(player, camel, "camel");
					if (player.HealthPool <= 0)
						break;
				}
			}
			break;
		case 4:
			if (rival.HealthPool <= 0)
			{
				rival.HealthPool = 10;
			}
			//Rival adventurer encounter

			while (rival.HealthPool >= 1)
			{
				PlayerTurn(player, rival, "rival");
				if (rival.HealthPool <= 0)
				{
					std::cout << "You have slain the beast!" << std::endl;
					break;
				}
				else
				{
					EncounterTurn(player, rival, "rival");
					if (player.HealthPool <= 0)
						break;
				}
			}
			break;
		case 5:
			if (dragon.HealthPool <= 0)
			{
				dragon.HealthPool = 20;
			}
			//Dragon encounter

			while (dragon.HealthPool >= 1)
			{
				PlayerTurn(player, dragon, "dragon");
				if (dragon.HealthPool <= 0)
				{
					std::cout << "You have slain the beast!" << std::endl;
					break;
				}
				else
				{
					EncounterTurn(player, dragon, "dragon");
					if (player.HealthPool <= 0)
						break;
				}
			}
			break;
		}
	}
}

void PlayerTurn(Player& player, Encounter& encounter, std::string name)
{
	//Player input determines actions taken in player turn
	std::cout << "You have come across a " << name << " (" << encounter.HealthPool << " HP)" << std::endl;
	std::cout << "Press 1 to Fight, 2 to drink a health potion, 3 to run away, or 4 to check your current status." << std::endl;
	int choice;
	std::cin >> choice;
	int critroll = (1 + rand() % 100);

	auto potionPointer = std::find(player.Inventory.begin(), player.Inventory.end(), "potion");

	switch (choice)
	{
	case 1:
		if ((rand() % 100) <= 5)
		{
			std::cout << "Your strike goes wide as the creature dodges nimbly out of the way! (0 Damage)" << std::endl;
		}
		else
		{
			if (critroll < player.CritChance)
			{
				std::cout << "You land a vicious blow dealing critical damage! (" << ((player.BasicAttackDamage + player.StrengthBonus) * 2) << " Damage)" << std::endl;
				encounter.HealthPool -= (player.BasicAttackDamage * 2);
			}
			else
			{
				int damageRoll = (1+rand()%player.BasicAttackDamage + player.StrengthBonus);
				std::cout << "You manage to land a hit! (" << damageRoll << " Damage)" << std::endl;
				encounter.HealthPool -= damageRoll;
				std::cout << "The " << name << " has " << encounter.HealthPool << " hp remaining!" << std::endl;
			}
		}

		break;
	case 2:
		if (potionPointer != player.Inventory.end())
		{
			std::cout << "You quickly down the contents of a potion bottle." << std::endl;
			player.HealthPool += (5 + player.ExtraHealing);
		}
		else
		{
			std::cout << "You fumble around for a potion, but you have none left!" << std::endl;
			PlayerTurn(player, encounter, name);
		}
		break;
	case 3:
		std::cout << "You just about manage to escape from the encounter." << std::endl;
		break;
	case 4:
		std::cout << "Current Health: " << player.HealthPool << std::endl;
		std::cout << "Crit chance: " << player.CritChance << std::endl;
		std::cout << "Additional healing recieved: " << player.ExtraHealing << std::endl;
		PlayerTurn(player, encounter, name);
		break;
	default:
		std::cout << "Input unrecognized, please enter 1, 2 or 3" << std::endl;
		PlayerTurn(player, encounter, name);
		break;
	}
}

void EncounterTurn(Player& player, Encounter& encounter, std::string name)
{
	//Encounter takes a turn (Basic just attacks, 
	//                        could include checks against player and encounter health to determine if to heal instead)

	int missChance = (rand() % 5);

	std::cout << "The " << name << " lashes out at you..." << std::endl;
	if (missChance == 0)
	{
		std::cout << "But missed!" << std::endl;
	}
	else
	{
		int damageRoll = ((1+rand() % encounter.BasicAttackDamage) - player.DefenseBonus);
		std::cout << "And scores a hit, dealing " << damageRoll << " damage!" << std::endl;
		player.HealthPool -= damageRoll;
		std::cout << "You have " << player.HealthPool << " hp left!" << std::endl;
	}
}

int RandomEncounter()
{
	//Selects a random encounter "on the road" returns a value between 0-5
	int EncounterFound = (rand() % 5);
	return EncounterFound;
}

void ShopTurn(Player& player)
{
	int ShopChoice;
	std::cout << "Enter 1 to take the rejuvination potion, 2 for the berserker amulet or 3 for neither.\n";
	std::cin >> ShopChoice;

	switch (ShopChoice)
	{
	case 1:
		player.HealthPool += 10;
		player.ExtraHealing += 2;
		std::cout << "You quickly chug the vibrant potion, it burns your throat on the way down. (healing recieved from potions is increased)\n";
		break;
	case 2:
		player.CritChance += 10;
		std::cout << "As you don the amulet you feel your blood boil and your muscles tighten. (Crit increased by 10%)\n";
		break;
	case 3:
		std::cout << "A brave choice traveller, may the Gods smile upon you.\n";
		break;
	default:
		std::cout << "What was that? I didn't quite catch that.\n";
		ShopTurn(player);
		break;
	}
}