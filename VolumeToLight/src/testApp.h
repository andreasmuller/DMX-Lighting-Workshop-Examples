#ifndef TESTAPP
#define TESTAPP

#include "ofMain.h"
#include "Utils/DmxPro.h"

//--------------------------------------------------------------
class testApp : public ofBaseApp 
{
	public:
	
		void 			setup();
		void 			update();
		void 			draw();
	
		void 			audioIn(float * input, int bufferSize, int nChannels);
			
		int 			dmxChannelAmount;
		unsigned char* 	dmxPacket;

		DmxPro 			dmxOut;
	
		vector <float> 	left;
		vector <float> 	right;
		vector <float> 	volHistory;
		
		int 			bufferCounter;
		int 			drawCounter;
		
		float 			smoothedVol;
		float 			scaledVol;
		
		ofSoundStream 	soundStream;
	
};

#endif