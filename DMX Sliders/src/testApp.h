#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "Utils/DmxPro.h"


#define SLIDER_AMOUNT 4

class testApp : public ofBaseApp 
{
	public:
	
	void 			setup();
	void 			update();
	void 			draw();

	ofParameter<int> sliderValues[SLIDER_AMOUNT];

	int 			dmxPacketLength;
	unsigned char* 	dmxPacket;

	DmxPro 			dmxOut;

	ofxPanel		gui;
	
};
