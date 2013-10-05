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
	

	//string serialPortAddress = "/dev/tty.usbserial-EN079717";
	string serialPortAddress = "/dev/tty.usbserial-EN099611";


	// Try to connect to that address, also give it the amount of channels we will be using
	bool isConnected = dmxOut.connect(serialPortAddress, dmxChannelAmount );  
	
	// Output an error to the console if we fail
	if( !isConnected )
	{
		ofLogError() << "We failed to connect to " << serialPortAddress << endl;
	}	
	
	soundStream.listDevices();
	
	//if you want to set a different device id
	//soundStream.setDeviceID(0); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.
	
	int bufferSize = 256;
	inputVolume.init( bufferSize );
	soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
}

//--------------------------------------------------------------
void testApp::update()
{
	// Scale the volume to the range 0..255
	int tmpValue = inputVolume.scaledVol * 255;
	
	//cout << tmpValue << endl;
	
	// Set each of the channels to that value
	for( int i = 0; i < dmxChannelAmount; i++ ) { dmxPacket[i] = tmpValue; }
	
	//dmxPacket[1] = 255-dmxPacket[1];
	
	// Send it to the DMX box
	dmxOut.sendLevels( dmxPacket, dmxChannelAmount );
}


//--------------------------------------------------------------
void testApp::draw()
{
	inputVolume.draw();
}


//--------------------------------------------------------------
void testApp::audioIn(float * input, int bufferSize, int nChannels){
	
	inputVolume.audioIn(input, bufferSize, nChannels );
}
