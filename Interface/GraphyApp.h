#ifndef _GRAPHYAPP_H_
#define _GRAPHYAPP_H_

#include "cinder/App/AppBasic.h"
#include "LineItem.h"
#include "Panel.h"
#include "InterfaceUtil.h"

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

	void receiveLineItemEvent(const Graphy_App::LineItem& eventItem);

	void mouseDown(MouseEvent me);
	void mouseUp(MouseEvent me);
	void mouseMove(MouseEvent me);
	void mouseDrag(MouseEvent me);
	Graphy_App::Panel panel;
	Graphy_App::Panel panel2;

	HCURSOR normalCursor;
	HCURSOR handCursor;

private:
	float prevMouseX;
	float prevMouseY;
	bool prevMouseSet;
};

#endif