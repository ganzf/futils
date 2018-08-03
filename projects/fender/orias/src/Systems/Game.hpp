//
// Created by arroganz on 7/30/18.
//


#pragma once

#include <ecs.hpp>
#include <json/Json.hpp>
#include <events.hpp>
#include <GameObjects/Game/Player.hpp>

namespace orias::scenes {
    class Game: public futils::ISystem {
        int state{0};
        void init();
        orias::game::Player *player{nullptr};

    public:
        explicit Game() {
            name = "Game";
            afterBuild = [this](){
                addReaction<fender::events::Shutdown>([this](futils::IMediatorPacket &){
                    entityManager->removeSystem(name);
                });
                this->init();
            };
        }
        virtual void run(float) final;
    };
}

