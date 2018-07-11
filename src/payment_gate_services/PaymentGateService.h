#pragma once

#include "ConfigurationManager.h"
#include "PaymentServiceConfiguration.h"

#include "log/ConsoleLogger.h"
#include "log/LoggerGroup.h"
#include "log/StreamLogger.h"

#include "payment_gate/NodeFactory.h"
#include "payment_gate/WalletService.h"

class PaymentGateService {
public:

  PaymentGateService();

  bool init(int argc, char** argv);

  const PaymentService::ConfigurationManager& getConfig() const { return config; }
  PaymentService::WalletConfiguration getWalletConfig() const;
  const CryptoNote::Currency getCurrency();

  void run();
  void stop();
  
  Logging::ILogger& getLogger() { return logger; }

private:

  void runInProcess(Logging::LoggerRef& log);
  void runRpcProxy(Logging::LoggerRef& log);

  void runWalletService(const CryptoNote::Currency& currency, CryptoNote::INode& node);

  System::Dispatcher* dispatcher;
  System::Event* stopEvent;
  PaymentService::ConfigurationManager config;
  PaymentService::WalletService* service;
  CryptoNote::CurrencyBuilder currencyBuilder;
  
  Logging::LoggerGroup logger;
  std::ofstream fileStream;
  Logging::StreamLogger fileLogger;
  Logging::ConsoleLogger consoleLogger;
};
