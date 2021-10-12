/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   Camera.cpp	
\author Wong Zhihao				(100%)
\par    email: zhihao.wong\@digipen.edu
\par    DigiPen login: zhihao.wong
\par    Course: GAM150
\date	13/04/18
\brief
	This file contains the functions that control the in game camera. The camera
	is bounded by the level width and height, and is able to zoom in and shake.

	Copyright (C) 2018 DigiPen Institute of Technology.
	Reproduction or disclosure of this file or its contents without the
	prior written consent of DigiPen Institute of Technology is prohibited.
	All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Camera.h"				// Function and class declarations
#include "LevelData.h"			// Level dimensions
#include "main.h"				// Screen dimensions
#include "SystemComponents.h"	// Cursor Position
#include "LogicComponents.h"	// Logic Components

/******************************************************************************/
/*!
	Constructor for camera
*/
/******************************************************************************/
Camera::Camera()
	:
	// Sets the threshold before the mouse is at the edge of the screen where the screen starts moving
	CAMERA_X_MOVE_THRESHOLD_{ int(HALF_SCREEN_WIDTH * 0.85f) },
	CAMERA_Y_MOVE_THRESHOLD_{ int(HALF_SCREEN_HEIGHT * 0.85f) },
	// Sets the max speed of the camera
	CAMERA_X_SPEED{ 11.0f },
	CAMERA_Y_SPEED{ 7.0f },
	// Adjustment for the UI at the bottom of the screen, so that game is still centered
	CAMERA_Y_UI_ADJUSTMENT{ 150.0f * 0.5f },
	// Smooth Trail y variable
	CAMERA_DEADZONE{ 10.0f },

	// Default position of the camera
	camera_position_{ 0, 0 },
	camera_position_target_{0, 0 },
	zoom_scale_{1.0f}, 
	zoom_scale_target_{1.0f},

	// Default boundaries of the camera
	camera_x_boundary_{0},
	camera_negative_x_boundary_{0},
	camera_y_boundary_{ 0 },
	camera_negative_y_boundary_{0},

	camera_y_actual_position_{0},

	// Shake variables
	camera_is_shaking_{false},
	camera_shake_offset_{0, 0},
	camera_is_zooming_{ 0 }
{
}

/******************************************************************************/
/*!
	Initialises the camera at the start of every level
*/
/******************************************************************************/
void Camera::Initialise_Camera()
{
	Update_Camera_Boundaries();
	Update_Camera();

	// Snaps the camera position to its target so you don't see it moving when you start the level
	camera_position_ = camera_position_target_;
	AEGfxSetCamPosition(camera_position_target_.x, camera_position_target_.y);
}

/******************************************************************************/
/*!
Updates camera properties
*/
/******************************************************************************/
void Camera::Update_Camera()
{
	// Zoom the camera if its target is diffirent 
	if (zoom_scale_target_ != zoom_scale_)
		Zoom_Camera();

	// Shake the camera if it is shaking.
	if (camera_is_shaking_)
		Shake_Camera();

	// Sets the camera position
	Set_Camera_Position();

	// Move the camea
	Move_Camera();
}

/******************************************************************************/
/*!
Gets the camera position
*/
/******************************************************************************/
AEVec2 Camera::Get_Camera_Position() const
{
	return camera_position_;
}

/******************************************************************************/
/*!
Gets the camera UI position, which is the position UI objects take from which
is not affected by the camera shaking.
*/
/******************************************************************************/
AEVec2 Camera::Get_Camera_UI_Position() const
{
	AEVec2 camera_ui_position{ camera_position_.x + camera_shake_offset_.x, camera_position_.y + camera_shake_offset_.y };
	return camera_ui_position;
}

/******************************************************************************/
/*!
Sets the camera position target based on cursor and camera position
*/
/******************************************************************************/
void Camera::Set_Camera_Position()
{
	// Find cursor position
	float cursor_x = system_components.cursor_position_->Get_Cursor_Position().x;
	float cursor_y = system_components.cursor_position_->Get_Cursor_Position().y;

	// Sets camera x and y axis based on cursor position
	Set_Camera_x(cursor_x);
	Set_Camera_y(cursor_y);
}

