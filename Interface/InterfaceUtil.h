#ifndef _INTERFACEUTIL_H_
#define _INTERFACEUTIL_H_

#include "cinder/app/AppBasic.h"

namespace Graphy_App
{
	static class InterfaceUtil
	{
	public:
		static ci::Vec2f worldToWindow(ci::Vec2f& coords);
		static ci::Vec2f windowToWorld(ci::Vec2f& coords);
	};
}

#endif