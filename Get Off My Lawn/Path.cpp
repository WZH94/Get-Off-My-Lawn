/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   Path.cpp
\author Wong Zhihao					(50%) | Tan Zhi Quan (50%)
\par    email: zhihao.wong\@digipen.edu | zhiquan.tan\@digipen.edu
\par    DigiPen login: zhihao.wong | zhiquan.tan
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the implementation for the paths that soldiers follow. Paths
are initialised and created here. Automation of path direction and location is 
also done here.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Path.h"			// Class and function declarations
#include "RenderManager.h"	// Render Object
#include "ObjectList.h"		// Path types

#include "main.h"			// SCREEN_WIDTH

/******************************************************************************/
/*!
Constructor for the path
*/
/******************************************************************************/ 
Path::Path(int node_placement, Path * parent, Orientation orientation, UNIT_TYPES type)
	: 
	// Calls the parent constructor
	GameObject(
		NONE, 
		0, 
		0, 
		100.0f, 
		100.0f,
		PATH, 
		type
	),

	// Sets variables
	path_placement_{node_placement},
	parent_{parent}, 
	orientation_{orientation},
	skip_node_{false}					// Default to not be a skipped node
{
	// Coordinate of the path
	float node_x;
	float node_y;

	// Check if the path is the first to be set
	if (path_placement_ == 0)
	{
		// Sets the path at the Grandma's base location.

		// Set it to not print anything so that it does not overlap with the base.
		Set_Texture(nullptr);

		switch (orientation_)
		{
		case UP:
			// Set this path to be above the parent's path
			node_x = 0;
			node_y = radius_;
			break;

		case DOWN:
			// Set this path to be below the parent's path
			node_x = 0;
			node_y = -radius_;
			break;

		case LEFT:
			// Set this path to be to the left of the parent's path
			node_x = -radius_;
			node_y = 0;
			break;

		case RIGHT:
			// Set this path to be to the right of the parent's path
			node_x = radius_;
			node_y = 0;
			break;

			// What the heck did you input?
		default:
			node_x = 0;
			node_y = 0;
			break;
		}
	}

	// Check it's orientation to set it's coordinate relative to it's parent path
	else
	{
		float parent_x = parent_->Get_x();
		float parent_y = parent_->Get_y();

		// If this path is in the middle of a straight section, set it to be skipped by soldiers.
		// Soldiers instead move to the end of the straight section rather than going through each path needlessly.
		if (type == PATH_STRAIGHT && parent_->orientation_ == orientation_)
			skip_node_ = true;

		switch (orientation_)
		{
		case UP:
			// Set this path to be above the parent's path
			node_x = parent_x;
			node_y = parent_y + scale_y;
			break;

		case DOWN:
			// Set this path to be below the parent's path
			node_x = parent_x;
			node_y = parent_y - scale_y;
			break;

		case LEFT:
			// Set this path to be to the left of the parent's path
			node_x = parent_x - scale_x;
			node_y = parent_y;
			break;

		case RIGHT:
			// Set this path to be to the right of the parent's path
			node_x = parent_x + scale_x;
			node_y = parent_y;
			break;

			// What the heck did you input?
		default:
			node_x = 0;
			node_y = 0;
			break;
		}
	}

	// Sets the coordinate of the path
	Set_x(node_x);
	Set_y(node_y);
}

/******************************************************************************/
/*!
Renders out the path
*/
/******************************************************************************/
void Path::Draw()
{
	// Check if it has texture, cause first and last paths don't need to be rendered
	if (this->Get_Texture())
		Render_Object(*this);
}

/******************************************************************************/
/*!
Gets this path's placement
*/
/******************************************************************************/
int Path::Get_Node_Placement() const
{
	return path_placement_;
}

/******************************************************************************/
/*!
Check if this node should be skipped
*/
/******************************************************************************/ 
bool Path::Get_Skip_Node() const
{
	return skip_node_;
}

/******************************************************************************/
/*!
Gets the orientation of this path
*/
/******************************************************************************/
Orientation Path::Get_Orientation() const
{
	return orientation_;
}
