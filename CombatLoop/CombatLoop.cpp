// CombatLoop.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

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
	int Money;
	int CritChance;
	int ExtraHealing;
};

void PlayerTurn(Player& p, Encounter& e, std::string name);
void EncounterTurn(Player& player, Encounter& encounter, std::string name);
int RandomEncounter();
void ShopTurn(Player& player);

Player player = {
		30,
		3,
		5,
		0,
		0
};
Encounter shop = {
			0,
			100,
			10,
			false
};
Encounter rat = {
			1,
			3,
			1,
			true
};
Encounter cow = {
			2,
			5,
			2,
			true
};
Encounter camel = {
			3,
			10,
			3,
			true
};
Encounter rival = {
4,
10,
3,
true
};
Encounter dragon = {
			5,
			20,
			5,
			true
};

int main()
{

	std::cout << "Your adventure has begun!\n";

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
	std::cout << "Oh dear, you have died.";
}

void PlayerTurn(Player& player, Encounter& encounter, std::string name)
{
	//Player input determines actions taken in player turn
	std::cout << "You have come across a " << name << " (" << encounter.HealthPool << " HP)" << std::endl;
	std::cout << "Press 1 to Fight, 2 to drink a health potion, 3 to run away, or 4 to check your current status." << std::endl;
	int choice;
	std::cin >> choice;
	int critroll = (1 + rand() % 100);

	switch (choice)
	{
	case 1:
		if (critroll < player.CritChance)
		{
			std::cout << "You land a vicious blow dealing critical damage! (" << (player.BasicAttackDamage*2) << " Damage)" << std::endl;
			encounter.HealthPool -= (player.BasicAttackDamage * 2);
		}
		else
		{
			std::cout << "You manage to land a hit! (" << player.BasicAttackDamage << " Damage)" << std::endl;
			encounter.HealthPool -= player.BasicAttackDamage;
			std::cout << "The " << name << " has " << encounter.HealthPool << " hp remaining!" << std::endl;
		}
		break;
	case 2:
		std::cout << "You quickly down the contents of a potion bottle." << std::endl;
		player.HealthPool += (5 + player.ExtraHealing);
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
		std::cout << "And scores a hit, dealing " << encounter.BasicAttackDamage << " damage!" << std::endl;
		player.HealthPool -= encounter.BasicAttackDamage;
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