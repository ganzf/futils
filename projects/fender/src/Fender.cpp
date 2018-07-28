//
// Created by arroganz on 11/26/17.
//

#include <Systems/Log.hpp>
# include "fender.hpp"
# include "sigCatch.hpp"
# include "goToBinDir.hpp"

extern "C" fender::Fender *Fender(std::string const &execPath) {
    return new fender::Fender(execPath);
}

static bool interrupt = false;

void onSigint(int)
{
  std::cout << "Interrupt signal received. Shutting down." << std::endl;
  interrupt = true;
}

fender::Fender::Fender(std::string const &arg0) {
    futils::goToBinDir(arg0);

    entityManager = std::make_unique<futils::EntityManager>();
    events = std::make_unique<futils::Mediator>();
    entityManager->provideMediator(*events);
    futils::SigHandler &sig = futils::SigHandler::inst();
    sig.set(SIGINT, onSigint);
}

void fender::Fender::loadSystemDir(std::string const &path)
{
    events->send("Loading systems in " + path);
}

int fender::Fender::start(std::string const &configFilePath) {
    // Here I should probably load the dir with all modules
    addSystem<systems::Log>();
    this->loadSystemDir(configFilePath);
//    entityManager->run(); // I Want log to be the first thing to exist so that any string event can be tracked.
//    addSystem<systems::Fysics>();
//    entityManager->run(); // This way, the output is more coherent
//    addSystem<systems::SFMLRenderer>();
    return entityManager->run(); // this will init all systems
}

int fender::Fender::run() {
    int64_t runs = 0;
    for (;entityManager->getNumberOfSystems() > 0; runs++) {
        if (entityManager->run() != 0 || interrupt)
            break ;
    }
    events->send<std::string>("Fender shutting down. Ran " + std::to_string(runs) + " times.");
    events->send<events::Shutdown>();
    entityManager->cleanSystems();
    return 0;
}
