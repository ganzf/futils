//
// Created by clara on 1/11/18.
//


#pragma once

# include "fender.hpp"

namespace fender::components {
    struct Clickable : futils::IComponent {
        std::function<void()> func;
    };
}