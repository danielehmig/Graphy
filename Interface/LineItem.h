#ifndef _LINEITEM_H_
#define _LINEITEM_H_

#include "cinder/app/AppBasic.h"
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
		LineItem();
		LineItem(ci::Vec2f& tl, std::string l, std::size_t w, std::size_t h);
		virtual bool checkClick(ci::Vec2f& coords);
		virtual bool checkHover(ci::Vec2f& coords);
		std::size_t get_width() const;
		std::size_t get_height() const;
		virtual void update();
		virtual void draw();

		enum type { BUTTON, RADIO, CHECKBOX };
	protected:

		// Line items should have corresponding text that
		// alludes to their features
		std::string label;
		ci::Vec2f topLeft;
		std::size_t width;
		std::size_t height;

		
	};
}

#endif