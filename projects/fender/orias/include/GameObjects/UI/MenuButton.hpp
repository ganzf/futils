//
// Created by arroganz on 7/29/18.
//


#pragma once

# include <Components/Color.hpp>
# include "Button.hpp"

namespace orias::ui {
    class MenuButton : public Button {
    public:
        MenuButton(std::string const &label, std::function<void()> func):
                Button(label, 14, 3, 18) {
            this->setPosition(-7, -1.5f);
            auto &c = attach<fender::components::Color>();
            c.color = futils::Blanchedalmond;
            auto &buttonClickable = get<fender::components::Clickable>();
            buttonClickable.waitForRelease = true;
            buttonClickable.func = func;
        }

        ~MenuButton() {
            detach<fender::components::Color>();
        }
    };
}