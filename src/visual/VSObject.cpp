//
//  VSObject.cpp
//  cornetas
//
//  Created by Lolo on 14/07/2019.
//

#include "VSObject.hpp"

VSObject::VSObject()
{
    val = 0.0f;
    x = 0.0f;
    y = 0.0f;
    simulated = false;
}

VSObject::~VSObject()
{
    
}

void    VSObject::setup(string _name)
{
    name = _name;
 //   params.setName(name);
    buttonDrawGui.setup(name + " GUI",false);

    gui.setup(name,"mostras/"+name+".xml",300,20);

    
    
    simVal.set("Valor", 0.0);
    simVal.addListener(this, &VSObject::setSimVal);
  //  params.add(simVal);
    
    gui.add(simVal);

    customSetup();
}

void    VSObject::setSimulation(bool _val)
{
  simulated = _val;
}


void    VSObject::setVal(float _val)
{
  
    val = _val;

    //customSetVal(val);
}

void    VSObject::born()
{
    
}

void    VSObject::dead()
{
    
}

void    VSObject::update()
{
    
    if(ofGetFrameNum() == 1)
    {
        gui.loadFromFile("mostras/"+name+".xml");
    }
    
    
    ofxINObject::update();
    if(simulated)
    {
      setVal(simVal);
    }
    customUpdate();
}

void    VSObject::draw()
{
    customDraw();
}

void    VSObject::drawGui()
{
    gui.draw();
}


void    VSObject::setSimVal(float &_val)
{
  if(simulated){
    setVal(_val);
  }
}