/******************************************************************************/
/*!
Sets target camera x axis based on cursor position on x axis
*/
/******************************************************************************/
void Camera::Set_Camera_x(float cursor_x)
{
	// Check if camera is at the left x threshold and it can still move left
	if (cursor_x <= -CAMERA_X_MOVE_THRESHOLD_ && camera_position_target_.x > camera_negative_x_boundary_)
	{
		// Amount to move 
		float target = 0;

		// Max speed if cursor is past the screen widthh
		if (cursor_x <= -HALF_SCREEN_WIDTH)
			target = -CAMERA_X_SPEED;

		// Sets it faster the closer it is to the edge of the screen
		else
		{
			target = cursor_x;
			target += CAMERA_X_MOVE_THRESHOLD_;
			target *= 0.07f;
		}

		// Multiply by zoom amount
		target *= zoom_scale_;

		// Adds this to the target
		camera_position_target_.x += target;
	}

	// Check if camera is at the right x threshold and it can still move right
	else if (cursor_x >= CAMERA_X_MOVE_THRESHOLD_ && camera_position_target_.x < camera_x_boundary_)
	{
		// Amount to move 
		float target = 0;

		// Max speed if cursor is past the screen widthh
		if (cursor_x >= HALF_SCREEN_WIDTH)
			target = CAMERA_X_SPEED;

		// Sets it faster the closer it is to the edge of the screen
		else
		{
			target = cursor_x;
			target -= CAMERA_X_MOVE_THRESHOLD_;
			target *= 0.07f;
		}

		// Multiply by zoom amount
		target *= zoom_scale_;

		// Adds this to the target
		camera_position_target_.x += target;
	}

	if (zoom_cursor_target_.x)
	{
		camera_position_target_.x += zoom_cursor_target_.x;
		zoom_cursor_target_.x = 0;
	}

	// If it moved past camera boundary, moves it back in bounds
	if (camera_x_larger_than_play_area == false)
	{
		if (camera_position_target_.x < camera_negative_x_boundary_)
			camera_position_target_.x = camera_negative_x_boundary_;

		else if (camera_position_target_.x > camera_x_boundary_)
			camera_position_target_.x = camera_x_boundary_;
	}
		
	else if (camera_x_larger_than_play_area == true)
	{
		float midpoint = (camera_x_boundary_ + camera_negative_x_boundary_) * 0.5f;

		camera_position_target_.x = midpoint;
	}

}

/******************************************************************************/
/*!
Sets target camera y axis based on cursor position on y axis
*/
/******************************************************************************/
void Camera::Set_Camera_y(float cursor_y)
{
	// Amount to move 
	float target = 0;

	// Check if cmaera is at the bottom y threshold and it can still move downwards
	if (cursor_y <= -CAMERA_Y_MOVE_THRESHOLD_ && camera_position_target_.y > camera_negative_y_boundary_)
	{
		// Max speed if cursor is past the screen height
		if (cursor_y <= -HALF_SCREEN_HEIGHT)
			target = -CAMERA_Y_SPEED;

		// Sets it faster the closer it is to the edge of the screen
		else
		{
			target = cursor_y;
			target += CAMERA_Y_MOVE_THRESHOLD_;
			target *= 0.1f;
		}

		// Multiply by zoom amount
		target *= zoom_scale_;

		camera_position_target_.y += target;
	}

	// Check if cmaera is at the top y threshold and it can still move upwards
	else if (cursor_y >= CAMERA_Y_MOVE_THRESHOLD_ && camera_position_target_.y < camera_y_boundary_)
	{
		// Max speed if cursor is past the screen height
		if (cursor_y >= HALF_SCREEN_HEIGHT)
			target = CAMERA_Y_SPEED;

		// Sets it faster the closer it is to the edge of the screen
		else
		{
			target = cursor_y;
			target -= CAMERA_Y_MOVE_THRESHOLD_;
			target *= 0.1f;
		}

		// Multiply by zoom amount
		target *= zoom_scale_;

		camera_position_target_.y += target;
	}

	if (zoom_cursor_target_.y)
	{
		camera_position_target_.y += zoom_cursor_target_.y;
		zoom_cursor_target_.y = 0;
	}

	if (camera_x_larger_than_play_area == false)
	{
		// If it moved past camera boundary, moves it back in bounds
		if (camera_position_target_.y < camera_negative_y_boundary_)
			camera_position_target_.y = camera_negative_y_boundary_;

		else if (camera_position_target_.y > camera_y_boundary_)
			camera_position_target_.y = camera_y_boundary_;
	}

	else if (camera_y_larger_than_play_area == true)
	{
		float midpoint = (camera_y_boundary_ + camera_negative_y_boundary_) * 0.5f;

		camera_position_target_.y = midpoint;
	}
}

