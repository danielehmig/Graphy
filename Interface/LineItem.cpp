#include "LineItem.h"

namespace Graphy_App
{
	/* ====================================================
		LineItem()
	==================================================== */
	LineItem::LineItem()
	{
		label = "";
		width = 0;
		height = 0;	
	}

	/* ====================================================
		LineItem(Vec2f, string, size_t, size_t)
	==================================================== */
	LineItem::LineItem(ci::Vec2f& tl, std::string l, std::size_t w, std::size_t h)
	{
		topLeft = tl;
		label = l;
		width = w;
		height = h;
	}

	/* ====================================================
		checkClick(Vec2f)
	==================================================== */
	bool LineItem::checkClick(ci::Vec2f& coords)
	{
		return false;
	}

	/* ====================================================
		checkHover(Vec2f)
	==================================================== */
	bool LineItem::checkHover(ci::Vec2f& coords)
	{
		return false;
	}

	/* ====================================================
		updatePos(Vec2f)
	==================================================== */
	void LineItem::updatePos(ci::Vec2f& delta)
	{
		
	}

	/* ====================================================
		update()
	==================================================== */
	void LineItem::update()
	{

	}

	/* ====================================================
		draw()
	==================================================== */
	void LineItem::draw()
	{

	}

	/* ====================================================
		get_width()
	==================================================== */
	std::size_t LineItem::get_width() const
	{
		return this->width;
	}

	/* ====================================================
		get_height()
	==================================================== */
	std::size_t LineItem::get_height() const
	{
		return this->height;
	}

}