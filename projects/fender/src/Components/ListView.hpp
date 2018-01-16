//
// Created by arroganz on 1/12/18.
//


#pragma once

#include <Entities/GameObject.hpp>
# include "fender.hpp"

namespace fender::components {
    struct ListView : futils::IComponent {
        int offset{0};
        int size{0};
        bool reversed;
        float padding;
        futils::Align align;
        futils::VAlign valign;
        futils::Ordering order;
        std::vector<entities::GameObject *> content;
    };
}