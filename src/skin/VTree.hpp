//
//  VTree.hpp
//  cornetas
//
//  Created by Lolo on 16/07/2019.
//

#ifndef VTree_hpp
#define VTree_hpp

#include <stdio.h>
#include "VStick.hpp"
#include "ParticleSystem.hpp"

class VTree : public VStick
{
public:
    VTree();
    ~VTree();
    void    setupStick();
    void    preUpdate();
    void    updateStick();
    void    renderStick();
private:
    ParticleSystem  particles;
    
    ofPath      bodyPath;
    
};

#endif /* VTree_hpp */
