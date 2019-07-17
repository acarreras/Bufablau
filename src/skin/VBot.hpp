//
//  VBot.hpp
//  cornetas
//
//  Created by Lolo on 16/07/2019.
//

#ifndef VBot_hpp
#define VBot_hpp

#include <stdio.h>
#include "VStick.hpp"
#include "ParticleSystem.hpp"

class VBot : public VStick
{
public:
    VBot();
    ~VBot();
    void    setupStick();
    void    preUpdate();
    void    updateStick();
    void    renderStick();
private:
    ParticleSystem  particles;
    
    ofPath      bodyPath;
    ofParameter<float>  danceRadius;
    
    float       headWidth;
    float       baseWidth;
    
    
};

#endif /* VBot_hpp */
