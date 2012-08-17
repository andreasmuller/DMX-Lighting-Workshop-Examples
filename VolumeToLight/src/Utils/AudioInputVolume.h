#pragma once

#include "ofMain.h"

// This is basically just the code from the openFrameworks 
// audioInputExample packaged up into an object for convenience

//--------------------------------------------------------------
class AudioInputVolume 
{
	public:
	
		AudioInputVolume();
	
		void 			init( int _bufferSize );
		void 			draw();
	
		void 			audioIn(float * input, int bufferSize, int nChannels);
			
		float 			smoothedVol;
		float 			scaledVol;
			
	private:

		void 			updateVolume();

		vector <float> 	left;
		vector <float> 	right;
		vector <float> 	volHistory;
	
		int				volumeHistoryLength;
		
		int 			bufferCounter;
		int 			drawCounter;

		ofSoundStream 	soundStream;		
};
