//
// Created by arroganz on 1/12/18.
//


#pragma once

# include "System.hpp"
# include "Components/ListView.hpp"

namespace fender::systems::SFMLSystems {
    class ListView : public System {
        void init();
        void update();
    public:
        ListView(): System("ListView") {

        }
        void run(float) override;
    };
}


