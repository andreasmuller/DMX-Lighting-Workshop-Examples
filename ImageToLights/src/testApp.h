#pragma once

#include "ofMain.h"

#include "Utils/DmxPro.h"

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
class testApp : public ofBaseApp
{
	
	public:
		
		void setup();
		void update();
		void draw();
	
		void changeImage( string _path );
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		
		
		ofImage 		currentImage;
		unsigned char* 	currentImagePixels;
	
		int 			rgbLightAmount;
		ofColor* 		colors;
	
		int				dmxPacketLength;	
		unsigned char*	dmxPacket;
	
		DmxPro 			dmxOut;
	
		int 			mouseX;
		int 			mouseY;	
	
};

