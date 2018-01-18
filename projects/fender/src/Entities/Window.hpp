//
// Created by arroganz on 1/1/18.
//

#pragma once

# include "fender.hpp"
# include "Components/Window.hpp"

namespace fender::entities
{
    class Window : public futils::IEntity
    {
    public:
        Window() {
            attach<components::Window>();
        }
        ~Window()
        {
            std::cerr << __PRETTY_FUNCTION__ << std::endl;
            detach<components::Window>();
        }
    };
}
