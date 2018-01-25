//
// Created by arroganz on 1/23/18.
//


#pragma once

# include "Components/Color.hpp"
# include "Components/ViewInfo.hpp"
# include "AModule.hpp"
# include "ecs.hpp"

namespace demo::systems
{
    /*
     * Loader is the first module of the demo
     * It will create a small window with a demo-selector list.
     * It will display a background, maybe some music...
     */
    class Loader : public AModule {
        /*
         * I recommend using using for clearer code
         */
        Window *_win {nullptr};
        Camera *_cam {nullptr};
        World *_world {nullptr};
        Input *_input {nullptr};
        // Main container
        ListView *_mainFrame{nullptr};
        ListView *_leftFrame{nullptr};
        // Right side of demo with vertical ordering
        ListView *_rightFrame{nullptr};
        // Debug Container
        ListView *_debug{nullptr};
        // Demo Selector
        ListView *_selector{nullptr};

        std::string currentDemo{""};

        // Simple init function
        void init();
        void initInputs();
        void initInputsCam();
        void initMainFrame();
        void loadExtensions();
        void loadDefaults();

        void add(std::string const &label, std::function<void()> func, futils::Color filter = futils::White)
        {
            auto &leftContent = _leftFrame->get<fender::components::ListView>();
            auto *button = &entityManager->smartCreate<fender::entities::Button>();
            button->setBorderVisible(false);
            button->borderColor(futils::Sandybrown);
            auto &buttonImg = button->get<fender::components::Image>();
            auto &buttonColor = button->attach<fender::components::Color>();
            buttonColor.color = filter;
            buttonImg.file = "button.jpg";
            auto &buttonTxt = button->get<fender::components::Text>();
            buttonTxt.str = label;
            buttonTxt.style.font = "jedi.ttf";
            buttonTxt.style.color = futils::White;
            buttonTxt.style.size = 12;
            buttonTxt.style.valign = futils::VAlign::Middle;
            buttonTxt.style.align = futils::Align::Center;
            auto &buttonTr = button->get<fender::components::Transform>();
            buttonTr.size.w = _leftFrame->get<fender::components::Transform>().size.w;
            buttonTr.size.h = 1.75;

            auto &action = button->get<fender::components::Clickable>();
            action.func = func;
            action.waitForRelease = true;

            leftContent.content.push_back(button);
        }

    public:
        Loader() : AModule("Loader") {}
        void run(float) override;
    };
}

