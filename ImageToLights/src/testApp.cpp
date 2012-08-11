#include "testApp.h"

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
void testApp::setup()
{
	
	// set this to NULL so we can check for that
	currentImagePixels = NULL;
	
	// Start with an image
	changeImage( "color-spectrum.jpeg" );
	
	
	rgbLightAmount = 16;
	
	// allocate the right amount of color objects
	colors = new ofColor[rgbLightAmount];
		
	mouseX = 0;
	mouseY = 0;	

	// How many DMX channels we need to address, each 'pixel' needs 3 channels
	// and we add 1 as arrays start with 0 but DMX channels start with 1
	dmxChannelAmount  = (rgbLightAmount * 3) + 1;		
	
	// allocate enough bytes for all the DMX channels we want and also start them at 0
	dmxPacket = new unsigned char[dmxChannelAmount];
	for( int i = 0; i < dmxChannelAmount; i++ ) { dmxPacket[i] = 0; }	// clear it
	
	// Set the address, depending on whether we are on OSX or Windows,
	// this might be different on your machine!
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
			// ((Y position * Image Width) + X position) * Bytes per pixel
			int pixelIndex = ((mouseY * currentImage.getWidth()) + currentX) * 3;
			
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
	
	// Send them channel values to the DMX box
	dmxOut.sendLevels( dmxPacket, dmxChannelAmount );
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
	
	// grab the pixels here so we don't need to do it each frame
	currentImagePixels = currentImage.getPixels(); // 
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

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
void testApp::mouseMoved(int x, int y )
{
	mouseX = x;
	mouseY = y;	
}
