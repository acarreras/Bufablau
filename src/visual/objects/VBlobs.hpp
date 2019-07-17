//
//  VBlobs.hpp
//  cornetas
//
//  Created by Lolo on 14/07/2019.
//

#ifndef VBlobs_hpp
#define VBlobs_hpp

#include <stdio.h>
#include "VSObject.hpp"

class VBlobs : public VSObject
{
public:
    VBlobs();
    ~VBlobs();
    void    customSetup();
    void    customUpdate();
    void    customDraw();
private:
    ofPath  path;
    int     segments;
    float   cVal;
    float   cVel;
    float   noiseVel;
    
    float   friction;
    float   easing;
    
    
    ofParameter<float>  noiseMax;
    ofParameter<float>  radius;
    ofParameter<float>  radiusMult;
    ofParameter<float>  timeMult;
    ofParameter<ofFloatColor>   tint;

};

#endif /* VBlobs_hpp */
