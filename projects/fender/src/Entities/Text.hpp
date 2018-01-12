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
        Text(std::string const &s) {
            attach<components::Text>();
            auto &text = get<components::Text>();
            text.style.size = 24;
            text.style.color = futils::White;
            text.style.font = "arial.ttf";
            text.str = s;
        }

        ~Text() {
            detach<components::Text>();
        }
    };
}