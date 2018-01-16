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

    void ListView::updateHorizontalList(components::ListView &list,
                                        components::Transform &listPos,
                                        int &count)
    {
        float current = listPos.position.y;
        float size = 0.0;
        for (auto elem: list.content) {
            count++;
            if (count < list.offset || (count > list.offset + list.size && list.size >= 0))
                continue ;
            auto &transform = elem->get<components::Transform>();
            transform.position.y = current;
            transform.position.x = listPos.position.x;
            transform.size.w = transform.size.w < listPos.size.w ? listPos.size.w : transform.size.w;
            transform.size.h = transform.size.h == 0 ? 0.5 : transform.size.h;
            listPos.size.w = transform.size.w > listPos.size.w ? transform.size.w : listPos.size.w;
            current += transform.size.h;
            size += transform.size.h;
        }
        listPos.size.h = size;
    }

    void ListView::updateVerticalList(components::ListView &list,
                                      components::Transform &listPos,
                                      int &count)
    {
        float current = listPos.position.x;
        float size = 0.0;
        for (auto elem: list.content) {
            count++;
            if (count < list.offset || (count > list.offset + list.size && list.size >= 0))
                continue ;
            auto &transform = elem->get<components::Transform>();
            transform.position.x = current;
            transform.position.y = listPos.position.y;
            transform.size.h = transform.size.h < listPos.size.h ? listPos.size.h : transform.size.h;
            transform.size.w = transform.size.w == 0 ? 0.5 : transform.size.w;
            listPos.size.h = transform.size.h > listPos.size.h ? transform.size.h : listPos.size.h;
            current += transform.size.w;
            size += transform.size.w;
        }
        listPos.size.w = size;
    }

    void ListView::update() {
        auto lists = entityManager->get<components::ListView>();
        for (auto &list: lists) {
            auto &listPos = list->getEntity().get<components::Transform>();
            int count = -1;
            if (list->order == futils::Ordering::Horizontal) {
                updateHorizontalList(*list, listPos, count);
            } else {
                updateVerticalList(*list, listPos, count);
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