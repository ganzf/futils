//
// Created by arroganz on 1/3/18.
//

#pragma once

# include "fender.hpp"
# include "Components/World.hpp"

namespace fender::entities {
    class World : public futils::IEntity {
    public:
        World() {
            attach<components::World>();
        }
        ~World() {
            std::cerr << __PRETTY_FUNCTION__ << std::endl;
            detach<components::World>();
        }
    };
}

