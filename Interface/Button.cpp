#include "Button.h"
namespace Graphy_App
{
	Button::Button()
	{

	}

	Button::Button(cinder::Color bc, cinder::Color fc, cinder::Color ufc, ci::Vec2f& tl,
		std::string l, std::size_t w, std::size_t h) : LineItem(tl, l, w, h)
	{
		borderColor = bc;
		unfilledColor = currentColor = ufc;
		fillColor = fc;
		labelFont = cinder::Font("Helvetica", 18);

		redIncr = (1.0f - fillColor.r) / 30.0f;
		greenIncr = (1.0f - fillColor.g) / 30.0f;
		blueIncr = (1.0f - fillColor.b) / 30.0f;

		animating = false;

		// Start the button at 'Normal', i.e. no click or mouse hover
		currentState = NORMAL;
	}

	bool Button::checkClick(ci::Vec2f& coords)
	{
		if (inBounds(coords))
		{
			changeState(true);
			return true;
		}

		return false;
	}

	bool Button::checkHover(ci::Vec2f& coords)
	{
		if (inBounds(coords))
		{
			changeState(false);
			return true;
		}
		else
		{
			currentState = NORMAL;
			currentColor = unfilledColor;
			animating = false;
		}

		return false;
	}

	bool Button::inBounds(ci::Vec2f& coords)
	{
		if (coords.x > topLeft.x && coords.x < (topLeft.x + get_width()))
		{
			if (coords.y > topLeft.y && coords.y < (topLeft.y + get_height()))
			{
				return true;
			}
		}

		return false;
	}

	void Button::changeState(bool click)
	{
		// State was changed by a click
		if (click)
		{
			currentState = CLICKED;
			//animating = true;
			//currentColor = cinder::Color(1.0f, 1.0f, 1.0f);
			//theApp.receiveLineItemEvent(this);
		}
		// State was changed by a hover
		else
		{
			currentState = HOVER;
			currentColor = fillColor;
			// Might still be animating, don't necessarily want
			// to set color to the filled Color
		}
	}

	void Button::update()
	{
		if (animating)
		{
			currentColor.r -= redIncr;
			currentColor.g -= greenIncr;
			currentColor.b -= blueIncr;

			bool stopRed = false, 
				 stopGreen = false, 
				 stopBlue = false;


			if (currentColor.r < fillColor.r)
			{
				currentColor.r = fillColor.r;
				stopRed = true;
			}

			if (currentColor.g < fillColor.g)
			{
				currentColor.g = fillColor.g;
				stopGreen = true;
			}

			if (currentColor.b < fillColor.b)
			{
				currentColor.b = fillColor.b;
				stopBlue = true;
			}

			if (stopRed && stopGreen && stopBlue)
			{
				animating = false;
			}
		}
		else
		{
			if (currentState == HOVER)
			{
				currentColor = fillColor;
			}
			else if (currentState == NORMAL)
			{
				currentColor = unfilledColor;
			}
		}
		
	}

	void Button::draw()
	{
		// Draw the button's border
		ci::Rectf rect(topLeft.x - 2, topLeft.y - 2, topLeft.x + width + 2, topLeft.y + height + 2);
		cinder::gl::color(borderColor);
		cinder::gl::drawSolidRect(rect);

		// Draw based on current color scheme
		rect = ci::Rectf(topLeft.x, topLeft.y, topLeft.x + width, topLeft.y + height);
		cinder::gl::color(currentColor);
		cinder::gl::drawSolidRect(rect);

		// Now, draw the button's text
		ci::Vec2f label_pos(topLeft.x + (width / 4.0), topLeft.y + (height / 3.0f));
		cinder::gl::enableAlphaBlending();
		cinder::gl::drawString(this->label, label_pos, cinder::Color(0.0f, 0.0f, 0.0f), labelFont);
	}

}