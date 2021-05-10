// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <memory>
#include <unordered_set>

// Types for IDs
using PlaceID = long long int;
using AreaID = long long int;
using Name = std::string;
using WayID = std::string;

// Return values for cases where required thing was not found
PlaceID const NO_PLACE = -1;
AreaID const NO_AREA = -1;
WayID const NO_WAY = "!!No way!!";

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
Name const NO_NAME = "!!NO_NAME!!";

// Enumeration for different place types
// !!Note since this is a C++11 "scoped enumeration", you'll have to refer to
// individual values as PlaceType::SHELTER etc.
enum class PlaceType { OTHER=0, FIREPIT, SHELTER, PARKING, PEAK, BAY, AREA, NO_TYPE };

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Type for a distance (in metres)
using Distance = int;

// Return value for cases where Duration is unknown
Distance const NO_DISTANCE = NO_VALUE;

struct Place
{
    PlaceID id = NO_PLACE;
    Name name = NO_NAME;
    PlaceType type = PlaceType::NO_TYPE;
    Coord coord = NO_COORD;
};

struct Area
{
    AreaID id = NO_AREA;
    Name name = NO_NAME;
    std::vector<Coord> coords;
    std::shared_ptr<Area> parent = nullptr;
    std::vector<std::shared_ptr<Area>> subareas;
};

struct Way
{
    WayID id = NO_WAY;
    std::vector<Coord> coords;
    Distance length = 0;
};

struct Node
{
    Coord pos = NO_COORD;
    unsigned g = 0;
    unsigned h = 0;
    unsigned f = 0;
};

// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance: O(1)
    // Short rationale for estimate: unordered_map::size
    int place_count();

    // Estimate of performance: O(n)
    // Short rationale for estimate: unordered_map::clear
    void clear_all();

    // Estimate of performance: O(n)
    // Short rationale for estimate: std::transorfm
    std::vector<PlaceID> all_places();

    // Estimate of performance: O(n)
    // Short rationale for estimate: unordered_map::find
    bool add_place(PlaceID id, Name const& name, PlaceType type, Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate: unordered_map::find
    std::pair<Name, PlaceType> get_place_name_type(PlaceID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: unordered_map::find
    Coord get_place_coord(PlaceID id);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(nlogn)
    // Short rationale for estimate: std::sort
    std::vector<PlaceID> places_alphabetically();

    // Estimate of performance: O(nlogn)
    // Short rationale for estimate: std::sort
    std::vector<PlaceID> places_coord_order();

    // Estimate of performance: O(n)
    // Short rationale for estimate: iterates through all places
    std::vector<PlaceID> find_places_name(Name const& name);

    // Estimate of performance: O(n)
    // Short rationale for estimate: iterates through all places
    std::vector<PlaceID> find_places_type(PlaceType type);

    // Estimate of performance: O(n)
    // Short rationale for estimate: unordered_map::find
    bool change_place_name(PlaceID id, Name const& newname);

    // Estimate of performance: O(n)
    // Short rationale for estimate: unordered_map::find
    bool change_place_coord(PlaceID id, Coord newcoord);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n)
    // Short rationale for estimate: unordered_map::find
    bool add_area(AreaID id, Name const& name, std::vector<Coord> coords);

    // Estimate of performance: O(n)
    // Short rationale for estimate: unordered_map::find
    Name get_area_name(AreaID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: unordered_map::find
    std::vector<Coord> get_area_coords(AreaID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: iterates through all areas
    std::vector<AreaID> all_areas();

    // Estimate of performance: O(n)
    // Short rationale for estimate: unordered_map::find called twice
    bool add_subarea_to_area(AreaID id, AreaID parentid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: unordered_map::find
    std::vector<AreaID> subarea_in_areas(AreaID id);

    // Non-compulsory operations

    // Estimate of performance:
    // Short rationale for estimate:
    void creation_finished();

    // Estimate of performance: O(n)
    // Short rationale for estimate: unordered_map::find
    std::vector<AreaID> all_subareas_in_area(AreaID id);

    // Estimate of performance: too much
    // Short rationale for estimate: wrote a terrible but somewhat working solution
    std::vector<PlaceID> places_closest_to(Coord xy, PlaceType type);

    // Estimate of performance: O(n)
    // Short rationale for estimate: unordered_map::find
    bool remove_place(PlaceID id);

    // Estimate of performance: O(n) maybe?
    // Short rationale for estimate: calls unordered_map::find a few times
    AreaID common_area_of_subareas(AreaID id1, AreaID id2);

    // Phase 2 operations

    // Estimate of performance: O(n)
    // Short rationale for estimate: std::transorfm
    std::vector<WayID> all_ways();

    // Estimate of performance: O(n)
    // Short rationale for estimate: std::find
    bool add_way(WayID id, std::vector<Coord> coords);

    // Estimate of performance: O(n)
    // Short rationale for estimate: iterates through all ways
    std::vector<std::pair<WayID, Coord>> ways_from(Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate: std::find
    std::vector<Coord> get_way_coords(WayID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: unordered_map::clear
    void clear_ways();
    
    // Estimate of performance: O(n)
    // Short rationale for estimate: each node is traversed once
    std::vector<std::tuple<Coord, WayID, Distance>> route_any(Coord fromxy, Coord toxy);

    // Non-compulsory operations

    // Estimate of performance:
    // Short rationale for estimate:
    bool remove_way(WayID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<std::tuple<Coord, WayID, Distance>> route_least_crossroads(Coord fromxy, Coord toxy);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<std::tuple<Coord, WayID>> route_with_cycle(Coord fromxy);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<std::tuple<Coord, WayID, Distance>> route_shortest_distance(Coord fromxy, Coord toxy);

    // Estimate of performance:
    // Short rationale for estimate:
    Distance trim_ways();

private:
    std::unordered_map<PlaceID, std::shared_ptr<Place>> places_;
    std::unordered_map<AreaID, std::shared_ptr<Area>> areas_;
    std::unordered_map<WayID, std::shared_ptr<Way>> ways_;
    std::unordered_map<Coord, std::unordered_set<WayID>, CoordHash> crossroads_;

    std::vector<std::shared_ptr<Place>> get_place_vector();
    std::vector<std::shared_ptr<Area>> find_parent_areas_recursive(std::shared_ptr<Area> area);
    std::vector<std::shared_ptr<Area>> find_subareas_recursive(std::shared_ptr<Area> area);
    AreaID find_common_parent_recursive(std::vector<std::shared_ptr<Area>> &parent, std::shared_ptr<Area> area);
    std::vector<std::shared_ptr<Place>> find_nearest_brute_force(Coord xy, PlaceType type);

    // returns distance to power of two to minimize calculations
    unsigned calculate_coord_distance(Coord c1, Coord c2);

    Distance calculate_way_length(std::vector<Coord> coords);

    // Pathfinding algorithms
    std::vector<std::tuple<Coord, WayID, Distance>> astar(Coord c1, Coord c2); // not implemented
    std::vector<std::tuple<Coord, WayID, Distance>> dfs(Coord c1, Coord c2);
};

#endif // DATASTRUCTURES_HH
