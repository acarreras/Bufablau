#pragma once

#include "ofMain.h"

#define TOTALB      4 // numero total de botones
#define TOTALT      6 // numero total de treompetas

class ofApp : public ofBaseApp{

public:
  void setup();
  void update();
  void draw();

  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y );
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void mouseEntered(int x, int y);
  void mouseExited(int x, int y);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);

  // APP
  bool brunMode = false;
  ofColor colorF; // fondo
  ofColor color1;
  ofColor color2;

  // BOTONES PULSADORES
  bool botones[TOTALB];

  // TROMPETAS SOPLADORAS
  float trompetas[TOTALT];

};
