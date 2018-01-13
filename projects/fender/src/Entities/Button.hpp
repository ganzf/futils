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
        components::Image *_image;
        components::Text *_text;
        components::Clickable *_clickable;

    public:
        Button() {
            _image = &attach<components::Image>();
            _text = &attach<components::Text>();
            _clickable = &attach<components::Clickable>();
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

        Button(std::string const &txt, std::string const &img,
               std::string const &font = "ressources/arial.ttf") {
            _image = &attach<components::Image>();
            _text = &attach<components::Text>();
            _clickable = &attach<components::Clickable>();
            auto &hover = attach<components::Hoverable>();
            hover.onHover = [this](){
                auto &border = this->get<components::Border>();
                border.visible = true;
            };
            hover.onLeave = [this](){
                auto &border = this->get<components::Border>();
                border.visible = false;
            };

            _image->file = img;
            _text->style.font = font;
            _text->style.size = 24;
            _text->style.color = futils::Antiquewhite;
            _text->str = txt;
        }

        ~Button() {
            detach<components::Image>();
            detach<components::Text>();
            detach<components::Clickable>();
        }
    };
}