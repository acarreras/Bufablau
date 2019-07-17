//
//  VDoble.hpp
//  cornetas
//
//  Created by Lolo on 16/07/2019.
//

#ifndef VDoble_hpp
#define VDoble_hpp

#include "VStick.hpp"
#include "ParticleSystem.hpp"

class VDoble : public VStick
{
public:
    VDoble();
    ~VDoble();
    void    setupStick();
    void    preUpdate();
    void    updateStick();
    void    renderStick();
private:
    ParticleSystem  particles;
    
    VStick      stick2;
    ofPath      bodyPath2;
    
    
    ofPath      bodyPath;
    float       headWidth;
    float       headWidth2;
    float       baseWidth;
    
};
    

#endif /* VDoble_hpp */
