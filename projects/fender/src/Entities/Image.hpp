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
        components::Image *image;
    public:
        Image(std::string const &img) {;
            image = &attach<components::Image>();
            image->file = img;
        }
        Image(std::string const &img, futils::Vec2<int> size, futils::Vec2<int> pos = {0, 0}) {
            image = &attach<components::Image>();
            image->file = img;
            setSize(size);
            setPosition(pos);
        }
        ~Image() {
            detach<components::Image>();
        }

        void setImageFile(std::string const &file) {
            image->file = file;
        }
    };
}