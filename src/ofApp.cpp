#include "ofApp.h"
#include "ofxMeshWarpIO.h"
using namespace std;

//--------------------------------------------------------------
void ofApp::setup(){
  // APP GENERAL
  appW = ofGetWidth();
  appH = ofGetHeight();

  brunMode = true; // FALSE para testear TRUE for game
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
  
  // FULLES
  fulles.reserve(TOTAL_FULLES);
  for(int i=0; i<TOTAL_FULLES; i++){
    ofImage f;
    f.load("fulles/fulla" + ofToString(i+1) + ".png");
    fulles.push_back(f);
  }
  ampli = 8.5;

  // WARP
  tex_.allocate(appW,appH, GL_RGB);
  mesh_ = make_shared<ofxMeshWarp>();
  mesh_->setup(ofRectangle(0, appH, appW,-appH),20,20); // apaño en negativo porque las texturas y los mesh tienen los ejes y girados
                                                        // y la forma correct usando ofDisableArbTex(); no funciona
  mesh_->setUVRect(ofRectangle(0, 0, appW,appH));
  controller_.add(mesh_);
  controller_.disable();

  // COMENTADO PARA DESARROLLO
  // para no deformar con el load de ajuste de warp
  /*
  ofxMeshWarpLoad loader; // load config
  vector<shared_ptr<ofxMeshWarp>> result = loader.load("bufablau.txt");
  if(!result.empty()) {
      controller_.clear();
      mesh_ = result[0];
      controller_.add(mesh_);
  }
  */
}

