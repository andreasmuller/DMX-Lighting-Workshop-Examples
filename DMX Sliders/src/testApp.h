#ifndef TESTAPP
#define TESTAPP

#include "ofMain.h"
#include "Utils/DmxPro.h"
#include "ofxUI.h"

class testApp : public ofBaseApp 
{
	public:
	
	void 			setup();
	void 			update();
	void 			draw();
	void 			exit(); 

	void 			showGUI( int _num );
	
	void 			initSliders16();	
	void 			initSliders48();	
	
	void 			keyPressed  (int key);
	void 			keyReleased(int key);
	void 			mouseMoved(int x, int y );
	void 			mouseDragged(int x, int y, int button);
	void 			mousePressed(int x, int y, int button);
	void 			mouseReleased(int x, int y, int button);
	void 			windowResized(int w, int h);
	void 			dragEvent(ofDragInfo dragInfo);
	void 			gotMessage(ofMessage msg);

	void 			guiEvent(ofxUIEventArgs &e);	
	
	ofxUICanvas* 	guiSliders16;   	
	ofxUICanvas* 	guiSliders48;   	
	
	int 			dmxPacketLength;
	unsigned char* 	dmxPacket;

	DmxPro 			dmxOut;
	
};

#endif