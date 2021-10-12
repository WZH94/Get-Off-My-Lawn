/******************************************************************************/
/*!
\game Get Off My Lawn!
\file   List.cpp
\author Wong Zhihao						(10%) |Zachary Sng Zhi Ren(90%)
\par    email: zhihao.wong\@digipen.edu		| z.sng\@digipen.edu
\par    DigiPen login: zhihao.wong			| z.sng
\par    Course: GAM150
\date	13/04/18
\brief
This file handles the particle system, which handles updating every particle
and emitter in the game.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Particle.h"         // Function declarations
#include "SystemComponents.h" // System components
#include "LogicComponents.h"  // Logic components
#include "Movement.h"         // Movement functions for particles
#include "ObjectSpawner.h"    // Spawning and activation functions for particles
#include "ObjectList.h"       // Object enums
#include "RenderManager.h"    // Render functions for particles

/******************************************************************************/
/*!
Default constructor of particles
*/
/******************************************************************************/
Particle::Particle()
	:
	GameObject(
		NONE,			// Which side this unit is on
		0, 0,			// Spawn position
		0,				// Scale/Radius of object
		0,
		PARTICLE,		// What type of object it is
		PARTICLE_BLANK	// What specific type of unit it is
	),
	lifetime_{0},
	initial_lifetime_{0},
	transparency_{0},
	tint_{1.0f},
	speed_{0},
	velocity_{0}
{
	alive_ = false;
}

/******************************************************************************/
/*!
Contructor for particles
*/
/******************************************************************************/
Particle::Particle(float lifetime, float transparency, float speed, AEVec2 velocity, float x, float y, float scale_x, float scale_y, UNIT_TYPES unit_type)
	:
	GameObject(
		NONE,			// Which side this unit is on
		x, y,			// Spawn position
		scale_x,			// Scale/Radius of object
		scale_y,
		PARTICLE,		// What type of object it is
		unit_type		// What specific type of unit it is
	),
	lifetime_ {lifetime},
	initial_lifetime_ {lifetime},
	transparency_ {transparency},
	tint_{1.0f},
	speed_ {speed},
	velocity_{velocity.x, velocity.y}
{
	alive_ = false;
}

/******************************************************************************/
/*!
Sets the stats of the particles
*/
/******************************************************************************/
void Particle::Set_Particle_Stats(float lifetime, float transp, float speed, AEVec2 velocity, float x, float y, UNIT_TYPES unit_type)
{
	lifetime_ = lifetime;
	initial_lifetime_ = lifetime;
	transparency_ = transp;
	speed_ = speed;
	velocity_ = velocity;
	pos_.x = x;
	pos_.y = y;
	alive_ = true;
	tint_ = 1.0f;
	renderMesh_ = system_components.graphics_manager_->Get_Render_Mesh(unit_type);
	// Sets the size of the particle based on the particle type
	switch (unit_type)
	{
	case PARTICLE_POOF:
		scale_x = scale_y = 20.0f;
		break;
	case PARTICLE_HIT_EFFECT: {
		scale_x = scale_y = 10.0f;
		break; }
	case PARTICLE_FIRE: {
		scale_x = scale_y = 20.0f;
		break; }
	case PARTICLE_SMOKE:
	case PARTICLE_EXPLOSION: {
		scale_x = scale_y = 50.0f;
		break; }
	case PARTICLE_POISON: {
		scale_x = scale_y = 20.0f;
		break; }
	case PARTICLE_SLEEPY_BUBBLE: {
		scale_x = scale_y = 20.0f;
		break; }
	case PARTICLE_GLOW:
	case PARTICLE_ATTACK_AURA: {
		scale_x = scale_y = 35.0f;
		break; }
	case PARTICLE_MONEY_DROPS: {
		scale_x = scale_y = 5.0f;
		break; }
	case PARTICLE_SWEAT: {
		scale_x = scale_y = 5.0f;
		break; }
	case PARTICLE_RUBBLE: {
		scale_x = scale_y = 15.0f;
		break; }
	}

}