/******************************************************************************/
/*!
Unused function. Was created when the height of the level was not going to change.
Moves the camera up and down on an arctan curve when the cursor moves towards
the top and bottom of the screen
*/
/******************************************************************************/
float Camera::Smooth_Y_Trail(float cursor_y)
{
	// New y axis based on the cursor position
	float new_y = 0;

	cursor_y -= CAMERA_Y_UI_ADJUSTMENT;

	// If camera is not in the deadzone in the centre of the map
	if (cursor_y >= CAMERA_DEADZONE || cursor_y <= -CAMERA_DEADZONE)
	{
		// Check if cursor is at top half of the map
		if (cursor_y > 0)
		{
			// Check if cursor is within the game world. 
			if (cursor_y > HALF_SCREEN_HEIGHT - CAMERA_Y_UI_ADJUSTMENT)
				// Sets the new y at how many spaces above the camera deadzone
				new_y = float(HALF_SCREEN_HEIGHT - CAMERA_DEADZONE);

			// Cursor is outside the game world, set it to the max game size. May happen when game is not fullscreen
			else new_y = cursor_y - CAMERA_DEADZONE;
		}

		// Cursor is at bottom half of the map
		else 
		{
			// Check if cursor is within the game world. 
			if (cursor_y < -HALF_SCREEN_HEIGHT + CAMERA_Y_UI_ADJUSTMENT)
				// Sets the new y at how many spaces below the camera deadzone
				new_y = -float(HALF_SCREEN_HEIGHT - CAMERA_DEADZONE);

			// Cursor is outside the game world, set it to the max game size. May happen when game is not fullscreen
			else new_y = cursor_y + CAMERA_DEADZONE;
		}

		// Note: Cursor will never equal to 0 in this instance since that will be in the camera deadzone

		// Cursor is at top half of the map, it is positive
		if (cursor_y > 0)
			// Some wacky S shape graph, y rises slowly at the start, a lot in the middle, and lesser at the end
			new_y = (AEATan((0.029f * new_y) - 3.2f) + 1.267f) * 8.0f;

		// Cursor is at bottom half of the map, it is negative
		else
		{
			// Make y positive so that the Arctan function doesn't screw up.
			new_y *= -1.0f;
			// Some wacky S shape graph, y rises slowly at the start, a lot in the middle, and lesser at the end
			new_y = (AEATan((0.029f * new_y) - 3.2f) + 1.267f) * 8.0f;
			// Return y to its negative value
			new_y *= -1.0f;
		}
	}

	// Set the camera target y axis to be this new y
	return new_y;
}

/******************************************************************************/
/*!
Moves the camera to its new position set by the Set Functions before.
*/
/******************************************************************************/
void Camera::Move_Camera()
{
	if (camera_position_target_.x != camera_position_.x)
		Move_Camera_X();

	if (camera_position_target_.y != camera_position_.y)
		// Move the camera in its y axis
		Move_Camera_Y();

	// Sets the camera position after it is moved
	AEGfxSetCamPosition(camera_position_.x + camera_shake_offset_.x, camera_position_.y + camera_shake_offset_.y);
}

/******************************************************************************/
/*!
Moves the camera slowly towards its targeted x axis. 
This function handles the smooth movement of the camera
*/
/******************************************************************************/
void Camera::Move_Camera_X()
{
	// Sets the speed of the camera based on how big of a distance it has to cover.
	// E.g. larger distance makes it move faster, smaller distance makes it move slower.
	float speed = (camera_position_target_.x - camera_position_.x) * 0.3f;

	// Moves the camera's y by its speed.
	camera_position_.x += speed;

	// If it moved past its target, moves it back in bounds
	if ((speed > 0 && camera_position_.x > camera_position_target_.x) ||
		(speed < 0 && camera_position_.x < camera_position_target_.x))
		Trim_Excess(camera_position_.x, camera_position_target_.x);

	if (camera_position_target_.x - camera_position_.x > -0.001f && camera_position_target_.x - camera_position_.x < 0.001f)
		camera_position_.x = camera_position_target_.x;
}

