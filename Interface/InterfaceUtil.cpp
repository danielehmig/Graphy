#include "InterfaceUtil.h"

namespace Graphy_App
{
	/* ====================================================
		worldToWindow(Vec2f)
	==================================================== */
	ci::Vec2f InterfaceUtil::worldToWindow(ci::Vec2f& coords)
	{
		ci::Vec2f retVal;
		retVal.x = coords.x + (cinder::app::getWindowWidth() / 2);
		if (coords.y <= 0)
		{
			retVal.y = (cinder::app::getWindowHeight() / 2) + abs(coords.y);
		}
		else
		{
			retVal.y = (cinder::app::getWindowHeight() / 2) - coords.y;
		}

		return retVal;
	}

	/* ====================================================
		windowToWorld(Vec2f)
	==================================================== */
	ci::Vec2f InterfaceUtil::windowToWorld(ci::Vec2f& coords)
	{
		ci::Vec2f retVal;
		retVal.x = coords.x - (cinder::app::getWindowWidth() / 2);
		std::size_t halfHeight = cinder::app::getWindowHeight() / 2;

		if (coords.y >= halfHeight)
		{
			retVal.y = -(coords.y - halfHeight);
		}
		else
		{
			retVal.y = halfHeight - coords.y;
		}

		return retVal;
	}
}