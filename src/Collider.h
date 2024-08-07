#ifndef COLLIDER_H
#define COLLIDER_H
#include <vector>
#include <iterator>
#include "Sprite.h"

class Collider{
    static std::vector<Collider> colliderList;
    float x,y;
    float width,height;
    int img_id;//purely for tests before switching to server-client architecture
    Collider(float x,float y,float width,float height);
    void UpdatePos(void);
    public:
    static void UpdateAllPos(void);
    static void Initialize(void);
    static void processReceivedData(std::string buffer);
};
#endif