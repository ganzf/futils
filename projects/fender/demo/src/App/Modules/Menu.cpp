//
// Created by arroganz on 1/24/18.
//

#include "Menu.hpp"

namespace demo::systems
{
    void Menu::init() {
        win = &entityManager->smartCreate<Window>(800, 600, "[Menu (Demo)]");
        auto &winC = win->get<fender::components::Window>();
        winC.visible = true;

        world = &entityManager->smartCreate<World>();
        auto &worldC = world->get<fender::components::World>();
        worldC.name = "MenuWorld";
        worldC.unit = 32;

        camera = &entityManager->smartCreate<Camera>();
        auto &cameraC = camera->get<fender::components::Camera>();
        cameraC.window = win;
        cameraC.activated = true;
        cameraC.name = "Default";
        auto &cameraPos = camera->get<fender::components::Transform>();
        cameraPos.position.x = 10;
        cameraPos.position.y = 10;

        input = &entityManager->smartCreate<Input>();
        auto &inputC = input->get<fender::components::Input>();
        inputC.activated = true;
        inputC.map[futils::Keys::Escape] = [this](){
            entityManager->removeSystem(name);
        };
    }
    void Menu::update() {

    }
    void Menu::run(float) {
        switch (state) {
            case 0:
                state = 1;
                return init();
            case 1:
                return update();
        }
    }
}