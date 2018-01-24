//
// Created by arroganz on 1/13/18.
//


#pragma once

#include <Components/Clickable.hpp>
# include "fender.hpp"
# include "GameObject.hpp"
# include "Components/Editable.hpp"
# include "Components/Text.hpp"


namespace fender::entities {
    class InputField : public GameObject {
    public:
        InputField(std::string const &placeholder = "") {
            attach<components::Editable>();
            auto &text = attach<components::Text>();
            text.str = placeholder;
        }
        ~InputField(){
            detach<components::Editable>();
            detach<components::Text>();
        }
    };
}


