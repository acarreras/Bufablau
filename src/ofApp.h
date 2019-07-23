#pragma once

#include "ofMain.h"
// ofxMeshWarp: https://github.com/nariakiiwatani/ofxMeshWarp
#include "ofxMeshWarp.h"
#include "ofxMeshWarpManagedController.h"
#include "Visual.hpp"


#define TOTALB      4 // numero total de botones
#define TOTALT      6 // numero total de treompetas
#define TOTAL_FULLES    20

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
  float appW;
  float appH;

  // WARP
  bool bcontrolerDraw = false;
  std::shared_ptr<ofxMeshWarp> mesh_;
  ofxMeshWarpController controller_;
  ofTexture tex_;

  // BOTONES PULSADORES
  bool botones[TOTALB];

  // TROMPETAS SOPLADORAS
  float trompetas[TOTALT];

  // FULLES
  vector<ofImage> fulles;
  float t;
  float ampli;
  void drawFulles();

  //  VISUAL
  Visual  visual;


};
