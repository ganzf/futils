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
        components::Editable *_editable{nullptr};
        components::Text *_text{nullptr};
    public:
        InputField(std::string const &placeholder = "") {
            _editable = &attach<components::Editable>();
            _text = &attach<components::Text>();
            _text->str = placeholder;
        }
        ~InputField(){
            detach<components::Editable>();
            detach<components::Text>();
        }
    };
}


