//
//  VBot.cpp
//  cornetas
//
//  Created by Lolo on 16/07/2019.
//

#include "VBot.hpp"


VBot::VBot()
{
    
    
}

VBot::~VBot()
{
    
}

void    VBot::setupStick()
{
    
    
    baseWidth = 100;
    
    headWidth = 100;
    
    for(int i=0;i<bodySticks.size();i++){
        float delta = i/(float)bodySticks.size();
        bodySticks.at(i)->setWidth(ofLerp(baseWidth,headWidth,delta));
    }
    
    
    addArm(.8,100,90,1.2);
    
    
    particles.setup(20);
    
    
    
}

void    VBot::preUpdate()
{
    
    
  
    
}

void    VBot::updateStick()
{
    
    
    for(int i=0;i<particles.size();i++)
    {
        
        Particle *p = particles.at(i);
        
        if(p->born)
        {
            
            p->vel+=p->acc;
            p->pos+=p->vel;
            p->pos.y+=-.4;
            
            
            p->computeLife();
            
        }else{
            int index = i%sticks.size();
            if(val > particlesThreshold){
                p->reborn(sticks.at(index).a->x, sticks.at(index).a->y, ofRandom(-.08,.08), ofRandom(-.06,-.12), ofRandom(30,120));
            }
            
        }
    }
    
}

void    VBot::renderStick()
{
    
    ofPushMatrix();
    ofTranslate(0, 80.0);
    for(int i=1;i<bodySticks.size();i++){
        float delta = i/(float)bodySticks.size();
        ofPushMatrix();
        ofTranslate(bodySticks.at(i)->a->x, bodySticks.at(i)->a->y);
        ofRotateZRad(-PI+bodySticks.at(i)->angle);
        
        float sC = sin(delta*6.0+ofGetElapsedTimef()*4.0)*8;
       

        ofSetColor(mainTint.get());
        
        ofDrawRectRounded(0,-headWidth*.5,bodySticks.at(i)->height*1.1,headWidth,headWidth*.2);
        
        ofFloatColor    colorDark = mainTint.get();
        colorDark.setBrightness(.8);
        ofSetColor(colorDark);
        ofDrawRectRounded(0,-(headWidth*.6)*.5,bodySticks.at(i)->height*1.1,headWidth*.6,headWidth*.2);
        
        
        colorDark = mainTint.get();
        colorDark.setBrightness(1.2);
        
        
        if(i == bodySticks.size()-1)
        {
            ofPushMatrix();
            ofTranslate(headWidth*.5, 0);
            ofSetColor(mainTint.get());
            ofDrawCircle(0, 0, headWidth*.5);
            
            
            float eyeSize = headWidth*.1;
            ofPushMatrix();
            ofRotateZRad(PI*.5);
            ofTranslate(0,eyeSize*.7);
            
            ofPushMatrix();
            ofTranslate(-headWidth*.2, 0);
            
            ofSetColor(255);
            ofDrawCircle(0, 0, eyeSize);
            ofSetColor(0);
            ofDrawEllipse(0, 0, eyeSize*1.5,eyeSize*.4);
            ofPopMatrix();
            
            ofPushMatrix();
            ofTranslate(headWidth*.2, 0);
            
            ofSetColor(255);
            ofDrawCircle(0, 0, eyeSize);
            ofSetColor(0);
            ofDrawEllipse(0, 0, eyeSize*1.5,eyeSize*.4);
            ofPopMatrix();
            
        
            ofPopMatrix();
            ofPopMatrix();
        }else{
            ofPushMatrix();
            ofRotateZRad(PI*.5);
            ofTranslate(0,-headWidth*.1);
            
            ofSetColor(colorDark);
            ofDrawCircle(-30-sC, 0,headWidth*.1);
            ofDrawCircle(30+sC, 0,headWidth*.1);
            ofPopMatrix();
        }
        
        
        
        
        ofPopMatrix();
        
    }
    
    for(int i=0;i<particles.size();i++)
    {
        Particle *p = particles.at(i);
        if(p->born){
            
            ofPushMatrix();
            ofTranslate(p->pos);
            ofRotateZRad(p->normalized*TWO_PI);
            ofSetColor(mainTint.get());
            
            float lon = sin(p->normalized*PI)*10;
            
            ofPushStyle();
            ofSetLineWidth(2);
            ofDrawLine(-lon, 0, lon, 0);
            ofDrawLine(0, -lon, 0, lon);
            ofPopStyle();
            
           // ofDrawCircle(0, 0, sin(p->normalized*PI)*15);
            
            ofPopMatrix();
            p = nullptr;
        }
    }
    
    
    
    ofPopMatrix();
}
