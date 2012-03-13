#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetVerticalSync(true); 
	ofEnableSmoothing(); 
    	
    
	dmxPacketLength = 4 + 1; // the maximum amount of sliders we'll make + 1 as DMX channels start at address 1
	dmxPacket = new unsigned char[ dmxPacketLength ];
	for( int i = 0; i < dmxPacketLength; i++ ) { dmxPacket[i] = 0; }
	
	
	string serialPortAddress = "/dev/tty.usbserial-EN079717";
	bool isConnected = dmxOut.connect(serialPortAddress, dmxPacketLength);  
	if( !isConnected )
	{
		ofLogError() << "We failed to connect to " << serialPortAddress << endl;
	}	
	
	
}

//--------------------------------------------------------------
void testApp::update()
{
	int tmpValue = ((sin( ofGetElapsedTimef() ) + 1.0f) / 2.0f) * 255;
	
	ofBackground(tmpValue, tmpValue, tmpValue); 	
	
	for( int i = 0; i < dmxPacketLength; i++ ) { dmxPacket[i] = tmpValue; }
	
	dmxOut.sendLevels( dmxPacket, dmxPacketLength );
}

//--------------------------------------------------------------
void testApp::draw()
{    

}
