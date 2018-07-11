#include "FileLogger.h"

namespace Logging {

FileLogger::FileLogger(Level level) : StreamLogger(level) {
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
void FileLogger::init(const std::string& fileName) {
  fileStream.open(fileName, std::ios::app);
  StreamLogger::attachToStream(fileStream);
}
//------------------------------------------------------------- Seperator Code -------------------------------------------------------------//
}
