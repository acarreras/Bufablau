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
    
    //ARDUINO
    ofSetVerticalSync(true);
    ofSetFrameRate(60);

    
    buttonState = "digital pin:";
    potValue = "analog pin:";

    ard.connect("/dev/cu.usbmodem1411", 57600);

    ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino    = false;
    
    //arduino gui
    trompetas_gui.setup(); // most of the time you don't need a name
    trompetas_gui.add(trompeta_1_val.setup("trompeta 1", 1, 0, 5));
    trompetas_gui.add(trompeta_2_val.setup("trompeta 2", 1, 0, 5));
    trompetas_gui.add(trompeta_3_val.setup("trompeta 3", 1, 0, 5));
    trompetas_gui.add(trompeta_4_val.setup("trompeta 4", 1, 0, 5));
    trompetas_gui.add(trompeta_5_val.setup("trompeta 5", 1, 0, 5));
    trompetas_gui.add(trompeta_6_val.setup("trompeta 6", 1, 0, 5));
        showGui = false;
    
    //SOUND
    bicho_1.load("sound/bicho_1.wav");
    bicho_2.load("sound/bicho_2.wav");
    bicho_3.load("sound/bicho_3.wav");
    bicho_4.load("sound/bicho_4.wav");
    bicho_5.load("sound/bicho_5.wav");
    bicho_6.load("sound/bicho_6.wav");
}

//--------------------------------------------------------------
void ofApp::update(){
  // WARP
  mesh_->update();

  // FULLES
  t = ofGetElapsedTimef()/5;

  // TROMPETAS
  //  enviar data , el toggle de simulacion tiene que estar apagado
  for(int i=0; i<TOTALT; i++){
   // trompetas[i] = ofNoise(i, ofGetElapsedTimef());
  }
  for(int i=0; i<TOTALT; i++){
    visual.setVal(i,trompetas[i]);
  }
  
  visual.update();
    
// ARDUINO
   updateArduino();
  
}

//------------ arduino firmata --------------

void ofApp::setupArduino(const int & version) {
    
    // remove listener because we don't need it anymore
    ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);
    
    // it is now safe to send commands to the Arduino
    bSetupArduino = true;
    
    // print firmware name and version to the console
    ofLogNotice() << ard.getFirmwareName();
    ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();
    

    // set pins D2 and A5 to digital input
    ard.sendDigitalPinMode(17, ARD_INPUT);
    ard.sendDigitalPinMode(15, ARD_INPUT);
    ard.sendDigitalPinMode(19, ARD_INPUT);
    ard.sendDigitalPinMode(3, ARD_INPUT);
    
    // set pin A0 to analog input
    ard.sendAnalogPinReporting(0, ARD_ANALOG);
    ard.sendAnalogPinReporting(1, ARD_ANALOG);
    ard.sendAnalogPinReporting(2, ARD_ANALOG);
    ard.sendAnalogPinReporting(3, ARD_ANALOG);
    ard.sendAnalogPinReporting(4, ARD_ANALOG);
    ard.sendAnalogPinReporting(5, ARD_ANALOG);

    
    
    // Listen for changes on the digital and analog pins
    ofAddListener(ard.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
    ofAddListener(ard.EAnalogPinChanged, this, &ofApp::analogPinChanged);
}

//--------------------------------------------------------------
void ofApp::updateArduino(){

    ard.update();

    
}



//--------------------------------------------------------------
void ofApp::digitalPinChanged(const int & pinNum) {
    //botones cambian fondo, FALTA UNO
    buttonState = "digital pin: " + ofToString(pinNum) + " = " + ofToString(ard.getDigital(pinNum));
    if(pinNum==15){
        
        if(ard.getDigital(pinNum)==1){
            botones[0] = true;
            visual.buttonBang(0);
        }else{
            botones[0] = false;
            visual.buttonReset(0);
        }
        
        
       
    }else if(pinNum==17){
        if(ard.getDigital(pinNum)==1){
            botones[1] = true;
            visual.buttonBang(1);
        }else{
            botones[1] = false;
            visual.buttonReset(1);
        }
    }else if(pinNum==19){
        if(ard.getDigital(pinNum)==1){
            botones[2] = true;
            visual.buttonBang(2);
        }else{
            botones[2] = false;
            visual.buttonReset(2);
        }
    }else if(pinNum==3){
        if(ard.getDigital(pinNum)==1){
            botones[3] = true;
            visual.buttonBang(3);
        }else{
            botones[3] = false;
            visual.buttonReset(3);
        }
        
    }
}

// analog pin event handler, called whenever an analog pin value has changed

//--------------------------------------------------------------
void ofApp::analogPinChanged(const int & pinNum) {
    // FALTAN TROMPETAS
    potValue = "analog pin: " + ofToString(pinNum) + " = " + ofToString(ard.getAnalog(pinNum));
    
    
    for(int i=0;i<6;i++){
        if(pinNum==i){
            trompetas[i] = ofMap(ard.getAnalog(pinNum),0,3,0,1); 
        }
    }
    
    switch(pinNum){
        case 0:
            if(!bicho_1.isPlaying()){
                bicho_1.play();
            }
            break;
        case 1:
            if(!bicho_2.isPlaying()){
                bicho_2.play();
            }
            break;
        case 2:
            if(!bicho_3.isPlaying()){
                bicho_3.play();
            }
            break;
        case 3:
            if(!bicho_4.isPlaying()){
                bicho_4.play();
            }
            break;
        case 4:
            if(!bicho_5.isPlaying()){
                bicho_5.play();
            }
            break;
        case 5:
            if(!bicho_6.isPlaying()){
                bicho_6.play();
            }
            break;
    }
    
    
        
        
    
}

//------------ arduino --------------

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

    // ARDUINO
    ofSetColor(0);
    if (!bSetupArduino){
        //SI ARDUINO NO ESTÁ READY
      ofDrawBitmapString("arduino not ready...\n", 515, 40);
    } else {
      // ofDrawBitmapString(potValue + "\n" + buttonState, 515, 40);
        
        ofDrawBitmapString(potValue+" "+ofToString(trompetas[2]), 515, 40);
        
    }
    
    
    if(showGui){
        trompetas_gui.draw();
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
    
    if(key == 't'){
        showGui = !showGui;
    }
    if(key == 'm'){
    trompetas_gui.saveToFile("trompetas.xml");
    }
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