//--------------------------------------------------------------
void ofApp::update(){
  // WARP
  mesh_->update();

  // FULLES
  t = ofGetElapsedTimef();

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

  // BOTONES

  //  VISUAL
  ofBackground(255);
  visual.draw();

  // FULLES
  drawFulles();

  // WARP
  tex_.loadScreenData(0,0,appW, appH);
  ofBackground(0);

  tex_.bind();
  mesh_->drawMesh();
  // controller_.drawFace();
  tex_.unbind();
  if(bcontrolerDraw) controller_.draw();

  // DEBUG
  if(!brunMode){
    ofSetColor(0);
    ofDrawBitmapString(ofToString((int)ofGetFrameRate()) + " FPS", 20,20);
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if(!brunMode){
    // TEST BOTONES
    if((key == '0')&&(botones[0]==false)){
      botones[0] = true;
      visual.buttonBang(0);
    }
    else if((key == '1')&&(botones[1]==false)){
      botones[1] = true;
      visual.buttonBang(1);
    }
    else if((key == '2')&&(botones[2]==false)){
      botones[2] = true;
      visual.buttonBang(2);
    }
    else if((key == '3')&&(botones[3]==false)){
      botones[3] = true;
      visual.buttonBang(3);
    }
  } // end if brunMode

  if((key == 'g')||(key == 'G')){
    visual.drawGui = !visual.drawGui;
  }
  else if((key == 'c')||(key == 'C')){
    ofShowCursor();
  }
  else if((key == 'u')||(key == 'U')){
    ofHideCursor();
  }
  else if((key == 'f')||(key == 'F')){
    ofToggleFullscreen();
  }
  else if((key == 'e')||(key == 'E')){
    controller_.enable();
  }
  else if((key == 'd')||(key == 'D')){
    controller_.disable();
  }
  else if((key == 'r')||(key == 'R')){
      mesh_->reset(ofRectangle(0, appH, appW, -appH));
      controller_.clear();
      controller_.add(mesh_);
  }
  else if(key == ' '){
    bcontrolerDraw = !bcontrolerDraw;
  }
  else if((key == 's')||(key == 'S')){
    ofxMeshWarpSave saver;
    saver.addMesh(mesh_);
    saver.save("bufablau.txt");
  }
  else if((key == 'l')||(key == 'L')){
    ofxMeshWarpLoad loader;
    vector<shared_ptr<ofxMeshWarp>> result = loader.load("bufablau.txt");
    if(!result.empty()) {
        controller_.clear();
        mesh_ = result[0];
        controller_.add(mesh_);
    }
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
  if(!brunMode){
    // TEST BOTONES
    if(key == '0'){
      botones[0] = false;
      visual.buttonReset(0);
    }
    else if(key == '1'){
      botones[1] = false;
      visual.buttonReset(1);
    }
    else if(key == '2'){
      botones[2] = false;
      visual.buttonReset(2);
    }
    else if(key == '3'){
      botones[3] = false;
      visual.buttonReset(3);
    }
  } // end if brunMode
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
void ofApp::drawFulles(){
  // diseño para 1920 x 1080

  // ramillete dalt esquerra
  ofPushMatrix();
  ofTranslate(205,0);
  ofRotateDeg(ampli*ofNoise(t,1));
  fulles.at(0).draw(-205,0);
  ofPopMatrix();

  ofPushMatrix();
  ofTranslate(161+73,0);
  ofRotateDeg(ampli*ofNoise(t,2));
  fulles.at(1).draw(-73,0);
  ofPopMatrix();

  ofPushMatrix();
  ofTranslate(252+10,0);
  ofRotateDeg(ampli*ofNoise(t,3));
  fulles.at(2).draw(-10,0);
  ofPopMatrix();

  // ramillete dalt mig
  ofPushMatrix();
  ofTranslate(809+155,0);
  ofRotateDeg(ampli*ofNoise(t,4));
  fulles.at(3).draw(-155,-20);
  ofPopMatrix();

  ofPushMatrix();
  ofTranslate(917+83,0);
  ofRotateDeg(ampli*ofNoise(t,5));
  fulles.at(4).draw(-83,0);
  ofPopMatrix();

  ofPushMatrix();
  ofTranslate(1005+18,0);
  ofRotateDeg(ampli*ofNoise(t,6));
  fulles.at(5).draw(-18,0);
  ofPopMatrix();

  // ramillete dalt dreta
  ofPushMatrix();
  ofTranslate(1530+206,0);
  ofRotateDeg(ampli*ofNoise(t,7));
  fulles.at(6).draw(-206,0);
  ofPopMatrix();

  ofPushMatrix();
  ofTranslate(1630+119,0);
  ofRotateDeg(ampli*ofNoise(t,8));
  fulles.at(7).draw(-119,0);
  ofPopMatrix();

  ofPushMatrix();
  ofTranslate(1740+21,0);
  ofRotateDeg(ampli*ofNoise(t,9));
  fulles.at(8).draw(-21,0);
  ofPopMatrix();

  ofPushMatrix();
  ofTranslate(1778,0);
  ofRotateDeg(ampli*ofNoise(t,10));
  fulles.at(9).draw(0,-20);
  ofPopMatrix();

  // ramillete esquerra
  ofPushMatrix();
  ofTranslate(appW,480+19);
  ofRotateDeg(180+ampli*ofNoise(t,11));
  fulles.at(10).draw(0,-19);
  ofPopMatrix();

  ofPushMatrix();
  ofTranslate(appW,451+65);
  ofRotateDeg(180+ampli*ofNoise(t,12));
  fulles.at(11).draw(0,-65);
  ofPopMatrix();


  // ramillete baix dreta
  ofPushMatrix();
  ofTranslate(1373+8,appH);
  ofRotateDeg(ampli*ofNoise(t,13));
  fulles.at(12).draw(-8,-112);
  ofPopMatrix();

  ofPushMatrix();
  ofTranslate(1290+68,appH);
  ofRotateDeg(ampli*ofNoise(t,14));
  fulles.at(13).draw(-68,-298);
  ofPopMatrix();

  ofPushMatrix();
  ofTranslate(1225+96,appH);
  ofRotateDeg(ampli*ofNoise(t,15));
  fulles.at(14).draw(-96,-172);
  ofPopMatrix();

  // ramillete baix esquerra
  ofPushMatrix();
  ofTranslate(612+2,appH);
  ofRotateDeg(ampli*ofNoise(t,16));
  fulles.at(15).draw(-2,-177);
  ofPopMatrix();

  ofPushMatrix();
  ofTranslate(450+133,appH);
  ofRotateDeg(ampli*ofNoise(t,17));
  fulles.at(16).draw(-133,-249);
  ofPopMatrix();

  ofPushMatrix();
  ofTranslate(390+160,appH);
  ofRotateDeg(ampli*ofNoise(t,18));
  fulles.at(17).draw(-160,-134);
  ofPopMatrix();

  // ramillete dreta
  ofPushMatrix();
  ofTranslate(0,719+14);
  ofRotateDeg(ampli*ofNoise(t,19));
  fulles.at(18).draw(0,-14);
  ofPopMatrix();

  ofPushMatrix();
  ofTranslate(0,661+47);
  ofRotateDeg(ampli*ofNoise(t,20));
  fulles.at(19).draw(0,-47);
  ofPopMatrix();
}