/******************************************************************************/
/*!
Activates the particles
*/
/******************************************************************************/
void Particle::Set_Active(float lifetime, float transparency, float speed, AEVec2 velocity, float x, float y, UNIT_TYPES unit_type)
{
	alive_ = true;
	pos_.x = x;
	pos_.y = y;
	unit_type_ = unit_type;
	lifetime_ = lifetime;
	initial_lifetime_ = lifetime;
	transparency_ = transparency;
	speed_ = speed;
	velocity_ = velocity;
	direction_ = 0;
	renderMesh_ = system_components.graphics_manager_->Get_Render_Mesh(unit_type);
	tint_ = 1.0f;
	// Sets the size of the particles based on the particle type
	switch (unit_type)
	{
	case PARTICLE_POOF:
		scale_x = scale_y = 20.0f;
		break;
	case PARTICLE_HIT_EFFECT: {
		scale_x = scale_y = 10.0f;
		break; }
	case PARTICLE_FIRE: {
		scale_x = scale_y = 20.0f;
		break; }
	case PARTICLE_SMOKE:
	case PARTICLE_EXPLOSION: {
		scale_x = scale_y = 50.0f;
		break; }
	case PARTICLE_POISON: {
		scale_x = scale_y = 20.0f;
		break; }
	case PARTICLE_SLEEPY_BUBBLE: {
		scale_x = scale_y = 20.0f;
		break; }
	case PARTICLE_GLOW:
	case PARTICLE_ATTACK_AURA: {
		scale_x = scale_y = 35.0f;
		break; }
	case PARTICLE_MONEY_DROPS: {
		scale_x = scale_y = 5.0f;
		break; }
	case PARTICLE_SWEAT: {
		scale_x = scale_y = 5.0f;
		break; }
	case PARTICLE_RUBBLE: {
		scale_x = scale_y = 15.0f;
		break; }
	}
	radius_ = scale_x / 2;
}

/******************************************************************************/
/*!
Deactivates the particles
*/
/******************************************************************************/
void Particle::Set_Inactive()
{
	alive_ = false;
	pos_.x = 0;
	pos_.y = 0;
	unit_type_ = PARTICLE_BLANK;
	lifetime_ = 0;
	initial_lifetime_ = 0;
	transparency_ = 0;
	speed_ = 0;
	velocity_.x = 0;
	velocity_.y = 0;
	scale_x = 0;
	scale_y = 0;
	radius_ = 0;
	direction_ = 0;
}


/******************************************************************************/
/*!
Get the lifetime of the Particle
*/
/******************************************************************************/
float Particle::Get_Lifetime() const
{
	return lifetime_;
}


/******************************************************************************/
/*!
Reduces the lifetime of the Particle
*/
/******************************************************************************/
void Particle::Reduce_Lifetime(float time_difference)
{
	lifetime_ -= time_difference;
}


/******************************************************************************/
/*!
Get the initial lifetime of the Particle
*/
/******************************************************************************/
float Particle::Get_Initial_Lifetime() const
{
	return initial_lifetime_;
}

/******************************************************************************/
/*!
Set the initial lifetime of the Particle
*/
/******************************************************************************/
void Particle::Set_Initial_Lifetime(float time)
{
	initial_lifetime_ = time;
}

/******************************************************************************/
/*!
Get the transparency of the Particle
*/
/******************************************************************************/
float Particle::Get_Transparency() const
{
	return transparency_;
}

/******************************************************************************/
/*!
Set the transparency of the Particle
*/
/******************************************************************************/
void Particle::Change_Transparency(float fader)
{
	transparency_ += fader;
}

/******************************************************************************/
/*!
Get the tint of the Particle
*/
/******************************************************************************/
float Particle::Get_Tint() const
{
	return tint_;
}

/******************************************************************************/
/*!
Set the tint of the Particle
*/
/******************************************************************************/
void Particle::Change_Tint(float shader)
{
	tint_ += shader;
}

/******************************************************************************/
/*!
Get the speed of the Particle
*/
/******************************************************************************/
float Particle::Get_Speed() const
{
	return speed_;
}

