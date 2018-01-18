//
// Created by clara on 1/10/18.
//


#pragma once

#include <Components/Image.hpp>
#include <Components/Clickable.hpp>
# include "fender.hpp"
# include "GameObject.hpp"
# include "Components/Camera.hpp"
# include "Components/Children.hpp"

namespace fender::entities {
    class Image : public GameObject {
    public:
        Image() {;
            attach<components::Image>();
        }
        ~Image() {
            std::cerr << __PRETTY_FUNCTION__ << std::endl;
            detach<components::Image>();
        }
    };
}