#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "LineItem.h"

namespace Graphy_App
{
	class Button : public LineItem
	{
	public:
		Button();
		Button(cinder::Color bc, cinder::Color fc, cinder::Color ufc, ci::Vec2f& tl,
			std::string l, std::size_t w, std::size_t h);
		bool checkClick(ci::Vec2f& coords);
		void update();
		void draw();

		bool checkHover(ci::Vec2f& coords);

		// NOTE: Need a way to fire off events to a listener
		// IDEA: GraphyApp is the only listener - have specific functions in GraphyApp
		// for each type of LineItem and pass those "listener" functions data that
		// identifies which instance of Button, CheckBox, etc fired the event
	private:

		// click = true --> the state was changed by a click
		// click = false --> the state was changed by a hover
		void changeState(bool click);
		bool inBounds(ci::Vec2f& coords);

		cinder::Color borderColor;
		cinder::Color fillColor;
		cinder::Color unfilledColor;
		cinder::Color currentColor;
		float redIncr;
		float greenIncr;
		float blueIncr;
		bool animating;
		cinder::Font labelFont;

		enum state {NORMAL, HOVER, CLICKED};

		state currentState;
	};
}

#endif