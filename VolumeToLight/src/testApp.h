#ifndef TESTAPP
#define TESTAPP

#include "ofMain.h"
#include "Utils/DmxPro.h"
#include "Utils/AudioInputVolume.h"

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
	
		ofSoundStream 	soundStream;
		AudioInputVolume inputVolume;
	
};

#endif