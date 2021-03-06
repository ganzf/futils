//
// Created by arroganz on 1/25/18.
//

#pragma once

# include "events.hpp"
# include "ecs.hpp"
# include "Entities/Camera.hpp"
# include "Entities/TextBox.hpp"
# include "Components/Children.hpp"

class Debug : public futils::ISystem {
    fender::entities::Camera *_cam{nullptr};
    fender::entities::TextBox *_box{nullptr};
    int state{0};

    void init();
public:
    Debug() {
        name = "Debug";
    }
    void run(float) override;
};


