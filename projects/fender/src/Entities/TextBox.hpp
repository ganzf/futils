//
// Created by arroganz on 1/15/18.
//


#pragma once

# include "fender.hpp"
# include "ListView.hpp"
# include "Text.hpp"
#include "Button.hpp"

namespace fender::entities {
    class TextBox : public ListView {
        void initTextList(components::ListView &list, int size)
        {
            list.order = futils::Ordering::Vertical;
            auto tmp = 0;
            while (tmp < size)
            {
                auto txt = &entityManager->create<entities::Text>("");
                auto &border = txt->get<components::Border>();
                border.visible = false;
                list.content.push_back(txt);
                tmp++;
            }
            _list = &list;
        }
        void goUp()
        {

        }

        void goDown()
        {

        }

    public:
        explicit TextBox(int size = 1, bool scrollable = false) {
            //TODO: Remove rng
            futils::IntegralRange rng(0, 100);
            if (rng.getRandom() < 50)
                scrollable = !scrollable;

            afterBuild = [this, size, scrollable](){
                if (scrollable) {
                    _list->order = futils::Ordering::Horizontal;
                    auto *scrollbarContainer = &entityManager->create<entities::ListView>();
                    auto &scrollBarContent = scrollbarContainer->get<components::ListView>();
                    scrollBarContent.order = futils::Ordering::Vertical;
                    auto buttonUp = &entityManager->create<Button>();
                    auto &onUp = buttonUp->get<components::Clickable>();
                    onUp.func = [this](){
                        this->goUp();
                    };
                    auto buttonDown = &entityManager->create<Button>();
                    auto &onDown = buttonDown->get<components::Clickable>();
                    onDown.func = [this](){
                        this->goDown();
                    };
                    scrollBarContent.content.push_back(buttonUp);
                    scrollBarContent.content.push_back(buttonDown);
                    auto &scrollBorder = scrollbarContainer->get<components::Border>();
                    scrollBorder.visible = true;
                    scrollBorder.color = futils::Orange;
                    _list->content.push_back(scrollbarContainer);
                    auto *box = &entityManager->create<entities::ListView>();
                    initTextList(box->get<components::ListView>(), size);
                    auto &boxBorder = box->get<components::Border>();
                    boxBorder.visible = true;
                    boxBorder.color = futils::Pink;
                    _list->content.push_back(box);
                } else {
                    initTextList(*_list, size);
                }
            };
        }
        TextBox &operator << (std::string const &str);
    };
}

//namespace fender
//{
//    class TextBoxOutput
//    {
//        entities::TextBox &textBox;
//        std::string str;
//    public:
//        TextBoxOutput(entities::TextBox &textBox, std::string const &str = ""): textBox(textBox), str(str) {}
//        void set(std::string const &string){
//            str = string;
//        }
//        std::string const &get() const {
//            return str;
//        }
//    };
//}
