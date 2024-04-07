#ifndef COLLIDER_H
#define COLLIDER_H
#include <vector>
class Collider{
    static std::vector<Collider> colliderList;
    float x,y;
    float width,height;
    Collider(float x,float y,float width,float height);
    void Move(float x,float y);
    bool Collision();

};
#endif