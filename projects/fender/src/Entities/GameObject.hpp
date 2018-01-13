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
    protected:
        components::Transform *_transform;
        components::AbsoluteTransform *_absoluteTransform;
        components::Border *_border;

    public:
        GameObject() {
            attach<components::GameObject>();
            _transform = &attach<components::Transform>();
            _transform->position.z = 1;
           _absoluteTransform = &attach<components::AbsoluteTransform>();
            _border = &attach<components::Border>();
            _border->color = futils::Indianred;
            _border->thickness = 2;
            _border->visible = true;
        }
        ~GameObject() {
            detach<components::GameObject>();
            detach<components::Transform>();
            detach<components::AbsoluteTransform>();
        }

        void setPosition(int x, int y) {
            _transform->position.x = x;
            _transform->position.y = y;
        }

        void setSize(int w, int h) {
            _transform->size.x = w;
            _transform->size.y = h;
        }

        void setBorderVisibile(bool b) {
            _border->visible = b;
        }

    };
}

