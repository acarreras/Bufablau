#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  // APP GENERAL
  brunMode = false; // FALSE para testear TRUE for game
  ofSetVerticalSync(true);
  ofSetCircleResolution(300);
  ofTrueTypeFont::setGlobalDpi(72);
  if(brunMode == true){
    ofSetFullscreen(true);
    ofHideCursor();
    ofSetLogLevel(OF_LOG_SILENT);  // OF_LOG_SILENT is a special value which disables all messages
  }
  else{
      ofSetFullscreen(false);
      ofShowCursor();
      ofSetLogLevel(OF_LOG_NOTICE);
      //ofLogToFile("logs/DEBUG" + ofGetTimestampString() + ".txt", true);
  }

  // APP ESTETICA
  colorF = ofColor(0,0,0);
  color1 = ofColor(0,255,255);
  color2 = ofColor(255,128,0);

  // BOTONES PULSADORES
  for(int i=0; i<TOTALB; i++){
    botones[i] = false;
  }
  // TROMPETAS SOPLADORAS
  for(int i=0; i<TOTALT; i++){
    trompetas[i] = 0.0;
  }

  // AUDIO IN TEST
  if(!brunMode){
    bufferSize = 256;
    ofSoundStreamSettings settings;
    auto devices = soundStream.getMatchingDevices("default");
    if(!devices.empty()){
      settings.setInDevice(devices[0]);
    }

    settings.setInListener(this);
    settings.sampleRate = 44100;
    settings.numOutputChannels = 0;
    settings.numInputChannels = 2;
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);
    soundStream.start();

    smoothedVol = 0.0;
    scaledVol = 0.0;

    threshold = 0.01;
  }
  
  
  //  VISUAL
  //  posibles colores de fondo
  visual.addBackColor(0xBCC4DB);
  visual.addBackColor(0xC0A9B0);
  visual.addBackColor(0x7880B5);
  visual.addBackColor(0x6987C9);
  visual.addBackColor(0x6BBAEC);
  
  
  visual.setup();
  ofSetCircleResolution(42);
  
  
}

//--------------------------------------------------------------
void ofApp::update(){
  // FONDO TEST
  if(botones[0] == true){
    colorF = color1;
  }
  else{
    colorF = color2;
  }

  // AUDIO IN TEST
  //lets scale the vol up
  if(smoothedVol < threshold){
    volHistory.clear();
  }
  else{
    scaledVol = ofMap(smoothedVol, 0.0, 1.0, 0.0, 200.0, true);
    scaledThreshold = ofMap(threshold, 0.0, 1.0, 0.0, 200.0, true);

    //lets record the volume into an array
    volHistory.push_back(scaledVol);
  }
  
  visual.update();

  
}

//--------------------------------------------------------------
void ofApp::draw(){
  // APP GENERAL
  ofBackground(colorF);
  ofSetColor(255);
 // ofSetWindowTitle("BUFABLAU running at " + ofToString((int)ofGetFrameRate()) + " frames per second");

  // TROMPETAS

  // BOTONES

  // AUDIO IN
  
  //  VISUAL
  
  
  ofBackground(255);
  
  visual.draw();
  
  //
  
  
  ofBeginShape();
  ofSetColor(255);
  for (unsigned int i=0; i<volHistory.size(); i++){
    if(i == 0) ofVertex(i, ofGetHeight());

    ofVertex(i, ofGetHeight() - volHistory[i]);

    if(i == volHistory.size()-1) ofVertex(i, ofGetHeight());
  }
  ofEndShape(false);
  ofSetColor(255,100,100);
  ofDrawLine(0,ofGetHeight()-scaledThreshold, ofGetWidth(),ofGetHeight()-scaledThreshold);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if(!brunMode){
    // TEST BOTONES
    if(key == '0'){
      botones[0] = !botones[0];
      visual.buttonBang(0);

    }
    else if(key == '1'){
      botones[1] = !botones[1];
      
      visual.buttonBang(1);

      if(botones[1])
      {
        visual.buttonBang(1);
      }else{
        visual.buttonReset(1);
      }
      
      
    }
    else if(key == '2'){
      botones[2] = !botones[2];
      if(botones[2])
      {
        visual.buttonBang(2);
      }else{
        visual.buttonReset(2);
      }
    }
    else if(key == '3'){
      botones[3] = !botones[3];
      if(botones[3])
      {
        visual.buttonBang(3);
      }
    }
  }else if(key == 'g')
  {
    visual.drawGui = !visual.drawGui;
  }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer & input){

  float curVol = 0.0;
  int numCounted = 0;

  //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
  for (size_t i = 0; i < input.getNumFrames(); i++){
    float left = input[i*2]*0.5;
    float right = input[i*2+1]*0.5;

    curVol += left * left;
    curVol += right * right;
    numCounted+=2;
  }

  //this is how we get the mean of rms :)
  curVol /= (float)numCounted;

  // this is how we get the root of rms :)
  curVol = sqrt(curVol);

  smoothedVol *= 0.93;
  smoothedVol += 0.07 * curVol;
}
