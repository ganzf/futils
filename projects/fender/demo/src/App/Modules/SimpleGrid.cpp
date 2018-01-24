//
// Created by arroganz on 1/24/18.
//

#include "SimpleGrid.hpp"

namespace demo
{
    void SimpleGrid::init()
    {
        win = &entityManager->smartCreate<Window>(800, 600, "[SimpleGrid]");
        auto &winC = win->get<fender::components::Window>();
        winC.visible = true;

        input = &entityManager->smartCreate<Input>();
        auto &inputC = input->get<fender::components::Input>();
        inputC.activated = true;
        inputC.map[futils::Keys::Escape] = [this](){
            entityManager->removeSystem(name);
        };
    }

    void SimpleGrid::update()
    {

    }

    void SimpleGrid::run(float) {
        switch (state) {
            case 0:
                state = 1;
                return init();
            case 1:
                return update();
        }
    }
}