/*footways.h*/

//
// A collection of footways in the Open Street Map.
//

#include <iostream>
#include <string>
#include <vector>
#include <cassert>

#include "footways.h"
#include "osm.h"
#include "tinyxml2.h"
#include "nodes.h"

using namespace std;
using namespace tinyxml2;
//
// Reads footways from the given XML document.
//
void Footways::readMapFootways(XMLDocument& xmldoc)
{
    XMLElement* osm = xmldoc.FirstChildElement("osm");
    assert(osm != nullptr);

    // look for footways
    XMLElement* way = osm->FirstChildElement("way");

    while (way != nullptr)
    {
        const XMLAttribute* attr = way->FindAttribute("id");
        assert(attr != nullptr);

        // if footway, store info into vector
        if (osmContainsKeyValue(way, "highway", "footway") || osmContainsKeyValue(way, "area:highway", "footway"))
        {
            long long id = attr->Int64Value();

            Footway F(id);

            XMLElement* nd = way->FirstChildElement("nd");

            while (nd != nullptr)
            {
                const XMLAttribute* ndref = nd->FindAttribute("ref");
                assert(ndref != nullptr);

                long long id = ndref->Int64Value();

                F.add(id);

                // advance next node ref
                nd = nd->NextSiblingElement("nd");
            }

            // addfootway
            this->MapFootways.push_back(F);
        }

        //next way element
        way = way->NextSiblingElement("way");
    }
}

//
// Returns the number of footways.
//
int Footways::getNumMapFootways() const
{
    return (int)this->MapFootways.size();
}