/******************************************************************************/
/*!
Set the speed of the Particle
*/
/******************************************************************************/
void Particle::Set_Speed(float input_speed)
{
	speed_ = input_speed;
}

/******************************************************************************/
/*!
Get the x-directional speed of the Particle
*/
/******************************************************************************/
float Particle::Get_x_Speed() const
{
	return velocity_.x;
}

/******************************************************************************/
/*!
//Set the x-directional speed of the Particle
*/
/******************************************************************************/
void Particle::Set_x_Speed(float x_speed)
{
	velocity_.x = x_speed;
}

/******************************************************************************/
/*!
Get the y-directional speed of the projectile
*/
/******************************************************************************/
float Particle::Get_y_Speed() const
{
	return velocity_.y;
}

/******************************************************************************/
/*!
Set the y-directional speed of the Particle
*/
/******************************************************************************/
void Particle::Set_y_Speed(float y_speed)
{
	velocity_.y = y_speed;
}

/******************************************************************************/
/*!
"Update" function of particles
*/
/******************************************************************************/
void Particle::Update()
{
	// Checks if particle is alive
	if (!alive_)
		return;
	// Reduces the lifetime of the particle
	lifetime_ -= (system_components.framerate_manager->Get_Game_Time());
	// Deactivates particles of lifetime is over
	if (lifetime_ < 0.0f)
	{
		alive_ = false;
		Set_Inactive();
		return;
	}
	// Calls the correct movement function for the type of particle
	switch (unit_type_)
	{
	case PARTICLE_POISON:
	case PARTICLE_SLEEPY_BUBBLE:
	case PARTICLE_HIT_EFFECT:
	case PARTICLE_FIRE:
	case PARTICLE_EXPLOSION:
	case PARTICLE_GLOW:
	case PARTICLE_ATTACK_AURA:
	case PARTICLE_SMOKE:
	case PARTICLE_POOF:
		Move_Particle(*this);
		break;
	case PARTICLE_SWEAT:
	case PARTICLE_MONEY_DROPS:
		Move_Particle_With_Gravity(*this);
		break;
	default:
		Move_Particle(*this);
		break;
	}
	// Makes specific particle types grow
	if (unit_type_== PARTICLE_EXPLOSION || unit_type_ == PARTICLE_ATTACK_AURA)
	{
		Set_Scale_X(Get_Scale_X() + 0.5f);
		Set_Scale_Y(Get_Scale_Y() + 0.5f);
	}
}

/******************************************************************************/
/*!
"Draw" function of particles
*/
/******************************************************************************/
void Particle::Draw()
{
	// Checks if particle is alive
	if (!alive_)
		return;
	// Calls the correct render function based on the particle type
	switch (unit_type_)
	{
	case PARTICLE_FIRE:
	case PARTICLE_EXPLOSION:
	case PARTICLE_GLOW:
	case PARTICLE_ATTACK_AURA:
	case PARTICLE_HIT_EFFECT:
	case PARTICLE_SMOKE:
	case PARTICLE_POOF:
		Render_Particle(*this);
		break;
	case PARTICLE_SWEAT:
	case PARTICLE_MONEY_DROPS:
	case PARTICLE_POISON:
	case PARTICLE_SLEEPY_BUBBLE:
	case PARTICLE_RUBBLE:
		Render_Particle_Without_Fade(*this);
		break;
	default:
		Render_Particle(*this);
		break;
	}
}

/******************************************************************************/
/*!
Default constructor of the particle emitter
*/
/******************************************************************************/
ParticleEmitter::ParticleEmitter()
	:
	GameObject(
		NONE,
		0, 0,
		0,
		0,
		PARTICLE_EMITTER,
		PARTICLE_BLANK
	),
	active_{ false },
	source_{ EMIT_POINT },
	velocity_{ 0 },
	particle_lifetime_{ 0 },
	timer_{ 0 },
	range_{ 0 },
	total_particles_{ 0 },
	emitter_lifetime_{ 0 },
	particle_wave_{ 0 }
{
	alive_ = false;
	// Creates a blank particle
	for (unsigned i = 0; i < MAX_PARTICLE_COUNT; ++i)
		particle_list_.at(i) = new Particle;
}

