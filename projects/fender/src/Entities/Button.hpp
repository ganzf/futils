//
// Created by clara on 1/12/18.
//

#pragma once

#include <Components/Image.hpp>
#include <Components/Clickable.hpp>
#include <Components/Text.hpp>
#include <Components/Hoverable.hpp>
# include "fender.hpp"
# include "GameObject.hpp"
# include "Components/Camera.hpp"
# include "Components/Children.hpp"

namespace fender::entities {
    class Button : public GameObject {
    public:
        Button() {;
            attach<components::Image>();
            attach<components::Text>();
            attach<components::Clickable>();
            auto &hover = attach<components::Hoverable>();
            hover.onHover = [this](){
                auto &border = this->get<components::Border>();
                border.visible = true;
            };
            hover.onLeave = [this](){
                auto &border = this->get<components::Border>();
                border.visible = false;
            };
        }
        ~Button() {
            std::cerr << __PRETTY_FUNCTION__ << std::endl;
            detach<components::Image>();
            detach<components::Text>();
            detach<components::Clickable>();
        }
    };
}