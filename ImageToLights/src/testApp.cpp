#include "testApp.h"

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
void testApp::setup()
{
	currentImagePixels = NULL;
	changeImage( "lena.jpg" );
	
	rgbLightAmount = 16;
	colors = new ofColor[rgbLightAmount];
		
	mouseX = 0;
	mouseY = 0;	

	dmxPacketLength  = (rgbLightAmount * 3) +1;							// Room for each light's 3 colors and add one as dmx channels start at 1
	dmxPacket = new unsigned char[dmxPacketLength];
	for( int i = 0; i < dmxPacketLength; i++ ) { dmxPacket[i] = 0; }	// clear it
	
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

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
void testApp::update()
{	
	// Set all colors to black
	for( int i = 0; i < rgbLightAmount; i++ )
	{
		colors[i].set(0,0,0);
	}
	
	if( currentImagePixels == NULL )
	{
		return;	// bail if we don't have any pixels
	}
	
	// Grab the colors under the mouse and to the right, 
	// making sure we don't read past the image width
	
	int currentX = mouseX;
	
	for( unsigned int i = 0; i < rgbLightAmount; i++ )
	{
		if( mouseY >= 0	  && mouseY   < currentImage.getHeight() &&
		    currentX >= 0 && currentX < currentImage.getWidth()  )  
		{
			int pixelIndex = ((mouseY * currentImage.getWidth()) + currentX) * 3; // ((Y * Image Width) + X) * Bytes per pixel
			
			colors[i].r = currentImagePixels[pixelIndex    ];
			colors[i].g = currentImagePixels[pixelIndex + 1];
			colors[i].b = currentImagePixels[pixelIndex + 2];			
			
			currentX++;
		}
	}
	
	
	// Copy from our ofColors to the byte array we use as a DMX packet
	int tmpIndex = 1;
	for( int i = 0; i < rgbLightAmount; i++ )
	{
		dmxPacket[tmpIndex++] = colors[i].r;
		dmxPacket[tmpIndex++] = colors[i].g;
		dmxPacket[tmpIndex++] = colors[i].b;		
	}
	
	dmxOut.sendLevels( dmxPacket, dmxPacketLength );

}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
void testApp::draw()
{	
	// draw the image
	ofSetColor(255);
	currentImage.draw(0, 0);
		
	// Draw a little line showing what pixels we are using
	ofEnableAlphaBlending();
	ofSetColor(255, 255, 255, 60 );
	ofLine( mouseX, mouseY, mouseX + rgbLightAmount, mouseY );
	ofDisableAlphaBlending();
	
	// Draw some circles on screen to show the colors
	for( int i = 0; i < rgbLightAmount; i++ )
	{
		ofSetColor( colors[i] );
		ofCircle( 50.0f + (i * 51.0f), ofGetHeight() - 50.0f, 25.0f );
	}

}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
void testApp::changeImage( string _path )
{
	cout << "Loading an image from: " << _path << endl;

	currentImage.loadImage( _path );
	currentImagePixels = currentImage.getPixels(); // 
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
void testApp::keyPressed  (int key)
{ 	
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
void testApp::keyReleased(int key)
{ 	
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
void testApp::mouseMoved(int x, int y )
{
	mouseX = x;
	mouseY = y;	
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
void testApp::mouseDragged(int x, int y, int button)
{	
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
void testApp::mousePressed(int x, int y, int button)
{	
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
void testApp::mouseReleased(int x, int y, int button)
{
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
void testApp::windowResized(int w, int h)
{
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
void testApp::gotMessage(ofMessage msg)
{
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
void testApp::dragEvent(ofDragInfo dragInfo)
{ 	
	if( dragInfo.files.size() > 0 )
	{
		// We are going to assume you are only dropping images on here.		
		string tmpFilePath = dragInfo.files.at(0);
		changeImage(tmpFilePath);
	}
}
