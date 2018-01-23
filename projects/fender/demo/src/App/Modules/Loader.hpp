//
// Created by arroganz on 1/23/18.
//


#pragma once

# include "Entities/Window.hpp"
# include "Entities/Camera.hpp"
# include "Entities/World.hpp"
# include "Entities/Image.hpp"
# include "Entities/Input.hpp"
# include "Entities/ListView.hpp"
# include "Components/Color.hpp"
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
        using Input = fender::entities::Input;
        using ListView = fender::entities::ListView;

        Window *_win {nullptr};
        Camera *_cam {nullptr};
        World *_world {nullptr};
        Input *_input {nullptr};
        // Main container
        ListView *_mainFrame{nullptr};
        ListView *_leftFrame{nullptr};
        // Right side of demo with vertical ordering
        ListView *_rightFrame{nullptr};
        // Debug Container
        ListView *_debug{nullptr};
        // Demo Selector
        ListView *_selector{nullptr};

        // Simple init function
        void init();
        void initInputs();
        void initInputsCam();
    public:
        Loader() : AModule("Loader") {}
        void run(float) override;
    };
}

