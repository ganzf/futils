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
        components::Image *_image;
    public:
        Image() {
            _image = &attach<components::Image>();
        }
        Image(std::string const &file) {
            _image = &attach<components::Image>();
            _image->file = file;
        }
        ~Image() {
            detach<components::Image>();
        }

        void setImageFile(std::string const &file) {
            _image->file = file;
        }
    };
}