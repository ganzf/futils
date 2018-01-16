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

    void ListView::updateVerticalListSize(components::ListView &list)
    {
        auto &listPos = list.getEntity().get<components::Transform>();
        float size = 0.0;
        float current = listPos.position.y;
        for (auto elem: list.content) {
            auto &transform = elem->get<components::Transform>();
            transform.size.w = transform.size.w < listPos.size.w ? listPos.size.w : transform.size.w;
            transform.size.h = transform.size.h == 0 ? 0.5 : transform.size.h;
            listPos.size.w = transform.size.w > listPos.size.w ? transform.size.w : listPos.size.w;
            current += transform.size.h;
            size += transform.size.h;
        }
        listPos.size.h = size;
    }

    void ListView::updateHorizontalListSize(components::ListView &list)
    {
        auto &listPos = list.getEntity().get<components::Transform>();
        float size = 0.0;
        float current = listPos.position.y;
        for (auto elem: list.content) {
            auto &transform = elem->get<components::Transform>();
            transform.size.h = transform.size.h < listPos.size.h ? listPos.size.h : transform.size.h;
            transform.size.w = transform.size.w == 0 ? 0.5 : transform.size.w;
            listPos.size.h = transform.size.h > listPos.size.h ? transform.size.h : listPos.size.h;
            current += transform.size.w;
            size += transform.size.w;
        }
        listPos.size.h = size;
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
        std::cout << "Updating Vertical List positions of " << list.name << std::endl;
        auto &listPos = list.getEntity().get<components::Transform>();
        int count = -1;
        float current = listPos.position.y;
        float size = 0.0;
        for (auto elem: list.content) {
            count++;
            if (count < list.offset || (count > list.offset + list.size && list.size >= 0)) {
                auto &obj = elem->get<components::GameObject>();
                obj.visible = false;
                continue ;
            }
            auto &transform = elem->get<components::Transform>();
            transform.position.y = current;
            transform.position.x = listPos.position.x;
//            transform.size.w = transform.size.w < listPos.size.w ? listPos.size.w : transform.size.w;
//            transform.size.h = transform.size.h == 0 ? 0.5 : transform.size.h;
//            listPos.size.w = transform.size.w > listPos.size.w ? transform.size.w : listPos.size.w;
            current += transform.size.h;
            size += transform.size.h;
        }
        listPos.size.h = size;
    }

    void ListView::updateHorizontalList(components::ListView &list)
    {
        std::cout << "Updating Horizontal List positions of " << list.name << std::endl;
        auto &listPos = list.getEntity().get<components::Transform>();
        int count = -1;
        float current = listPos.position.x;
        float size = 0.0;
        for (auto elem: list.content) {
            count++;
            if (count < list.offset || (count > list.offset + list.size && list.size >= 0)) {
                auto &obj = elem->get<components::GameObject>();
                obj.visible = false;
                continue;
            }
            auto &transform = elem->get<components::Transform>();
            transform.position.x = current;
            transform.position.y = listPos.position.y;
//            transform.size.h = transform.size.h < listPos.size.h ? listPos.size.h : transform.size.h;
//            transform.size.w = transform.size.w == 0 ? 0.5 : transform.size.w;
//            listPos.size.h = transform.size.h > listPos.size.h ? transform.size.h : listPos.size.h;
            current += transform.size.w;
            size += transform.size.w;
        }
        listPos.size.w = size;
    }

    void ListView::updateList(components::ListView &list)
    {
        std::cout << "Updating list " << list.name << std::endl;
        for (auto content : list.content)
        {
            if (content->has<components::ListView>()) {
                std::cout << "\t Recursion : updating " << content->get<components::ListView>().name << ", child of " << list.name << std::endl;
                updateList(content->get<components::ListView>());
            }
        }
        std::cout << "Updating list size of " << list.name << std::endl;
        updateListSize(list);
        if (list.order == futils::Ordering::Horizontal)
            updateHorizontalList(list);
        else
            updateVerticalList(list);
    }

    void ListView::update() {
        for (auto &list: entityManager->get<components::ListView>())
            updateList(*list);
    }

    void ListView::run(float) {
        switch (phase)
        {
            case 0: return init();
            case 1: return update();
        }
    }
}