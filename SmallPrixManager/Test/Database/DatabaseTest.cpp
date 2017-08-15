#include "gtest/gtest.h"

#include "../../Database/Database.h"

#include "../../Simulation/Track.h"
#include <vector>

namespace spm {
    
TEST(Database, tracks_from_file__names) {
    Database d;
    const std::vector<Track> t = d.loadTracks();

    ASSERT_EQ(t.size(), 2);
    ASSERT_EQ(t.at(0).getName(), std::string("Autodromo"));
    ASSERT_EQ(t.at(1).getName(), std::string("Pista"));
}


TEST(Database, tracks_from_file__points) {
    Database d;
    const std::vector<Track> t = d.loadTracks();

    ASSERT_EQ(t.size(), 2);
    ASSERT_EQ(t.at(0).getTrackCurve().at(0).x, 1);
}

}