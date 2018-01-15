//
// Created by arroganz on 1/15/18.
//

#include "TextBox.hpp"
#include "Text.hpp"

namespace fender::entities
{
    TextBox &TextBox::operator << (std::string const &str)
    {
        auto txt = &entityManager->create<Text>(str);
        auto &border = txt->get<components::Border>();
        border.visible = false;
        _list->content.push_back(txt);
        return *this;
    }
}
