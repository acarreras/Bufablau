//
//  VPride.hpp
//  cornetas
//
//  Created by Lolo on 16/07/2019.
//

#ifndef VPride_hpp
#define VPride_hpp

#include "VStick.hpp"
#include "ParticleSystem.hpp"

class VPride : public VStick
{
public:
    VPride();
    ~VPride();
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

#endif /* VPride_hpp */
