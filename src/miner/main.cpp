#include "common/SignalHandler.h"

#include "log/LoggerGroup.h"
#include "log/ConsoleLogger.h"
#include "log/LoggerRef.h"

#include "MinerManager.h"

#include <System/Dispatcher.h>

int main(int argc, char** argv) {
  try {
    CryptoNote::MiningConfig config;
    config.parse(argc, argv);

    if (config.help) {
      config.printHelp();
      return 0;
    }

    Logging::LoggerGroup loggerGroup;
    Logging::ConsoleLogger consoleLogger(static_cast<Logging::Level>(config.logLevel));
    loggerGroup.addLogger(consoleLogger);

    System::Dispatcher dispatcher;
    Miner::MinerManager app(dispatcher, config, loggerGroup);

    app.start();
  } catch (std::exception& e) {
    std::cerr << "Fatal: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
