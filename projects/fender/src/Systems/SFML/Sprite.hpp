//
// Created by clara on 1/28/18.
//

#pragma once

#include "System.hpp"
#include "Image.hpp"

namespace fender::systems::SFMLSystems
{
    class Sprite : public System {
        enum States
        {
            Init = 0,
            Run
        };
        void update(float elapsed);
        void init();
    public:
        Sprite(): System("Sprite") {}
        void run(float) override;
    };
}

