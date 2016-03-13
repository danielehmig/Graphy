#ifndef _PANEL_H_
#define _PANEL_H_

#include <vector>
#include "LineItem.h"
#include "cinder/App/AppBasic.h"
#include "Expander.h"

namespace Graphy_App
{
	/* ====================================================
		CLASS: Panel
		Defines an expandable, dynamically-sized panel that
		contains various UI elements for editing a 
		visual graph in the scene
	==================================================== */
	class Panel
	{
	public:
		// minHeight: Height of the panel when collapsed;
		// also determines height of each LineItem
		// e: Whether or not the panel starts expanded
		Panel(ci::Vec2f& topLeft, std::size_t width,
			std::size_t minHeight, ci::Color c, bool e);

		// Stupid default constructor that we need to have
		Panel();

		// Returns whether this panel or one of its 
		// sub-components was clicked
		bool checkClick(ci::Vec2f& coords);

		// Returns whether one of sub-components is
		// currently being hovered over by the cursor
		// (useful for buttons)
		bool checkHover(ci::Vec2f& coords);

		// When dragging, this function is invoked
		// to update the current position of the panel
		// Returns false if the panel should not be dragged further
		bool updatePos(ci::Vec2f& delta);

		// Called before every frame draw by cinder
		void update();

		// Called every frame to draw the scene's current state
		void draw();

		// Inline set() function for dragging member variable
		inline void setDragging(const bool val)
		{
			if (val)
			{
				// If the panel wasn't actually clicked in a
				// mouse click event, don't set it to drag
				if (panelClicked)
				{
					dragging = val;
				}
				else
				{
					dragging = false;
				}
			}
			else
			{
				dragging = val;
			}
			
		}

		// Inline get() function for dragging
		inline bool isDragging() const
		{
			return dragging;
		}

		// Add a (Button | CheckBox | Radio Button) to the panel
		void addLineItem(LineItem::type typ, std::string l);

		// Remove one of the panel's sub-components
		void removeLineItem(std::size_t row);

	private:

		// The LineItems which populate the panel when it's expanded
		std::vector<LineItem *> lineItems;

		// The triangle clicked to expand and collapse the panel
		Expander expander;

		// Position of the top left corner of the panel
		ci::Vec2f topLeft;

		// Height of the panel when it's collapsed
		std::size_t collapsedHeight;

		// Height of the panel when it's expanded
		std::size_t expandedHeight;

		// The current height of the panel (used when it's animating)
		std::size_t currentHeight;

		// Width of the panel
		std::size_t width;

		// The (solid) color of the panel when rasterized
		ci::Color color;

		// Determines how fast the panel expands and collapses
		int heightIncr;

		// When a click event occurs, whether the panel itself was
		// clicked (true) or one of its sub-components was clicked (false)
		bool panelClicked;

		// Whether the panel should be dragged when the mouse is moved
		bool dragging;

		// COLL: The panel is currently collapsed
		// SHRINK: The panel is currently collapsing
		// GROW: The panel is currently expanding
		// EXP: The panel is currently expanded
		enum state {COLL, SHRINK, GROW, EXP};

		// Self-explanatory
		state currentState;
	};
}

#endif