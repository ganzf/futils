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
        //TODO: enlever le component clickable et faire une entité bouton
        Image() {;
            attach<components::Image>();
            attach<components::Clickable>();
        }
        ~Image() {
            detach<components::Image>();
            detach<components::Clickable>();
        }
    };
}