/******************************************************************************/
/*!
Constructor for the particle emitter
*/
/******************************************************************************/
ParticleEmitter::ParticleEmitter(float x, float y, EMITTER_SOURCE_TYPE sourcetype, UNIT_TYPES particletype, float range, float lifetime)
	:
	GameObject(
		NONE,			// Which side this unit is on
		x, y,			// Spawn position
		0.0f,			// Scale/Radius of object
		0.0f,
		PARTICLE_EMITTER,// What type of object it is
		particletype	// What specific type of unit it is
	),
	active_{ false },
	source_{ sourcetype },
	velocity_{ 0 },
	angle_{ 0.0f },
	particle_lifetime_{ 0.0f },
	timer_{ 0.0f },
	range_{ range },
	total_particles_{ 0 },
	emitter_lifetime_{ lifetime },
	particle_wave_{ 0 }
{
	alive_ = false;
	// Sets the correct total number of particles based on the particle type
	switch (particletype)
	{
	case PARTICLE_FIRE:
		total_particles_ = 16;
		break;
	case PARTICLE_EXPLOSION:
	case PARTICLE_SMOKE:
		total_particles_ = 200;
		break;
	case PARTICLE_POISON:
	case PARTICLE_SLEEPY_BUBBLE:
		total_particles_ = 1;
		break;
	case PARTICLE_GLOW:
	case PARTICLE_ATTACK_AURA:
		total_particles_ = 1;
		break;
	case PARTICLE_HIT_EFFECT:
	case PARTICLE_POOF:
		total_particles_ = 50;
		break;
	case PARTICLE_SWEAT:
		total_particles_ = 3;
		break;
	case PARTICLE_MONEY_DROPS:
		total_particles_ = 6;
		break;
	case PARTICLE_RUBBLE:
		total_particles_ = 15;
		break;
	default:
		break;
	}
}

/******************************************************************************/
/*!
Revives a particle in a list
*/
/******************************************************************************/
void ParticleEmitter::Revive_Particle(int index, float lifetime, float transp, float speed, AEVec2 velocity, float x, float y, UNIT_TYPES unit_type)
{
	particle_list_.at(index)->Set_Particle_Stats(lifetime, transp, speed, velocity, x, y, unit_type);
}

/******************************************************************************/
/*!
Get the type of the Emitter
*/
/******************************************************************************/
EMITTER_SOURCE_TYPE ParticleEmitter::Get_Emitter_Type() const
{
	return source_;
}

/******************************************************************************/
/*!
Sets the type of the Emitter
*/
/******************************************************************************/
void ParticleEmitter::Change_Emitter_Type(EMITTER_SOURCE_TYPE type)
{
	source_ = type;
}

/******************************************************************************/
/*!
Get the velocity of the Emitter
*/
/******************************************************************************/
AEVec2 ParticleEmitter::Get_Velocity() const
{
	return velocity_;
}

/******************************************************************************/
/*!
Sets the velocity of the Emitter
*/
/******************************************************************************/
void ParticleEmitter::Set_Velocity(AEVec2 velocity)
{
	velocity_ = velocity;
}

/******************************************************************************/
/*!
Get the direction of the Emitter
*/
/******************************************************************************/
float ParticleEmitter::Get_Angle() const
{
	return angle_;
}

/******************************************************************************/
/*!
Sets the direction of the Emitter
*/
/******************************************************************************/
void ParticleEmitter::Set_Angle(float direction)
{
	angle_ = direction;
}

/******************************************************************************/
/*!
Get the particle lifetime of the Emitter
*/
/******************************************************************************/
float ParticleEmitter::Get_Particle_Lifetime() const
{
	return particle_lifetime_;
}

