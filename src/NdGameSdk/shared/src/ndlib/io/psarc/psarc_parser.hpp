#pragma once

#include <string>
#include <vector>

#include "psarc_reader.hpp"
#include "psarc.hpp"

namespace NdGameSdk::ndlib::io { 
    
#if defined(T2R)

    namespace PSARC {
        // Returns true on success and fills names using PSARC::Header/TEntry
        bool ListFilenames(iReader& rdr, std::vector<std::string>& names);
        // Overload: use a provided normalized header (skips header read)
        bool ListFilenames(iReader& rdr, const Header& header, std::vector<std::string>& names);
    }

#endif
}
