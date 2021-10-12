/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   Players.h
\author Wong Zhihao			(80%)| Zachary Sng Zhi Ren (20%)
\par    email: zhihao.wong\@digipen.edu | z.sng\@digipen.edu
\par    DigiPen login: zhihao.wong
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the declaration of the Player class and its functions.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef PLAYERS_H
#define PLAYERS_H

class Players
{
private:
	float current_granny_mojo_;	// Player's current granny mojo
	float max_granny_mojo_;		// Player's max granny mojo attainable
	float rate_granny_mojo_;	// How fast the player's granny mojo recharge
	int grandma_base_HP_;       // Grandma's Base Health
	int kid_base_HP_;           // Kid's Base Health

public:
	// Default constructor of Player
	Players();

	// Resets Player class to default variables
	void Players::Reset_Player_Stats();

	// Gets the current granny mojo amount
	float Get_Granny_Mojo() const;

	// Adds to the current granny mojo amount
	void Set_Granny_Mojo(float modifier);

	// Gives the player mojo coins during the tutorial.
	void Tutorial_Give_Granny_Mojo(float mojo);

	// Gets the max mojo coins the player can earn currently.
	float Get_Max_Granny_Mojo();

	// Sets the max mojo coins the player can earn currently.
	void Set_Max_Granny_Mojo(float modifier);

	// Sets the rate at which the player earns mojo coins.
	void Set_Rate_Granny_Mojo(float modifier);

	// Gets the rate at which the player earns mojo coins.
	float Get_Rate_Granny_Mojo();

	// 	Retrieves Player's Base Health
	int Get_Grandma_Base_HP();

	// Retrieves the Kid's base Health
	int Get_Kid_Base_HP();

	// Prints the player's currency
	void Print_Currency();

	// Handles granny mojo earning
	void Granny_Mojo_Earn();

	// Handles granny mojo earned from defeating kids
	void Granny_Mojo_Drop(int);

	// Damages the Grandma Base
	void Damage_Grandma_Base();

	// Damages the Kid Base
	void Damage_Kid_Base(int level_no);

	// Handles player data updating when player wins.
	void Victory(int grandma_base_HP, int level_no);
};

#endif PLAYERS_H
