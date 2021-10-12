/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   Path.h
\author Wong Zhihao			(50%)| Tan Zhi Quan(50%)
\par    email: zhihao.wong\@digipen.edu | zhiquan.tan\@digipen.edu
\par    DigiPen login: zhihao.wong | zhiquan.tan
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the declarations of the Path class and its functions.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef MOVEMENTNODE_H
#define MOVEMENTNODE_H

#include "GameObject.h" // Path inherits from GameObject

// Orientation of the path
enum Orientation
{
	UP = 0,
	DOWN,
	LEFT,
	RIGHT,
};

// Path class declarations
class Path : public GameObject {
private:
	Path* parent_;				// Which path came before this.
	Orientation orientation_;	// The rotation of the path.

	int path_placement_;		// Position of the node in the game. 0 is at Grandma's base, connects to last node at Kid's base
	bool skip_node_;			// Skip this node for soldier movement if it is part of a straight path

public:
	// Constructor for the path
	Path(int node_placement, Path* parent, Orientation orientation, UNIT_TYPES type);

	// Renders out the path
	void Draw();

	// Gets this path's placement
	int Get_Node_Placement() const;

	// Check if this node should be skipped
	bool Get_Skip_Node() const;

	// Finds the orientation of this path
	Orientation Get_Orientation() const;
};

#endif MOVEMENTNODE_H