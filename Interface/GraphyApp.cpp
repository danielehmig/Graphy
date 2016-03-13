
#include "GraphyApp.h"

/* ========================================================
	GraphyApp()
======================================================== */
GraphyApp::GraphyApp()
{

}

/* ========================================================
	prepareSettings(Settings*)
======================================================== */
void GraphyApp::prepareSettings(Settings *settings)
{
	settings->setWindowSize(1024, 768);
	settings->setFrameRate((float) Graphy_App::InterfaceUtil::FPS);
}

/* ========================================================
	setup()
======================================================== */
void GraphyApp::setup()
{
	normalCursor = LoadCursor(NULL, MAKEINTRESOURCE(32512));
	handCursor = LoadCursor(NULL, MAKEINTRESOURCE(32649));

	prevMouseSet = false;

	panel = Graphy_App::Panel(Vec2f(50.0f, 50.0f), 150, 30, Color(0.9686f, 0.5961f, 0.1216f), true);
	panel.addLineItem(Graphy_App::LineItem::BUTTON, "Button");
	
	//panel.addLineItem(Graphy_App::LineItem::BUTTON, "Button2");
	panel.addLineItem(Graphy_App::LineItem::CHECKBOX, "Check Box");
	panel.addLineItem(Graphy_App::LineItem::BUTTON, "Button1");

	panel2 = Graphy_App::Panel(Vec2f(250.0f, 100.0f), 125, 25, Color(0.3f, 0.3f, 0.9f), false);
	panel2.addLineItem(Graphy_App::LineItem::BUTTON, "Button1");
	panel2.addLineItem(Graphy_App::LineItem::BUTTON, "Button2");
	panel2.addLineItem(Graphy_App::LineItem::BUTTON, "Button3");
}

/* ========================================================
	update()
======================================================== */
void GraphyApp::update()
{
	panel.update();
	panel2.update();
}

/* ========================================================
	draw()
======================================================== */
void GraphyApp::draw()
{
	gl::clear(Color(0, 0, 0), true);
	glDisable(GL_TEXTURE_2D);

	panel.draw();
	panel2.draw();

	//gl::color(Color(1.0f, 1.0f, 1.0f));

	// test
	//gl::drawSolidTriangle(Vec2f(500.0f, 500.0f), Vec2f(510.0f, 500.0f), Vec2f(505.0f, 510.0f));

	/*gl::color(Color(1.0f, 1.0f, 1.0f));

	gl::drawSolidCircle(Vec2f(500.0f, 300.0f), 10.0f);*/
}

/* ========================================================
	mouseDown(MouseEvent)
======================================================== */
void GraphyApp::mouseDown(MouseEvent me)
{
	Vec2i pos = me.getPos();

	if (me.isLeft())
	{
		if (panel.checkClick(Vec2f(pos.x, pos.y)))
		{
			panel.setDragging(true);
		}
		else if (panel2.checkClick(Vec2f(pos.x, pos.y)))
		{
			panel2.setDragging(true);
		}
	}
}

/* ========================================================
	mouseUp(MouseEvent)
======================================================== */
void GraphyApp::mouseUp(MouseEvent me)
{
	if (panel.isDragging())
	{
		panel.setDragging(false);
	}
	else if (panel2.isDragging())
	{
		panel2.setDragging(false);
	}
	prevMouseSet = false;
}

/* ========================================================
	mouseMove(MouseEvent)
======================================================== */
void GraphyApp::mouseMove(MouseEvent me)
{
	Vec2i pos = me.getPos();
	
	if (panel.checkHover(Vec2f(pos.x, pos.y)) || panel2.checkHover(Vec2f(pos.x, pos.y)))
	{
		::SetCursor(handCursor);
	}
	else
	{
		::SetCursor(normalCursor);
	}
}

/* ========================================================
	mouseDrag(MouseEvent)
======================================================== */
void GraphyApp::mouseDrag(MouseEvent me)
{
	Vec2i pos = me.getPos();
	float deltaX = 0.0f;
	float deltaY = 0.0f;

	if (prevMouseSet)
	{
		deltaX = pos.x - prevMouseX;
		deltaY = pos.y - prevMouseY;
	}

	bool setPrev = true;

	if (panel.isDragging())
	{
		if (!panel.updatePos(ci::Vec2f(deltaX, deltaY)))
		{
			setPrev = false;
		}
	}
	else if (panel2.isDragging())
	{
		if (!panel2.updatePos(ci::Vec2f(deltaX, deltaY)))
		{
			setPrev = false;
		}
	}

	if (!setPrev)
	{
		prevMouseSet = false;
		int posX = (prevMouseX >= 0 ? (int)(prevMouseX + 0.5f) : (int)(prevMouseX - 0.5f));
		int posY = (prevMouseY >= 0 ? (int)(prevMouseY + 0.5f) : (int)(prevMouseY - 0.5f));
		SetPhysicalCursorPos(posX + ci::app::getWindowPos().x, posY + ci::app::getWindowPos().y);
	}
	else
	{
		prevMouseSet = true;
		prevMouseX = pos.x;
		prevMouseY = pos.y;
	}
}

/* ========================================================
	receiveLineItem(LineItem)
======================================================== */
void GraphyApp::receiveLineItemEvent(const Graphy_App::LineItem& eventItem)
{
	// poop
}

CINDER_APP_BASIC(GraphyApp, RendererGl)