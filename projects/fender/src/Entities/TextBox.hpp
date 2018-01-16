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
        ListView *_scroll{nullptr};
        ListView *_stream{nullptr};
        Button *_Up{nullptr};
        Button *_Down{nullptr};

        void initScroll()
        {
            _list->order = futils::Ordering::Horizontal;
            _scroll = &entityManager->create<ListView>();
            _list->content.push_back(_scroll);
            auto &scrollView = _scroll->get<components::ListView>();
            scrollView.name = "ScrollView";
            _Up = &entityManager->create<Button>();
            auto &upAction = _Up->get<components::Clickable>();
            upAction.func = [this](){
                if (_list->offset > 0)
                    _list->offset--;
            };
            _Down = &entityManager->create<Button>();
            auto &downAction = _Down->get<components::Clickable>();
            downAction.func = [this](){
                if (_list->offset < _list->size)
                    _list->offset++;
            };
            scrollView.content.push_back(_Up);
            scrollView.content.push_back(_Down);
        }

        void initStream(int size) {
            _stream = &entityManager->create<ListView>(size);
            auto &list = _stream->get<components::ListView>();
            list.name = "TextBoxTextStream";
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
            _list->content.push_back(_stream);
        }
    public:
        explicit TextBox(int size = 1, bool scrollable = false) {
            afterBuild = [this, size, scrollable](){
                _list->name = "TextBoxContainer";
                if (scrollable) {
                    initScroll();
                    initStream(size);
                } else {
                    initStream(size);
                }
            };
        }
        TextBox &operator << (std::string const &str);
    };
}
