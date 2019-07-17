//
//  VUtils.h
//  cornetas
//
//  Created by Lolo on 15/07/2019.
//

#ifndef VUtils_h
#define VUtils_h




class   VerletPoint : public glm::vec2
{
public:
    VerletPoint(){
        delta = glm::vec2(0.0,0.0);
    };
    ~VerletPoint()
    {
        
    };
    void    setup(float _x,float _y)
    {
        x = _x;
        y = _y;
        prev = glm::vec2(x,y);
     
    };
    
    void    update()
    {
        glm::vec2 temp = glm::vec2(x,y);
        *this+=getVelocity();
        prev = glm::vec2(temp.x,temp.y);
        delta = *this-prev;
        

    }
    
    void    draw()
    {
        ofSetColor(0);
        ofDrawCircle(x,y,5);
    }
    
    void    setPosition(float _x,float _y)
    {
        x = _x;
        y = _y;
        prev = glm::vec2(x,y);
    }
    
    void    setVelocity(float _x,float _y)
    {
        prev = glm::vec2(x,y)-glm::vec2(_x,_y);
    }
    
    glm::vec2   getVelocity()
    {
        return glm::vec2(x,y)-prev;
    }
    
    glm::vec2   prev;
    glm::vec2   delta;
    
};


class VerletStick
{
public:
    VerletStick(){
        len = 0;
        a = nullptr;
        b = nullptr;
        base = false;
        skin = false;
        angle = 0.0f;
        offset = glm::vec2(0.0);
        angleOffset = 0;
        pAngle = 0;
        limit = false;

    };
    ~VerletStick()
    {
        
    }
    
    void    setup(VerletPoint *_a,VerletPoint *_b,float _easing = 10.0f){
        a=_a;
        b=_b;
        len = glm::distance((glm::vec2)*a,(glm::vec2)*b);
        easing=_easing;
    };
    
    void    setWidth(float _w)
    {
        width = _w;
    }
    
    void    update()
    {
        float dist = glm::distance(glm::vec2(a->x,a->y),glm::vec2(b->x,b->y));
        float dif = len-dist;
        offset = (glm::vec2(a->x,a->y)-glm::vec2(b->x,b->y))*(dif/dist/easing);

        *a+=offset;
        *b-=offset;
        
        angle = atan2(a->y-b->y,a->x-b->x);
        height = glm::distance(glm::vec2(a->x,a->y),glm::vec2(b->x,b->y));
  /*
        if(limit)
        {
            float minX = a->x+cos(angle+ofDegToRad(limitAngle))*100;
            float minY = a->y+sin(angle+ofDegToRad(limitAngle))*100;

            float maxX = a->x+cos(angle+ofDegToRad(limitAngle))*100;
            float maxY = a->y+sin(angle+ofDegToRad(limitAngle))*100;
            
            b->x = maxX;
            b->y = maxY;

            
        }*/
        
    //    offset=glm::vec2(0.0,0.0);
        
        angleOffset = angle-pAngle;
                
        pAngle = angle;
        
        float a0 = base ? -PI*.5 : angle-PI*.5f;
        float a1 = base ? PI*.5 :angle+PI*.5f;
        
       // width = 30.0;
        
        pa = glm::vec2(a->x+cos(a0)*width,a->y+sin(a0)*width);
        pb = glm::vec2(a->x+cos(a1)*width,a->y+sin(a1)*width);

        
    }
    
    void    draw()
    {
        if(a != nullptr && b != nullptr){
            ofSetColor(255,0,0);
            ofDrawLine(a->x,a->y,b->x,b->y);
            ofSetColor(255,0,0);
            ofDrawCircle(pa.x,pa.y,3);
            ofDrawCircle(pb.x,pb.y,3);

            
        }
    }
    
    VerletPoint *a;
    VerletPoint *b;
    float       len;
    bool        base;
    bool        skin;
    bool        limit;
    float       limitAngle;
    float       tolerance;
    
    float       width;
    float       height;
    
    float       pAngle;
    float       angleOffset;
    float       angle;
    float       easing;
    glm::vec2   offset;
    glm::vec2   pa;
    glm::vec2   pb;
};
/*
class VArm : public glm::vec2
{
public:
    VArm()
    {
        
    };
    
    ~VArm()
    {
        
    };
    
    void    setup(VerletStick *_stick,float _angle,float _tolerance)
    {
        stick = _stick;
        angle = _angle;
        tolerance = _tolerance;
    };
    
    void    update()
    {
        if(_stick->angle > angle+tolerance)
        {
            
        }
        
    };
    
    float angle;
    float tolerance;
    VerletStick *stick;
};
*/


class VSegment {
    
public:
    VSegment()
    {
        parent = nullptr;
        dest = glm::vec2(0.0,0.0);
    };
    
    ~VSegment()
    {
        
    };
    
    void    setup(float _x,float _y,float _len,float _angle)
    {
        source = glm::vec2(_x,_y);
        len = _len;
        angle = _angle;
        calcDest();
        
        cout << source << " " << dest << endl;

    };
    
    void    setup(VSegment *_parent,float _len,float _angle)
    {
        parent = _parent;
        source = glm::vec2(parent->dest.x,parent->dest.y);
        len = _len;
        angle = _angle;
        calcDest();
        
    };
    
    void    setSource(float _x,float _y)
    {
        source = glm::vec2(_x,_y);
        
        calcDest();
    }
    
    
    void    follow(float _x,float _y)
    {
        glm::vec2 target(_x,_y);
        glm::vec2 dir = target-source;
        
        angle = atan2(target.y-source.y,target.x-source.x);
    
        dir = dir*len/glm::length(dir);
        dir = dir*-1.0;
        
        source = target+dir;
    

    }
    
    void    follow()
    {
        glm::vec2 target(parent->source.x,parent->source.y);
        glm::vec2 dir = target-source;
        
        angle = atan2(target.y-source.y,target.x-source.x);
        
        dir = dir*len/glm::length(dir);
        dir = dir*-1.0;
        
        source = target+dir;
        
    }
    
    void    calcDest()
    {
        dest = glm::vec2(source.x+cos(angle)*len,source.y+sin(angle)*len);

    }
    
    void    update()
    {
        calcDest();
        
    };
    
    void    draw()
    {
      
        
        ofSetColor(255,0,0);
        ofDrawCircle(source.x,source.y,10);
        ofSetColor(0,0,0);

        ofDrawLine(source.x,source.y,dest.x,dest.y);
        ofSetColor(0,0,255);

        ofDrawCircle(dest.x,dest.y,10);

        
        
    };
    
    
    
    
    glm::vec2   dest;
    glm::vec2 source;

    
private:
    float   len;
    float   angle;
    VSegment    *parent;
    
    
};



#endif /* VUtils_h */