/******************************************************************************/
/*!
Sets the particle lifetime of the Emitter
*/
/******************************************************************************/
void ParticleEmitter::Set_Particle_Lifetime(float time)
{
	particle_lifetime_ = time;
}

/******************************************************************************/
/*!
Get the timer of the Emitter
*/
/******************************************************************************/
float ParticleEmitter::Get_Timer() const
{
	return timer_;
}

/******************************************************************************/
/*!
Sets the timer of the Emitter
*/
/******************************************************************************/
void ParticleEmitter::Set_Timer(float time)
{
	timer_ = time;
}

/******************************************************************************/
/*!
Get the range of the Emitter
*/
/******************************************************************************/
float ParticleEmitter::Get_Range() const
{
	return range_;
}

/******************************************************************************/
/*!
Sets the range of the Emitter
*/
/******************************************************************************/
void ParticleEmitter::Set_Range(float range)
{
	range_ = range;
}

/******************************************************************************/
/*!
Get the total number of particles the Emitter is using
*/
/******************************************************************************/
int ParticleEmitter::Get_Total_Particles() const
{
	return total_particles_;
}

/******************************************************************************/
/*!
Sets the total number of particles the Emitter is using
*/
/******************************************************************************/
void ParticleEmitter::Set_Total_Particles(int number)
{
	total_particles_ = number;
}

/******************************************************************************/
/*!
Gets the lifetime of the emitter
*/
/******************************************************************************/
float ParticleEmitter::Get_Emitter_Lifetime()
{
	return emitter_lifetime_;
}

/******************************************************************************/
/*!
Sets the lifetime of the emitter
*/
/******************************************************************************/
void ParticleEmitter::Set_Emitter_Lifetime(float lifetime)
{
	emitter_lifetime_ = lifetime;
}

/******************************************************************************/
/*!
Gets the status of whether the emitter is active or not
*/
/******************************************************************************/
bool ParticleEmitter::Get_Active()
{
	return active_;
}

/******************************************************************************/
/*!
Checks whether any particle in the emitter's list is still active
*/
/******************************************************************************/
bool ParticleEmitter::Check_Particle_List()
{
	for (unsigned i = 0; i < total_particles_; ++i)
	{
		//Checks if particle is alive
		if (particle_list_[i]->Get_Alive() == true)
			return true;
	}
	return false;
}

/******************************************************************************/
/*!
Resets the position of the particles
*/
/******************************************************************************/
void ParticleEmitter::Reset_Particle_Position()
{
	for (unsigned i = 0; i < total_particles_; ++i)
	{
		particle_list_[i]->Set_x(pos_.x);
		particle_list_[i]->Set_y(pos_.y);
	}
	return;
}

/******************************************************************************/
/*!
Activates the emitter
*/
/******************************************************************************/
void ParticleEmitter::Set_Active(float x, float y, UNIT_TYPES particletype, float range, float lifetime)
{
	pos_.x = x;
	pos_.y = y;
	unit_type_ = particletype;
	active_ = true;
	range_ = range;
	emitter_lifetime_ = lifetime;
	alive_ = true;
	velocity_.x = 0;
	velocity_.y = 0;
	angle_ = 0;
	timer_ = 0;
	particle_wave_ = 0;
	// Sets the total number of particles and source type baed on particle type
	switch (unit_type_)
	{
	case PARTICLE_FIRE:
		total_particles_ = 4;
		source_ = EMIT_LINE;
		break;
	case PARTICLE_EXPLOSION:
	case PARTICLE_SMOKE:
		total_particles_ = 200;
		source_ = EMIT_CIRCLE;
		break;
	case PARTICLE_POISON:
	case PARTICLE_SLEEPY_BUBBLE:
		total_particles_ = 1;
		source_ = EMIT_POINT;
		break;
	case PARTICLE_GLOW:
	case PARTICLE_ATTACK_AURA:
		total_particles_ = 1;
		source_ = EMIT_POINT;
		break;
	case PARTICLE_HIT_EFFECT:
	case PARTICLE_POOF:
		total_particles_ = 50;
		source_ = EMIT_CIRCLE;
		break;
	case PARTICLE_SWEAT:
		total_particles_ = 3;
		source_ = EMIT_POINT;
		break;
	case PARTICLE_MONEY_DROPS:
		total_particles_ = 6;
		source_ = EMIT_POINT;
		break;
	case PARTICLE_RUBBLE:
		total_particles_ = 15;
		source_ = EMIT_LINE;
		break;
	default:
		break;
	}
	// Zero velocity
	AEVec2 null_vel = { 0, 0 };
	// Counter to prevent the loop from going past the maximum particle count
	unsigned int j = 0;
	// Activeates all the particles needed
	for (unsigned i = 0; i < total_particles_; ++i)
	{
		for (; j < MAX_PARTICLE_COUNT; ++j)
		{
			if (!particle_list_.at(j)->Get_Alive())
			{
				particle_list_.at(j)->Set_Active(0.0f, 1.0f, 0.0f, null_vel, pos_.x, pos_.y, particletype);
				break;
			}
		}			
	}
}

