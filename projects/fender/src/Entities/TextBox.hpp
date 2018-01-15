//
// Created by arroganz on 1/15/18.
//


#pragma once

# include "fender.hpp"
# include "ListView.hpp"
# include "Text.hpp"

namespace fender::entities {
    class TextBox : public ListView {
    public:
        explicit TextBox(int size = 1) {
            _list->order = futils::Ordering::Vertical;
            afterBuild = [this, size](){
                auto tmp = 0;
                while (tmp < size)
                {
                    auto txt = &entityManager->create<entities::Text>("");
                    auto &border = txt->get<components::Border>();
                    border.visible = false;
                    _list->content.push_back(txt);
                    tmp++;
                }
                std::cout << "Text box created with " << tmp << " lines" << std::endl;
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
