#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "LineItem.h"

namespace Graphy_App
{
	/* ====================================================
		CLASS: Button
		Extends LineItem to define a Button UI element
		that will be contained in a Panel; users click
		the button to trigger some event
	==================================================== */
	class Button : public LineItem
	{
	public:

		// Default constructor, don't use
		Button();

		// The constructor that should be used
		// bc: Color of the button's border
		// fc: Color of the button on hover
		// ufc: Color of the button when not hovered
		// tl: (x,y) position of top-left corner
		// l: The button's text
		// w: width of the button
		// h: height of the button
		Button(cinder::Color bc, cinder::Color fc, cinder::Color ufc, ci::Vec2f& tl,
			std::string l, std::size_t w, std::size_t h);

		// Returns whether the current button was clicked
		bool checkClick(ci::Vec2f& coords);

		// Update the current button's position if the
		// surrounding panel is being dragged
		void updatePos(ci::Vec2f& delta);

		// Function invoked before every frame draw by cinder
		void update();

		// Function invoked on every frame to draw the [current] scene
		void draw();

		// Returns whether the current button has the cursor on top
		bool checkHover(ci::Vec2f& coords);

		// NOTE: Need a way to fire off events to a listener
		// IDEA: GraphyApp is the only listener - have specific functions in GraphyApp
		// for each type of LineItem and pass those "listener" functions data that
		// identifies which instance of Button, CheckBox, etc fired the event
	private:

		// click = true --> the state was changed by a click
		// click = false --> the state was changed by a hover
		void changeState(bool click);

		// Private helper function to check if some (x,y) coords
		// fall within the current button's bounds
		bool inBounds(ci::Vec2f& coords);

		// Color of the button's border
		cinder::Color borderColor;

		// Color of the button when the cursor is hovering
		cinder::Color fillColor;

		// Color of the button when the cursor is not hovering
		cinder::Color unfilledColor;

		// Current internal color of the button (filled or unfilled, basically)
		cinder::Color currentColor;

		// When animating a button click, how much to increment Red value
		float redIncr;

		// When animating a button click, how much to increment Green value
		float greenIncr;

		// When animating a button click, how much to increment Blue value
		float blueIncr;

		// Whether the button is animating (from after a button click)
		bool animating;

		// The font of the button's text
		cinder::Font labelFont;

		// State of the button's appearance
		// NORMAL: Button not clicked or being hovered
		// HOVER: Cursor is hovering over the button
		// CLICKED: The button has been clicked
		enum state {NORMAL, HOVER, CLICKED};

		// Self-explanatory
		state currentState;
	};
}

#endif