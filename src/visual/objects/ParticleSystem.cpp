//
//  ParticleSystem.cpp
//  cornetas
//
//  Created by Lolo on 16/07/2019.
//

#include "ParticleSystem.hpp"

ParticleSystem::ParticleSystem()
{
    
}

ParticleSystem::~ParticleSystem()
{
    
}

void    ParticleSystem::setup(vector<VerletStick>   *_sticks,float _gravity)
{
    sticks = _sticks;
    gravity = _gravity;
    for(int i=0;i<sticks->size();i++)
    {
        particles.push_back(Particle());
        particles.at(particles.size()-1).born = false;
      //  particles.at(particles.size()-1).pos = glm::vec2(;

    }
    
    
    
}

void    ParticleSystem::setup(int _ammount)
{
    for(int i=0;i<_ammount;i++)
    {
        particles.push_back(Particle());
        particles.at(particles.size()-1).born = false;
        
    }
}

void    ParticleSystem::update(float _tr)
{
    
    /*
    for(int i=0;i<particles.size();i++)
    {

        Particle *p = &particles.at(i);
            
        if(p->born)
        {
            
            p->vel+=p->acc;
            p->pos+=p->vel;
            p->pos.y+=gravity;
            
            p->lifeCount++;
            p->normalized = p->lifeCount/(float)p->lifeMax;
            if(p->lifeCount > p->lifeMax)
            {
                p->born = false;
                
            }
        }else{
            float len =glm::length(sticks->at(i).offset);
            
            if(len > _tr){
            
               
                
            }
            p->normalized = 0.0;

        }
    }*/
}

void    ParticleSystem::draw()
{
   
}

Particle*     ParticleSystem::getFree()
{
    int i = 0;
    Particle *ret = nullptr;
    while(i < particles.size() && ret == nullptr)
    {
        if(!particles.at(i).born)
        {
            ret = &particles.at(i);
        }
        i++;
    }
    return ret;
}
