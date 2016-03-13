#pragma once

#include "LineItem.h"

namespace Graphy_App
{
	class CheckBox : public LineItem
	{
	public:
		CheckBox();
		CheckBox(cinder::Color boxColor, cinder::Color checkColor, 
				 cinder::Color textColor, ci::Vec2f& tl, 
				 std::string l, std::size_t w, std::size_t h);
		bool checkClick(ci::Vec2f& coords);
		bool checkHover(ci::Vec2f& coords);
		void updatePos(ci::Vec2f& delta);
		void update();
		void draw();
	private:
		bool checked;
		cinder::Color boxColor;
		cinder::Color checkColor;
		cinder::Color textColor;
		cinder::Font labelFont;

		std::size_t boxDim;
	};
}