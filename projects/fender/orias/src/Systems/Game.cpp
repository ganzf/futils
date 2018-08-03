//
// Created by arroganz on 7/30/18.
//

#include "Game.hpp"

namespace orias::scenes {
    void Game::run(float) {
        switch (state) {
            case 0: return;
        }
    }

    void Game::init() {
        this->player = &entityManager->smartCreate<orias::game::Player>();
    }
}