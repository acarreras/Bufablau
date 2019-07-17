//
//  VTree.cpp
//  cornetas
//
//  Created by Lolo on 16/07/2019.
//

#include "VTree.hpp"

VTree::VTree()
{
    
    
}

VTree::~VTree()
{
    
}

void    VTree::setupStick()
{
    
    for(int i=0;i<bodySticks.size();i++)
        bodySticks.at(i)->setWidth(30);
    
    addArm(.8,100,90,1.2);

    
    particles.setup(&sticks,-0.2);
    
    
    
    
}

void    VTree::preUpdate()
{
    
   
    
}

void    VTree::updateStick()
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
            
            float len =glm::length(sticks.at(i).offset);
            if(val > particlesThreshold){
                p->reborn(sticks.at(i).a->x, sticks.at(i).a->y, ofRandom(-.1,.1), ofRandom(-.1,.1), ofRandom(50,200));
            }
   
        }
    }
    

}

void    VTree::renderStick()
{
    
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
    
    
    ofSetColor(mainTint.get());
    ofDrawCircle(bodySticks.at(bodySticks.size()-1)->a->x, bodySticks.at(bodySticks.size()-1)->a->y, 30);
    
    
    ofSetColor(255);
    ofDrawCircle(bodySticks.at(bodySticks.size()-1)->a->x, bodySticks.at(bodySticks.size()-1)->a->y, 20);

    ofSetColor(0);
    ofDrawCircle(bodySticks.at(bodySticks.size()-1)->a->x+bodySticks.at(bodySticks.size()-1)->a->delta.x, bodySticks.at(bodySticks.size()-1)->a->y+bodySticks.at(bodySticks.size()-1)->a->delta.y, 5);

    
    for(int i=0;i<particles.size();i++)
    {
        Particle *p = particles.at(i);
        if(p->born){
            
            ofPushMatrix();
            ofTranslate(p->pos);
            
            ofSetColor(mainTint.get());
            ofDrawCircle(0, 0, sin(p->normalized*PI)*15);

            ofPopMatrix();
            p = nullptr;
        }
    }
    

}
