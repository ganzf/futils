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
        addReaction<futils::Keys>([this](futils::IMediatorPacket &pkg){
            static int i = 0;
            auto &key = futils::Mediator::rebuild<futils::Keys>(pkg);
            if (key == futils::Keys::U) {
                std::cout << "Update nbr " << i++ << std::endl;
                update();
            }
        });
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
        auto &t = list.getEntity().get<fender::components::Transform>();
        std::cout << "\t List " << list.name << " is now size(" << t.size.w << "," << t.size.h << ")" << std::endl;
    }

    void ListView::updateVerticalList(components::ListView &list)
    {
        std::cout << "Updating Vertical List positions of " << list.name << std::endl;
        auto &listPos = list.getEntity().get<components::Transform>();
        std::cout << "\t\t Position : " << listPos.position.x << ", " << listPos.position.y << std::endl;
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
            std::cout << "\t\t\t elem at " << transform.position.x <<", "<< transform.position.y << std::endl;
//            transform.size.w = transform.size.w < listPos.size.w ? listPos.size.w : transform.size.w;
//            transform.size.h = transform.size.h == 0 ? 0.5 : transform.size.h;
//            listPos.size.w = transform.size.w > listPos.size.w ? transform.size.w : listPos.size.w;
            current += transform.size.h;
            size += transform.size.h;
        }
        listPos.size.h = size;
        std::cout << "List is now " << size << " high." << std::endl;
    }

    void ListView::updateHorizontalList(components::ListView &list)
    {
        std::cout << "Updating Horizontal List positions of " << list.name << std::endl;
        auto &listPos = list.getEntity().get<components::Transform>();
        std::cout << "\t\t " << listPos.position.x << ", " << listPos.position.y << std::endl;
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
        std::cout << "List is now " << size << " wide." << std::endl;
    }

    void ListView::updateList(components::ListView &list)
    {
        std::cout << "Updating list " << list.name << std::endl;
        for (auto content : list.content)
        {
            if (content->has<components::ListView>()) {
                std::cout << "\t \e[034m [" << content->get<components::ListView>().name << "] \e[0m";
                if (content->get<components::ListView>().order == futils::Ordering::Horizontal)
                    std::cout << " <-> " << std::endl;
                else
                    std::cout << " | " << std::endl;
                // std::cout << "\t Recursion : updating " << content->get<components::ListView>().name << ", child of " << list.name << std::endl;
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
        for (auto &list: entityManager->get<components::ListView>()) {
            std::cout << "\e[033m UPDATING " << list->name << " \e[0m";
            if (list->order == futils::Ordering::Horizontal)
                std::cout << " <-> " << std::endl;
            else
                std::cout << " | " << std::endl;
            updateList(*list);
        }
    }

    void ListView::run(float) {
        switch (phase)
        {
            case 0: return init();
            case 1: return ;
        }
    }
}