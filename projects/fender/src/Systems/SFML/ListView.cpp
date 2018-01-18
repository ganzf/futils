//
// Created by arroganz on 1/12/18.
//

#include <inputKeys.hpp>
#include "ListView.hpp"

namespace fender::systems::SFMLSystems
{
    void ListView::init()
    {
        __init();
        phase = 1;
    }

    void ListView::updateVerticalListSize(components::ListView &list)
    {
        auto &listPos = list.getEntity().get<components::Transform>();
        float size = 0.0;
        float current = listPos.position.y;
        int count = -1;
        for (auto elem: list.content) {
            count++;
            auto &transform = elem->get<components::Transform>();
            transform.size.w = transform.size.w < listPos.size.w ? listPos.size.w : transform.size.w;
            transform.size.h = transform.size.h == 0 ? 0.5 : transform.size.h;
            if (count >= list.offset && count < list.offset + list.size) {
                if (list.fit)
                    listPos.size.w = transform.size.w > listPos.size.w ? transform.size.w : listPos.size.w;
                current += transform.size.h;
                size += transform.size.h;
                if (list.fit)
                    listPos.size.h = size;
            }
        }
    }

    void ListView::updateHorizontalListSize(components::ListView &list)
    {
        auto &listPos = list.getEntity().get<components::Transform>();
        float size = 0.0;
        float current = listPos.position.y;
        int count = -1;
        for (auto elem: list.content) {
            count++;
            auto &transform = elem->get<components::Transform>();
            transform.size.h = transform.size.h < listPos.size.h ? listPos.size.h : transform.size.h;
            transform.size.w = transform.size.w == 0 ? 0.5 : transform.size.w;
            if (count >= list.offset && count < list.offset + list.size) {
                if (list.fit)
                    listPos.size.h = transform.size.h > listPos.size.h ? transform.size.h : listPos.size.h;
                current += transform.size.w;
                size += transform.size.w;
                if (list.fit)
                    listPos.size.h = size;
            }
        }
    }

    void ListView::updateListSize(components::ListView &list)
    {
        if (list.order == futils::Ordering::Vertical)
            updateVerticalListSize(list);
        else
            updateHorizontalListSize(list);
    }

    void ListView::updateVerticalList(components::ListView &list)
    {
        auto &listPos = list.getEntity().get<components::Transform>();
        int count = -1;
        float current = listPos.position.y;
        float size = 0.0;
        for (auto elem: list.content) {
            count++;
            auto &obj = elem->get<components::GameObject>();
            if (count < list.offset || (count >= list.offset + list.size && list.size >= 0)) {
                if (obj.visible) {
                    obj.visible = false;
                }
                continue ;
            } else
                obj.visible = true;
            auto &transform = elem->get<components::Transform>();
            transform.position.y = current;
            transform.position.x = listPos.position.x;
            current += transform.size.h;
            size += transform.size.h;
        }
    }

    void ListView::updateHorizontalList(components::ListView &list)
    {
        auto &listPos = list.getEntity().get<components::Transform>();
        int count = -1;
        float current = listPos.position.x;
        float size = 0.0;
        for (auto elem: list.content) {
            count++;
            if (count < list.offset || (count > list.offset + list.size && list.size >= 0)) {
                auto &obj = elem->get<components::GameObject>();
                if (obj.visible == true) {
                    obj.visible = false;
                }
                continue;
            }
            auto &transform = elem->get<components::Transform>();
            transform.position.x = current;
            transform.position.y = listPos.position.y;
            current += transform.size.w;
            size += transform.size.w;
        }
    }

    void ListView::updateList(components::ListView &list, int depth)
    {
        for (auto content : list.content)
        {
            if (content->has<components::ListView>())
                updateList(content->get<components::ListView>(), depth + 1);
        }
        updateListSize(list);
        if (list.order == futils::Ordering::Horizontal)
            updateHorizontalList(list);
        else
            updateVerticalList(list);
    }

    void ListView::update() {
        for (auto &list: entityManager->get<components::ListView>()) {
            updateList(*list, 0);
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