//
// Created by arroganz on 7/29/18.
//


#pragma once

# include <Components/Text.hpp>
# include <Entities/Button.hpp>
# include "ecs.hpp"

using FenderButton = fender::entities::Button;

namespace orias::ui {
    class Button : public FenderButton {
    public:
        Button(std::string const &label, float width, float height, int fontSize): FenderButton(label) {
            afterBuild = [this, label, width, height, fontSize](){
                this->setSize(width, height);
                auto &text = get<fender::components::Text>();
                text.str = label;
                text.style.size = fontSize;
                text.style.font = "arial.ttf";
                text.style.valign = futils::VAlign::Middle;
                text.style.align = futils::Align::Center;
            };
        }
    };
}

