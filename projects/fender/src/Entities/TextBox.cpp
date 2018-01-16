//
// Created by arroganz on 1/15/18.
//

#include "TextBox.hpp"
#include "Text.hpp"

namespace fender::entities
{
    TextBox &TextBox::operator << (std::string const &str)
    {
        if (!_stream)
            return *this;
        auto txt = &entityManager->create<Text>(str);
        auto &border = txt->get<components::Border>();
        border.visible = false;
        auto &list = _stream->get<components::ListView>();
        if ((int)list.content.size() + 1 > list.size)
            list.offset++;
        list.content.push_back(txt);
        return *this;
    }
}
