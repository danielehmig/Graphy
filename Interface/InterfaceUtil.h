#ifndef _INTERFACEUTIL_H_
#define _INTERFACEUTIL_H_

#include "cinder/App/AppBasic.h"

namespace Graphy_App
{
	/* ====================================================
		CLASS: InterfaceUtil
		Class that will hold various static utility
		functions used throughout the whole program
	==================================================== */
	static class InterfaceUtil
	{
	public:

		// The current Frames Per Second (FPS) value
		static const unsigned int FPS = 60.0f;

		// Converts coordinates in world format (Cartesian Plane)
		// to coordinates in window format (origin in top left)
		static ci::Vec2f worldToWindow(ci::Vec2f& coords);

		// Converts coordinates in window format (origin in top left)
		// to world format (Cartesian Plane), with origin in center
		static ci::Vec2f windowToWorld(ci::Vec2f& coords);
	};
}

#endif