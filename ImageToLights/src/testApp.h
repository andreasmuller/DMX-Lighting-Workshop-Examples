#pragma once

#include "ofMain.h"

#include "Utils/DmxPro.h"

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
class testApp : public ofBaseApp
{
	
	public:
		
		void 			setup();
		void 			update();
		void 			draw();
	
		void 			changeImage( string _path );
		
		void 			mouseMoved(int x, int y );
		void 			dragEvent(ofDragInfo dragInfo);

		ofImage 		currentImage;
		unsigned char* 	currentImagePixels;
	
		int 			rgbLightAmount;
		ofColor* 		colors;
	
		int				dmxChannelAmount;	
		unsigned char*	dmxPacket;
	
		DmxPro 			dmxOut;
	
		int 			mouseX;
		int 			mouseY;	
};

