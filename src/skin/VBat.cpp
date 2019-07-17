//
//  VBat.cpp
//  cornetas
//
//  Created by Lolo on 16/07/2019.
//

#include "VBat.hpp"


VBat::VBat()
{
    
}

VBat::~VBat()
{
    
}

void    VBat::setupStick()
{
    
    
    particles.setup(&sticks,-0.2);
    
    headWidth = 40;
    baseWidth = headWidth*1.2;
    
    for(int i=0;i<bodySticks.size();i++){
        float delta = i/(float)bodySticks.size();
        bodySticks.at(i)->setWidth(ofLerp(baseWidth,headWidth,delta));
    }
    
    

}

void    VBat::preUpdate()
{
    /*
    float time = ofGetElapsedTimef()*oscTimeMul;
    head.x = base.x+cos(time*oscFreq.get().x)*oscRad.get().x;
    head.y = ofGetHeight()*.5+oscYOffset+sin(time*oscFreq.get().y)*oscRad.get().y;
    
    follow(head.x,head.y);*/
    
}

void    VBat::updateStick()
{
   // particles.update(1.1f);
    
    for(int i=0;i<particles.size();i++)
    {
        
        Particle *p = particles.at(i);
        
        if(p->born)
        {
            
            p->vel+=p->acc;
            p->pos+=p->vel;
            p->pos.y+=1;
            
            
            p->computeLife();
            
        }else{
            
            float len =glm::length(sticks.at(i).offset);
            if(val > particlesThreshold){
                p->reborn(sticks.at(i).a->x, sticks.at(i).a->y, ofRandom(-.05,.05), ofRandom(.02,.3), ofRandom(50,200));
            }
            
        }
    }
    
    

}

void    VBat::renderStick()
{
    
    
    ofPushMatrix();
    ofTranslate(0,-50);
    
    //  cuerpo
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
    //  panza
    bodyPath.clear();
    bodyPath.setPolyWindingMode(OF_POLY_WINDING_NONZERO);
    bodyPath.moveTo(base.x-baseWidth,base.y);
    for(int i=1;i<bodySticks.size()-5;i++){
        bodyPath.lineTo(bodySticks.at(i)->pa);
    }
    for(int i=bodySticks.size()-6;i>0;i--){
        bodyPath.lineTo(bodySticks.at(i)->pb);
    }
    bodyPath.lineTo(base.x+baseWidth,base.y);
    bodyPath.close();
    ofFloatColor    lightColor = mainTint.get();
    lightColor.setBrightness(1.1);
    bodyPath.setFillColor(lightColor);
    bodyPath.setStrokeColor(ofFloatColor(0));
    bodyPath.setStrokeWidth(0);
    bodyPath.draw();
    
    
    
    //
    
    ofSetColor(mainTint.get());
    ofDrawCircle(bodySticks.at(bodySticks.size()-1)->a->x, bodySticks.at(bodySticks.size()-1)->a->y, headWidth);

    float angle = bodySticks.at(bodySticks.size()-1)->angle;
    ofPushMatrix();
    ofTranslate(bodySticks.at(bodySticks.size()-1)->b->x,bodySticks.at(bodySticks.size()-1)->b->y);
    ofRotateZRad(angle+PI*.5);
    
    
    ofSetColor(255,255,0);
    ofDrawCircle(-15, -10, 8);
    
    ofSetColor(255,255,0);
    ofDrawCircle(15, -10, 8);
    
    ofPushMatrix();
    ofSetColor(mainTint.get());

    ofTranslate(15,5);
    
    ofDrawTriangle(-10, 0, 0, 50, 10, 0);
    

    ofPopMatrix();
    
    ofTranslate(-15,5);
    
    ofDrawTriangle(-10, 0, 0, 50, 10, 0);
    
    
    ofPopMatrix();
    
    
    ofPopMatrix();
    

 
    
    for(int i=0;i<particles.size();i++)
    {
        Particle *p = particles.at(i);
        if(p->born){
            
            ofPushMatrix();
            ofTranslate(p->pos);
            ofScale(sin(p->normalized*PI));
            ofRotateRad(p->normalized*TWO_PI);
            
            ofSetColor(lightColor.getLerped(mainTint.get(), p->normalized));
            ofPushStyle();
            ofNoFill();
            ofSetLineWidth(2);
            ofDrawTriangle(-10, 0, 0, 20, 10, 0);
            ofPopStyle();
            
            ofPopMatrix();
            p = nullptr;
        }
    }
    
    ofPopMatrix();
}
