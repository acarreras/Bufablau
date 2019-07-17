//
//  VDoble.cpp
//  cornetas
//
//  Created by Lolo on 16/07/2019.
//

#include "VDoble.hpp"


VDoble::VDoble()
{
    
}

VDoble::~VDoble()
{
    
}

void    VDoble::setupStick()
{
    
    particles.setup(50);
    
    headWidth = 20;
    baseWidth = headWidth*1.2;
    
    for(int i=0;i<bodySticks.size();i++){
        float delta = i/(float)bodySticks.size();
        bodySticks.at(i)->setWidth(ofLerp(0.0,headWidth,sin(delta*PI)));
    }
    
    headWidth2 = 10;
    
    stick2.setPos(base.x, base.y);
    stick2.create(20, 200, 1,15);
    stick2.setup("Otro");

    for(int i=0;i<stick2.bodySticks.size();i++){
        float delta = i/(float)stick2.bodySticks.size();
        stick2.bodySticks.at(i)->setWidth(ofLerp(0.0,headWidth2,sin(delta*PI)));
    }
    

    
    
}

void    VDoble::preUpdate()
{
   
    
    glm::vec2   head2;
    float time = ofGetElapsedTimef()*1.0;

    head2.x = head->x-cos(time*2.2)*oscRad.get().x*.5;
    head2.y = head->y-sin(time*2.0)*oscRad.get().y*.5;

    stick2.follow(head2.x,head2.y);
    
}

void    VDoble::updateStick()
{
    
    stick2.updatePointStick();
    
    for(int i=0;i<particles.size();i++)
    {
        
        Particle *p = particles.at(i);
        
        if(p->born)
        {
            float scale = 100;
            float noi = ofNoise(p->pos.x/scale,p->pos.y/scale);
            float a = noi*PI;
            
            p->pos+=glm::vec2(cos(a),-sin(a));
        
            
            //p->vel+=p->acc;
            //p->pos+=p->vel;
            p->pos.y-=.4;
            
            
            p->computeLife();
            
        }else{
            int index =i%sticks.size();
            float len =glm::length(sticks.at(index).offset);
            if(val > particlesThreshold){
                p->reborn(sticks.at(index).a->x, sticks.at(index).a->y, 0,0, ofRandom(50,200));
            }
            
        }
    }
    
}

void    VDoble::renderStick()
{
    
    
    //VStick::draw();
    
    
    bodyPath.clear();
    bodyPath.setPolyWindingMode(OF_POLY_WINDING_NONZERO);
    
    
    
    bodyPath.moveTo(base.x+40,base.y);
    
    for(int i=1;i<bodySticks.size();i++){
        bodyPath.lineTo(bodySticks.at(i)->pa);
    }
    
    for(int i=bodySticks.size()-1;i>0;i--){
        bodyPath.lineTo(bodySticks.at(i)->pb);
    }
    
    bodyPath.lineTo(base.x-40,base.y);
    
    bodyPath.close();
    
    
    
    bodyPath.setFillColor(mainTint.get());
    bodyPath.setStrokeColor(ofFloatColor(0));
    bodyPath.setStrokeWidth(0);
    
    
    bodyPath.draw();
    
    bodyPath2.clear();
    
    ofFloatColor    colorDark = mainTint.get();
    colorDark.setBrightness(.8);
    
    
    bodyPath2.setPolyWindingMode(OF_POLY_WINDING_NONZERO);
    
    
    
    bodyPath2.moveTo(base.x+40,base.y);
    
    for(int i=1;i<stick2.bodySticks.size();i++){
        bodyPath2.lineTo(stick2.bodySticks.at(i)->pa);
    }
    
    for(int i=stick2.bodySticks.size()-1;i>0;i--){
        bodyPath2.lineTo(stick2.bodySticks.at(i)->pb);
    }
    
    bodyPath2.lineTo(base.x-40,base.y);
    
    bodyPath2.close();
    
  
    bodyPath2.setFillColor(colorDark);
    bodyPath2.setStrokeColor(ofFloatColor(0));
    bodyPath2.setStrokeWidth(0);
    
    
    bodyPath2.draw();
    
    
    for(int i=0;i<particles.size();i++)
    {
        Particle *p = particles.at(i);
        if(p->born){
            
            float noise = ofNoise(p->pos.x/100,p->pos.y/100);
            ofFloatColor color = mainTint.get();
            color.setBrightness(noise);
            
            ofPushMatrix();
            ofTranslate(p->pos);
            
            ofSetColor(color);
            ofDrawCircle(0, 0, sin(p->normalized*PI)*20*noise);
            
            ofPopMatrix();
            p = nullptr;
        }
    }
    
    
    
}