/******************************************************************************/
/*!
Deactivates the emitter
*/
/******************************************************************************/
void ParticleEmitter::Set_Inactive()
{
	pos_.x = 0;
	pos_.y = 0;
	unit_type_ = PARTICLE_BLANK;
	active_ = false;
	range_ = 0;
	emitter_lifetime_ = 0;
	alive_ = false;
	total_particles_ = 0;
	velocity_.x = 0;
	velocity_.y = 0;
	angle_ = 0;
	timer_ = 0;
	particle_wave_ = 0;
	// Deactivates the particles
	for (unsigned i = 0; i < MAX_PARTICLE_COUNT; ++i)
	{
		if (particle_list_.at(i)->Get_Alive())
			particle_list_.at(i)->Set_Inactive();
	}
}

/******************************************************************************/
/*!
Revives a particle in a list
*/
/******************************************************************************/
void ParticleEmitter::Update()
{
	// Reduces the emitter lifetime
	emitter_lifetime_ -= system_components.framerate_manager->Get_Game_Time();
	// Checks if the emitter is active
	if (active_)
	{
		// Resets the particle's position
		Reset_Particle_Position();
		float transp = 1.0f;               // Particle transparency
		AEVec2 start = { pos_.x, pos_.y }; // Starting position
		float speed = 0.0f;                // Speed of particle
		// Sets the variables of all the needed particles based on the particle type
		for (unsigned i = 0; i < total_particles_; ++i)
		{
			// Sets starting position
			switch (source_)
			{
			case EMIT_CIRCLE:
				AEVec2 direction;
				angle_ = AERandFloat() * 2.0f * PI;
				AEVec2FromAngle(&direction, angle_);
				AEVec2Scale(&direction, &direction, radius_);
				AEVec2Add(&start, &start, &direction);
				break;
			case EMIT_LINE:
				start.x = AERandFloat() * range_ * 2.0f + (pos_.x - range_);
				break;
			case EMIT_POINT:
			default:
				break;
			}
			// Sets Velocity, transparency and lifetime
			switch (unit_type_)
			{
			case PARTICLE_FIRE:
				angle_ = PI / 3 + (PI / 3 * AERandFloat());
				AEVec2FromAngle(&velocity_, angle_);
				speed = 40.0f + (20.0f * AERandFloat());
				AEVec2Scale(&velocity_, &velocity_, speed);
				particle_lifetime_ = 4.0f + AERandFloat();
				transp = 0.5f;
				break;
			case PARTICLE_EXPLOSION:
				angle_ = AERandFloat() * 2.0f * PI;
				AEVec2FromAngle(&velocity_, angle_);
				speed = 200.0f + (300.0f * AERandFloat());
				AEVec2Scale(&velocity_, &velocity_, speed);
				particle_lifetime_ = 1.0f + 4.0f * AERandFloat();
				break;
			case PARTICLE_SMOKE:
				angle_ = AERandFloat() * 2.0f * PI;
				AEVec2FromAngle(&velocity_, angle_);
				speed = 60.0f + (40.0f * AERandFloat());
				AEVec2Scale(&velocity_, &velocity_, speed);
				particle_lifetime_ = 1.0f + 4.0f * AERandFloat();
				break;
			case PARTICLE_GLOW:
				angle_ += 2.0f * PI / total_particles_;
				AEVec2FromAngle(&velocity_, angle_);
				speed = 1.0f;
				AEVec2Scale(&velocity_, &velocity_, speed);
				particle_lifetime_ = 1.0f;
				transp = 0.5f;
				break;
			case PARTICLE_ATTACK_AURA:
				angle_ = 0.0f;
				AEVec2FromAngle(&velocity_, angle_);
				speed = 0.0f;
				AEVec2Scale(&velocity_, &velocity_, speed);
				particle_lifetime_ = 0.5f;
				transp = 1.0f;
				break;
			case PARTICLE_POOF:
			case PARTICLE_HIT_EFFECT:
				angle_ = AERandFloat() * 2.0f * PI;
				AEVec2FromAngle(&velocity_, angle_);
				speed = 100.0f + (40.0f * AERandFloat());
				AEVec2Scale(&velocity_, &velocity_, speed);
				particle_lifetime_ = 0.5f;
				transp = 0.5f;
				break;
			case PARTICLE_SWEAT:
				angle_ = AERandFloat() * PI;
				AEVec2FromAngle(&velocity_, angle_);
				speed = 50.0f + (50.0f * AERandFloat());
				AEVec2Scale(&velocity_, &velocity_, speed);
				particle_lifetime_ = 0.3f;
				transp = 1.0f;
				break;
			case PARTICLE_MONEY_DROPS:
				angle_ = AERandFloat() * PI;
				AEVec2FromAngle(&velocity_, angle_);
				speed = 50.0f + (100.0f * AERandFloat());
				AEVec2Scale(&velocity_, &velocity_, speed);
				particle_lifetime_ = 0.5f;
				transp = 1.0f;
				break;
			case PARTICLE_POISON:
			case PARTICLE_SLEEPY_BUBBLE:
				AEVec2FromAngle(&velocity_, PI / 2);
				AEVec2Scale(&velocity_, &velocity_, 20.0f);
				particle_lifetime_ = 1.0f;
				transp = 0.5f;
				break;
			case PARTICLE_RUBBLE:
				AEVec2FromAngle(&velocity_, 3 * PI / 2);
				speed = 250.0f + (250.0f * AERandFloat());
				AEVec2Scale(&velocity_, &velocity_, speed);
				particle_lifetime_ = 0.5f;
				transp = 1.0f;
				break;
			}
			// revives the particle
			Revive_Particle(i, particle_lifetime_, transp, speed, velocity_, start.x, start.y, unit_type_);
		}
	}
	else
	{
		// Updates the particles
		for (unsigned i = 0; i < total_particles_; ++i)
		{
			if (particle_list_.at(i)->Get_Alive())
			{
				particle_list_.at(i)->Update();
				particle_list_.at(i)->Set_Matrix();
			}
		}
	}
	// Chceks if there are any active particles in the list
	if (!Check_Particle_List())
	{
		active_ = false;
		alive_ = false;
	}
	// Resets the wave and deactivates the emitter
	particle_wave_ = 0;
	active_ = false;
	// Resets the variables of the emitter is it is not alive or active
	if (!active_ && !alive_)
		Set_Inactive();
}

/******************************************************************************/
/*!
Revives a particle in a list
*/
/******************************************************************************/
void ParticleEmitter::Draw()
{
	for (unsigned i = 0; i < total_particles_; ++i)
	{
		if (particle_list_[i]->Get_Alive())
			particle_list_[i]->Draw();
	}
}

/******************************************************************************/
/*!
Revives a particle in a list
*/
/******************************************************************************/
void ParticleEmitter::Free()
{
	for (unsigned i = 0; i < MAX_PARTICLE_COUNT; ++i)
	{
		delete particle_list_.at(i);
		particle_list_.at(i) = nullptr;
	}
}
