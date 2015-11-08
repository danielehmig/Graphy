#ifndef _PANEL_H_
#define _PANEL_H_

#include <vector>
#include "LineItem.h"
#include "cinder/app/AppBasic.h"
#include "Expander.h"

namespace Graphy_App
{
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

		bool checkClick(ci::Vec2f& coords);
		bool checkHover(ci::Vec2f& coords);
		void update();
		void draw();

		void addLineItem(LineItem::type typ, std::string l);
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

		// COLL: The panel is currently collapsed
		// SHRINK: The panel is currently collapsing
		// GROW: The panel is currently expanding
		// EXP: The panel is currently expanded
		enum state {COLL, SHRINK, GROW, EXP};

		state currentState;
	};
}

#endif