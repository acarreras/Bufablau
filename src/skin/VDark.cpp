//
//  VDark.cpp
//  cornetas
//
//  Created by Lolo on 16/07/2019.
//

#include "VDark.hpp"

VDark::VDark()
{
    
    
}

VDark::~VDark()
{
    
}

void    VDark::setupStick()
{
    
  
    baseWidth = 60;

    headWidth = 20;
    
    for(int i=0;i<bodySticks.size();i++){
        float delta = i/(float)bodySticks.size();
        bodySticks.at(i)->setWidth(ofLerp(baseWidth,headWidth,delta));
    }
    
    
    addArm(.8,100,90,1.2);
    
    particles.setup(20);
    
    headWidth = 60;
    
  /*  for(int i=0;i<bodySticks.size();i++){
        float delta = i/(float)bodySticks.size();
        bodySticks.at(i)->setWidth(headWidth);
    }*/
    
    
    
    
    
}

void    VDark::preUpdate()
{
    
    
}

void    VDark::updateStick()
{

    for(int i=0;i<particles.size();i++)
    {
        
        Particle *p = particles.at(i);
        
        if(p->born)
        {
            
            p->vel+=p->acc;
            p->pos+=p->vel;
            p->pos.y-=.07;
            
            
            p->computeLife();
            
        }else{
            
            float len =glm::length(bodySticks.at(bodySticks.size()-1)->offset);
            if(val > particlesThreshold){
                p->reborn(bodySticks.at(bodySticks.size()-1)->a->x, bodySticks.at(bodySticks.size()-1)->a->y, ofRandom(-.02,.02), ofRandom(.1,.3), ofRandom(39,160));
            }
            
        }
    }
    
}

void    VDark::renderStick()
{
    
    int tot = 10;
    float sW = 40;
    
    for(int i=0;i<tot;i++)
    {
        float posx = ofMap(i, 0, 10, -baseWidth*.8, baseWidth*.8,true);
        float delta = i/(float)tot;
        ofPushMatrix();
        ofTranslate(base.x+posx, -20);
        
        float sinC = sin((ofGetElapsedTimef()*oscTimeMul)+delta*8.0);
        
        ofFloatColor color = mainTint.get();
        color.setBrightness(sinC);
        ofSetColor(color);
        
        ofDrawRectRounded(glm::vec2(posx,0), sW, ofLerp(40, 250, sinC), sW*.5);
        
        
        ofPopMatrix();
        
    }
    
    
    ofPushMatrix();
    ofTranslate(0, -60);
    
    bodyPath.clear();
    bodyPath.setPolyWindingMode(OF_POLY_WINDING_NONZERO);
    
    
    
    bodyPath.moveTo(base.x-baseWidth,base.y);
    
    for(int i=1;i<bodySticks.size();i++){
        bodyPath.lineTo(bodySticks.at(i)->pa);
    }
    
    for(int i=bodySticks.size()-1;i>0;i--){
        bodyPath.lineTo(bodySticks.at(i)->pb);
    }
    
    bodyPath.lineTo(base.x+baseWidth,base.y);
    
    bodyPath.close();
    
    
    
    bodyPath.setFillColor(mainTint.get());
    bodyPath.setStrokeColor(ofFloatColor(0));
    bodyPath.setStrokeWidth(0);
    
    
    bodyPath.draw();
    
    
    
    ofFloatColor    colorLight = mainTint.get();
    colorLight.setSaturation(mainTint.get().getSaturation()*2.0f);
    
    ofSetColor(colorLight);
    ofDrawCircle(bodySticks.at((int)(bodySticks.size()*.5))->a->x, bodySticks.at((int)(bodySticks.size()*.5))->a->y, 60);
    
    ofSetColor(255);
    ofDrawCircle(bodySticks.at((int)(bodySticks.size()*.5))->a->x, bodySticks.at((int)(bodySticks.size()*.5))->a->y, 50);
    
    ofSetColor(0);
    ofDrawCircle(bodySticks.at((int)(bodySticks.size()*.5))->a->x+bodySticks.at((int)(bodySticks.size()*.5))->a->delta.x, bodySticks.at((int)(bodySticks.size()*.5))->a->y+bodySticks.at((int)(bodySticks.size()*.5))->a->delta.y, 30);
    
    
    float pWidth = 10;
    
    for(int i=0;i<particles.size();i++)
    {
        Particle *p = particles.at(i);
        if(p->born){
            
            ofPushMatrix();
            ofTranslate(p->pos);
            
            ofSetColor(mainTint.get());
            
            ofDrawRectRounded(glm::vec2(-pWidth*.5,0.0), pWidth,  pWidth+sin(p->normalized*PI)* pWidth*2.0, pWidth*.5,  pWidth*.5,  pWidth*.5,  pWidth*.5);
            //ofDrawCircle(0, 0, sin(p->normalized*PI)*5);
            
            ofPopMatrix();
            p = nullptr;
        }
    }
    
    
   
  
    
    ofPopMatrix();
    
  
    
    
}
