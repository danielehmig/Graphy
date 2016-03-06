#ifndef _EXPANDER_H_
#define _EXPANDER_H_

#include "cinder/App/AppBasic.h"
#include "../Interface/InterfaceUtil.h"

#define MAX_ROTATION 90.0f

namespace Graphy_App
{
	/* ====================================================
		CLASS: Expander
		Defines the triangle that is clicked to expand
		a panel of interactive elements
	==================================================== */
	class Expander
	{
	public:

		// pos: the position of the center of the triangle
		// c: the triangle's color
		// l: the length of the triangle's sides
		// expanded: Whether or not the triangle in its "expanded" state
		Expander(ci::Vec2f& pos, ci::Color c, float l, bool expanded);

		// Don't use
		Expander();

		// If the triangle is currently rotating, this function will update
		// the triangle's vertices to reflect the change
		void update();

		// Just draw the triangle with the current value of its vertices
		void draw();

		// Update the position of the expander, for example, in the
		// event that the surrounding panel is moved
		void updatePos(ci::Vec2f& delta);

		// Called on a mouse click; determines if the mouse click was
		// on the triangle
		bool checkClick(ci::Vec2f& mouseCoords);

	private:

		// Length of each side of the triangle (it's equilateral)
		float sideLength;

		// The (solid) color that the triangle will be rasterized with
		ci::Color color;

		// x,y coordinates of each vertex of the triangle
		ci::Vec2f pt1;
		ci::Vec2f pt2;
		ci::Vec2f pt3;

		// x, y coordinates for the center of the triangle
		ci::Vec2f center;

		// The radius of the circle that defines an "onClick zone"
		float clickRadius;

		// When the triangle is animating, how much to rotate each frame (degrees)
		float rotationIncr;

		// The current angle of rotation of the triangle (degrees)
		float currentRotation;

		// COLL: The triangle is not rotated (i.e. the panel is COLLapsed)
		// CW: The triangle is rotating ClockWise (i.e. the panel is expanding)
		// CCW: The triangle is rotating CounterClockWise (i.e. the panel is collapsing)
		// EXP: The triangle is rotated 90 degrees (i.e. the panel is fully expanded)
		enum state {COLL, CW, CCW, EXP};

		// Obvious
		state currentState;

		// Private helper member function to immediately rotate the
		// expander to its fully-expanded state (i.e. 90.0f)
		void rotateToMax();
	};
}

#endif