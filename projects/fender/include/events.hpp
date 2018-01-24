//
// Created by arroganz on 11/29/17.
//

#ifndef FENDER_EVENTS_HPP
#define FENDER_EVENTS_HPP

# include "ecs.hpp"
# include "mediator.hpp"
# include "math.hpp"

namespace fender::events {
    struct Shutdown // A simple message to shutdown every system in the engine.
    {

    };

    struct Collision
    {
        futils::IEntity *first;
        futils::IEntity *second;
    };
}

#endif //FENDER_EVENTS_HPP
