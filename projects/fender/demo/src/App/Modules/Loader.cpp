//
// Created by arroganz on 1/23/18.
//

#include <Entities/Sprite.hpp>
#include "Components/rigidBody.hpp"
#include "Loader.hpp"
#include "Text.hpp"
#include "Grid.hpp"
#include "Dir.hpp"
#include "Menu.hpp"
#include "Collision.hpp"
#include "Runner.hpp"
#include "AdvancedGUI.hpp"

namespace demo::systems
{
    void Loader::initInputsCam() {
        auto &input = _input->get<fender::components::Input>();

        futils::InputSequence up;
        futils::InputAction actionUp(futils::Keys::ArrowUp, futils::InputState::GoingDown);
        up.actions.push_back(actionUp);

        futils::InputSequence down;
        futils::InputAction actionDown(futils::Keys::ArrowDown, futils::InputState::GoingDown);
        down.actions.push_back(actionDown);

        futils::InputSequence left;
        futils::InputAction actionLeft(futils::Keys::ArrowLeft, futils::InputState::GoingDown);
        left.actions.push_back(actionLeft);

        futils::InputSequence right;
        futils::InputAction actionRight(futils::Keys::ArrowRight, futils::InputState::GoingDown);
        right.actions.push_back(actionRight);

        input.map[up] = [this]() {
            _cam->setPosition(_cam->getPositionX(), _cam->getPositionY() - 1);
        };
        input.map[down] = [this]() {
            _cam->setPosition(_cam->getPositionX(), _cam->getPositionY() + 1);
        };
        input.map[left] = [this]() {
            _cam->setPosition(_cam->getPositionX() - 1, _cam->getPositionY());
        };
        input.map[right] = [this]() {
            _cam->setPosition(_cam->getPositionX() + 1, _cam->getPositionY());
        };
    }
    void Loader::initInputs() {
        addReaction<futils::SystemDestroyed>([this](futils::IMediatorPacket &pkg){
           auto &packet = futils::Mediator::rebuild<futils::SystemDestroyed>(pkg);
            if (packet.name == currentDemo)
            {
                auto &inputC = _input->get<fender::components::Input>();
                inputC.activated = true;
            }
        });

        _input = &entityManager->smartCreate<fender::entities::Input>();
        auto &input = _input->get<fender::components::Input>();

        futils::InputSequence escape;
        futils::InputAction action(futils::Keys::Escape, futils::InputState::GoingDown);
        escape.actions.push_back(action);

        input.map[escape] = [this]() {
            events->send<fender::events::Shutdown>();
        };
        input.activated = true;
    }
    void Loader::loadExtensions() {
        auto &rightContent = _rightFrame->get<fender::components::ListView>();
        rightContent.order = futils::Ordering::Vertical;

        auto *sprite = &entityManager->smartCreate<fender::entities::Sprite>(0.04, true);
        sprite->setBorderVisible(false);
        sprite->autoLoad("spritesheet.png", futils::Vec2<int>(4, 4), futils::Vec2<int>(128, 128));
        auto &gui = _cam->get<fender::components::Children>();
        gui.add(*sprite);
        auto &spriteInfos = sprite->get<fender::components::ChildInfo>();
        spriteInfos.relSize.w = 30;
        spriteInfos.relSize.h = 30;
        spriteInfos.offset.x = 50;
        spriteInfos.offset.y = 50;

        futils::Dir modules("./src/App/Extensions");
        int found = 0;
        for (auto &file: modules.getContent()) {
            auto systemName = futils::split(file, '/').back();
            if ((file.find(".so") == std::string::npos
                 && file.find(".dll") == std::string::npos)
                || systemName == "Loader.cpp")
                continue ;

            auto *b = &entityManager->smartCreate<fender::entities::Button>();
            b->borderColor(futils::Gray);
            b->setBorderVisible(true);
            auto &bText = b->get<fender::components::Text>();
            bText.str = "Load";
            if (bText.str == "Loader.cpp")
                continue ;
            bText.style.size = 18;
            bText.style.font = "earthorbiter.ttf";
            bText.style.color = futils::Crimson;
            bText.style.align = futils::Align::Center;
            bText.style.valign = futils::VAlign::Middle;
            bText.style.mod = futils::TextModifier::Bold;

            auto &bImg = b->get<fender::components::Image>();
            bImg.file = "button.png";
            auto &alterColor = b->attach<fender::components::Color>();
            alterColor.color = futils::Peacock;

            auto &bTr = b->get<fender::components::Transform>();
            bTr.size.w = 2;
            bTr.size.h = 1.33;

            auto &bAction = b->get<fender::components::Clickable>();
            bAction.waitForRelease = true;
            auto *label = &entityManager->smartCreate<fender::entities::Text>(systemName);
            label->setBorderVisible(false);
            bAction.func = [this, file, &bText, label, systemName](){
                static auto bState = 0;
                static std::string sysName = "";
                auto &labelC = label->get<fender::components::Text>();
                if (bState == 0) {
                    futils::LoadStatus status = this->entityManager->loadSystem(file);
                    if (!status.loaded) {
                        fender::events::Alert alert;
                        alert.what = "Failed to load extension in " + file;
                        events->send<fender::events::Alert>(alert);
                        labelC.style.color = futils::Crimson;
                        return ;
                    } else {
                        sysName = status.sysName;
                        bText.str = "X";
                        bText.style.color = futils::Crimson;
                        labelC.style.color = futils::Green;
                        labelC.str = systemName + " : [" + sysName + "]";
                        bState = 1;
                    }
                } else {
                    this->entityManager->removeSystem(sysName);
                    bText.str = "load";
                    bText.style.color = futils::White;
                    labelC.style.color = futils::White;
                    bState = 0;
                }
            };

            auto *list = &entityManager->smartCreate<fender::entities::ListView>();
            auto &listC = list->get<fender::components::ListView>();
            listC.order = futils::Ordering::Horizontal;

            auto &labelTr = label->get<fender::components::Transform>();
            labelTr.size.w = 12;
            labelTr.size.h = 1.33;
            listC.content.push_back(label);
            listC.content.push_back(b);
            auto &listTr = list->get<fender::components::Transform>();
            listTr.size.w = 8;
            listTr.size.h = 1.33;
            list->setBorderVisible(false);
            rightContent.content.push_back(list);
            found++;
        }
        if (found == 0)
        {
            auto *NoData = &entityManager->smartCreate<fender::entities::Button>();
            NoData->setSize(_rightFrame->get<fender::components::Transform>().size.w, 3);
            NoData->borderColor(futils::Cadmiumyellow);
            NoData->setBorderVisible(true);
            auto &noDataTxt = NoData->get<fender::components::Text>();
            noDataTxt.str = "No extensions in src/App/Extensions.";
            noDataTxt.style.size = noDataTxt.str.size() / 2;
            noDataTxt.style.font = "earthorbiter.ttf";
            noDataTxt.style.mod = futils::TextModifier::Bold;
            noDataTxt.style.valign = futils::VAlign::Middle;
            noDataTxt.style.align = futils::Align::Center;
            noDataTxt.style.color = futils::White;

            NoData->detach<fender::components::Image>();

            NoData->detach<fender::components::Hoverable>();
            NoData->detach<fender::components::Clickable>();
            rightContent.content.push_back(NoData);
        }
    }
    void Loader::loadDefaults() {
        auto &leftContent = _leftFrame->get<fender::components::ListView>();
        auto *Header = &entityManager->smartCreate<fender::entities::Text>("Available Demos");
        Header->setBorderVisible(true);
        Header->borderColor(futils::White);
        auto &headerTxt = Header->get<fender::components::Text>();
        headerTxt.style.font = "earthorbiter.ttf";
        headerTxt.style.color = futils::White;
        headerTxt.style.size = 18;
        headerTxt.style.valign = futils::VAlign::Middle;
        headerTxt.style.align = futils::Align::Center;
        auto &headerTr = Header->get<fender::components::Transform>();
        headerTr.size.w = _leftFrame->get<fender::components::Transform>().size.w;
        headerTr.size.h = 1;
        leftContent.content.push_back(Header);

        add("Grid", [this](){
            auto &inputC = _input->get<fender::components::Input>();
            inputC.activated = false;
            currentDemo = "Grid (Demo)";
            fender::events::ChangeGridColor cgc;
            entityManager->addSystem<systems::Grid>();
        }, futils::Crimson);
        add("Text", [this](){
            auto &inputC = _input->get<fender::components::Input>();
            inputC.activated = false;
            currentDemo = "Text (Demo)";
            entityManager->addSystem<systems::Text>();
        }, futils::Green);
        add("Menu", [this](){
            auto &inputC = _input->get<fender::components::Input>();
            inputC.activated = false;
            currentDemo = "Menu (Demo)";
            entityManager->addSystem<systems::Menu>();
        }, futils::Lightblue);
        add("Advanced gui", [this](){
            auto &inputC = _input->get<fender::components::Input>();
            inputC.activated = false;
            currentDemo = "AdvancedGUI";
            entityManager->addSystem<systems::AdvancedGUI>();
        }, futils::Green);
        add("Collision", [this](){
            auto &inputC = _input->get<fender::components::Input>();
            inputC.activated = false;
            currentDemo = "Collision (Demo)";
            entityManager->addSystem<systems::Collision>();
        }, futils::Goldenrod);
        add("Runner", [this](){
            auto &inputC = _input->get<fender::components::Input>();
            inputC.activated = false;
            currentDemo = "Runner";
            entityManager->addSystem<systems::Runner>();
        }, futils::Mediumvioletred);
    }
    void Loader::initMainFrame() {
        // entityManager->smartCreate<fender::entities::Image>("poulpi.png", futils::Vec2<float >{0, 0}, futils::Vec2<float>{10, 10});
        auto &gui = _cam->get<fender::components::Children>();
        _mainFrame = &entityManager->smartCreate<ListView>();
        _mainFrame->setBorderVisible(false);
        _mainFrame->borderColor(futils::Crimson);
        gui.add(*_mainFrame);
        auto &mainSize = _mainFrame->get<fender::components::ChildInfo>();
        mainSize.offset.x = 2;
        mainSize.offset.y = 2;
        mainSize.relSize.w = 96;
        mainSize.relSize.h = 96;
        auto &mainContent = _mainFrame->get<fender::components::ListView>();
        mainContent.padding = 0.5;
        mainContent.order = futils::Ordering::Horizontal;

        // Add content ...
        // Ajouter relative size ou modifier le systeme avec des booleans ? :/
        _leftFrame = &entityManager->smartCreate<ListView>();
        _leftFrame->setBorderVisible(false);
        _leftFrame->borderColor(futils::White);
        auto &leftRelSize = _leftFrame->attach<fender::components::ViewInfo>();
        leftRelSize.w = 33.333;
        leftRelSize.h = 100;

        _rightFrame = &entityManager->smartCreate<ListView>();
        _rightFrame->setBorderVisible(false);
        _rightFrame->borderColor(futils::Greenyellow);
        auto &rightRelSize = _rightFrame->attach<fender::components::ViewInfo>();
        rightRelSize.w = 100 - leftRelSize.w - 2;
        rightRelSize.h = 100;

        mainContent.content.push_back(_leftFrame);
        mainContent.content.push_back(_rightFrame);
        loadExtensions();
        loadDefaults();
    }
    void Loader::init() {
        _win = &entityManager->smartCreate<Window>(800, 600, "Demo Test", futils::WStyle::Default, futils::Granite);
        _win->setVisible(true);

        _cam = &entityManager->smartCreate<Camera>(_win);
        _cam->setActivated(true);

        _world = &entityManager->smartCreate<World>("Loader");

        initInputs();
        initInputsCam();
        initMainFrame();
    }
    void Loader::run(float) {
        if (!_win) return init();
    }
}