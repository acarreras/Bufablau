//
//  VStick.hpp
//  cornetas
//
//  Created by Lolo on 15/07/2019.
//

#ifndef VStick_hpp
#define VStick_hpp

#include <stdio.h>
#include "ofMain.h"
#include "VSObject.hpp"
#include "VUtils.h"

class VStick : public VSObject
{
public:
    VStick();
    ~VStick();
    void    create(int _res,float _height,float _dir,float _easing = 10.0);
    void    follow(float _x,float _h);
    
    void    customSetup();
    void    customUpdate();
    void    customDraw();
    void    updatePointStick();
    void    addArm(float _heightPercent,float _lon,float _angle,float _easing);
    
    
    //void    customDraw();
    
    virtual void    setupStick(){};
    virtual void    renderStick(){};
    virtual void    preUpdate(){};
    virtual void    updateStick(){};
    
    vector<VerletStick*>    bodySticks;
    vector<VerletStick*>    armSticks;
protected:
    int     resolution;
    
    vector<VerletPoint> points;
    vector<VerletStick> sticks;
    

    ofParameter<float>      particlesThreshold;

    ofParameter<float>      oscTimeMul;
    ofParameter<float>      oscYOffset;
    ofParameter<glm::vec2>  oscRad;
    ofParameter<glm::vec2>  oscFreq;
    ofParameterGroup        oscParams;
    ofParameter<ofFloatColor>   mainTint;

    float       height;
    float       easing;
    
    VerletPoint *head;
    
    float       headY;
    
    
    float an;
    float dan;
    float       growDir;
    glm::vec2    target;
    glm::vec2   base;
    glm::vec2   acel;
    VSegment    segment;
    VSegment    segment2;

    
};

#endif /* VStick_hpp */
