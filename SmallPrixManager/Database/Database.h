#ifndef SPM_DATABASE
#define SPM_DATABASE

#include <vector>
#include "../Simulation/Track.h"

namespace spm {
    
    /** Access point to the "database", actually the data stored on files. 
    
    Tutorial on TinyXml 2: https://shilohjames.wordpress.com/2014/04/27/tinyxml2-tutorial/
    */
    class Database {
    public:
        std::vector<Track> loadTracks(const std::string& sourceFile);

    };
}

#endif