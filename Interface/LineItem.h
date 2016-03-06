#ifndef _LINEITEM_H_
#define _LINEITEM_H_

#include "cinder/App/AppBasic.h"
#include <string>
//#include "GraphyApp.h"

namespace Graphy_App
{
	/* ====================================================
		CLASS: LineItem
		Base class for all items that can show in a panel
	==================================================== */
	class LineItem
	{
	public:

		// Stupid default constructor that we need
		LineItem();

		// Constructor that should be used
		// tl: (x,y) coordinates of top-left corner
		// l: The text content of the LineItem
		// w: Width of the LineItem
		// h: Height of the LineItem
		LineItem(ci::Vec2f& tl, std::string l, std::size_t w, std::size_t h);

		// Returns whether this LineItem was clicked
		// Note: Should be overridden
		virtual bool checkClick(ci::Vec2f& coords);

		// Returns whether the cursor is hovering over
		// this LineItem
		// Note: Should be overridden
		virtual bool checkHover(ci::Vec2f& coords);

		// get() function for the width
		std::size_t get_width() const;

		// get() function for the height
		std::size_t get_height() const;

		// Update the current position based on a drag event
		virtual void updatePos(ci::Vec2f& delta);

		// Function invoked before every frame draw by cinder
		virtual void update();

		// Function invoked every frame to draw the current scene
		virtual void draw();

		// This LineItem's type possibilities
		enum type { BUTTON, RADIO, CHECKBOX };
	protected:

		// Line items should have corresponding text that
		// alludes to their features
		std::string label;

		// Stores the current position (in window coords)
		// of this LineItem
		ci::Vec2f topLeft;

		// Width of this LineItem
		std::size_t width;

		// Height of this LineItem
		std::size_t height;

		
	};
}

#endif