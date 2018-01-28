//
// Created by clara on 1/28/18.
//

#include <Components/Sprite.hpp>
#include "Sprite.hpp"

namespace fender::systems::SFMLSystems {

    void Sprite::update(float elapsed) {
        for (auto &sprite : entityManager->get<fender::components::Sprite>()) {
            sprite->timeElapsed += elapsed;
            if (sprite->loop == false)
                continue;
            if (sprite->timeElapsed > sprite->speed) {
                sprite->timeElapsed = 0.0;
                sprite->index += 1;
                if (sprite->index >= sprite->files.size())
                    sprite->index = 0;
                if (sprite->getEntity().has<components::Image>()) {
                    auto &img = sprite->getEntity().get<components::Image>();
                    img.file = sprite->files[sprite->index];
                }
            }
        }
    }

    void Sprite::init() {
        __init();
        phase = 1;
    }

    void Sprite::run(float elapsed) {
        switch (phase) {
            case 0:
                return init();
            case 1:
                return update(elapsed);
        }
    }
}