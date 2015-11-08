
#include "GraphyApp.h"

GraphyApp::GraphyApp()
{

}

void GraphyApp::prepareSettings(Settings *settings)
{
	settings->setWindowSize(1024, 768);
	settings->setFrameRate((float) Graphy_App::InterfaceUtil::FPS);
}

void GraphyApp::setup()
{
	normalCursor = LoadCursor(NULL, MAKEINTRESOURCE(32512));
	handCursor = LoadCursor(NULL, MAKEINTRESOURCE(32649));

	panel = Graphy_App::Panel(Vec2f(50.0f, 50.0f), 100, 25, Color(0.9686f, 0.5961f, 0.1216f), false);
	panel.addLineItem(Graphy_App::LineItem::BUTTON, "Button");
	panel.addLineItem(Graphy_App::LineItem::BUTTON, "Button1");
	panel.addLineItem(Graphy_App::LineItem::BUTTON, "Button2");
	panel.addLineItem(Graphy_App::LineItem::BUTTON, "Button3");
	panel.addLineItem(Graphy_App::LineItem::BUTTON, "Button4");
	panel.addLineItem(Graphy_App::LineItem::BUTTON, "Button5");
	panel.addLineItem(Graphy_App::LineItem::BUTTON, "Button6");
}

void GraphyApp::update()
{
	panel.update();
}

void GraphyApp::draw()
{
	gl::clear(Color(0, 0, 0), true);
	glDisable(GL_TEXTURE_2D);

	panel.draw();

	//gl::color(Color(1.0f, 1.0f, 1.0f));

	// test
	//gl::drawSolidTriangle(Vec2f(500.0f, 500.0f), Vec2f(510.0f, 500.0f), Vec2f(505.0f, 510.0f));

	/*gl::color(Color(1.0f, 1.0f, 1.0f));

	gl::drawSolidCircle(Vec2f(500.0f, 300.0f), 10.0f);*/
}

void GraphyApp::mouseDown(MouseEvent me)
{
	Vec2i pos = me.getPos();

	if (me.isLeft())
	{
		panel.checkClick(Vec2f(pos.x, pos.y));
	}
}

void GraphyApp::mouseUp(MouseEvent me)
{

}

void GraphyApp::mouseMove(MouseEvent me)
{
	Vec2i pos = me.getPos();
	if (panel.checkHover(Vec2f(pos.x, pos.y)))
	{
		::SetCursor(handCursor);
	}
	else
	{
		::SetCursor(normalCursor);
	}
}

void GraphyApp::receiveLineItemEvent(const Graphy_App::LineItem& eventItem)
{
	// poop
}

CINDER_APP_BASIC(GraphyApp, RendererGl)