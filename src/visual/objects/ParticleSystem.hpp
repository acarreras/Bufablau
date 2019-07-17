//
//  ParticleSystem.hpp
//  cornetas
//
//  Created by Lolo on 16/07/2019.
//

#ifndef ParticleSystem_hpp
#define ParticleSystem_hpp

#include <stdio.h>
#include "ofMain.h"
#include "VUtils.h"


struct Particle
{
    glm::vec2   pos;
    glm::vec2   vel;
    glm::vec2   acc;
    int         lifeCount;
    int         lifeMax;
    float       lifeTime;
    float       normalized;
    bool        born;
    void        computeLife()
    {
        lifeCount++;
        normalized = lifeCount/(float)lifeMax;
        if(lifeCount > lifeMax)
        {
            normalized = 1.0f;
            born = false;
        }
    }
    void        reborn(float _px,float _py,float _accX,float _accY,int   _lifeMax)
    {
        pos = glm::vec2(_px,_py);
        vel = glm::vec2(0.0,0.0);
        vel = glm::vec2(0.0,0.0);
        acc = glm::vec2(_accX,_accY);
        born = true;
        lifeCount = 0.0;
        lifeMax = _lifeMax;
    }
};


class ParticleSystem
{
public:
    ParticleSystem();
    ~ParticleSystem();
    void    setup(vector<VerletStick>   *_sticks,float _gravity);
    void    setup(int _ammount);
    void    update(float _tr);
    
    void    draw();
    Particle*   at(int _index){ return &particles.at(_index); };
    int     size() { return particles.size(); };
    Particle*     getFree();

private:
    vector<Particle>   particles;
    vector<VerletStick>   *sticks;
    float   gravity;
    
};

#endif /* ParticleSystem_hpp */
