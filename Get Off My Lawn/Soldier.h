/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   Soldier.h
\author Wong Zhihao (40%) | Zachary Sng Zhi Ren(60%)
\par    email: zhihao.wong\@digipen.edu | z.sng\@digipen.edu
\par    DigiPen login: zhihao.wong | z.sng
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the implementation of the Soldier class.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef SOLDIER_H
#define SOLDIER_H

#include "Combatant.h" // Combatant functions

typedef class Graphics_Manager Graphics_Manager;
typedef class Path Path;

// What type of soldier it is
enum SOLDIER_TYPE
{
	NORMAL = 0,
	RUSHER,
	ANTI_RUSHER,
	ANTI_TOWER
};

class Soldier : public Combatant
{
protected:
	float speed_;			// Movement speed of soldiers
	float direction_;		// Direction the soldier is moving in ** NOT USED YET **
	AEVec2 vel_;			// Velocity of the object
	SOLDIER_TYPE category_; // Classification of a soldier
	Path * move_target_;		// Which node this unit is moving to next

	bool is_stunned_;           // Whether a unit is stunned
	double stun_start_time_;    // The time when a unit gets stunned
	double stun_recovery_time_; // The recovery timer for a stunned unit

	bool is_poisoned_;           // Whether a unit is poisoned
	double poison_start_time_;    // The time when a unit gets poisoned
	double poison_recovery_time_; // The recovery timer for a poisoned unit
	int poison_flag_;			// Flags for poison damage

	bool is_slowed_;           // Whether a unit is slowed
	double slow_start_time_;    // The time when a unit gets slowed
	double slow_recovery_time_; // The recovery timer for a slowed unit

	bool is_buffed_;           // Whether a unit's attack is buffed
	double buff_start_time_;    // The time when a unit's attack gets buffed
	double buff_recovery_time_; // The recovery timer for an attack buffed unit

	float bubble_counter_;             // Timer for status effect visuals
public:
	// Default constructor
	Soldier();

	// Specialised constructor
	Soldier(
		// Soldier variables
		float speed,			// Speed of the unit
		SOLDIER_TYPE category,	// Which type of soldier it is
		
		// Combatant variables
		bool is_aoe,				// Whether unit is AOE
		int health,					// Health AND max health
		int cost,					// Cost to buy unit
		int loot,					// Amount of lunch money unit gives when it is defeated
		int attack_power,			// Damage of the unit
		float attack_rate,			// Attack speed
		float range,				// Attack range

		// GameObject variables
		SIDES side,					// Grandma or Kid?
		float x, float y,			// Spawn position
		float scale_x,				// Scale/Radius of the unit
		float scale_y,
		OBJECT_TYPES object_type,	// What kind of object it is
		UNIT_TYPES unit_type		// What type of unit it is
	);

	// Default destructor
	virtual ~Soldier();

	virtual void Update();
	virtual void Draw();
	virtual void Free();

	// Gets the speed of the soldier
	float const Get_Speed() const;
	// Set the speed of the soldier
	void Set_Speed(float);


	//Gets the x-directional speed
	float Get_x_Speed() const;
	//Sets the x-directional speed
	void Set_x_Speed(float speed);

	//Gets the y-directional speed
	float Get_y_Speed() const;
	//Sets the y-directional speed
	void Set_y_Speed(float speed);

	// Get the category of the soldier
	SOLDIER_TYPE const Get_Category() const;
	// Set the category of the soldier
	void Set_Category(SOLDIER_TYPE);

	//Gets the stun status of the soldier
	bool Get_is_Stunned()const;
	//Sets the stun status of the soldier
	void Set_is_Stunned(bool);

	//Gets the stun start time of the soldier
	double Get_Stun_Start_Time()const;
	//Sets the stun start time of the soldier
	void Set_Stun_Start_Time();

	//Gets the stun timer of the soldier
	double Get_Stun_Recovery_Time()const;
	//Sets the stun timer of the soldier
	void Set_Stun_Recovery_Time(double);

	//Gets the poison status of the soldier
	bool Get_is_Poisoned()const;
	//Sets the poison status of the soldier
	void Set_is_Poisoned(bool);

	//Gets the poison start time of the soldier
	double Get_Poison_Start_Time()const;
	//Sets the poison start time of the soldier
	void Set_Poison_Start_Time();

	//Gets the poison timer of the soldier
	double Get_Poison_Recovery_Time()const;
	//Sets the poison timer of the soldier
	void Set_Poison_Recovery_Time(double);

	//Gets the slow status of the soldier
	bool Get_is_Slowed()const;
	//Sets the slow status of the soldier
	void Set_is_Slowed(bool);

	//Gets the slow start time of the soldier
	double Get_Slow_Start_Time()const;
	//Sets the slow start time of the soldier
	void Set_Slow_Start_Time();

	//Gets the slow timer of the soldier
	double Get_Slow_Recovery_Time()const;
	//Sets the slow timer of the soldier
	void Set_Slow_Recovery_Time(double);

	//Gets the attack buff status of the soldier
	bool Get_is_Buffed()const;
	//Sets the attack buff status of the soldier
	void Set_is_Buffed(bool);

	//Gets the poison flag of the soldier
	int Get_Poison_Flag()const;
	//Sets the poison flag of the soldier
	void Set_Poison_Flag(int);

	//Gets the bubble timer counter of the soldier
	float Get_Bubble_Counter()const;
	//Reduces the bubble timer counter of the soldier
	void Set_Bubble_Counter(float);

	//Gets the next movement node
	Path * Get_Move_Target() const;
	//Sets the next movement node
	void Set_Move_Target(Path * target);

	//Handles all the status effects of the soldier
	void Status_Updates();
};
#endif SOLDIER_H