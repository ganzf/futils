//
// Created by arroganz on 7/30/18.
//


#pragma once

#include <Entities/Window.hpp>

using FenderWindow = fender::entities::Window;

namespace orias::ui {
    class Window : public FenderWindow {
    public:
        Window(float width, float height, std::string const &title):
                FenderWindow(width, height, title, futils::WStyle::Default, futils::Granite)
        {

        }
    };
}

