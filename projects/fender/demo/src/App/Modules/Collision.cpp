//
// Created by arroganz on 1/24/18.
//

#include "Collision.hpp"

using Vec2 = futils::Vec2<float>;

namespace demo::systems
{
    void Collision::initInputs() {
        input = &entityManager->smartCreate<Input>();
        input->setActivated(true);
        auto &inputC = input->get<fender::components::Input>();
        inputC.map[futils::Keys::Escape] = [this](){
            entityManager->removeSystem(name);
        };
        inputC.map[futils::Keys::ArrowDown] = [this]() {
            poulpi->setPosition(poulpi->getPositionX(), poulpi->getPositionY() + 1);
        };
        inputC.map[futils::Keys::ArrowUp] = [this]() {
            poulpi->setPosition(poulpi->getPositionX(), poulpi->getPositionY() - 1);
        };
        inputC.map[futils::Keys::Space] = [this]() {
            auto *bullet = &entityManager->smartCreate<Ennemy>("golds.png");
            bullet->setPosition(poulpi->getPositionX() + 3, poulpi->getPositionY());
            auto &rigidBody = bullet->get<fender::components::rigidBody>();
            bullet->setBorderVisible(false);
            rigidBody.weight = 0;
            rigidBody.force = futils::Vec3<float>{10, 0, 0};
        };
    }

    void Collision::createEnemy() {
        ennemy = &entityManager->smartCreate<Ennemy>("poulpi.png", Vec2(15, randomPop.getRandom()));
        ennemy->setBorderVisible(false);

        auto &rb = ennemy->get<fender::components::rigidBody>();
        rb.weight = 0;

        rb.force = futils::Vec3<float>(0, 3, 0);
    }

    void Collision::createEntities() {
        poulpi = &entityManager->smartCreate<fender::entities::Image>("ship.jpg", Vec2{2, 15}, Vec2{2, 2});
        poulpi->setBorderVisible(false);

        createEnemy();
    }

    void Collision::init() {
        win = &entityManager->smartCreate<Window>(800, 600, "[Collision (Demo)]");
        win->setVisible(true);

        world = &entityManager->smartCreate<World>("CollisionWorld");

        camera = &entityManager->smartCreate<Camera>(win);
        camera->setActivated(true);
        camera->setPosition(10, 10);

        addReaction<fender::events::Collision>([this](futils::IMediatorPacket &pkg){
            auto &packet = futils::Mediator::rebuild<fender::events::Collision>(pkg);

            entityManager->destroy(*(packet.first));
            entityManager->destroy((*packet.second));

            createEnemy();
        });

        initInputs();
        createEntities();
    }
    void Collision::update() {
        if (ennemy != nullptr) {
            if (randomPop.getRandom() > 14.5) {
                auto *bullet = &entityManager->smartCreate<Ennemy>("golds.png");
                bullet->setPosition(ennemy->getPositionX() - 2, ennemy->getPositionY());
                auto &rigidBody = bullet->get<fender::components::rigidBody>();
                bullet->setBorderVisible(false);
                rigidBody.weight = 0;
                rigidBody.force = futils::Vec3<float>{-5, 0, 0};
            }

            if (ennemy->getPositionY() < 2 || ennemy->getPositionY() > 17)
                ennemy->changeDirection();
        }
    }

    void Collision::run(float elapsed) {
        static float time = 0.0;

        time += elapsed;
        switch (state) {
            case 0:
                state = 1;
                return init();
            case 1:
            {
                if (time > 0.1) {
                    time = 0.0;
                    return update();
                }
            }
        }
    }
}