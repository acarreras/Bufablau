//
//  VStick.cpp
//  cornetas
//
//  Created by Lolo on 15/07/2019.
//

#include "VStick.hpp"


VStick::VStick()
{
    
}

VStick::~VStick()
{
    
}

void    VStick::create(int _res,float _height,float _dir,float _easing)
{
    resolution = _res;
    height = _height;
    an = dan = PI*.5;
    growDir = _dir;
    easing = _easing;
    
    
    
   
    
}


void    VStick::customSetup()
{

    
    
    oscParams.setName("Oscilador");
    oscParams.add(oscTimeMul.set("Time Mul",1.0,-5.0,5.0));
    oscParams.add(oscYOffset.set("Y Offset",0.0,-ofGetHeight()*.5,ofGetHeight()*.5));
    oscParams.add(oscRad.set("Radius",glm::vec2(50.0),glm::vec2(0.0),glm::vec2(ofGetWidth()*.5)));
    oscParams.add(oscFreq.set("Freq",glm::vec2(1.0),glm::vec2(0.0),glm::vec2(10.0)));
    //params.add(oscParams);
    
    
    gui.add(oscParams);
    
    particlesThreshold.set("P.Threshold",0.5,0.0,1.0);
    
    mainTint.set("Tint",ofFloatColor(1.0),ofFloatColor(0.0),ofFloatColor(1.0));
    gui.add(particlesThreshold);
    gui.add(mainTint);
    base  = glm::vec2(x,y);
    target.x = x;
    target.y = base.y+(height*growDir);

    headY = target.y;
    
    for (int i = 0; i < resolution; i++) {
        points.push_back(VerletPoint());
        points.at(points.size()-1).setup(base.x+i*5,base.y+(growDir*(i*(height/(float)resolution))));
  
     
    }
    for (int i = 1; i < points.size(); i++) {
        sticks.push_back(VerletStick());
        sticks.at(sticks.size()-1).setup(&points[i - 1], &points[i],easing);
    }
    
    head = &points.at(points.size()-1);
    
    
    for(int i=0;i<sticks.size();i++)
    {
        bodySticks.push_back(&sticks.at(i));
    }
 
    setupStick();

}


void    VStick::addArm(float _heightPercent,float _lon,float _angle,float _easing)
{
    int index = bodySticks.size()*_heightPercent;

    float x = bodySticks.at(index)->a->x+cos(ofDegToRad(_angle))*_lon;
    float y = bodySticks.at(index)->a->y+sin(ofDegToRad(_angle))*_lon;

    points.push_back(VerletPoint());
    points.at(points.size()-1).setup(x,y);
    
    sticks.push_back(VerletStick());
    sticks.at(sticks.size()-1).setup(&points[index],&points[points.size()-1],_easing);
    
    armSticks.push_back(&sticks.at(sticks.size()-1));

}


void    VStick::customUpdate()
{
    
    
    
    float time = ofGetElapsedTimef()*oscTimeMul;
    target.x = base.x+cos(time*oscFreq.get().x)*oscRad.get().x*ofLerp(.1,1.0,val);
    target.y = ofGetHeight()*.5+oscYOffset+sin(time*oscFreq.get().y)*oscRad.get().y*ofLerp(.1,1.0,val);
    
    follow(target.x,target.y);
    
    
    preUpdate();
    updatePointStick();
    updateStick();


}

void    VStick::updatePointStick()
{
    
    for(int i=0;i<points.size();i++){
        points.at(i).update();
    }
    
    
    for(int j=0;j<5;j++){
        for(int i=0;i<sticks.size();i++){
            sticks.at(i).update();
        }
    }
    
    
    points[0].x = base.x;
    points[0].y = base.y;
}

void    VStick::follow(float _x,float _y)
{
    head->x = _x;
    head->y = _y;
}

void    VStick::customDraw()
{
    /*
    VerletStick   pa = sticks.at(18);
    glm::vec2   b;
    dan=pa.angle+PI*.5;
    
    an+=(dan-an)*.05;
    b.x=pa.a->x+cos(an)*100;
    b.y=pa.a->y+sin(an)*100;*/
    
    
   /*
    for(int i=0;i<sticks.size();i++){
        sticks.at(i).draw();
    }*/
    
     // ofDrawLine(pa.a->x, pa.a->y, b.x, b.y);
    
    renderStick();
    
    /*
    ofPath  path;
    
    path.setPolyWindingMode(OF_POLY_WINDING_NONZERO);
    
    for(int i=0;i<sticks.size();i++){
        sticks.at(i).draw();
    }
    
    
    
    
    b.x=(pa.a->x+cos(pa.angle+PI*.5)*100)-pa.offset.x*2.0;
    b.y=(pa.a->y+sin(pa.angle+PI*.5)*100)-pa.offset.y*2.0;
    
    ofDrawLine(pa.a->x, pa.a->y, b.x, b.y);

    
    path.moveTo(base.x+40,base.y);

    for(int i=1;i<sticks.size();i++){
            path.lineTo(sticks.at(i).pa);
    }
    
    for(int i=sticks.size()-1;i>0;i--){
            path.lineTo(sticks.at(i).pb);
    }
    
    path.lineTo(base.x-40,base.y);

    
    path.close();
    
    
    
    path.setFillColor(ofFloatColor(1.0,0.0,0.0));
    path.setStrokeColor(ofFloatColor(0));
    path.setStrokeWidth(0);
  //  path.draw();*/

}


