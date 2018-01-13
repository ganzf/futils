//
// Created by arroganz on 1/12/18.
//

#pragma once

# include "fender.hpp"
# include "Components/ListView.hpp"

namespace fender::entities {
    class ListView : public GameObject {
    public:
        ListView() {
            attach<components::ListView>();
        }
        ~ListView()
        {
            detach<components::ListView>();
        }
    };
}

