//
// Created by arroganz on 1/3/18.
//


#pragma once

#include <Components/AbsoluteTransform.hpp>
#include <Components/Border.hpp>
# include "fender.hpp"
# include "Components/GameObject.hpp"
# include "Components/Transform.hpp"

namespace fender::entities {
    class GameObject : public futils::IEntity {
        components::GameObject *object{nullptr};
        components::AbsoluteTransform *absTransform{nullptr};
        components::Transform *transform;
        components::Border *border;

    public:
        GameObject() {
            object = &attach<components::GameObject>();
            transform = &attach<components::Transform>();
            transform->position.z = 1;
            absTransform = &attach<components::AbsoluteTransform>();
            border = &attach<components::Border>();
            border->color = futils::Indianred;
            border->thickness = 2;
            border->visible = true;
        }

        ~GameObject() {
            detach<components::GameObject>();
            detach<components::Transform>();
            detach<components::AbsoluteTransform>();
        }

        void setSize(float width, float height) {
            transform->size.x = width;
            transform->size.y = height;
        }

        void setSize(futils::Vec2<float> const &size) {
            transform->size.x = size.w;
            transform->size.y = size.h;
        }

        void setPosition(float x, float y) {
            transform->position.x = x;
            transform->position.y = y;
        }

        void setPosition(futils::Vec2<float> const &pos) {
            transform->position.x = pos.x;
            transform->position.y = pos.y;
        }

        void setPosition(float x, float y, float z) {
            transform->position.x = x;
            transform->position.y = y;
            transform->position.z = z;
        }

        void setBorderVisible(bool visible) {
            border->visible = visible;
        }

        void hide() {
            object->hide();
        }

        void show() {
            object->show();
        }

    };
}

