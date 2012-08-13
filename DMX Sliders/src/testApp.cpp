#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetVerticalSync(true); 
	ofEnableSmoothing(); 
    	
	initSliders16();	
	initSliders48();	
    
	// the maximum amount of sliders we'll make + 1 as DMX channels start at address 1
	dmxPacketLength = 48 + 1;
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
	
	showGUI( 0 );
	
	ofBackground(233, 27, 52); 
}

//--------------------------------------------------------------
void testApp::update()
{
	
	dmxOut.sendLevels( dmxPacket, dmxPacketLength );
}

//--------------------------------------------------------------
void testApp::draw()
{    

}

//--------------------------------------------------------------
void testApp::showGUI( int _num )
{
	if( _num == 0 )
	{
		guiSliders16->enable();
		guiSliders48->disable();
	}
	else if( _num == 1 )
	{
		guiSliders16->disable();		
		guiSliders48->enable();
	}
	else if( _num == 2 )
	{
		guiSliders16->disable();
		guiSliders48->disable();
	}	
}

//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 
	
	// this is a bit hacky, but use the name of the widget, which we set to just a number
	// convert it from a string to a number, that gives us the channel, then pop the value 
	// from the widget in there.
	
	int channel = (int)ofToFloat( name );
	int value = 0;
	
	if( kind == OFX_UI_WIDGET_SLIDER_V )
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		value = slider->getScaledValue(); 
	}
	else if( kind == OFX_UI_WIDGET_ROTARYSLIDER )
	{
		ofxUIRotarySlider *rotarySlider = (ofxUIRotarySlider *) e.widget; 
		value = rotarySlider->getScaledValue(); 	
	}
	
	dmxPacket[ channel ] = value;
	
	cout << "channel: " << channel << " value: " << value << endl;
}

//--------------------------------------------------------------
void testApp::initSliders16()
{
	guiSliders16 = new ofxUICanvas(0,0,/*length+xInit*/ ofGetWidth(),ofGetHeight());     	
    //guiSliders16->addWidgetDown(new ofxUILabel("SLIDER WIDGETS", OFX_UI_FONT_LARGE)); 		

	int sliderAmount = 16;
	float sliderWidth = 20;	
	float sliderHeight = 200;	
	
	for( int i = 0; i < sliderAmount; i++ )
	{
		bool down = false;
		
		if( i == 0 ) down = true;
		
		if( down )
		{
			guiSliders16->addWidgetDown(new ofxUISlider(sliderWidth,sliderHeight, 0.0, 255.0, 0, ofToString(i+1) ));
		}
		else
		{
			guiSliders16->addWidgetRight(new ofxUISlider(sliderWidth,sliderHeight, 0.0, 255.0, 0, ofToString(i+1) ));
		}
	}	
	
	ofAddListener(guiSliders16->newGUIEvent,this,&testApp::guiEvent);			
}

//--------------------------------------------------------------
void testApp::initSliders48()
{
	guiSliders48 = new ofxUICanvas(0,0,/*length+xInit*/ ofGetWidth(),ofGetHeight());     
	
    //guiSliders48->addWidgetDown(new ofxUILabel("SLIDER WIDGETS", OFX_UI_FONT_LARGE)); 	
	
	int sliderAmount = 48;
	float sliderWidth = 70;

	
	for( int i = 0; i < sliderAmount; i++ )
	{
		bool down = false;
		
		if( i == 0 ) down = true;
		if( i % 10 == 0 ) down = true;
		
		if( down )
		{
			//guiSliders48->addWidgetDown(new ofxUISlider(sliderWidth,sliderHeight, 0.0, 255.0, 0, /*ofToString(i)*/ "000" ));
			guiSliders48->addWidgetDown(new ofxUIRotarySlider( 90.0f, 0.0, 255.0, 0, ofToString(i+1))  );
		}
		else
		{
			//guiSliders48->addWidgetRight(new ofxUISlider(sliderWidth,sliderHeight, 0.0, 255.0, 0, /*ofToString(i)*/ "000" ));
			guiSliders48->addWidgetRight(new ofxUIRotarySlider( 90.0f, 0.0, 255.0, 0, ofToString(i+1)) );			
		}
	}	
	
	ofAddListener(guiSliders48->newGUIEvent,this,&testApp::guiEvent);		
	
}



//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
    switch (key) 
    {

		case '1':
        	
			showGUI( 0 );
			
			break;
			
		case '2':
			
			showGUI( 1 );
			
			break;
			
        default:
            break;
    }
}

