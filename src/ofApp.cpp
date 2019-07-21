#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  // APP GENERAL
  brunMode = false; // FALSE para testear TRUE for game
  ofSetVerticalSync(true);
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

  // BOTONES PULSADORES
  for(int i=0; i<TOTALB; i++){
    botones[i] = false;
  }
  // TROMPETAS SOPLADORAS
  for(int i=0; i<TOTALT; i++){
    trompetas[i] = 0.0;
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

  // TROMPETAS
  //  enviar data , el toggle de simulacion tiene que estar apagado
  for(int i=0; i<TOTALT; i++){
    trompetas[i] = ofNoise(i, ofGetElapsedTimef());
  }
  for(int i=0; i<TOTALT; i++){
    visual.setVal(i,trompetas[i]);
  }
  
  visual.update();

  
}

//--------------------------------------------------------------
void ofApp::draw(){
  // APP GENERAL

  // TROMPETAS

  // BOTONES

  //  VISUAL
  
  
  ofBackground(255);
  
  visual.draw();

  ofSetColor(0);
  ofDrawBitmapString(ofToString((int)ofGetFrameRate()) + " FPS", 20,20);
  
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
    else if(key == 'g')
    {
      visual.drawGui = !visual.drawGui;
    }
    else if(key == 'c')
    {
      ofShowCursor();
    }
    else if(key == 'u')
    {
      ofHideCursor();
    }
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
