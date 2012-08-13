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

	void 			showGUI( int _num );
	
	void 			initSliders16();	
	void 			initSliders48();	
	
	void 			keyPressed  (int key);

	void 			guiEvent(ofxUIEventArgs &e);	
	
	ofxUICanvas* 	guiSliders16;   	
	ofxUICanvas* 	guiSliders48;   	
	
	int 			dmxPacketLength;
	unsigned char* 	dmxPacket;

	DmxPro 			dmxOut;
	
};

#endif