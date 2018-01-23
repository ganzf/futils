//
// Created by arroganz on 1/23/18.
//


#pragma once

# include "Entities/Window.hpp"
# include "Entities/Camera.hpp"
# include "Entities/World.hpp"
# include "AModule.hpp"

namespace demo
{
    /*
     * Loader is the first module of the demo
     * It will create a small window with a demo-selector list.
     * It will display a background, maybe some music...
     */
    class Loader : public AModule {
        /*
         * I recommend using using for clearer code
         */
        using Window = fender::entities::Window;
        using Camera = fender::entities::Camera;
        using World = fender::entities::World;

        Window *_win;
        Camera *_cam;
        World *_world;

        // Simple init function
        void init();
    public:
        Loader() : AModule("Loader") {}
        void run(float) override;
    };
}

