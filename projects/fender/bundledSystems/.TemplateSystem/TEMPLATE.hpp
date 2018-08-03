//
// Created by TEMPLATE_MODULE_CREATOR on TEMPLATE_MODULE_CREATION_DATE
//

#pragma once
#include "ecs.hpp"

class TEMPLATE_MODULE_NAME : public futils::ISystem {
    int phase{0};
    void init();
public:
    TEMPLATE_MODULE_NAME();

    void run(float) final;
};
