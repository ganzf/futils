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
        for (auto &list: lists) {
            auto &listPos = list->getEntity().get<components::Transform>();
            if (list->order == futils::Ordering::Horizontal) {
                float current = listPos.position.x;
                float size = 0.0;
                for (auto elem: list->content) {
                    auto &transform = elem->get<components::Transform>();
                    transform.position.x = current;
                    transform.position.y = listPos.position.y;
                    listPos.size.h = transform.size.h > listPos.size.h ? transform.size.h : listPos.size.h;
                    current += transform.size.w;
                    size += transform.size.w;
                }
                listPos.size.w = size;
            } else {
                float current = listPos.position.y;
                float size = 0.0;
                for (auto elem: list->content) {
                    auto &transform = elem->get<components::Transform>();
                    transform.position.y = current;
                    transform.position.x = listPos.position.x;
                    listPos.size.w = transform.size.w > listPos.size.w ? transform.size.w : listPos.size.w;
                    current += transform.size.h;
                    size += transform.size.h;
                }
                listPos.size.h = size;
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