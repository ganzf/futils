//
// Created by arroganz on 7/29/18.
//


#pragma once

# include "events.hpp"
# include "fender.hpp"
# include "rendering.hpp"
# include "inputKeys.hpp"

# include "Entities/Window.hpp"
# include "Entities/World.hpp"
# include "Entities/Camera.hpp"
# include "Entities/Input.hpp"

# include "GameObjects/UI/MenuButton.hpp"
# include "GameObjects/UI/Window.hpp"
# include "json/Json.hpp"

namespace orias::scenes {
    using Window = orias::ui::Window;
    using World = fender::entities::World;
    using Camera = fender::entities::Camera;
    using Input = fender::entities::Input;
    using Button = orias::ui::MenuButton;

    class Splashscreen : public futils::ISystem {
        int phase{0};
        orias::utils::Json const &config;
        Window *window{nullptr};
        World *world{nullptr};
        Camera *camera{nullptr};
        Input *input{nullptr};
        Button *button{nullptr};

        void init();
    public:
        Splashscreen(orias::utils::Json const &config);
        virtual void run(float) final;
    };
}

