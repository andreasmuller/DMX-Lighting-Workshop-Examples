#ifndef TESTAPP
#define TESTAPP

#include "ofMain.h"
#include "Utils/DmxPro.h"


class testApp : public ofBaseApp 
{
	public:
	void setup();
	void update();
	void draw();
	
	int 			dmxPacketLength;
	unsigned char* 	dmxPacket;

	DmxPro 			dmxOut;
	
};

#endif