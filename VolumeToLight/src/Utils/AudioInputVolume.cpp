#include "AudioInputVolume.h"

//--------------------------------------------------------------
AudioInputVolume::AudioInputVolume()
{
	volumeHistoryLength = 400;
	
	bufferCounter	= 0;
	drawCounter		= 0;
	smoothedVol     = 0.0;
	scaledVol		= 0.0;
}

//--------------------------------------------------------------
void AudioInputVolume::init( int _bufferSize )
{
	left.assign(  _bufferSize, 0.0 );
	right.assign( _bufferSize, 0.0 );
	volHistory.assign( volumeHistoryLength, 0.0 );
}

//--------------------------------------------------------------
void AudioInputVolume::updateVolume()
{
	//lets scale the vol up to a 0-1 range
	scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
	
	//lets record the volume into an array
	volHistory.push_back( scaledVol );
	
	//if we are bigger the the size we want to record - lets drop the oldest value
	if( volHistory.size() >= volumeHistoryLength )
	{
		volHistory.erase(volHistory.begin(), volHistory.begin()+1);
	}
}


//--------------------------------------------------------------
void AudioInputVolume::draw()
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
void AudioInputVolume::audioIn(float * input, int bufferSize, int nChannels)
{
	float curVol = 0.0;
	
	// samples are "interleaved"
	int numCounted = 0;
	
	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume
	for (int i = 0; i < bufferSize; i++)
	{
		left[i]	 = input[ i*2   ] * 0.5;
		right[i] = input[ i*2+1 ] * 0.5;
		
		curVol += left[i]  * left[i];
		curVol += right[i] * right[i];
		
		numCounted += 2;
	}
	
	//this is how we get the mean of rms :)
	curVol /= (float)numCounted;
	
	// this is how we get the root of rms :)
	curVol = sqrt( curVol );
	
	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;
	
	bufferCounter++;
	
	updateVolume();
	
}
