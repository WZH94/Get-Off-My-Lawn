/******************************************************************************/
/*!
\game Get Off My Lawn!
\file   Particle.h
\author Wong Zhihao						(10%) |Zachary Sng Zhi Ren(90%)
\par    email: zhihao.wong\@digipen.edu		| z.sng\@digipen.edu
\par    DigiPen login: zhihao.wong			| z.sng
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the declaration of the Particle System and all of its
functions.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef PARTICLE_H
#define PARTICLE_H

#include "GameObject.h"

// Containers
#include <array>

const int MAX_PARTICLE_COUNT = 200; // Maximum number of particles in the list of each emitter

// The different patterns that the particles can spawn from
enum EMITTER_SOURCE_TYPE
{
	EMIT_POINT,
	EMIT_LINE,
	EMIT_CIRCLE
};

class Particle : public GameObject
{
protected:
	float lifetime_;         // Current lifetime of the particle
	float initial_lifetime_; // Initial lifetime of the particle
    float transparency_;     // Transparency of the particle
	float tint_;             // Tint of the particle
	float speed_;            // Speed of the particle
	float direction_;        // Direction that the particle is moving in
	AEVec2 velocity_;        // Velocity of the particle
public:
    Particle();
	Particle(float lifetime,        // Lifetime of the particle
			 float transparency,    // Transparency of the particle
			 float speed,           // Speed of the particle
			 AEVec2 velocity,       // Velocity of the particle
			 float x,               // Position of the particle
			 float y,
			 float scale_x,         // Scale of the particle
			 float scale_y, 
			 UNIT_TYPES unit_type   // Type of the particle
	);

	// Sets the stats of the particles
	void Set_Particle_Stats(float lifetime, float transp, float speed, AEVec2 velocity, float x, float y, UNIT_TYPES unit_type);
	// Activates the particles 
	void Set_Active(float lifetime, float transparency, float speed, AEVec2 velocity, float x, float y, UNIT_TYPES unit_type);
	// Deactivates the particles
	void Set_Inactive();

	//Get the lifetime of the Particle
	float Get_Lifetime() const;
	//Set the lifetime of the Particle
	void Reduce_Lifetime(float);

	//Get the initial lifetime of the Particle
	float Get_Initial_Lifetime() const;
	//Set the initial lifetime of the Particle
	void Set_Initial_Lifetime(float);

	//Get the transparency of the Particle
	float Get_Transparency() const;
	//Set the transparency of the Particle
	void Change_Transparency(float);

	//Get the tint of the Particle
	float Get_Tint() const;
	//Set the tint of the Particle
	void Change_Tint(float);

	//Get the speed of the Particle
	float Get_Speed() const;
	//Set the speed of the Particle
	void Set_Speed(float);

	//Get the x-directional speed of the Particle
	float Get_x_Speed() const;
	//Set the x-directional speed of the Particle
	void Set_x_Speed(float speed);

	//Get the y-directional speed of the Particle
	float Get_y_Speed() const;
	//Set the y-directional speed of the Particle
	void Set_y_Speed(float speed);

	void Update();
	void Draw();	
};


class ParticleEmitter : public GameObject
{
protected:
	std::array <Particle*, MAX_PARTICLE_COUNT> particle_list_; // List of Particles
	EMITTER_SOURCE_TYPE source_;                               // Type of pattern that particles spawn from
	AEVec2 velocity_;                                          // Velocity of the particles
	float angle_;                                              // Angle of the direction that the particles move in 
	float particle_lifetime_;                                  // Lifetime of the particles
	float timer_;                                              // Timers for particle spawns
	float range_;                                              // Radius of the area of the spawn patterns
	unsigned total_particles_;                                 // Total number of particles needed
	float emitter_lifetime_;                                   // Lifetime of the emitter
	int particle_wave_;                                        // Wave number of the particles
	bool active_;                                              // Whether the pariticle emitter is still emitting particles or not
public:
	ParticleEmitter::ParticleEmitter();
	ParticleEmitter(float x,                        // Position of the particle emitter
					float y,                        
					EMITTER_SOURCE_TYPE sourcetype, // Spawn pattern of the particle emitter
					UNIT_TYPES particletype,        // Type of particle the emitter spawns
					float range,                    // Radius of the area of the spawn patterns
					float lifetime                  // Lifetime of the emitter
	);

	// Revives a particle in a list
	void Revive_Particle(int index, float lifetime, float transp, float speed, AEVec2 velocity_, float x, float y, UNIT_TYPES unit_type);

	//Get the type of the Emitter
	EMITTER_SOURCE_TYPE Get_Emitter_Type() const;
	//Set the type of the Emitter
	void Change_Emitter_Type(EMITTER_SOURCE_TYPE);

	//Get the velocity of the Emitter
	AEVec2 Get_Velocity() const;
	//Set the velocity of the Emitter
	void Set_Velocity(AEVec2);

	//Get the direction of the Emitter
	float Get_Angle() const;
	//Set the direction of the Emitter
	void Set_Angle(float);

	//Get the particle lifetime of the Emitter
	float Get_Particle_Lifetime() const;
	//Set the particle lifetime of the Emitter
	void Set_Particle_Lifetime(float);

	//Get the timer of the Emitter
	float Get_Timer() const;
	//Set the timer of the Emitter
	void Set_Timer(float);

	//Get the range of the Emitter
	float Get_Range() const;
	//Set the range of the Emitter
	void Set_Range(float);

	//Get the total number of particles the Emitter is using
	int Get_Total_Particles() const;
	//Set the total number of particles the Emitter is using
	void Set_Total_Particles(int);

	// Gets the lifetime of the emitter
	float Get_Emitter_Lifetime();
	// Sets the lifetime of the emitter
	void Set_Emitter_Lifetime(float lifetime);

	// Gets the status of whether the emitter is active or not
	bool Get_Active();
	// Activates the emitter
	void Set_Active(float x, float y, UNIT_TYPES particletype, float range, float lifetime);
	// Deactivates the emitter
	void Set_Inactive();
	// Checks whether any particle in the emitter's list is still active
	bool Check_Particle_List();
	// Resets the position of the particles
	void Reset_Particle_Position();

	void Update();
	void Draw();
	void Free();
};

#endif PARTICLE_H