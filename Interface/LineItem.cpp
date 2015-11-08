#include "LineItem.h"

namespace Graphy_App
{
	LineItem::LineItem()
	{
		label = "";
		width = 0;
		height = 0;	
	}

	LineItem::LineItem(ci::Vec2f& tl, std::string l, std::size_t w, std::size_t h)
	{
		topLeft = tl;
		label = l;
		width = w;
		height = h;
	}

	bool LineItem::checkClick(ci::Vec2f& coords)
	{
		return false;
	}

	bool LineItem::checkHover(ci::Vec2f& coords)
	{
		return false;
	}

	void LineItem::update()
	{

	}

	void LineItem::draw()
	{

	}

	std::size_t LineItem::get_width() const
	{
		return this->width;
	}

	std::size_t LineItem::get_height() const
	{
		return this->height;
	}

}