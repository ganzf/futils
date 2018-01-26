//
// Created by arroganz on 1/24/18.
//


#pragma once

# include "AModule.hpp"

namespace demo::systems {
    class Runner: public AModule {
        Window *win{nullptr};
        Camera *camera{nullptr};
        World *world{nullptr};
        Input *input{nullptr};

        void init();
        void update();
    public:
        Runner(): AModule("Runner") {}
        void run(float) override;
    };
}


