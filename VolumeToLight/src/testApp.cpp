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
	
	
	
	soundStream.listDevices();
	
	//if you want to set a different device id
	//soundStream.setDeviceID(0); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.
	
	int bufferSize = 256;
	
	left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);
	volHistory.assign(400, 0.0);
	
	bufferCounter	= 0;
	drawCounter		= 0;
	smoothedVol     = 0.0;
	scaledVol		= 0.0;
	
	soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
	
	
}

//--------------------------------------------------------------
void testApp::update()
{
	//lets scale the vol up to a 0-1 range
	scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
	
	//lets record the volume into an array
	volHistory.push_back( scaledVol );
	
	//if we are bigger the the size we want to record - lets drop the oldest value
	if( volHistory.size() >= 400 )
	{
		volHistory.erase(volHistory.begin(), volHistory.begin()+1);
	}
	
	/*
	// Fade a value between 0 and 255
	int tmpValue = ((sin( ofGetElapsedTimef() ) + 1.0f) / 2.0f) * 255;

	// Set the background to that greyscale value to give us some feedback
	ofBackground(tmpValue, tmpValue, tmpValue); 	
	*/

	// Scale the volume to the range 0..255
	int tmpValue = scaledVol * 255;
	
	// Set each of the channels to that value
	for( int i = 0; i < dmxChannelAmount; i++ ) { dmxPacket[i] = tmpValue; }
	
	// Send it to the DMX box
	dmxOut.sendLevels( dmxPacket, dmxChannelAmount );
}


//--------------------------------------------------------------
void testApp::draw()
{
	ofNoFill();
	
	// draw the left channel:
	ofPushStyle();
		ofPushMatrix();
	
			ofTranslate(32, 170, 0);
			
			ofSetColor(225);
			ofDrawBitmapString("Left Channel", 4, 18);
			
			ofSetLineWidth(1);
			ofRect(0, 0, 512, 200);
			
			ofSetColor(245, 58, 135);
			ofSetLineWidth(3);
			
			ofBeginShape();
				for (int i = 0; i < left.size(); i++)
				{
					ofVertex(i*2, 100 -left[i]*180.0f);
				}
			ofEndShape(false);
		
		ofPopMatrix();
	ofPopStyle();
	
	// draw the right channel:
	ofPushStyle();
		ofPushMatrix();
	
			ofTranslate(32, 370, 0);
			
			ofSetColor(225);
			ofDrawBitmapString("Right Channel", 4, 18);
			
			ofSetLineWidth(1);
			ofRect(0, 0, 512, 200);
			
			ofSetColor(245, 58, 135);
			ofSetLineWidth(3);
			
			ofBeginShape();
				for (int i = 0; i < right.size(); i++)
				{
					ofVertex(i*2, 100 -right[i]*180.0f);
				}
			ofEndShape(false);
		
		ofPopMatrix();
	ofPopStyle();
	
	// draw the average volume:
	ofPushStyle();
		ofPushMatrix();
			ofTranslate(565, 170, 0);
			
			ofSetColor(225);
			ofDrawBitmapString("Scaled average vol (0-100): " + ofToString(scaledVol * 100.0, 0), 4, 18);
			ofRect(0, 0, 400, 400);
			
			ofSetColor(245, 58, 135);
			ofFill();
			ofCircle(200, 200, scaledVol * 190.0f);
			
			//lets draw the volume history as a graph
			ofBeginShape();
				for (int i = 0; i < volHistory.size(); i++)
				{
					if( i == 0 ) ofVertex(i, 400);
					
					ofVertex(i, 400 - volHistory[i] * 70);
					
					if( i == volHistory.size() -1 ) ofVertex(i, 400);
				}
			ofEndShape(false);
		
		ofPopMatrix();
	ofPopStyle();
}


//--------------------------------------------------------------
void testApp::audioIn(float * input, int bufferSize, int nChannels){
	
	float curVol = 0.0;
	
	// samples are "interleaved"
	int numCounted = 0;
	
	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume
	for (int i = 0; i < bufferSize; i++)
	{
		left[i]		= input[i*2]*0.5;
		right[i]	= input[i*2+1]*0.5;
		
		curVol += left[i] * left[i];
		curVol += right[i] * right[i];
		
		numCounted+=2;
	}
	
	//this is how we get the mean of rms :)
	curVol /= (float)numCounted;
	
	// this is how we get the root of rms :)
	curVol = sqrt( curVol );
	
	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;
	
	bufferCounter++;
	
}
