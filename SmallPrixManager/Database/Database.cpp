#include "Database.h"

#include <functional>
#include <sstream>

#include "tinyxml2.h"

#include "../Simulation/Bezier.h"
#include "../Simulation/Track.h"

using namespace tinyxml2;

namespace spm {

    static void stopOnError(const XMLDocument& doc) {
        if (doc.Error()) {
            doc.PrintError();
            throw std::runtime_error("XML problem, check stdout for details.");
        }
    }

    static void stopOnNull(const void* p) {
        if (!p)
            throw std::runtime_error("Cpp.Lang.NullPointerException");  //...same as Java.
    }

    std::vector<Track> Database::loadTracks(const std::string& sourceFile) {
        std::vector<Track> tracks;

        XMLDocument tracksOnFile;
        tracksOnFile.LoadFile(sourceFile.c_str());
        stopOnError(tracksOnFile);
        
        XMLElement* root = tracksOnFile.FirstChildElement("tracks");
        stopOnError(tracksOnFile); stopOnNull(root);

        XMLElement* currentTrack = root->FirstChildElement("track");
        stopOnError(tracksOnFile); stopOnNull(currentTrack);
        while (currentTrack != nullptr) {
            const char* trackName = currentTrack->FirstChildElement("name")->GetText();
            stopOnError(tracksOnFile); stopOnNull(trackName);
            
            XMLElement* points = currentTrack->FirstChildElement("points");
            stopOnError(tracksOnFile); stopOnNull(points);

            XMLElement* currentPoint = points->FirstChildElement("p");
            stopOnError(tracksOnFile); stopOnNull(currentPoint);

            std::vector<Point> pointsForTrack;

            while (currentPoint != nullptr) {
                Point p;
                currentPoint->QueryFloatAttribute("x", &p.x);
                stopOnError(tracksOnFile);
                currentPoint->QueryFloatAttribute("y", &p.y);
                stopOnError(tracksOnFile);

                pointsForTrack.push_back(p);

                currentPoint = currentPoint->NextSiblingElement("p");
                stopOnError(tracksOnFile);
            }

            tracks.push_back(Track(trackName, BezierPath(pointsForTrack)));

            currentTrack = currentTrack->NextSiblingElement("track");
            stopOnError(tracksOnFile);
        }

        return tracks;
    }
}