#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	ofBackground(0, 0, 0);	
	
	ofSetCircleResolution( 50 ); // nicer circles
	
	dmxChannelAmount = DIMMER_POINT_AMOUNT + 1; // the maximum amount of sliders we'll make + 1 as DMX channels start at address 1
	
	dmxPacket = new unsigned char[ dmxChannelAmount ];
	for( int i = 0; i < dmxChannelAmount; i++ ) { dmxPacket[i] = 0; }
	
	// Set the address, depending on whether we are on OSX or Windows, this might be different on your machine!
#ifdef TARGET_WIN32
	string serialPortAddress = "COM3";
#else
	string serialPortAddress = "/dev/tty.usbserial-EN079717";
#endif
	
	//Try to connect to that address, also give it the amount of channels we will be using
	bool isConnected = dmxOut.connect(serialPortAddress, dmxChannelAmount );  
	
	// Output an error to the console if we fail
	if( !isConnected )
	{
		ofLogError() << "We failed to connect to " << serialPortAddress << endl;
	}

	// Zero out the intensities
	for( int i = 0; i < DIMMER_POINT_AMOUNT; i++ ) { dimmerPointIntensity[i] = 0.0f; }
	
	// Place the points
	dimmerPointPositions[0].set( ofGetWidth() * 0.25f, ofGetHeight() * 0.25f );
	dimmerPointPositions[1].set( ofGetWidth() * 0.75f, ofGetHeight() * 0.25f );
	dimmerPointPositions[2].set( ofGetWidth() * 0.25f, ofGetHeight() * 0.75f );
	dimmerPointPositions[3].set( ofGetWidth() * 0.75f, ofGetHeight() * 0.75f );
	
	// This is the maximum radius around the points that we are interested in
	dimmerPointAffectionRadius = 160.0f;
	
	mouseX = 0;
	mouseY = 0;
	
}

//--------------------------------------------------------------
void testApp::update()
{
	
	// Check the distance to each point, if we are under 'dimmerPointAffectionRadius'
	// then adjust intensity of the light accordingly
	
	for( int i = 0; i < DIMMER_POINT_AMOUNT; i++ ) 
	{ 
		ofVec2f tmpDifference = ofVec2f( mouseX, mouseY ) - dimmerPointPositions[i];
		
		float tmpDistance = tmpDifference.length();
		
		if( tmpDistance <= dimmerPointAffectionRadius )
		{
			dimmerPointIntensity[i] = 1.0f - (tmpDistance / dimmerPointAffectionRadius); 
		}
		else 
		{
			dimmerPointIntensity[i] = 0.0f; 			
		}

	}

	// fill in the values in the DMX packet
	for( int i = 0; i < DIMMER_POINT_AMOUNT; i++ ) 
	{ 
		dmxPacket[i+1] = dimmerPointIntensity[i] * 255;
	}
	
	// send the packet out to the DMX box
	dmxOut.sendLevels( dmxPacket, dmxChannelAmount );
}

//--------------------------------------------------------------
void testApp::draw()
{    

	for( int i = 0; i < DIMMER_POINT_AMOUNT; i++ )
	{
		ofSetColor( 255, 255, 255 );
		
		ofFill();

		// ofSetColor( int ) is a shortcut for setting a greyscale color
		ofSetColor( dimmerPointIntensity[i] * 255 ); 		
		ofCircle( dimmerPointPositions[i].x, dimmerPointPositions[i].y, dimmerPointAffectionRadius );		
		
		ofSetColor( 255, 255, 255 );
		ofNoFill();
		ofCircle( dimmerPointPositions[i].x, dimmerPointPositions[i].y, dimmerPointAffectionRadius );		

		ofFill();		
		ofCircle( dimmerPointPositions[i].x, dimmerPointPositions[i].y, 2.0f );		
	}
	
	ofFill(); // set fill mode back
}


//--------------------------------------------------------------
void testApp::exit()
{

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
//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y )
{ 
	mouseX = x;
	mouseY = y;	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{
 
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{
 

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}