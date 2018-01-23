//
// Created by arroganz on 1/1/18.
//

#include <Components/rigidBody.hpp>
#include "OtherSystem.hpp"
#include "Components/Color.hpp"
#include "Components/World.hpp"
#include "Entities/Image.hpp"
#include "Entities/Text.hpp"
#include "Entities/Button.hpp"
#include "inputKeys.hpp"
#include "Entities/ListView.hpp"
#include "Entities/InputField.hpp"
#include "Entities/TextBox.hpp"

void OtherSystem::initWindow()
{

}

void OtherSystem::initInputs()
{
    input = &entityManager->smartCreate<fender::entities::Input>();
    auto &component = input->get<fender::components::Input>();
    component.name = "OtherSystem";
    component.activated = true;
    futils::InputSequence escape;
    futils::InputAction action(futils::Keys::Escape, futils::InputState::Down);
    escape.actions.push_back(action);

    futils::InputSequence generate;
    futils::InputAction gen_action(futils::Keys::Space, futils::InputState::Down);
    generate.actions.push_back(gen_action);
    component.map[escape] = [this](){
        events->send<fender::events::Shutdown>();
        entityManager->removeSystem(name);
    };
    component.map[generate] = [this](){

    };
}

void OtherSystem::initGui() {
    auto *hud = &entityManager->smartCreate<fender::entities::ListView>(4);
    auto *debug = &entityManager->smartCreate<fender::entities::TextBox>(10, true);
//    auto &cam = camera->get<fender::components::Children>();
//    cam.add(*hud);
//    cam.add(*debug);
    debug->setBorderVisible(true);
    hud->setBorderVisible(true);
    hud->setSize(10, 3);

    auto &hudBorder = hud->get<fender::components::Border>();
    hudBorder.color = futils::Greenyellow;
    hudBorder.thickness = 4;

//    auto &hudOffset = hud->get<fender::components::ChildInfo>();
//    hudOffset.offset.x = 3.4;
//    // Bug 1 : La bordure commence pas en haut de l'ecran
//    hudOffset.offset.y = 3.5;

    auto &hudContent = hud->get<fender::components::ListView>();
    // hudContent.fit = true;

    auto *hudCell = &entityManager->smartCreate<fender::entities::ListView>();
    hudCell->setBorderVisible(true);
    auto &hudCellContent = hudCell->get<fender::components::ListView>();
    hudCellContent.padding = 0.25;
    hudCellContent.order = futils::Ordering::Horizontal;
    auto *cellImg = &entityManager->smartCreate<fender::entities::Image>("cells.png", futils::Vec2<float>(0, 0), futils::Vec2<float>(0.5, 0.5));
    // Bug 2 : Le contenu ne semble pas s'adapter a la taille du bouton, ni l'inverse...
    hudCellContent.fit = true;
    hudCellContent.content.push_back(cellImg);
    auto *cellCount = &entityManager->smartCreate<fender::entities::Text>("0");
    cellCount->setFontSize(16);
    cellCount->setColor(futils::Lightskyblue);
    hudCellContent.content.push_back(cellCount);
    hudContent.content.push_back(hudCell);

    auto *hudGold = &entityManager->smartCreate<fender::entities::ListView>();
    hudGold->setBorderVisible(true);
    auto &hudGoldContent = hudGold->get<fender::components::ListView>();
    hudGoldContent.padding = 0.25;
    hudGoldContent.order = futils::Ordering::Horizontal;
    auto *goldImg = &entityManager->smartCreate<fender::entities::Image>("golds.png", futils::Vec2<float>(0, 0), futils::Vec2<float>(0.5, 0.5));
    // Bug 3 : hud ne met pas bien les boutons les uns apres les autres
    hudGoldContent.fit = true;
    hudGoldContent.content.push_back(goldImg);
    auto *goldCount = &entityManager->smartCreate<fender::entities::Text>("729");
    goldCount->setFontSize(16);
    goldCount->setColor(futils::Goldenrod);
    hudGoldContent.content.push_back(goldCount);
    hudContent.content.push_back(hudGold);

    auto *hudInventory = &entityManager->smartCreate<fender::entities::ListView>();
    hudInventory->setBorderVisible(true);
    hudContent.content.push_back(hudInventory);
    auto &hudInventoryContent = hudInventory->get<fender::components::ListView>();
    hudInventoryContent.padding = 0.1;
    hudInventoryContent.order = futils::Ordering::Horizontal;
    auto *collar = &entityManager->smartCreate<fender::entities::Button>();
    auto &collarAction = collar->get<fender::components::Clickable>();
    collarAction.waitForRelease = true;

    auto &collarImg = collar->get<fender::components::Image>();
    collarImg.file = "collar.png";
    auto *collarLabel = &entityManager->smartCreate<fender::entities::Text>("Collar");
    collarLabel->setFontSize(16);
    collarLabel->setColor(futils::Mediumpurple);
    hudInventoryContent.content.push_back(collarLabel);
    hudInventoryContent.content.push_back(collar);

    // Debug Context
//    auto &debugOffset = debug->get<fender::components::ChildInfo>();
    auto &debugList = debug->get<fender::components::ListView>();
    // Attention, on ne peut pas acceder au padding de _stream...
    debugList.padding = 0.1;
//    debugOffset.offset.x = 66.5;
//    debugOffset.offset.y = 3.5;
    auto &debugTr = debug->get<fender::components::Transform>();
    debugTr.size.w = 8;
    *debug << 18 << "Starting debug..." << futils::endl;
    auto h = hud->get<fender::components::Transform>().size.h;
    *debug << "Hud is " << std::to_string(h) << " units high." << futils::endl;

    collarAction.func = [this, debug](){
        entityManager->removeSystem(name);
    };
}

void OtherSystem::run(float) {

}
