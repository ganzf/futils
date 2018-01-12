//
// Created by clara on 1/11/18.
//

#pragma once

#include <Components/Text.hpp>
#include "GameObject.hpp"

namespace fender::entities
{
    class Text : public GameObject
    {
    public:
        Text() {
            attach<components::Text>();
        }

        ~Text() {
            detach<components::Text>();
        }
    };
}