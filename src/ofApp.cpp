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


}

//--------------------------------------------------------------
void ofApp::draw(){
  // APP GENERAL
  ofBackground(colorF);
  ofSetColor(255);
  ofSetWindowTitle("BUFABLAU running at " + ofToString((int)ofGetFrameRate()) + " frames per second");

  // TROMPETAS

  // BOTONES
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  // TEST BOTONES
  if(key == '0'){
    botones[0] = !botones[0];
  }
  else if(key == '1'){
    botones[1] = !botones[1];
  }
  else if(key == '2'){
    botones[2] = !botones[2];
  }
  else if(key == '3'){
    botones[3] = !botones[3];
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
