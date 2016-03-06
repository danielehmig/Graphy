#include "../Interface/Expander.h"


namespace Graphy_App
{
	/* ====================================================
		Expander()
	==================================================== */
	Expander::Expander()
	{
		center = ci::Vec2f(0.0f, 0.0f);
		color = cinder::Color(1.0f, 1.0f, 1.0f);

		sideLength = 1.0f;
		currentState = COLL;

		pt1.x = pt2.x = pt3.x = 0.0f;
		pt1.y = pt2.y = pt3.y = 0.0f;
	}

	/* ====================================================
		Expander(Vec2f, Color, float, bool)
	==================================================== */
	Expander::Expander(ci::Vec2f& pos, ci::Color c, float l, bool e)
	{
		color = c;
		sideLength = l;
		center = pos;

		currentRotation = 0.0f;	

		// rotates 90 degrees in 1/2 second (when framerate is at 60)
		rotationIncr = 90.0f / (InterfaceUtil::FPS / 2.0f);

		// Determine points of the triangle using a spell found deep in the
		// basement of the White Tower in Tar Valon
		pt1.x = pos.x - (sideLength * (sqrt(3.0f) / 6.0f));
		pt1.y = pos.y - (0.5f * sideLength);

		pt2.x = pos.x - (sideLength * (sqrt(3.0f) / 6.0f));
		pt2.y = pos.y + (0.5f * sideLength);

		pt3.x = pos.x + ((sqrt(3.0f) / 3.0f) * sideLength);
		clickRadius = (sqrt(3.0f) / 3.0f) * sideLength;
		pt3.y = pos.y;

		if (e)
		{
			currentState = EXP;
			rotateToMax();
		}
		else
		{
			currentState = COLL;
		}
	}

	/* ====================================================
		update()
	==================================================== */
	void Expander::update()
	{
		if (currentState == CW || currentState == CCW)
		{
			cinder::gl::pushModelView();

			// Temporarily tranform into world coordinates
			center = InterfaceUtil::windowToWorld(center);
			pt1 = InterfaceUtil::windowToWorld(pt1);
			pt2 = InterfaceUtil::windowToWorld(pt2);
			pt3 = InterfaceUtil::windowToWorld(pt3);

			cinder::gl::translate(cinder::app::getWindowWidth() / 2, cinder::app::getWindowHeight() / 2);
			
			cinder::gl::rotate(ci::Vec3f(180.0f, 0.0f, 0.0f));

			cinder::gl::translate(center.x, center.y);
			
			if (currentState == CW)
			{
				cinder::gl::rotate(-rotationIncr);
				currentRotation += rotationIncr;

				if (currentRotation >= MAX_ROTATION)
				{
					currentRotation = MAX_ROTATION;
					currentState = EXP;
				}
			}
			else
			{
				cinder::gl::rotate(rotationIncr);
				currentRotation -= rotationIncr;

				if (currentRotation <= 0.0f)
				{
					currentRotation = 0.0f;
					currentState = COLL;
				}
			}


			// Update the position of the triangle's vertices based on its
			// current rotation (we can't just draw the triangle here, so we
			// need to update the points before modelView is popped)
			cinder::gl::translate(-center.x, -center.y);

			ci::Vec4f cent(center.x, center.y, 0, 1);
			cent = cinder::gl::getModelView() * cent;
			center.x = cent.x;
			center.y = cent.y;

			ci::Vec4f point(pt1.x, pt1.y, 0, 1);
			point = cinder::gl::getModelView() * point;
			pt1.x = point.x;
			pt1.y = point.y;

			point = ci::Vec4f(pt2.x, pt2.y, 0, 1);
			point = cinder::gl::getModelView() * point;
			pt2.x = point.x;
			pt2.y = point.y;

			point = ci::Vec4f(pt3.x, pt3.y, 0, 1);
			point = cinder::gl::getModelView() * point;
			pt3.x = point.x;
			pt3.y = point.y;

			// Now, convert back to window coordinates
			center = InterfaceUtil::worldToWindow(center);
			pt1 = InterfaceUtil::worldToWindow(pt1);
			pt2 = InterfaceUtil::worldToWindow(pt2);
			pt3 = InterfaceUtil::worldToWindow(pt3);

			cinder::gl::popModelView();
		}
	}

	/* ====================================================
		draw()
	==================================================== */
	void Expander::draw()
	{
		cinder::gl::color(color);

		cinder::gl::drawSolidTriangle(pt1, pt2, pt3);
	}

	/* ====================================================
		updatePos()
	==================================================== */
	void Expander::updatePos(ci::Vec2f& delta)
	{
		this->center.x += delta.x;
		this->center.y += delta.y;

		this->pt1.x += delta.x;
		this->pt1.y += delta.y;

		this->pt2.x += delta.x;
		this->pt2.y += delta.y;

		this->pt3.x += delta.x;
		this->pt3.y += delta.y;
	}

	/* ====================================================
		checkClick(Vec2f)
	==================================================== */
	bool Expander::checkClick(ci::Vec2f& coords)
	{
		// Draw a line from center of "onClick zone" to coords
		// Check if line length exceeds radius
		float xDist = abs(coords.x - center.x);
		float yDist = abs(coords.y - center.y);

		float length = sqrt(pow(xDist, 2) + pow(yDist, 2));

		if (length < clickRadius)
		{
			// The triangle was clicked, so change the state accordingly
			switch (currentState)
			{
			case COLL:
			case CCW:
				currentState = CW;
				break;
			case CW:
			case EXP:
				currentState = CCW;
				break;
			default:
				break;
			}

			return true;
		}
		return false;
	}

	/* ====================================================
		rotateToMax()
	==================================================== */
	void Expander::rotateToMax()
	{
		cinder::gl::pushModelView();

		// Temporarily tranform into world coordinates
		center = InterfaceUtil::windowToWorld(center);
		pt1 = InterfaceUtil::windowToWorld(pt1);
		pt2 = InterfaceUtil::windowToWorld(pt2);
		pt3 = InterfaceUtil::windowToWorld(pt3);

		// We have to perform the world transformations in *reverse* order
		cinder::gl::translate(center.x, center.y);

		float rotationAmount = MAX_ROTATION - currentRotation;
		cinder::gl::rotate(-rotationAmount);
		currentRotation += rotationAmount;

		cinder::gl::translate(-center.x, -center.y);

		// Update the position of the triangle's vertices based on its
		// current rotation (we can't just draw the triangle here, so we
		// need to update the points before modelView is popped)

		ci::Vec4f cent(center.x, center.y, 0, 1);
		cent = cinder::gl::getModelView() * cent;
		center.x = cent.x;
		center.y = cent.y;

		ci::Vec4f point(pt1.x, pt1.y, 0, 1);
		point = cinder::gl::getModelView() * point;
		pt1.x = point.x;
		pt1.y = point.y;

		point = ci::Vec4f(pt2.x, pt2.y, 0, 1);
		point = cinder::gl::getModelView() * point;
		pt2.x = point.x;
		pt2.y = point.y;

		point = ci::Vec4f(pt3.x, pt3.y, 0, 1);
		point = cinder::gl::getModelView() * point;
		pt3.x = point.x;
		pt3.y = point.y;

		// Now, convert back to window coordinates
		center = InterfaceUtil::worldToWindow(center);
		pt1 = InterfaceUtil::worldToWindow(pt1);
		pt2 = InterfaceUtil::worldToWindow(pt2);
		pt3 = InterfaceUtil::worldToWindow(pt3);

		cinder::gl::popModelView();
	}
}