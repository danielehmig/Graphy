#include "Button.h"
#include "Panel.h"
#include "Theme.h"

namespace Graphy_App
{
	/* =======================================================
		Panel()
	======================================================= */
	Panel::Panel()
	{

	}

	/* =======================================================
		Panel(Vec2f, size_t, size_t, Color, bool)
	======================================================= */
	Panel::Panel(ci::Vec2f& topLeft, std::size_t width,
		std::size_t minHeight, ci::Color c, bool e)
	{
		this->topLeft = topLeft;
		this->width = width;
		color = c;

		panelClicked = false;
		dragging = false;

		currentState = (e ? EXP : COLL);

		// Initially, the height of the panel when expanded is the
		// same as it is when collapsed
		collapsedHeight = expandedHeight = currentHeight = minHeight;

		ci::Vec2f expCenter;
		std::size_t sideL = collapsedHeight - 10;
		expCenter.x = topLeft.x + sideL + 5;
		expCenter.y = topLeft.y + ((sideL / 2) + 5);

		expander = Expander(expCenter, cinder::Color(0.3098f, 0.5059f, 0.7412f), sideL, e);

		// Also calculate when line items are added
		heightIncr = (expandedHeight - collapsedHeight) / (InterfaceUtil::FPS / 2.0f);
		if (heightIncr == 0)
		{
			heightIncr = 1;
		}
	}

	/* =======================================================
		checkClick(Vec2f)
	======================================================= */
	bool Panel::checkClick(ci::Vec2f& coords)
	{
		
		if (!(coords.x > topLeft.x && 
			coords.x < (topLeft.x + width) && 
			coords.y > topLeft.y && 
			coords.y < (topLeft.y + currentHeight)))
		{
			return false;
		}

		panelClicked = true;

		if (expander.checkClick(coords))
		{
			panelClicked = false;
			switch (currentState)
			{
			case COLL:
			case SHRINK:
				currentState = GROW;
				break;
			case GROW:
			case EXP:
				currentState = SHRINK;
				break;
			default:
				break;
			}
		}
		else
		{
			// Check if any of the LineItems were clicked
			std::size_t i = 0;
			for (i = 0; i < lineItems.size(); ++i)
			{
				// Check to see if the LineItem is even visible
				int space = currentHeight - collapsedHeight - PADDING;
				int needed = (PADDING * (i + 1)) + (collapsedHeight * (i + 2));
				if (space >= needed)
				{
					if (lineItems[i]->checkClick(coords))
					{
						panelClicked = false;
					}
				}
			}
		}

		return true;
	}

	/* =======================================================
		checkHover(Vec2f)
	======================================================= */
	bool Panel::checkHover(ci::Vec2f& coords)
	{
		// We just want to check the LineItems
		std::size_t i = 0;
		bool retVal = false;
		for (i = 0; i < lineItems.size(); ++i)
		{
			// Check to see if the LineItem is even visible
			int space = currentHeight - collapsedHeight - PADDING;
			int needed = (PADDING * (i + 1)) + (collapsedHeight * (i + 2));
			if (space >= needed)
			{
				if (lineItems[i]->checkHover(coords))
				{
					retVal = true;
				}
			}
		}

		return retVal;
	}

	/* =======================================================
		addLineItem(LineItem::type, string)
	======================================================= */
	void Panel::addLineItem(LineItem::type typ, std::string l)
	{
		float tl_y = this->topLeft.y + (collapsedHeight * (lineItems.size() + 1)) + ((lineItems.size() + 1) * PADDING);
		float tl_x = this->topLeft.x + PADDING;

		std::size_t width = this->width - (PADDING * 2);

		// Adjust some of the panel's properties
		expandedHeight += collapsedHeight + PADDING;
		heightIncr = (expandedHeight - collapsedHeight) / (InterfaceUtil::FPS / 2.0f);

		cinder::Color bfc(BUTTON_BORDER_RED, BUTTON_BORDER_GREEN, BUTTON_BORDER_BLUE);
		switch (typ)
		{
		case LineItem::BUTTON:
			// Create and add the object with the fields
			lineItems.push_back(new Button(bfc, 
									   bfc, 
									   this->color, 
									   ci::Vec2f(tl_x, tl_y), 
									   l, 
									   width, 
									   this->collapsedHeight));
			if (currentState == EXP)
			{
				currentHeight = expandedHeight;
			}
			break;
		case LineItem::CHECKBOX:
			break;
		case LineItem::RADIO:
			break;
		default:
			return;
		}
	}

	/* =======================================================
		removeLineItem(size_t)
	======================================================= */
	void Panel::removeLineItem(std::size_t row)
	{
		// !!!!!!!!!!!!!!! DELETE THE DYNAMICALLY ALLOCATED OBJECTS !!!!!!!!!!!!!!!!!!
	}

	/* =======================================================
		updatePos(Vec2f)
	======================================================= */
	void Panel::updatePos(ci::Vec2f& delta)
	{
		topLeft.x += delta.x;
		topLeft.y += delta.y;

		expander.updatePos(delta);

		std::vector<LineItem*>::iterator it = lineItems.begin();
		for (; it != lineItems.end(); it++)
		{
			(*it)->updatePos(delta);
		}
	}

	/* =======================================================
		update()
	======================================================= */
	void Panel::update()
	{
		if (currentState == GROW)
		{
			currentHeight += heightIncr;

			if (currentHeight >= expandedHeight)
			{
				currentHeight = expandedHeight;
				currentState = EXP;
			}
		}
		else if (currentState == SHRINK)
		{
			currentHeight -= heightIncr;
			if (currentHeight <= collapsedHeight)
			{
				currentHeight = collapsedHeight;
				currentState = COLL;
			}
		}

		expander.update();
	}

	/* =======================================================
		draw()
	======================================================= */
	void Panel::draw()
	{
		ci::Rectf rect(topLeft.x, topLeft.y, topLeft.x + width, topLeft.y + currentHeight);
		cinder::gl::color(color);
		cinder::gl::drawSolidRect(rect);
		
		expander.draw();

		std::size_t i = 0;

		for (i = 0; i < lineItems.size(); ++i)
		{
			// Check to see if the LineItem is even visible
			int space = currentHeight - collapsedHeight - PADDING;
			int needed = (PADDING * (i+1)) + (collapsedHeight * (i+2));
			if (space >= needed)
			{
				lineItems[i]->draw();
			}
		}
	}
}