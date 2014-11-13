#pragma once

#include <string>
#include <sstream>

#include <vector>
#include <stdint.h>

extern "C"
{
#include "sc_memory_headers.h"
}

namespace sc
{

typedef std::string String;
typedef std::stringstream StringStream;


typedef std::vector<sc_addr> ScAddrVectorT;

}
