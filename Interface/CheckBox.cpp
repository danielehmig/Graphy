#include "CheckBox.h"

namespace Graphy_App
{
	CheckBox::CheckBox()
	{

	}

	CheckBox::CheckBox(cinder::Color boxColor, cinder::Color checkColor,
					   cinder::Color textColor, ci::Vec2f& tl, std::string l, 
					   std::size_t w, std::size_t h) : LineItem(tl, l, w, h)
	{
		this->boxColor = boxColor;
		this->checkColor = checkColor;
		this->textColor = textColor;

		this->checked = false;

		this->labelFont = cinder::Font("Helvetica", 18);
		this->boxDim = h / 2;
	}

	bool CheckBox::checkClick(ci::Vec2f& coords)
	{
		// Check click only returns true if the
		// check box itself was clicked
		if (coords.x > topLeft.x && 
			coords.x < (topLeft.x + boxDim) && 
			coords.y >(topLeft.y + (height / 4)) && 
			coords.y < (topLeft.y + height - (height / 4)))
		{
			checked = !checked;
			return true;
		}

		return false;
	}

	bool CheckBox::checkHover(ci::Vec2f& coords)
	{
		return (coords.x > topLeft.x &&
				coords.x < (topLeft.x + boxDim) &&
				coords.y >(topLeft.y + (height / 4)) &&
				coords.y < (topLeft.y + height - (height / 4)));
	}

	void CheckBox::updatePos(ci::Vec2f& delta)
	{
		topLeft.x += delta.x;
		topLeft.y += delta.y;
	}

	void CheckBox::update()
	{

	}

	void CheckBox::draw()
	{
		// Draw the box
		ci::gl::color(this->boxColor);

		ci::Rectf box(topLeft.x, topLeft.y + (height / 4),
					  topLeft.x + boxDim, topLeft.y + height - (height / 4));
		ci::gl::drawSolidRect(box);

		ci::gl::enableAlphaBlending();

		// if checked then draw check
		if (checked)
		{
			ci::gl::color(this->checkColor);

			ci::gl::lineWidth(3.0f);

			ci::Vec2f start1(topLeft.x, topLeft.y + (height / 2));
			ci::Vec2f end1(topLeft.x + (boxDim / 2), topLeft.y + height - (height / 4));

			ci::Vec2f start2(topLeft.x + (boxDim / 2), topLeft.y + height - (height / 4));
			ci::Vec2f end2(topLeft.x + boxDim, topLeft.y + (height / 4));

			ci::gl::drawLine(start1, end1);
			ci::gl::drawLine(start2, end2);
		}

		// a few more pixels +x, draw the text
		ci::Vec2f label_pos(topLeft.x + (width/2.0f), topLeft.y);
		label_pos.y += ((height - labelFont.getSize()) / 2.0f);
		cinder::gl::drawStringCentered(label, label_pos, textColor, labelFont);
	}
}