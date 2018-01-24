//
// Created by arroganz on 1/24/18.
//


#pragma once

# include "AModule.hpp"

namespace demo {
    class SimpleGrid : public AModule {
        Window *win{nullptr};
        Camera *camera{nullptr};
        World *world{nullptr};
        Input *input{nullptr};

        void init();
        void update();
    public:
        SimpleGrid(): AModule("SimpleGrid") {}
        void run(float) override;
    };
}


