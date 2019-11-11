//
//  Visual.cpp
//  cornetas
//
//  Created by Lolo on 14/07/2019.
//

#include "Visual.hpp"

Visual::Visual()
{
    loaded = false;
}

Visual::~Visual()
{
    
    
}

void    Visual::setup()
{
    gui.setup("Visual","visual.xml");
    ofAddListener(gui.savePressedE, this, &Visual::onGuiSave);
    ofAddListener(gui.loadPressedE,this,&Visual::onGuiLoad);
  
    //gui.add(fps.set("FPS","FPS"));
  
    simulation.addListener(this, &Visual::onSimulation);
    gui.add(simulation.set("Simulate",false));
    drawGui = false;
    
    float stepW = ofGetWidth()/7.0f;
    

    tree.setPos(stepW*1,ofGetHeight());
    tree.create(24, 200,-1);
    tree.setup("Stick");
    
    bat.setPos(stepW*2,0);
    bat.create(18, 100,1);
    bat.setup("Bat");
    
    pride.setPos(stepW*3,ofGetHeight());
    pride.create(12, 80,-1);
    pride.setup("Pride");
    
    doble.setPos(stepW*4,ofGetHeight());
    doble.create(24, 200,1,12);
    doble.setup("Doble");
    
    dark.setPos(stepW*5,0);
    dark.create(18, 60,1,8);
    dark.setup("Dark");
    
    bot.setPos(stepW*6,ofGetHeight());
    bot.create(15, 250,-1,5);
    bot.setup("Bot");
    
    
    addObject(&tree);
    addObject(&bat);
    addObject(&pride);
    addObject(&doble);
    addObject(&dark);
    addObject(&bot);
    
    ofFbo::Settings set;
    set.width = ofGetWidth();
    set.height = ofGetHeight();
    set.internalformat = GL_RGBA;
    set.numSamples = 1;
    //ofDisableArbTex();
    fbo.allocate(set);
    
    
   
    colorIndex = 0;
    colorNextIndex = 0;
    
  
    
    backColor = backgroundColors.at(colorIndex);
    
    
    shader.load("shader/shader.vert","shader/shader.frag");

    add_interpolator("Fondo", .2f, 0.0, 1.0,Sine::easeOut);
    add_interpolator("Shader", 3.0f, 0.0, 1.0,Sine::easeOut);
    add_interpolator("Circle", .5f, 0.0, 1.0,Sine::easeOut);

    particles.setup(10);
    pMix = pDMix = 0.0;
    
    imgNoise.load("noise.jpg");
    

}

void    Visual::onGuiSave()
{
 for(int i=0;i<objects.size();i++)
   objects.at(i)->saveGui();
}

void    Visual::onGuiLoad()
{
  for(int i=0;i<objects.size();i++)
    objects.at(i)->loadGui();
}

void    Visual::onSimulation(bool &_e)
{
  for(int i=0;i<objects.size();i++)
    objects.at(i)->setSimulation(_e);
}


void    Visual::setVal(int _index,float _val)
{
  if(!simulation){
    if(_index < objects.size()){
      objects.at(_index)->setVal(_val);
    }
  }
}


void    Visual::addObject(VSObject *_newObject)
{
    gui.add(&_newObject->buttonDrawGui);
    //gui.add(_newObject->getParams());
    objects.push_back(_newObject);
}

void    Visual::update()
{
    
    //shader.load("shader/shader.vert","shader/shader.frag");

    ofxINObject::update();
    
    if(ofGetFrameNum() == 1)
    {
        gui.loadFromFile("visual.xml");
        loaded = true;
    }
    
    if(!loaded)
        return;
    
    
    pMix+=(pDMix-pMix)*.3;
    
    if(get_interpolator("Circle").bang())
        get_interpolator("Circle").reset();
    
    
    
    //fps = ofToString(ofGetFrameRate(),2);
    
    for(auto object : objects)
    {
        object->update();
    }
    
    
    for(int i=0;i<particles.size();i++)
    {
        Particle *p = particles.at(i);
        
        if(p->born)
        {
            
            float scale = 100;
            float noi = ofNoise(p->pos.x/scale,p->pos.y/scale);
            float a = noi*PI;
            
            p->pos+=glm::vec2(cos(a),-sin(a));
            
            
            p->computeLife();
            
            
        }else{
            p->reborn(ofRandomWidth(), ofRandomHeight(), 0, 0, ofRandom(30,100));
        }
        
        
    }
    
    
    fbo.begin();
    ofClear(0,0);
    for(auto object : objects)
    {
        object->draw();
    }
    
    
    for(int i=0;i<particles.size();i++)
    {
        Particle *p = particles.at(i);
        if(p->born){
            
            float noise = ofNoise(p->pos.x/100,p->pos.y/100);
            ofFloatColor color = ofFloatColor(1.0,.8);
            
            ofPushMatrix();
            ofTranslate(p->pos);
            
            ofPushStyle();
            ofEnableBlendMode(OF_BLENDMODE_ADD);
            ofSetColor(color);
            ofDrawCircle(0, 0, (sin(p->normalized*PI)*140*noise)*pMix);
            ofPopStyle();
            
            ofPopMatrix();
            p = nullptr;
        }
    }
    
    
    fbo.end();
    
    
    
}
void    Visual::draw()
{
    
    if(!loaded)
        return;
    
    ofBackground(backColor.getLerped(backgroundColors.at(colorNextIndex), get_interpolator("Fondo").val()));

    shader.begin();
    ofSetColor(255);

    shader.setUniform1f("time",ofGetElapsedTimef());
    shader.setUniform1f("mezcla",waveMix);
    shader.setUniform2f("resolution",ofGetWidth(),ofGetHeight());
    shader.setUniform1f("circleMix",get_interpolator("Circle").val());
    
    shader.setUniformTexture("noise", imgNoise.getTexture(), 1);

    fbo.draw(0,0);
    shader.end();
  
  if(drawGui){
    gui.draw();
    
    
    for(int i=0;i<objects.size();i++)
    {
        if(objects.at(i)->buttonDrawGui)
        {
            objects.at(i)->drawGui();
        }
    }
  }
    
}


void    Visual::buttonBang(int _index)
{
    if(_index == 0)
    {
       
        //int next = (int)ofRandom(backgroundColors.size());
        //while(next == colorIndex)
        //    next = (int)ofRandom(backgroundColors.size());
        next++;
        if(next >= backgroundColors.size()){
          next = 0;
        }
        colorIndex = colorNextIndex;
        backColor = backColor.getLerped(backgroundColors.at(colorNextIndex),get_interpolator("Fondo").val());
        
        colorNextIndex = next;
        get_interpolator("Fondo").reset();
        get_interpolator("Fondo").start();
        
    }else if(_index == 1)
    {
        
        waveMix = 1;

        
    }else if(_index == 2)
    {
        pDMix = 1.0;
    }else if(_index == 3)
    {
        get_interpolator("Circle").reset();
        get_interpolator("Circle").start();
    }
}

void    Visual::buttonReset(int _index)
{
    if(_index == 1)
    {
        
        waveMix = 0;
    
    }else if(_index == 2)
    {
        pDMix = 0.0;
    }
}



void    Visual::addBackColor(int _hex)
{
    ofFloatColor newColor;
    newColor.setHex(_hex);
    backgroundColors.push_back(newColor);
}
