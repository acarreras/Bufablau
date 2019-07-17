//
//  VSObject.hpp
//  cornetas
//
//  Created by Lolo on 14/07/2019.
//

#ifndef VSObject_hpp
#define VSObject_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxINObject.h"
#include "ofxGui.h"

class VSObject : public ofxINObject
{
public:
    VSObject();
    ~VSObject();
    void    setup(string _name);
    void    setVal(float _val);
    void    setSimVal(float &_val);
    void    setPos(float _x,float _y){ x = _x; y = _y;};
    void    born();
    void    dead();
    void    update();
    void    draw();
    void    drawGui();

    virtual void    customSetup(){};
    virtual void    customUpdate(){};
    virtual void    customDraw(){};
    virtual void    customSetVal(float _val){};
    string  getName(){ return name; };
    ofParameterGroup    getParams() { return params; };
    ofxToggle       buttonDrawGui;

protected:
    ofParameterGroup    params;
    string  name;
    float   val;
    float   x,y;
    ofParameter<float>  simVal;
    ofxPanel    gui;
    
};


#endif /* VSObject_hpp */
