#ifndef BULLET_HPP
#define BULLET_HPP

#include <typeinfo>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "engine/ObjectsPool.hpp"
#include "engine/GameObject.hpp"
#include "engine/WindowInfo.hpp"
#include "game/entities/Explosion.hpp"
#include "game/entities/Enemy.hpp"

using namespace std;
using namespace sf;

class Bullet : public GameObject {
    Clock timer;
    Vector2f moveDir;
    float speed;
public:
    Bullet();
    
    void onUpdate(float dt);
    void onCollisionStay(GameObject *object);
};

#endif