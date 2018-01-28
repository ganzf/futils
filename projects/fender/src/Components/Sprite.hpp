//
// Created by clara on 1/28/18.
//

#pragma once

#include "fender.hpp"

namespace fender::components
{
    class Sprite : public futils::IComponent {
    public:
        std::vector<std::string>    files;
        bool loop{true};
        float speed{0.08};
        unsigned int index{0};

        void addSprite(std::string const &file) {
            files.push_back(file);
        }
    };
}