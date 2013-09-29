#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetVerticalSync(true); 
	ofEnableSmoothing(); 
    
	// the maximum amount of sliders we'll make + 1 as DMX channels start at address 1
	dmxPacketLength = 16 + 1;
	dmxPacket = new unsigned char[ dmxPacketLength ];
	for( int i = 0; i < dmxPacketLength; i++ ) { dmxPacket[i] = 0; }

	#ifdef TARGET_WIN32
		string serialPortAddress = "COM3";
	#else
		string serialPortAddress = "/dev/tty.usbserial-EN079717";
	#endif

	bool isConnected = dmxOut.connect(serialPortAddress, dmxPacketLength);  
	if( !isConnected )
	{
		ofLogError() << "We failed to connect to " << serialPortAddress << endl;
	}	
	
	gui.setup("DMX Sliders"); 
	for( int i = 0; i < SLIDER_AMOUNT; i++ )
	{
		gui.add( sliderValues[i].set( "Slider" + ofToString(i+1), 0, 0,255 ) );
	}

}

//--------------------------------------------------------------
void testApp::update()
{
	for(int i = 0; i < SLIDER_AMOUNT; i++ )
	{
		dmxPacket[i+1] = sliderValues[i];
	}

	dmxOut.sendLevels( dmxPacket, dmxPacketLength );
}

//--------------------------------------------------------------
void testApp::draw()
{    
	gui.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
    switch (key) 
    {
		case '1':
			break;

        default:
            break;
    }
}

