//
// Created by arroganz on 1/1/18.
//

#ifndef DEMO_WINDOWTEST_HPP
#define DEMO_WINDOWTEST_HPP

#include <Components/World.hpp>
# include "fender.hpp"
# include "Entities/Window.hpp"
# include "Entities/Input.hpp"
# include "Entities/Camera.hpp"

class WindowTest : public futils::ISystem {
    fender::entities::Window *window{nullptr};
    fender::entities::Input *input{nullptr};
    fender::entities::Camera *camera{nullptr};

    void initWindow();
    void initInputs();
    void initGui();
public:
    WindowTest(){
        name = "WindowTest";
        afterBuild = [this](){
            initWindow();
            initInputs();
            initGui();
        };
        afterDeath = [](futils::EntityManager *em){
            em->addSystem<WindowTest>();
        };
    }
    ~WindowTest()
    {
        window->detach<fender::components::World>();
    }
    void run(float) override;
};


#endif //DEMO_WINDOWTEST_HPP
