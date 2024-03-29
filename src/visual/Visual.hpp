//
//  Visual.hpp
//  cornetas
//
//  Created by Lolo on 14/07/2019.
//

#ifndef Visual_hpp
#define Visual_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxGui.h"
#include "VSObject.hpp"
#include "VBlobs.hpp"
#include "VStick.hpp"
#include "VTree.hpp"
#include "VBat.hpp"
#include "VPride.hpp"
#include "VDoble.hpp"
#include "VDark.hpp"
#include "VBot.hpp"
#include "ParticleSystem.hpp"

class Visual : public ofxINObject
{
public:
    Visual();
    ~Visual();
    void    setup();
    void    addObject(VSObject *_newObject);
    void    update();
    void    draw();
    
    void    setVal(int _index,float _val);  
    void    buttonBang(int _index);
    void    buttonReset(int _index);
    void    addBackColor(int _hex);
    void    onSimulation(bool &_e);
    void    onGuiLoad();  
    void    onGuiSave();
    bool  drawGui;

private:
    ofxPanel gui;
    //ofParameter<string> fps;
    ofParameter<bool>   simulation;
    bool     loaded;
    vector<VSObject*>   objects;
    //  objects
    VBlobs  blob;
    VStick  stick;
    VBat    bat;
    VPride  pride;
    VDoble  doble;
    VDark   dark;
    VBot    bot;
    VTree   tree;
    
    ofFbo   fbo;
    
    
    ofShader    shader;
    vector<ofFloatColor>    backgroundColors;
    ofFloatColor    backColor;
    int next = 0;
    int     colorIndex;
    int     colorNextIndex;
    
    float   waveMix;
    
    ParticleSystem  particles;
    
    float   pMix,pDMix;
    
    ofImage imgNoise;
};

#endif /* Visual_hpp */
