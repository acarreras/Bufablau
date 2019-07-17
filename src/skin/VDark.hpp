//
//  VDark.hpp
//  cornetas
//
//  Created by Lolo on 16/07/2019.
//

#ifndef VDark_hpp
#define VDark_hpp

#include <stdio.h>
#include "VStick.hpp"
#include "ParticleSystem.hpp"

class VDark : public VStick
{
public:
    VDark();
    ~VDark();
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

#endif /* VDark_hpp */
