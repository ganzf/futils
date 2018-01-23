//
// Created by arroganz on 1/23/18.
//

#include "Loader.hpp"

namespace demo
{
    void Loader::init() {
        // We create the window and bind it to this system.
        _win = &entityManager->smartCreate<Window>(1024, 768, futils::WStyle::None);
        // The camera is told which window to use for rendering.
        _cam = &entityManager->smartCreate<Camera>(_win);
        // And finally we create a world that will hold basic informations
        _world = &entityManager->smartCreate<World>("LoaderWorld", 32);
    }

    void Loader::run(float) {
        if (!_win) return init();
    }
}