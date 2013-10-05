
#include "testApp.h"
#include "Utils/DmxPro.h"

//--------------------------------------------------------------
void testApp::setup()
{
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(320,240);
	
	//img.allocate(640, 480 );
	img.allocate( 320, 240 );
	
	finder.setup("haarcascade_frontalface_default.xml");
	//finder.findHaarObjects(img);
    
    panValue = 0;
    
	// The maximum amount of lights + 1 as DMX channels start at address 1
	dmxChannelAmount = 12 + 1;
    
    // Allocate some space for the DMX packet
	dmxPacket = new unsigned char[ dmxChannelAmount ];
	
	// Make sure they start at 0
	for( int i = 0; i < dmxChannelAmount; i++ ) { dmxPacket[i] = 0; }
	
	// Set the address, depending on whether we are on OSX or Windows,
	// the adddress might be different on your machine!
#ifdef TARGET_WIN32
    string serialPortAddress = "COM3";
#else
    string serialPortAddress = "/dev/tty.usbserial-EN099611";
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
	vidGrabber.update();
	bool frameIsNew = vidGrabber.isFrameNew();
    
	if( frameIsNew )
	{
		//img.setFromPixels( vidGrabber.getPixels() );
		img.setFromPixels(vidGrabber.getPixels(), 320,240);
		
		finder.findHaarObjects( img.getPixelsRef() );
        
        if( finder.blobs.size() > 0 )
        {
            ofRectangle cur = finder.blobs[0].boundingRect;
            float tmpFaceX = cur.x + (cur.width * 0.5f);
            float tmpFaceNormalized = ofMap( tmpFaceX, 0, 320, 0, 1 );
            
            panValue = (int)(tmpFaceNormalized * 100);
            
        }
	}
   
    //cout << tmpFaceNormalized << endl;
    int panChannel = 2;
    dmxPacket[panChannel+1] = panValue;
    
    // Send it to the DMX box
    dmxOut.sendLevels( dmxPacket, dmxChannelAmount );
   
	
}

//--------------------------------------------------------------
void testApp::draw()
{
	img.draw(0, 0);
	ofNoFill();

	for(unsigned int i = 0; i < finder.blobs.size(); i++)
	{
		ofRectangle cur = finder.blobs[i].boundingRect;
		ofRect(cur.x, cur.y, cur.width, cur.height);
	}
    

    
}
