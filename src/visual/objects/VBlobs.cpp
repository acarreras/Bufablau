//
//  VBlobs.cpp
//  cornetas
//
//  Created by Lolo on 14/07/2019.
//

#include "VBlobs.hpp"

VBlobs::VBlobs()
{
    noiseVel = 0.0;
}

VBlobs::~VBlobs()
{
    
}

void    VBlobs::customSetup()
{
    segments = 32;
    radius = 150.0f;
    friction = 0.65f;
    easing = 0.15f;
    cVal = 0.0f;
    cVel = 0.0f;
    
    params.add(radius.set("Radius",50,10,200));
    params.add(radiusMult.set("Radius Mul",1.5f,1.1f,3.0f));
    params.add(noiseMax.set("Noise Max",.1,0.0,10.0));
    params.add(timeMult.set("Time Mul",1.0,0.0,10.0));
    params.add(tint.set("Color",ofFloatColor(1,0,0),ofFloatColor(0),ofFloatColor(1)));
    
}

void    VBlobs::customUpdate()
{
    
    /*
    cVel+=(val-cVal)*easing;
    cVel*=friction;
    cVal+=cVel;*/
    
    cVal+=(val-cVal)*easing;
    
    
    noiseVel+=ofLerp(0.0,.010f,cVal);
    
    
    path.clear();
    
    float   time = ofGetElapsedTimef()/10.0f;
    float   fx;
    float   fy;
    
    path.setPolyWindingMode(OF_POLY_WINDING_NONZERO);
    
    for(int i=0;i<segments;i++)
    {
        float delta = i/(float)(segments-2);
        float angle = delta*TWO_PI;
        float noiseVal = ofLerp(noiseMax*.5,noiseMax,cVal);
        float xoff = ofMap(cos(angle),-1.0,1.0,0,noiseVal,true);
        float yoff = ofMap(sin(angle),-1.0,1.0,0,noiseVal,true);
        
        float noise = ofNoise(xoff,yoff,noiseVel);
        
        float finalRadius = ofMap(noise,0.0,1.0,radius,radius*ofLerp(radiusMult*.2,radiusMult,cVal));
        
        float x = cos(time+angle)*finalRadius;
        float y = sin(time+angle)*finalRadius;
    
        if(i == 0){
            path.curveTo(x, y);
            fx = x;
            fy = y;
        }else{
            path.curveTo(x, y);
            
            
            if(i == segments-1)
            {
                path.curveTo(fx, fy);
            }
       
        }
    }

    path.close();
    
  
    
    
    
    
    
    
    
}

void    VBlobs::customDraw()
{
    
    
    float   time = ofGetElapsedTimef()*.8f;
    float   rad = 20.0;
    float   ex = cos(time)*ofLerp(rad*.1,rad,ofNoise(time*1.2));
    float   ey = sin(time)*ofLerp(rad*.1,rad,ofNoise(time*1.2));
    ofFloatColor    darker = tint;
    darker.setBrightness(tint.get().getBrightness()*.8);
    

    ofPushMatrix();
    ofTranslate(x,y);
    ofTranslate(ex,ey);

    path.setStrokeWidth(0.0);
    path.setFilled(true);
    path.setFillColor(darker);
    
    
    ofTranslate(cos(time*.5)*5, sin(time*.5)*5);
    
    path.scale(1.1, 1.1);
    path.draw();
    
    path.scale(.9,.9);
    path.setFillColor(tint.get());
    path.draw();

    
    
    
    ofPopMatrix();

    
    
}
