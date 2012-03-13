#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetVerticalSync(true); 
	ofEnableSmoothing(); 
    	
	dmxPacketLength = 4 + 1; // the maximum amount of sliders we'll make + 1 as DMX channels start at address 1
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