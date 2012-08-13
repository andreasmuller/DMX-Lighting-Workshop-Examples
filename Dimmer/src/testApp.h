#ifndef TESTAPP
#define TESTAPP

#include "ofMain.h"
#include "Utils/DmxPro.h"

#define DIMMER_POINT_AMOUNT 4

//--------------------------------------------------------------
class testApp : public ofBaseApp 
{
	public:
	
		void 			setup();
		void 			update();
		void 			draw();

		void 			mouseMoved(int x, int y );
		
		int 			dmxChannelAmount;
		unsigned char* 	dmxPacket;

		ofPoint 		dimmerPointPositions[DIMMER_POINT_AMOUNT];
		float 			dimmerPointIntensity[DIMMER_POINT_AMOUNT];
		float 			dimmerPointAffectionRadius;
		
		DmxPro 			dmxOut;

		int 			mouseX, mouseY;
};

#endif