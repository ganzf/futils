//
// Created by arroganz on 11/26/17.
//

# include <string>
# include <iostream>
# include <experimental/filesystem>
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
    std::cout << "Loading all systems in " << path << std::endl;
    const auto fsPath = std::experimental::filesystem::path(path);
    int count = 0;
    for (auto & p : std::experimental::filesystem::directory_iterator(fsPath)) {
        std::cout << "-> Loading " << p << " from " << path << std::endl;
        loadSystem(p.path());
        count += 1;
    }
}

int fender::Fender::start(std::string const &configFilePath) {
    // Here I should probably load the dir with all modules
    this->loadSystemDir(configFilePath);
    return entityManager->run(); // this will init all systems
}

int fender::Fender::run() {
    int64_t runs = 0;
    events->send<std::string>("Fender running...");
    for (;entityManager->getNumberOfSystems() > 0; runs++) {
        if (entityManager->run() != 0 || interrupt)
            break ;
    }
    events->send<std::string>("Fender shutting down. Ran " + std::to_string(runs) + " times.");
    events->send<events::Shutdown>();
    entityManager->cleanSystems();
    return 0;
}
