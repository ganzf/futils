//
// Created by arroganz on 1/15/18.
//

#include "TextBox.hpp"

namespace fender::entities
{
    TextBox &TextBox::operator << (std::string const &str)
    {
        if (!_stream)
            return *this;
        auto txt = &entityManager->create<Text>(str);
        auto &border = txt->get<components::Border>();
        border.visible = true;
        border.color = futils::Cadetblue;
        auto &list = _stream->get<components::ListView>();
        auto &tr = txt->get<components::Transform>();
        if (_scroll != nullptr) {
            std::cout << "Scrollable textbox has size " << this->get<components::Transform>().size << std::endl;
            tr.size.w = this->get<components::Transform>().size.w - _scroll->get<components::Transform>().size.w;
        } else {
            tr.size.w = _stream->get<components::Transform>().size.w;
        }
        if ((int)list.content.size() + 1 > list.size)
            list.offset++;
        list.content.push_back(txt);
        std::cout << "Inserted another text in " << list.name << " of size " << tr.size << std::endl;
        return *this;
    }
}
