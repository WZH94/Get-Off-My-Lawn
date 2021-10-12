/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   Camera.h
\author Wong Zhihao				(100%)
\par    email: zhihao.wong\@digipen.edu
\par    DigiPen login: zhihao.wong
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the declarations of functions that control the in game camera. 

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef CAMERA_H
#define CAMERA_H

#include "AEVec2.h"

class Camera
{
protected:
	// The point the cursor has to be at in the x and y-axis before the camera moves
	const int CAMERA_X_MOVE_THRESHOLD_;
	const int CAMERA_Y_MOVE_THRESHOLD_;

	// Speed the camera moves at each axis
	const float CAMERA_X_SPEED;
	const float CAMERA_Y_SPEED;

	// Centers the camera after accounting for the UI panel at the bottom.
	const float CAMERA_Y_UI_ADJUSTMENT;

	// Deadzone in the centre y-axis where the camera does not move in the y-axis
	const float CAMERA_DEADZONE;

	/////////////////////////////////////////
	// Camera behaviour based on LevelData

	float zoom_scale_;				// Magnifies object scales by this to give the effect of zooming
	float zoom_scale_target_;		// Zoom magnification to zoom towards to
	AEVec2 zoom_cursor_target_;		// 
	bool camera_is_zooming_;

	// Since camera centre is at 0, these calculates difference between edge of camera and edge of the screens
	float camera_x_boundary_;
	float camera_negative_x_boundary_;
	float camera_y_boundary_;
	float camera_negative_y_boundary_;

	// This flags if the camera viewport covers more than the play area, so that it does not spaz out snapping back into boundary
	bool camera_x_larger_than_play_area;
	bool camera_y_larger_than_play_area;

	////////////////////
	// Camera position

	AEVec2 camera_position_;		// Current camera position in the game
	AEVec2 camera_position_target_;	// Camera position to move to based on mouse cursor

	float camera_y_actual_position_;

	////////////////
	// Camera shake 

	bool camera_is_shaking_;		// Whether the camera is shaking

	AEVec2 camera_shake_offset_;	// Offset of the camera shaking

	float shake_amplitude_;			// Amount to shake
	float shake_frequency_;			// How often it shakes
	float shake_angle_;				// Angle it is shaking towards to this frame.

	//////////////////////////////
	// Tutorial camera variables

	// Unused variables. Saves the camera and zoom before it zoomed in to a unit.
	AEVec2 last_camera_position_target_;
	float last_zoom_scale_target_;

public:
	// Default constructor
	Camera();
	
	// Initialises the camera at the start of every level
	void Initialise_Camera();

	// Updates camera properties
	void Update_Camera();

	// Returns the camera position
	AEVec2 Get_Camera_Position() const;

	// Returns the camera position for UI
	AEVec2 Get_Camera_UI_Position() const;

	// Gets the camera UI position, which is the position UI objects take from which is not affected by the camera shaking.
	void Set_Camera_Position();

	// Sets target camera x axis based on cursor position on x axis
	void Set_Camera_x(float);

	// Sets target camera y axis based on cursor position on y axis
	void Set_Camera_y(float);

	// Unused function. Was created when the height of the level was not going to change.
	// Moves the camera up and down on an arctan curve when the cursor moves towards
	// the top and bottom of the screen
	float Smooth_Y_Trail(float);

	// Moves the camera to its new position
	void Move_Camera();

	// Moves the camera slowly towards its targeted x axis. This function handles the smooth movement of the camera
	void Move_Camera_X();

	// Moves the camera slowly towards its targeted y axis. This function handles the smooth movement of the camera
	void Move_Camera_Y();

	// Zooms the camera towards its target
	void Zoom_Camera();

	// Returns the zoom amount of the camera
	float Get_Zoom() const;

	// Sets the camera to zoom in or out. TRUE to zoom in, FALSE to zoom out.
	void Set_Zoom(bool);

	// Updates camera boundaries based on zoom amount
	void Update_Camera_Boundaries();

	// Resets camera values when restarting level
	void Reset_Camera();

	// Snap the camera to a coordinate
	void Snap_Camera_Position(float x, float y);

	/************************* CAMERA SHAKE FUNCTIONS *************************/

	// Inititates the camera to shake
	void Initialise_Shake_Camera();
	
	// Shakes the camera while it is shaking
	void Shake_Camera();

	// Stops the camera from shaking
	void Stop_Camera_Shake();

	// Unused function intended for tutorial. Zooms the camera to a specific unit's coordinate.
	void Zoom_To_Unit(AEVec2 target);

	// Unused function intended for tutorial. Restores the camera position after zooming in.
	void Resume_Play();
};

// Trims excess if camera position moved past its intented target
void Trim_Excess(float & current_position, float & target_position);

#endif CAMERA_H
