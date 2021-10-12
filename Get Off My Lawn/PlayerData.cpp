/******************************************************************************/
/*!
\file   PlayerData.cpp
\author Tan Zhi Quan (100%)
\par    email: zhiquan.tan\@digipen.edu
\par    DigiPen login: zhiquan.tan
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the algorithmn to handle player save files

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "PlayerData.h"
#include "GameStateList.h" //temp
#include "main.h"
#include <array>
#include <cstdio> // remove -> to delete files (DO NOT REMOVE)
#include <string>
#include "RenderManager.h"
#include "SystemComponents.h"
#include "LogicComponents.h"

PlayerData playdata;

bool Does_File_Exist(const char *filename)
{
	std::fstream file(filename);
	return (bool) file;
}

PlayerData::PlayerData()
	: stars_collected_(0),
	  stars_awarded_(0),
	  levels_complete_(0),
	  tutorial_complete_(false),
	  money_rate_upgrade_(0),
	  shooter_upgrade_(0),

	  tank_upgrade_(0),
	  speed_upgrade_(0),
	  saboteur_upgrade_(0),
	  slow_upgrade_(0),
	  bruiser_upgrade_(0),
	  stun_upgrade_(0),
	  heal_upgrade_(0),
	  buff_upgrade_(0),
	  stars_earned_(0),
	  stage_(1),
	  mydocuments_("")
	{
		// creates folder in my documents, stores path in mydocuments_
		Make_Path_To_My_Documents();


		for (unsigned i = 0; i < level_stars_.size(); ++i)
		{
			level_stars_[i] = 0;
		}
	}

// resets eveyrthing to fresh copy
void PlayerData::ReInit_PlayerData()
{
	stars_collected_ = 0;
	stars_awarded_ = 0;
	levels_complete_ = 0;
	tutorial_complete_ = false;

	for (unsigned i = 0; i < level_stars_.size(); ++i)
	{
		level_stars_[i] = 0;
	}

	money_rate_upgrade_ = 0;
	shooter_upgrade_ = 0;
	tank_upgrade_ = 0;
	speed_upgrade_ = 0;
	saboteur_upgrade_ = 0;
	slow_upgrade_ = 0;
	bruiser_upgrade_ = 0;
	stun_upgrade_ = 0;
	heal_upgrade_ = 0;
	buff_upgrade_ = 0;

//	current_save_file.clear();
	stars_earned_ = 0;
	stage_ = 1;
}


void PlayerData::Close_Current_Open_File()
{
	if (playersavefile.is_open())
	{
		playersavefile.close();
	}
}

void PlayerData::Make_New_Save(int save_no)
{
	// sets a different save file depending on input
	switch (save_no)
	{
	case 1:
		current_save_file = mydocuments_+ "\\playerdata1.txt";
		break;
	case 2:
		current_save_file = mydocuments_ + "\\playerdata2.txt";
		break;
	case 3:
		current_save_file = mydocuments_ + "\\playerdata3.txt";
		break;
	default:
		std::cout << "this isn't supposed to happen nani" << std::endl;
		return;
	}
	
	// creates file if not already made
	if (!Does_File_Exist(current_save_file.c_str()))
	{
		std::cout << "file does not exist\n";

		playersavefile.open(current_save_file.c_str(), std::fstream::out);
		//closes and reopens to allow input/output
		playersavefile.close();
		playersavefile.open(current_save_file.c_str());

		ReInit_PlayerData();
		Save_Save_File(); //saves the default values of 0 into file

		// If we couldn't open the output file stream for writing
		if (!playersavefile)
		{
			// Print an error and exit
			std::cerr << "GG player save can't be opened" << std::endl;
			gAEGameStateNext = AE_GS_QUIT;
		}
		playersavefile.close();
	}
	//if file exists, read it
	else
	{
		playersavefile.open(current_save_file.c_str());

		std::cout << "file exists\n";
		Read_Save_File();
		playersavefile.close();
	}
}

void PlayerData::Make_Path_To_My_Documents()
{
	// to store file path in wide char
	wchar_t* mydocs = 0;
	// gets file path to my documents
	SHGetKnownFolderPath(FOLDERID_Documents, 0, NULL, &mydocs);

	// inputs for wcstombs_s
	char cstr[80];
	size_t i;
	// converts wchar to normal c string
	wcstombs_s(&i, cstr, mydocs, 80);

	// stores file path into std::string
	std::string docpath(cstr);

	// following string are file paths to the game folder for save files
	std::string newfoldername = "Get off my Lawn!";
	mydocuments_ = docpath + "\\" + newfoldername;

	if (CreateDirectory(mydocuments_.c_str(), NULL) ||
		ERROR_ALREADY_EXISTS == GetLastError())
	{}

	//SHGetKnownFolderPath allocates memory, following code deallocates said memory
	CoTaskMemFree(static_cast<void*>(mydocs));
}

void PlayerData::Delete_Save(std::string& filename)
{
	if (Does_File_Exist(filename.c_str()))
	{
		if (current_save_file.c_str() == filename.c_str())
			Close_Current_Open_File();
		if (remove(filename.c_str()))
			std::cout << "Error! Failed to delete save file." << std::endl;
		else std::cout << "Save file successfully deleted." << std::endl;
	}
	logic_components.level_data->Spawn_Level_Play_Data();
}

void PlayerData::Read_Save_File()
{
	//stores unwanted strings to be discarded later
	std::string temp; 
	playersavefile >> temp >> stars_collected_;
	playersavefile >> temp >> stars_awarded_;
	playersavefile >> temp >> levels_complete_;
	playersavefile >> temp >> tutorial_complete_;
	playersavefile >> temp;
	for(unsigned i = 0; i < level_stars_.size(); ++i)
		playersavefile >> level_stars_[i];
	playersavefile >> temp >> money_rate_upgrade_;
	playersavefile >> temp >> shooter_upgrade_;
	playersavefile >> temp >> tank_upgrade_;
	playersavefile >> temp >> speed_upgrade_;
	playersavefile >> temp >> saboteur_upgrade_;
	playersavefile >> temp >> slow_upgrade_;
	playersavefile >> temp >> bruiser_upgrade_;
	playersavefile >> temp >> stun_upgrade_;
	playersavefile >> temp >> heal_upgrade_;
	playersavefile >> temp >> buff_upgrade_;
	
	printf("stars:collected %d, %s \n", stars_collected_, temp.c_str());

}

void PlayerData::Save_Save_File()
{
	if(!playersavefile.is_open())
		playersavefile.open(current_save_file.c_str());

	playersavefile << "Stars_Collected: ";
	Save_Stat(stars_collected_);
	playersavefile << "Stars_Awarded: ";
	Save_Stat(stars_awarded_);
	playersavefile << "Levels_Complete: ";
	Save_Stat(levels_complete_);
	playersavefile << "Tutorial_Complete: ";
	Save_Stat(tutorial_complete_);
	playersavefile << "Level_Stars: ";
	Save_Stat(level_stars_);
	playersavefile << "Money_Rate_Upgrade: ";
	Save_Stat(money_rate_upgrade_);
	playersavefile << "Shooter_Upgrade: ";
	Save_Stat(shooter_upgrade_);
	playersavefile << "Tank_Upgrade: ";
	Save_Stat(tank_upgrade_);
	playersavefile << "Speed_Upgrade: ";
	Save_Stat(speed_upgrade_);
	playersavefile << "Saboteur_Upgrade: ";
	Save_Stat(saboteur_upgrade_);
	playersavefile << "Slow_Upgrade: ";
	Save_Stat(slow_upgrade_);
	playersavefile << "Bruiser_Upgrade: ";
	Save_Stat(bruiser_upgrade_);
	playersavefile << "Stun_Upgrade: ";
	Save_Stat(stun_upgrade_);
	playersavefile << "Heal_Upgrade: ";
	Save_Stat(heal_upgrade_);
	playersavefile << "Buff_Upgrade: ";
	Save_Stat(buff_upgrade_);

	playersavefile.close();
}

template<typename T>
void PlayerData::Save_Stat(T input)
{
	playersavefile << input << std::endl;
}

template <typename T, unsigned N>
void PlayerData::Save_Stat(std::array<T, N> input)
{
	for (unsigned i = 0; i < N; ++i)
		playersavefile << input[i] << " ";
	playersavefile << std::endl;
}

int PlayerData::Get_Stars_Earned() const
{
	return stars_earned_;
}

int PlayerData::Get_Stars_Collected() const
{
	return stars_collected_;
}

int PlayerData::Get_Money_Rate_Upgrade() const
{
	return money_rate_upgrade_;
}

int PlayerData::Get_Shooter_Upgrade() const
{
	return shooter_upgrade_;
}

int PlayerData::Get_Tank_Upgrade() const
{
	return tank_upgrade_;
}

int PlayerData::Get_Speed_Upgrade() const
{
	return speed_upgrade_;
}

int PlayerData::Get_Saboteur_Upgrade() const
{
	return saboteur_upgrade_;
}

int PlayerData::Get_Slow_Upgrade() const
{
	return slow_upgrade_;
}

int PlayerData::Get_Bruiser_Upgrade() const
{
	return bruiser_upgrade_;
}

int PlayerData::Get_Stun_Upgrade() const
{
	return stun_upgrade_;
}

int PlayerData::Get_Heal_Upgrade() const
{
	return heal_upgrade_;
}

int PlayerData::Get_Buff_Upgrade() const
{
	return buff_upgrade_;
}

int PlayerData::Get_Stage() const
{
	return stage_;
}

int PlayerData::Get_Stars_Awarded() const
{
	return stars_awarded_;
}

int PlayerData::Get_Levels_Complete() const
{
	return levels_complete_;
}



int PlayerData::Get_Level_Stars(unsigned pos) const
{
	if (pos < 0 || pos > 9)
		return 0;
	else
		return level_stars_[pos];
}

bool PlayerData::Get_Tutorial_Completion() const
{
	return tutorial_complete_;
}

std::string PlayerData::Get_Path_Name() const
{
	return mydocuments_;
}


void PlayerData::Set_Stage(int stage)
{
	stage_ = stage;
}

void PlayerData::Set_Tutorial_Completion(bool complete)
{
	tutorial_complete_ = complete;
}

void PlayerData::Set_Levels_Complete(int level_no)
{
	if (levels_complete_ < level_no)
	{
		levels_complete_ = level_no;
		Save_Save_File();
	}
}

void PlayerData::Set_Level_Stars(int granny_hp, int level_no)
{
	if (!level_no) return;
	int stars_gained = (granny_hp / 6) ? (granny_hp / 6) : 1;
	stars_earned_ = stars_gained;

	if (level_stars_[level_no - 1] < stars_gained)
	{
		stars_gained -= level_stars_[level_no - 1];
		level_stars_[level_no - 1] += stars_gained;
		stars_collected_ += stars_gained;
		stars_awarded_ += stars_gained;
	}
}

void PlayerData::Open_Shop()
{
	// Money Rate Upgrade
	if (AEInputCheckTriggered(AEVK_1))
	{
		if (!stars_collected_)
		{
			std::cout << "You have no Stars" << std::endl;
			return;
		}
		if (!money_rate_upgrade_)
			Buy_Tier_1(Money_Rate);
		else if (money_rate_upgrade_ == 1)
			Buy_Tier_2(Money_Rate);
		else 
		{
			std::cout << "You have already bought all upgrades for this item";
			return;
		}
	}
	// Shooter Upgrade
	if (AEInputCheckTriggered(AEVK_2))
	{
		if (!stars_collected_)
		{
			std::cout << "You have no Stars" << std::endl;
			return;
		}
		if (!shooter_upgrade_)
			Buy_Tier_1(Shooter);
		else if (shooter_upgrade_ == 1)
			Buy_Tier_2(Shooter);
		else
		{
			std::cout << "You have already bought all upgrades for this item";
			return;
		}
	}
	// Tank Upgrade
	if (AEInputCheckTriggered(AEVK_3))
	{
		if (!stars_collected_)
		{
			std::cout << "You have no Stars" << std::endl;
			return;
		}
		if (!tank_upgrade_)
			Buy_Tier_1(Tank);
		else if (tank_upgrade_ == 1)
			Buy_Tier_2(Tank);
		else
		{
			std::cout << "You have already bought all upgrades for this item";
			return;
		}
	}
	// Speed Upgrade
	if (AEInputCheckTriggered(AEVK_4))
	{
		if (!stars_collected_)
		{
			std::cout << "You have no Stars" << std::endl;
			return;
		}
		if (!speed_upgrade_)
			Buy_Tier_1(Speed);
		else if (speed_upgrade_ == 1)
			Buy_Tier_2(Speed);
		else
		{
			std::cout << "You have already bought all upgrades for this item";
			return;
		}
	}
	// Saboteur Upgrade
	if (AEInputCheckTriggered(AEVK_5))
	{
		if (!stars_collected_)
		{
			std::cout << "You have no Stars" << std::endl;
			return;
		}
		if (!saboteur_upgrade_)
			Buy_Tier_1(Saboteur);
		else if (saboteur_upgrade_ == 1)
			Buy_Tier_2(Saboteur);
		else
		{
			std::cout << "You have already bought all upgrades for this item";
			return;
		}
	}
	// Slow Upgrade 
	if (AEInputCheckTriggered(AEVK_6))
	{
		if (!stars_collected_)
		{
			std::cout << "You have no Stars" << std::endl;
			return;
		}
		if (!slow_upgrade_)
			Buy_Tier_1(Slow);
		else if (slow_upgrade_ == 1)
			Buy_Tier_2(Slow);
		else
		{
			std::cout << "You have already bought all upgrades for this item";
			return;
		}
	}
	// Bruiser Upgrade 
	if (AEInputCheckTriggered(AEVK_7))
	{
		if (!stars_collected_)
		{
			std::cout << "You have no Stars" << std::endl;
			return;
		}
		if (!bruiser_upgrade_)
			Buy_Tier_1(Bruiser);
		else if (bruiser_upgrade_ == 1)
			Buy_Tier_2(Bruiser);
		else
		{
			std::cout << "You have already bought all upgrades for this item";
			return;
		}
	}
	// Stun Upgrade
	if (AEInputCheckTriggered(AEVK_8))
	{
		if (!stars_collected_)
		{
			std::cout << "You have no Stars" << std::endl;
			return;
		}
		if (!stun_upgrade_)
			Buy_Tier_1(Stun);
		else if (stun_upgrade_ == 1)
			Buy_Tier_2(Stun);
		else
		{
			std::cout << "You have already bought all upgrades for this item";
			return;
		}
	}
	// Heal Upgrade
	if (AEInputCheckTriggered(AEVK_9))
	{
		if (!stars_collected_)
		{
			std::cout << "You have no Stars" << std::endl;
			return;
		}
		if (!heal_upgrade_)
			Buy_Tier_1(Heal);
		else if (heal_upgrade_ == 1)
			Buy_Tier_2(Heal);
		else
		{
			std::cout << "You have already bought all upgrades for this item";
			return;
		}
	}
	// Buff Upgrade
	if (AEInputCheckTriggered(AEVK_0))
	{
		if (!stars_collected_)
		{
			std::cout << "You have no Stars" << std::endl;
			return;
		}
		if (!buff_upgrade_)
			Buy_Tier_1(Buff);
		else if (buff_upgrade_ == 1)
			Buy_Tier_2(Buff);
		else
		{
			std::cout << "You have already bought all upgrades for this item";
			return;
		}
	}
}

void PlayerData::Buy_Tier_1(int shop_item)
{
	switch (shop_item)
	{
	case Money_Rate:
		if (!money_rate_upgrade_) 
		{
			money_rate_upgrade_ = 1;
			--stars_collected_;
		}
		break;
	case Shooter:
		if (!shooter_upgrade_)
		{
			shooter_upgrade_ = 1;
			--stars_collected_;
		}
		break;
	case Tank:
		if (!tank_upgrade_)
		{
			tank_upgrade_ = 1;
			--stars_collected_;
		}
		break;
	case Speed:
		if (!speed_upgrade_)
		{
			speed_upgrade_ = 1;
			--stars_collected_;
		}
		break;
	case Saboteur:
		if (!saboteur_upgrade_)
		{
			saboteur_upgrade_ = 1;
			--stars_collected_;
		}
		break;
	case Slow:
		if (!slow_upgrade_)
		{
			slow_upgrade_ = 1;
			--stars_collected_;
		}
		break;
	case Bruiser:
		if (!bruiser_upgrade_)
		{
			bruiser_upgrade_ = 1;
			--stars_collected_;
		}
		break;
	case Stun:
		if (!stun_upgrade_)
		{
			stun_upgrade_ = 1;
			--stars_collected_;
		}
		break;
	case Heal:
		if (!heal_upgrade_)
		{
			heal_upgrade_ = 1;
			--stars_collected_;
		}
		break;
	case Buff:
		if (!buff_upgrade_)
		{
			buff_upgrade_ = 1;
			--stars_collected_;
		}
		break;
	}
	Save_Save_File();
}

void PlayerData::Buy_Tier_2(int shop_item)
{
	if (stars_collected_ < 2)
	{
		std::cout << "Insufficient Stars" << std::endl;
		return;
	}
	switch (shop_item)
	{
	case Money_Rate:
		if (money_rate_upgrade_ == 1)
		{
			money_rate_upgrade_ = 2;
			stars_collected_ -= 2;
		}
		break;
	case Shooter:
		if (shooter_upgrade_ == 1)
		{
			shooter_upgrade_ = 2;
			stars_collected_ -= 2;
		}
		break;
	case Tank:
		if (tank_upgrade_ == 1) 
		{
			tank_upgrade_ = 2;
			stars_collected_ -= 2;
		}
		break;
	case Speed:
		if (speed_upgrade_ == 1)
		{
			speed_upgrade_ = 2;
			stars_collected_ -= 2;
		}
		break;
	case Saboteur:
		if (saboteur_upgrade_ == 1)
		{
			saboteur_upgrade_ = 2;
			stars_collected_ -= 2;
		}
		break;
	case Slow:
		if (slow_upgrade_ == 1)
		{
			slow_upgrade_ = 2;
			stars_collected_ -= 2;
		}
		break;
	case Bruiser:
		if (bruiser_upgrade_ == 1)
		{
			bruiser_upgrade_ = 2;
			stars_collected_ -= 2;
		}
		break;
	case Stun:
		if (stun_upgrade_ == 1)
		{
			stun_upgrade_ = 2;
			stars_collected_ -= 2;
		}
		break;
	case Heal:
		if (heal_upgrade_ == 1)
		{
			heal_upgrade_ = 2;
			stars_collected_ -= 2;
		}
		break;
	case Buff:
		if (buff_upgrade_ == 1)
		{
			buff_upgrade_ = 2;
			stars_collected_ -= 2;
		}
		break;
	}
	Save_Save_File();
}

void PlayerData::Print_Player_Save_Stats() const
{
	char strBuffer[1024]; //buffer to contain string

	std::string player1 = mydocuments_ + "\\playerdata1.txt";
	std::string player2 = mydocuments_ + "\\playerdata2.txt";
	std::string player3 = mydocuments_ + "\\playerdata3.txt";


	if (Does_File_Exist(player1.c_str()))
	{
		std::fstream temp;
		temp.open(player1, std::fstream::in);
		int throwaway, stars_awarded, levels_complete; std::string discard;
		temp >> discard >> throwaway >> discard >> stars_awarded >> discard >> levels_complete;

		sprintf_s(strBuffer, "%d / 30", stars_awarded);
		Print_Text(system_components.font_manager_->Get_Font(F_GAME_GENERAL_TEXT), strBuffer, -427, -207);

		sprintf_s(strBuffer, "%d / 10", levels_complete);
		Print_Text(system_components.font_manager_->Get_Font(F_GAME_GENERAL_TEXT), strBuffer, -287, -207);
	}

	if (Does_File_Exist(player2.c_str()))
	{
		std::fstream temp;
		temp.open(player2, std::fstream::in);
		int throwaway, stars_awarded, levels_complete; std::string discard;
		temp >> discard >> throwaway >> discard >> stars_awarded >> discard >> levels_complete;

		sprintf_s(strBuffer, "%d / 30", stars_awarded);
		Print_Text(system_components.font_manager_->Get_Font(F_GAME_GENERAL_TEXT), strBuffer, -75, -207);

		sprintf_s(strBuffer, "%d / 10", levels_complete);
		Print_Text(system_components.font_manager_->Get_Font(F_GAME_GENERAL_TEXT), strBuffer, 65, -207);
	}

	if (Does_File_Exist(player3.c_str()))
	{
		std::fstream temp; 
		temp.open(player3, std::fstream::in);
		int throwaway, stars_awarded, levels_complete; std::string discard;
		temp >> discard >> throwaway >> discard >> stars_awarded >> discard >> levels_complete;

		sprintf_s(strBuffer, "%d / 30", stars_awarded);
		Print_Text(system_components.font_manager_->Get_Font(F_GAME_GENERAL_TEXT), strBuffer, 275, -207);

		sprintf_s(strBuffer, "%d / 10", levels_complete);
		Print_Text(system_components.font_manager_->Get_Font(F_GAME_GENERAL_TEXT), strBuffer, 415, -207);
	}

}

