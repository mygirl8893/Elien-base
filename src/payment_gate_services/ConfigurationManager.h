#pragma once

#include "core/CoreConfig.h"
#include "PaymentServiceConfiguration.h"
#include "p2p/NetNodeConfig.h"
#include "RpcNodeConfiguration.h"

namespace PaymentService {

class ConfigurationManager {
public:
  ConfigurationManager();
  bool init(int argc, char** argv);

  bool startInprocess;
  Configuration gateConfiguration;
  CryptoNote::NetNodeConfig netNodeConfig;
  CryptoNote::CoreConfig coreConfig;
  RpcNodeConfiguration remoteNodeConfig;
};

} //namespace PaymentService
