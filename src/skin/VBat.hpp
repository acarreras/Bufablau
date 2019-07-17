//
//  VBat.hpp
//  cornetas
//
//  Created by Lolo on 16/07/2019.
//

#ifndef VBat_hpp
#define VBat_hpp

#include "VStick.hpp"
#include "ParticleSystem.hpp"

class VBat : public VStick
{
public:
    VBat();
    ~VBat();
    void    setupStick();
    void    preUpdate();
    void    updateStick();
    void    renderStick();
private:
    ParticleSystem  particles;
    
    ofPath      bodyPath;
    float       headWidth;
    float       baseWidth;
    
};

#endif /* VBat_hpp */
