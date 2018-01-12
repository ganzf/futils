//
// Created by arroganz on 1/12/18.
//

#include "ListView.hpp"

namespace fender::systems::SFMLSystems
{
    void ListView::init()
    {
        __init();
        phase = 1;
    }

    void ListView::update() {
        auto lists = entityManager->get<components::ListView>();
        for (auto &list: lists)
        {
            auto &listPos = list->getEntity().get<components::Transform>();
            int current = listPos.position.x;
            for (auto elem: list->content)
            {
                auto &transform = elem->get<components::Transform>();
                transform.position.x = current;
                current += transform.size.w;
            }
        }
    }

    void ListView::run(float) {
        switch (phase)
        {
            case 0: return init();
            case 1: return update();
        }
    }
}