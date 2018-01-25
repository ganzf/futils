//
// Created by arroganz on 1/25/18.
//


#pragma once

# include "AModule.hpp"

namespace demo::systems {
    class Text : public AModule {
        Window *win{nullptr};
        Camera *camera{nullptr};
        World *world{nullptr};
        Input *input{nullptr};

        void init();
        void update();
    public:
        Text(): AModule("Text (Demo)") {}
        void run(float) override;
    };
}