//
// Created by arroganz on 1/24/18.
//

#include "AdvancedGUI.hpp"

namespace demo::systems
{
    void AdvancedGUI::init() {
        win = &entityManager->smartCreate<Window>(800, 600, "[AdvancedGUI]");
        auto &winC = win->get<fender::components::Window>();
        winC.visible = true;

        world = &entityManager->smartCreate<World>();
        auto &worldC = world->get<fender::components::World>();
        worldC.name = "AdvancedGUIWorld";
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

        auto &gui = camera->get<fender::components::Children>();
        auto *info = &entityManager->smartCreate<demo::Text>("You could show input fields and TextBox maybe ?");
        gui.add(*info);
        auto &infoPos = info->get<fender::components::ChildInfo>();
        infoPos.offset.x = 5;
        infoPos.offset.y = 5;
        infoPos.relSize.w = 90;
        infoPos.relSize.h = 10;
    }
    void AdvancedGUI::update() {

    }
    void AdvancedGUI::run(float) {
        switch (state) {
            case 0:
                state = 1;
                return init();
            case 1:
                return update();
        }
    }
}