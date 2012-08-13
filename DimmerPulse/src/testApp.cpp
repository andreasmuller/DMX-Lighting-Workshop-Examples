#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    	
	// The maximum amount of lights + 1 as DMX channels start at address 1
	dmxChannelAmount = 4 + 1; 
	
	 // Allocate some space for the DMX packet
	dmxPacket = new unsigned char[ dmxChannelAmount ];
	
	// Make sure they start at 0
	for( int i = 0; i < dmxChannelAmount; i++ ) { dmxPacket[i] = 0; }
	
	// Set the address, depending on whether we are on OSX or Windows,
	// this might be different on your machine!
	#ifdef TARGET_WIN32
		string serialPortAddress = "COM3";
	#else
		string serialPortAddress = "/dev/tty.usbserial-EN079717";
	#endif

	// Try to connect to that address, also give it the amount of channels we will be using
	bool isConnected = dmxOut.connect(serialPortAddress, dmxChannelAmount );  
	
	// Output an error to the console if we fail
	if( !isConnected )
	{
		ofLogError() << "We failed to connect to " << serialPortAddress << endl;
	}	
	
	
}

//--------------------------------------------------------------
void testApp::update()
{
	// Fade a value between 0 and 255
	int tmpValue = ((sin( ofGetElapsedTimef() ) + 1.0f) / 2.0f) * 255;

	// Set the background to that greyscale value to give us some feedback
	ofBackground(tmpValue, tmpValue, tmpValue); 	
	
	// Set each of the channels to that value
	for( int i = 0; i < dmxChannelAmount; i++ ) { dmxPacket[i] = tmpValue; }
	
	// Send it to the DMX box
	dmxOut.sendLevels( dmxPacket, dmxChannelAmount );
}
