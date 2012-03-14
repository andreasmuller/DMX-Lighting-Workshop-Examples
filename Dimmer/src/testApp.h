#ifndef TESTAPP
#define TESTAPP

#include "ofMain.h"
#include "Utils/DmxPro.h"

#define DIMMER_POINT_AMOUNT 4

class testApp : public ofBaseApp 
{
	public:
	
		void 			setup();
		void 			update();
		void 			draw();
		void 			exit(); 

		void 			keyPressed  (int key);
		void 			keyReleased(int key);
		void 			mouseMoved(int x, int y );
		void 			mouseDragged(int x, int y, int button);
		void 			mousePressed(int x, int y, int button);
		void 			mouseReleased(int x, int y, int button);
		void 			windowResized(int w, int h);
		void 			dragEvent(ofDragInfo dragInfo);
		void 			gotMessage(ofMessage msg);
		
		int 			dmxChannelAmount;
		unsigned char* 	dmxPacket;

		ofPoint 		dimmerPointPositions[DIMMER_POINT_AMOUNT];
		float 			dimmerPointIntensity[DIMMER_POINT_AMOUNT];
		float 			dimmerPointAffectionRadius;
		
		DmxPro 			dmxOut;

		int 			mouseX, mouseY;
};

#endif