/******************************************************************************/
/*!
Moves the camera slowly towards its targeted y axis.
This function handles the smooth movement of the camera
*/
/******************************************************************************/
void Camera::Move_Camera_Y()
{
	// Sets the speed of the camera based on how big of a distance it has to cover.
	// E.g. larger distance makes it move faster, smaller distance makes it move slower.
	float speed = (camera_position_target_.y - camera_position_.y) * 0.35f;

	// Moves the camera's y by its speed.
	camera_position_.y += speed;

	// If it moved past its target, moves it back in bounds
	if ((speed > 0 && camera_position_.y > camera_position_target_.y) ||
		(speed < 0 && camera_position_.y < camera_position_target_.y))
		Trim_Excess(camera_position_.y, camera_position_target_.y);

	if (camera_position_target_.y - camera_position_.y > -0.001f && camera_position_target_.y - camera_position_.y < 0.001f)
		camera_position_.y = camera_position_target_.y;
}

/******************************************************************************/
/*!
Zooms the camera towards its target
*/
/******************************************************************************/
void Camera::Zoom_Camera()
{
	// Sets the speed of the zoom based on how big of a distance it has to cover.
	// E.g. larger distance makes it move faster, smaller distance makes it move slower.
	float speed = (zoom_scale_target_ - zoom_scale_) * 0.3f;

	// Moves the camera's y by its speed.
	zoom_scale_ += speed;

	// If it moved past its target, moves it back in bounds
	if ((speed > 0 && zoom_scale_ > zoom_scale_target_) ||
		(speed < 0 && zoom_scale_ < zoom_scale_target_))
		Trim_Excess(zoom_scale_, zoom_scale_target_);

	if (zoom_scale_target_ - zoom_scale_ > -0.001f && zoom_scale_target_ - zoom_scale_ < 0.001f)
		zoom_scale_ = zoom_scale_target_;
}

/******************************************************************************/
/*!
Returns the zoom amount of the camera
*/
/******************************************************************************/
float Camera::Get_Zoom() const
{
	return zoom_scale_;
}

/******************************************************************************/
/*!
Sets the camera to zoom in or out. TRUE to zoom in, FALSE to zoom out.
*/
/******************************************************************************/
void Camera::Set_Zoom(bool zoom_type)
{
	// Zoom in
	if (zoom_type == true)
	{
		// Zoom in by this amount
		zoom_scale_target_ += 0.025f;

		// If exceeded due to floating point error, snap to max value
		if (zoom_scale_target_ > 2.0f)
			zoom_scale_target_ = 2.0f;

		// Sets the camera to zoom towards the cursor
		else
		{
			AEVec2 cursor = system_components.cursor_position_->Get_Cursor_Position();

			zoom_cursor_target_.x = ((cursor.x - -camera_position_target_.x) / zoom_scale_target_) * 0.02542f;
			zoom_cursor_target_.y = ((cursor.y - -camera_position_target_.y) / zoom_scale_target_) * 0.02542f;
		}
	}

	else
	{
		zoom_scale_target_ -= 0.025f;

		if (zoom_scale_target_ < 0.8f)
			zoom_scale_target_ = 0.8f;

		else
		{
			AEVec2 cursor = system_components.cursor_position_->Get_Cursor_Position();

			zoom_cursor_target_.x = -((cursor.x - -camera_position_target_.x) / zoom_scale_target_) * 0.02458f;
			zoom_cursor_target_.y = -((cursor.y - -camera_position_target_.y) / zoom_scale_target_) * 0.02458f;
		}
	}

	Update_Camera_Boundaries();
}


/******************************************************************************/
/*!
Updates camera boundaries based on zoom amount
*/
/******************************************************************************/
void Camera::Update_Camera_Boundaries()
{
	// Finds the camera boundaries based on the level boundaries found, multiplied by the zoom 
	camera_x_boundary_ = logic_components.level_data->Get_Positive_X_Boundary() * zoom_scale_target_ - HALF_SCREEN_WIDTH + 50.0f;
	camera_negative_x_boundary_ = HALF_SCREEN_WIDTH + logic_components.level_data->Get_Negative_X_Boundary() * zoom_scale_target_ - 50.0f;
	camera_y_boundary_ = logic_components.level_data->Get_Positive_Y_Boundary() * zoom_scale_target_ - CAMERA_Y_UI_ADJUSTMENT - 150.0f;
	camera_negative_y_boundary_ = logic_components.level_data->Get_Negative_Y_Boundary() * zoom_scale_target_ - CAMERA_Y_UI_ADJUSTMENT + 150.0f;

	// Check if the camera viewport is larger than the level boundary
	if (camera_x_boundary_ < camera_negative_x_boundary_)
		camera_x_larger_than_play_area = true;
	else camera_x_larger_than_play_area = false;

	if (camera_y_boundary_ < camera_negative_y_boundary_)
		camera_y_larger_than_play_area = true;
	else camera_y_larger_than_play_area = false;
}

