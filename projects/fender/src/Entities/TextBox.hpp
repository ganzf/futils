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
            auto &upSize = _Up->get<components::Transform>();
            upSize.size.w = 0.5;
            upSize.size.h = 0.5;
            auto &upAction = _Up->get<components::Clickable>();
            upAction.func = [this](){
                if (_list->offset > 0)
                    _list->offset--;
            };
            _Down = &entityManager->create<Button>();
            auto &downSize = _Down->get<components::Transform>();
            downSize.size.w = 0.5;
            downSize.size.h = 0.5;
            auto &downAction = _Down->get<components::Clickable>();
            downAction.func = [this](){
                if (_list->offset + _list->size < (int)_list->content.size())
                    _list->offset++;
            };
            scrollView.content.push_back(_Up);
            scrollView.content.push_back(_Down);
            scrollView.fit = true;
        }

        void initStream(int size) {
            static int i = 0;
            i++;
            _stream = &entityManager->create<ListView>(size);
            auto &list = _stream->get<components::ListView>();
            list.name = "TextBoxTextStream" + std::to_string(i);
            list.order = futils::Ordering::Vertical;
            _list->content.push_back(_stream);
            list.fit = true;
        }
    public:
        explicit TextBox(int size = 1, bool scrollable = false) {
            afterBuild = [this, size, scrollable](){
                _list->name = "TextBoxContainer" + std::to_string(size);
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
