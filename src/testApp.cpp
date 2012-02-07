#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofBackground(255, 255, 255);
    
    bArduinoInitialized = false;
    
    arduino.connect("tty.usbserial-A900abz9", 57600);
    ofAddListener(arduino.EInitialized, this, &testApp::onArduinoInitialized);
    
    control.setup("control", 0, 0, 250, 230);
    control.addPanel("RGB LED Control", 4, false);
    control.setupEvents();
    control.enableEvents();
}

//--------------------------------------------------------------
void testApp::update()
{
    arduino.update();
    
    if (bArduinoInitialized)
    {
        colors[0] = control.getValueI("redValue");
        colors[2] = control.getValueI("greenValue");
        colors[1] = control.getValueI("blueValue");
        
        for (int i = 0; i < 3; i++)
        {
            arduino.sendPwm(9 + i, colors[i]);
        }
    }
}

//--------------------------------------------------------------
void testApp::draw()
{
    control.draw();
}

//--------------------------------------------------------------
void testApp::onArduinoInitialized(const int &version)
{
    ofAddListener(arduino.EInitialized, this, &testApp::onArduinoInitialized);
    
    cout << "Arduino initialized! version: " << version << endl;
    
    control.addSlider("Red value", "redValue", 0, 0, 255, true);
    control.addSlider("Green value", "greenValue", 0, 0, 255, true);
    control.addSlider("Blue value", "blueValue", 0, 0, 255, true);
    
    arduino.sendDigitalPinMode(9, ARD_PWM);
    arduino.sendDigitalPinMode(10, ARD_PWM);
    arduino.sendDigitalPinMode(11, ARD_PWM);
    
    bArduinoInitialized = true;
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

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
    control.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
    control.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{
    control.mouseReleased();
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}