#pragma once

#include <string>
#include <vector>

namespace Common {

#ifndef __ANDROID__

  bool fetch_dns_txt(const std::string domain, std::vector<std::string>&records);

#endif

}

