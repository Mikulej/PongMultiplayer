#include "Collider.h"
using namespace std;
std::vector<Collider> Collider::colliderList;
Collider::Collider(float x,float y,float scaleX,float scaleY):x(x),y(y){
    img_id = Sprite::Add("box",x,y);
    Sprite::get(img_id).setScale(scaleX,scaleY);
    width = Sprite::get(img_id).getScaleX() / 16.0f;
    height = Sprite::get(img_id).getScaleY() / 9.0f;
}
void Collider::UpdateAllPos(void){
    for(auto& c : colliderList){    
        c.UpdatePos();
    }
}
void Collider::Initialize(){
    //add all elements to colliderlist here
    //colliderlist[0] is ball [1] is player1 [2] is player2
    colliderList.push_back(Collider(0,0,0.2f,0.2f));
    colliderList.push_back(Collider(0.8f,0,0.5f,2.5f));
    colliderList.push_back(Collider(-0.8f,0,0.5f,2.5f));
}
void Collider::processReceivedData(std::string buffer){
    std::stringstream ss;
    ss << buffer;
    //std::cout << ss.str() << std::endl;
    for(auto& c : colliderList){    
        ss >> c.x >> c.y;
        //std::cout << "x=" << c.x << " y=" << c.y << std::endl;
    }
}
void Collider::UpdatePos(){
    Sprite::get(img_id).setPos(x,y);
}
