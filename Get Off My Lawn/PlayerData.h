/******************************************************************************/
/*!
\file   PlayerData.h
\author Tan Zhi Quan		(100%)
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
#ifndef PLAYERDATA_H
#define PLAYERDATA_H

#include <fstream>				// File IO
#include <iostream>				// IO
#include <array>

#include <Shlobj.h>
#include <string>
#include <cstdlib>
#include <Windows.h>

enum Shop_Items
{
	Money_Rate = 0,
	Shooter,
	Tank,
	Speed,
	Saboteur,
	Slow,
	Bruiser,
	Stun,
	Heal,
	Buff
};
class PlayerData
{
private:
	// total number of stars the player currently has
	int stars_collected_;
	// total number of stars the player has gained so far in playthrough
	int stars_awarded_;
	// how many levels have been finished
	int levels_complete_;
	// array of 10 levels, 0-2 stars -> how many stars have been collected in which level, level 1 -> 0th index, level 10 -> 9th index
	std::array<int, 10> level_stars_;
	// checks if the tutorial is complete
	bool tutorial_complete_;

	/********************************************************************/
	/* Following variables track the level of upgrade that each unit has
	   0 -> none
	   1 -> first level
	   2 -> second and final
	*/
	/********************************************************************/
	// Level Up / Cost Down / Max Cap Gain Increase
	int money_rate_upgrade_;
	// Shooter up range atkrate
	int shooter_upgrade_;
	// Tank up health movspeed
	int tank_upgrade_;
	// Speed up health down cost
	int speed_upgrade_;
	// Saboteur up atk rate down cost
	int saboteur_upgrade_;
	// Slow up range damage
	int slow_upgrade_;
	// Damage up damage down cost
	int bruiser_upgrade_;
	// Stun up atkrate range
	int stun_upgrade_;
	// Heal up heal range
	int heal_upgrade_;
	// Buff up range health
	int buff_upgrade_;
	// string holding name of text file currently used for save
	std::string current_save_file;
	// number of stars earned in last completed level
	int stars_earned_;
	// stage reached in the tutorial
	int stage_;
	// path to my documents and folder within
	std::string mydocuments_;
public:
	std::fstream playersavefile;
	PlayerData();

	void ReInit_PlayerData();
	void Close_Current_Open_File();
	void Make_New_Save(int save_no);
	void Make_Path_To_My_Documents();
	void Delete_Save(std::string& filename);
	void Read_Save_File();
	void Save_Save_File();

	template<typename T>
	void Save_Stat(T input);
	template<typename T , unsigned N>
	void Save_Stat(std::array<T, N> input);

	int Get_Stars_Earned() const;
	int Get_Stars_Collected() const;
	int Get_Money_Rate_Upgrade() const;
	int Get_Shooter_Upgrade() const;
	int Get_Tank_Upgrade() const;
	int Get_Speed_Upgrade() const;
	int Get_Saboteur_Upgrade() const;
	int Get_Slow_Upgrade() const;
	int Get_Bruiser_Upgrade() const;
	int Get_Stun_Upgrade() const;
	int Get_Heal_Upgrade() const;
	int Get_Buff_Upgrade() const;
	int Get_Stage() const;
	int Get_Stars_Awarded() const;
	int Get_Levels_Complete() const;
	int Get_Level_Stars(unsigned pos) const;
	bool Get_Tutorial_Completion() const;
	std::string Get_Path_Name() const;


	void Set_Stage(int stage);
	void Set_Tutorial_Completion(bool complete);
	void Set_Levels_Complete(int level_no);
	void Set_Level_Stars(int granny_hp, int level_no);

	void Open_Shop();
	void Buy_Tier_1(int shop_item);
	void Buy_Tier_2(int shop_item);

	void Print_Player_Save_Stats() const;
};

bool Does_File_Exist(const char *filename);

extern PlayerData playdata;

#endif PLAYERDATA_H