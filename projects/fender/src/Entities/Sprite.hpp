//
// Created by clara on 1/28/18.
//



#pragma once

#include <Components/Sprite.hpp>
#include "GameObject.hpp"
#include "Image.hpp"

namespace fender::entities {

    class Sprite : public GameObject {

    public:
        Sprite(float speed, bool loop = true) {
            auto &sprite = attach<fender::components::Sprite>();
            attach<fender::components::Image>();
            sprite.speed = speed;
            sprite.loop = loop;
        }

        void addSprite(std::string const &file) {
            auto &sprites = get<fender::components::Sprite>();
            sprites.addSprite(file);
        }

        ~Sprite() {
            detach<components::Sprite>();
            detach<components::Image>();
        }
    };
}