#include "CoreConfig.h"

#include "common/Util.h"
#include "common/CommandLine.h"

namespace CryptoNote {

CoreConfig::CoreConfig() {
  configFolder = Tools::getDefaultDataDirectory();
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
void CoreConfig::init(const boost::program_options::variables_map& options) {
  if (options.count(command_line::arg_data_dir.name) != 0 && (!options[command_line::arg_data_dir.name].defaulted() || configFolder == Tools::getDefaultDataDirectory())) {
    configFolder = command_line::get_arg(options, command_line::arg_data_dir);
    configFolderDefaulted = options[command_line::arg_data_dir.name].defaulted();
  }
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
void CoreConfig::initOptions(boost::program_options::options_description& desc) {
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
} //namespace CryptoNote
