#pragma once

#include "ofMain.h"
#include "ofxCvHaarFinder.h"
#include "Utils/DmxPro.h"

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
	
		//ofImage img;
		ofxCvHaarFinder finder;
		ofVideoGrabber 		vidGrabber;
	
		ofxCvColorImage img;
    
        int 			dmxChannelAmount;
        unsigned char* 	dmxPacket;
    
        int             panValue;
    
        DmxPro 			dmxOut;
};
