//
// Created by arroganz on 7/30/18.
//


#pragma once
#include <ecs.hpp>
#include <Entities/GameObject.hpp>
#include <Components/Image.hpp>
#include <Components/Input.hpp>
#include <Components/rigidBody.hpp>

namespace orias::game {
    class Player: public fender::entities::GameObject {
        fender::components::rigidBody *rigidBody;
    public:
        Player() {
            afterBuild = [this](){
                this->setPosition(0, 0);
                this->setSize(3, 3);
                auto &img = this->attach<fender::components::Image>();
                img.file = "ship.png";
                auto &input = this->attach<fender::components::Input>();
                input.activated = true;
                input.name = "PlayerActions";
                rigidBody = &attach<fender::components::rigidBody>();
                rigidBody->weight = 100;
                input.map[futils::Keys::ArrowRight] = [this](){
                    rigidBody->force.x += 1;
                };
                input.map[futils::Keys::ArrowLeft] = [this](){
                    rigidBody->force.x -= 1;
                };
            };
        }

        ~Player() {
            detach<fender::components::Image>();
            detach<fender::components::Input>();
        }
    };
}

