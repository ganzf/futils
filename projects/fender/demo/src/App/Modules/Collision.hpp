//
// Created by arroganz on 1/24/18.
//


#pragma once

# include "AModule.hpp"

namespace demo::systems {
    class Ennemy : public fender::entities::GameObject {
    public:
        Ennemy(std::string const &img, futils::Vec2<float> const &pos = {0, 0}, futils::Vec2<float> size = {1, 1}) {
            auto &image = attach<fender::components::Image>();
            attach<fender::components::rigidBody>();
            image.file = img;
            setSize(size);
            setPosition(pos);
        }

        ~Ennemy() {
            detach<fender::components::Image>();
            detach<fender::components::rigidBody>();
        }

        void changeDirection() {
            auto &rb = get<fender::components::rigidBody>();
            rb.force.y = rb.force.y * - 1;
        }
    };

    class Collision: public AModule {
        Window *win{nullptr};
        Camera *camera{nullptr};
        World *world{nullptr};
        Input *input{nullptr};

        futils::FloatingRange<float> randomPop = futils::FloatingRange<float>(2.0, 15.0);
        futils::FloatingRange<float>     randomMove = futils::FloatingRange<float>(-1.0, 1.0);

        fender::entities::Image *poulpi{nullptr};
        Ennemy *ennemy{nullptr};

        void initInputs();
        void createEnemy();
        void createEntities();
        void init();
        void update();
    public:
        Collision(): AModule("Collision (Demo)") {}
        void run(float) override;
    };
}


