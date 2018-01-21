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

        components::Image *image;
        components::Text * text;
        components::Clickable *click;
        components::Hoverable *hover;

    public:
        Button() {
            image = &attach<components::Image>();
            text = &attach<components::Text>();
            click =  &attach<components::Clickable>();
            hover = &attach<components::Hoverable>();
            hover->onHover = [this](){
                setBorderVisible(true);
            };
            hover->onLeave = [this](){
                setBorderVisible(false);
            };
        }

        ~Button() {
            detach<components::Image>();
            detach<components::Text>();
            detach<components::Clickable>();
        }


    };
}