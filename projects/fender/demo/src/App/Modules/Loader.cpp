//
// Created by arroganz on 1/23/18.
//

#include "Loader.hpp"

namespace demo
{
    void Loader::initInputsCam() {
        auto &input = _input->get<fender::components::Input>();

        futils::InputSequence up;
        futils::InputAction actionUp(futils::Keys::ArrowUp, futils::InputState::GoingDown);
        up.actions.push_back(actionUp);

        futils::InputSequence down;
        futils::InputAction actionDown(futils::Keys::ArrowDown, futils::InputState::GoingDown);
        down.actions.push_back(actionDown);

        futils::InputSequence left;
        futils::InputAction actionLeft(futils::Keys::ArrowLeft, futils::InputState::GoingDown);
        left.actions.push_back(actionLeft);

        futils::InputSequence right;
        futils::InputAction actionRight(futils::Keys::ArrowRight, futils::InputState::GoingDown);
        right.actions.push_back(actionRight);

        input.map[up] = [this]() {
            _cam->setPosition(_cam->getPositionX(), _cam->getPositionY() - 1);
        };
        input.map[down] = [this]() {
            _cam->setPosition(_cam->getPositionX(), _cam->getPositionY() + 1);
        };
        input.map[left] = [this]() {
            _cam->setPosition(_cam->getPositionX() - 1, _cam->getPositionY());
        };
        input.map[right] = [this]() {
            _cam->setPosition(_cam->getPositionX() + 1, _cam->getPositionY());
        };
    }
    void Loader::initInputs() {
        _input = &entityManager->smartCreate<fender::entities::Input>();
        auto &input = _input->get<fender::components::Input>();

        futils::InputSequence escape;
        futils::InputAction action(futils::Keys::Escape, futils::InputState::GoingDown);
        escape.actions.push_back(action);

        input.map[escape] = [this]() {
            events->send<fender::events::Shutdown>();
        };

        input.activated = true;
    }
    void Loader::init() {
        // We create the window and bind it to this system.
        //_win = &entityManager->smartCreate<Window>(1024, 768, futils::WStyle::None);
        _win = &entityManager->smartCreate<Window>();
        auto &win = _win->get<fender::components::Window>();
        auto &bg = _win->attach<fender::components::Color>();

        bg.color = futils::Granite;

        win.size.x = 1024;
        win.size.y = 768;
        win.style = futils::WStyle::Default;
        win.visible = true;

        // The camera is told which window to use for rendering.
        //_cam = &entityManager->smartCreate<Camera>(_win);

        _cam = &entityManager->smartCreate<Camera>();
        auto &cam = _cam->get<fender::components::Camera>();
        cam.window = _win;
        cam.debugMode = false;
        cam.activated = true;
        _cam->setPosition(0, 0);
        // And finally we create a world that will hold basic informations
        //_world = &entityManager->smartCreate<World>("LoaderWorld", 32);

        _world = &entityManager->smartCreate<World>();
        auto &world = _world->get<fender::components::World>();
        world.name = "Loader";
        world.unit = 32;
        world.size.w = 100;
        world.size.h = 100;

        initInputs();
        initInputsCam();

        // entityManager->smartCreate<fender::entities::Image>("poulpi.png", futils::Vec2<float >{0, 0}, futils::Vec2<float>{10, 10});
        auto &gui = _cam->get<fender::components::Children>();
        _mainFrame = &entityManager->smartCreate<ListView>();
        _mainFrame->setBorderVisible(true);
        _mainFrame->borderColor(futils::Crimson);
        gui.add(*_mainFrame);
        auto &mainSize = _mainFrame->get<fender::components::ChildInfo>();
        mainSize.offset.x = 2;
        mainSize.offset.y = 2;
        mainSize.relSize.w = 96;
        mainSize.relSize.h = 96;
        auto &mainContent = _mainFrame->get<fender::components::ListView>();
        mainContent.order = futils::Ordering::Horizontal;

        // Add content ...
        _rightFrame = &entityManager->smartCreate<ListView>();
        _rightFrame->setBorderVisible(true);
        _rightFrame->borderColor(futils::Greenyellow);
        auto &rightSize = _rightFrame->get<fender::components::Transform>();
        rightSize.size.w = 4;
        rightSize.size.h = 4;
        // Ajouter relative size ou modifier le systeme avec des booleans ? :/
        _leftFrame = &entityManager->smartCreate<ListView>();
        _leftFrame->setBorderVisible(true);
        _leftFrame->borderColor(futils::White);
        auto &leftSize = _leftFrame->get<fender::components::Transform>();
        leftSize.size.w = 4;
        leftSize.size.h = 4;
        mainContent.content.push_back(_leftFrame);
        mainContent.content.push_back(_rightFrame);
    }
    void Loader::run(float) {
        if (!_win) return init();
    }
}