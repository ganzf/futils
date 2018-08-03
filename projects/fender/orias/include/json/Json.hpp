//
// Created by arroganz on 7/30/18.
//


#pragma once
# include <fstream>
# include "json/json.h"

using JsonObject = Json::Value;

namespace orias::utils {
    class Json {
        JsonObject object;
    public:
        explicit Json(std::string const &file) {
            std::ifstream jsonFile(file, std::ifstream::binary);
            jsonFile >> object;
        }

        JsonObject const &get() const {
            return object;
        }

        JsonObject const &operator [] (std::string const &key) const {
            return object[key];
        }
    };
}