/******************************************************************************/
/*!
Resets camera values when restarting level
*/
/******************************************************************************/
void Camera::Reset_Camera()
{
	camera_position_.x = 0;
	camera_position_.y = 0;
	camera_position_target_.x = 0;
	camera_position_target_.y = 0;
	zoom_scale_ = 1.0f;
	zoom_scale_target_ = 1.0f;
	camera_x_boundary_ = 0;
	camera_negative_x_boundary_ = 0;
	camera_y_boundary_ = 0;
	camera_y_actual_position_ = 0;
	shake_amplitude_ = 0;

	AEGfxSetCamPosition(0, 0);
}

/******************************************************************************/
/*!
Trim excess values due to floating point error
*/
/******************************************************************************/
void Trim_Excess(float & current_position, float & target_position)
{
	float excess = current_position - target_position;

	current_position -= excess;
}

/******************************************************************************/
/*!
Snap the camera to a coordinate
*/
/******************************************************************************/
void Camera::Snap_Camera_Position(float x, float y)
{
	camera_position_.x = x;
	camera_position_.y = y;

	AEGfxSetCamPosition(x, y);
}

/******************************************************************************/
/*!
Inititates the camera to shake
*/
/******************************************************************************/
void Camera::Initialise_Shake_Camera()
{
	shake_amplitude_ = 15; // 10 pixels

	// Randomises an angle
	shake_angle_ = (float)logic_components.Generate_Random_Integer(360);

	// Finds the offset based on the degree
	camera_shake_offset_.x = (AECos(AEDegToRad(shake_angle_) ));
	camera_shake_offset_.y = (AESin(AEDegToRad(shake_angle_)));

	camera_is_shaking_ = true;
}

/******************************************************************************/
/*!
Shakes the camera while it is shaking
*/
/******************************************************************************/
void Camera::Shake_Camera()
{
	// Decreases amplitude every frame
	shake_amplitude_ *= 0.9f;

	// Generate randon number between 1 and 0
	int random_number = logic_components.Generate_Random_Integer(1);

	// Chooses either +180 degrees or -60 degrees
	if (random_number)
		shake_angle_ += 180;

	else shake_angle_ -= 60;

	// Calculate new offset
	camera_shake_offset_.x = (AECos(AEDegToRad(shake_angle_))) * shake_amplitude_;
	camera_shake_offset_.y = (AESin(AEDegToRad(shake_angle_))) * shake_amplitude_;

	// Stop shaking after a certain amplitude
	if (shake_amplitude_ <= 0.5f)
		Stop_Camera_Shake();
}

/******************************************************************************/
/*!
Stops the camera from shaking
*/
/******************************************************************************/
void Camera::Stop_Camera_Shake()
{
	camera_is_shaking_ = false;

	camera_shake_offset_.x = 0;
	camera_shake_offset_.y = 0;

	shake_amplitude_ = 0;
}

/******************************************************************************/
/*!
Unused function intended for tutorial. Zooms the camera to a specific unit's coordinate.
*/
/******************************************************************************/
void Camera::Zoom_To_Unit(AEVec2 target)
{
	last_camera_position_target_ = camera_position_target_;
	last_zoom_scale_target_ = zoom_scale_target_;

	camera_position_target_.x = (target.x * 2);
	camera_position_target_.y = (target.y * 2) - CAMERA_Y_UI_ADJUSTMENT;

	zoom_scale_target_ = 2;

	Update_Camera_Boundaries();
}

/******************************************************************************/
/*!
Unused function intended for tutorial. Restores the camera position after zooming in.
*/
/******************************************************************************/
void Camera::Resume_Play()
{
	camera_position_target_ = last_camera_position_target_;
	zoom_scale_target_ = last_zoom_scale_target_;

	Update_Camera_Boundaries();
}