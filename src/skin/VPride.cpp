//
//  VPride.cpp
//  cornetas
//
//  Created by Lolo on 16/07/2019.
//

#include "VPride.hpp"


VPride::VPride()
{
    
}

VPride::~VPride()
{
    
}

void    VPride::setupStick()
{
    
    particles.setup(50);
    
    headWidth = 60;
    
    for(int i=0;i<bodySticks.size();i++){
        float delta = i/(float)bodySticks.size();
        bodySticks.at(i)->setWidth(headWidth);
    }
    
    
    
}

void    VPride::preUpdate()
{
   
    
}

void    VPride::updateStick()
{
    
    for(int i=0;i<particles.size();i++)
    {
        
        Particle *p = particles.at(i);
        
        if(p->born)
        {
            
            p->vel+=p->acc;
            p->pos+=p->vel;
            p->pos.y-=.8;
            
            
            p->computeLife();
            
        }else{
            
            float len =glm::length(bodySticks.at(bodySticks.size()-1)->offset);
            if(val > particlesThreshold && ofRandom(100) > 50){
                p->reborn(bodySticks.at(bodySticks.size()-1)->a->x, bodySticks.at(bodySticks.size()-1)->a->y, ofRandom(-.02,.02), ofRandom(-.1,-.3), ofRandom(50,200));
            }
            
        }
    }
    
    
    
}

void    VPride::renderStick()
{
    

    ofPushMatrix();
    ofTranslate(0, 50.0);
    for(int i=0;i<bodySticks.size();i++){
        
         float delta = i/(float)bodySticks.size();
        ofPushMatrix();
        ofTranslate(bodySticks.at(i)->a->x, bodySticks.at(i)->a->y);
        float angle = atan2(bodySticks.at(i)->a->y-bodySticks.at(i)->b->y,bodySticks.at(i)->a->x-bodySticks.at(i)->b->x);
        float dis = ofDist(bodySticks.at(i)->a->x,bodySticks.at(i)->a->y,bodySticks.at(i)->b->x,bodySticks.at(i)->b->y);
        ofRotateRad(PI+angle);
        
        ofFloatColor    color;
        color.setHsb(delta, 1.0, 1.0);
        ofSetColor(color);
        
        float head = i==bodySticks.size()-1;
        
        if(head)
        {
            ofDrawCircle(0, 0, headWidth*.5);
            
            ofSetColor(0);
            ofDrawCircle(0, -12, 6);
            ofDrawCircle(0, 12, 6);
        
            
        }else{
            ofDrawRectRounded(glm::vec2(0,-headWidth*.5), dis*1.2, headWidth, headWidth*.25,headWidth*.25,headWidth*.25, headWidth*.25);

        }
        
  
        ofPopMatrix();
     
    }
    
    
    
    
    
    for(int i=0;i<particles.size();i++)
    {
        Particle *p = particles.at(i);
        if(p->born){
            
            ofPushMatrix();
            ofTranslate(p->pos);
            ofScale(sin(p->normalized*PI));
            ofRotateRad(p->normalized*TWO_PI);
            
            ofFloatColor    color;
            color.setHsb(sin(p->normalized*PI), 1.0, 1.0);
            ofSetColor(color);
            
            ofDrawRectangle(0, 0, 30, 10);
            
            ofPopMatrix();
            p = nullptr;
        }
    }
    
    
    ofPopMatrix();
    
    
}
