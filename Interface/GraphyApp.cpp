#include "cinder/app/AppBasic.h"
#include "Expander.h"

using namespace ci;
using namespace ci::app;

class GraphyApp : public AppBasic
{
public:
	GraphyApp();
	void prepareSettings(Settings *settings);
	void setup();
	void update();
	void draw();

	void mouseDown(MouseEvent me);
	void mouseUp(MouseEvent me);

private:
	Graphy_App::Expander exp;
};

GraphyApp::GraphyApp()
{

}

void GraphyApp::prepareSettings(Settings *settings)
{
	settings->setWindowSize(1024, 768);
	settings->setFrameRate(60.0f);
}

void GraphyApp::setup()
{
	exp = Graphy_App::Expander(Vec2f(500.0f, 500.0f), 
		ci::Color(1.0f, 0.0f, 0.0f), 10.0f, false);
}

void GraphyApp::update()
{
	exp.update();
}

void GraphyApp::draw()
{
	gl::clear(Color(0, 0, 0), true);
	glDisable(GL_TEXTURE_2D);

	exp.draw();

	//gl::color(Color(1.0f, 1.0f, 1.0f));

	// test
	//gl::drawSolidTriangle(Vec2f(500.0f, 500.0f), Vec2f(510.0f, 500.0f), Vec2f(505.0f, 510.0f));

	/*gl::color(Color(1.0f, 1.0f, 1.0f));

	gl::drawSolidCircle(Vec2f(500.0f, 300.0f), 10.0f);*/
}

void GraphyApp::mouseDown(MouseEvent me)
{
	Vec2i pos = me.getPos();

	exp.checkClick(Vec2f(pos.x, pos.y));
}

void GraphyApp::mouseUp(MouseEvent me)
{

}

CINDER_APP_BASIC(GraphyApp, RendererGl)