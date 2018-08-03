# include "fender.hpp"
# include "Systems/Splashscreen.hpp"
# include "json/Json.hpp"

int main(int, char **av)
{
    fender::Fender engine(av[0]);
    orias::utils::Json config("./config.json");
    auto const &dependencies = config["dependencies"];

    fender::StartParameters params;
    params.logWhenLoading = dependencies["logWhenLoading"].asBool();
    params.recursive = dependencies["recursiveLoading"].asBool();
    params.configFilePath = dependencies["directory"].asString();

    if (engine.start(params) != 0)
        return 1;
    engine.addSystem<orias::scenes::Splashscreen>(config);
    engine.run();
    return 0;
}
