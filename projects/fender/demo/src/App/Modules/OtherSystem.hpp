//
// Created by arroganz on 1/22/18.
//

#ifndef DEMO_OtherSystem_HPP
#define DEMO_OtherSystem_HPP

#include <Components/World.hpp>
# include "fender.hpp"
# include "Entities/Window.hpp"
# include "Entities/Input.hpp"
# include "Entities/Camera.hpp"

class OtherSystem : public futils::ISystem {
    fender::entities::Input *input{nullptr};
    fender::entities::Camera *camera{nullptr};

    void initWindow();
    void initInputs();
    void initGui();
public:
    OtherSystem(){
        name = "OtherSystem";
        afterBuild = [this](){
            initInputs();
            initGui();
        };
        afterDeath = [](futils::EntityManager *){};
    }
    ~OtherSystem()
    {
        // window->detach<fender::components::World>();
    }
    void run(float) override;
};


#endif //DEMO_OtherSystem_HPP


