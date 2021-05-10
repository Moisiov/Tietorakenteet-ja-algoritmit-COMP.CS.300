// Datastructures.cc

#include "datastructures.hh"

#include <random>

#include <cmath>
#include <algorithm>
#include <iterator>
#include <stack>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
    : places_(), areas_(), ways_(), crossroads_()
{
    // Replace this comment with your implementation
}

Datastructures::~Datastructures()
{
    // Replace this comment with your implementation
}

int Datastructures::place_count()
{
    return places_.size();
}

void Datastructures::clear_all()
{
    places_.clear();
    areas_.clear();
}

std::vector<PlaceID> Datastructures::all_places()
{
    std::vector<PlaceID> place_ids;
    std::transform(places_.begin(), places_.end(), std::back_inserter(place_ids),
                   [](std::pair<PlaceID, std::shared_ptr<Place>> const& p)
            -> PlaceID { return p.second->id; });

    return place_ids;
}

bool Datastructures::add_place(PlaceID id, const Name& name, PlaceType type, Coord xy)
{
    if (places_.find(id) == places_.end()) {
        Place place_to_add = { id, name, type, xy };
        places_[id] = std::make_shared<Place>(place_to_add);
        return true;
    }

    return false;
}

std::pair<Name, PlaceType> Datastructures::get_place_name_type(PlaceID id)
{
    if (places_.find(id) != places_.end())
    {
        return {places_[id]->name, places_[id]->type};
    }
    return {NO_NAME, PlaceType::NO_TYPE};
}

Coord Datastructures::get_place_coord(PlaceID id)
{
    if (places_.find(id) != places_.end())
    {
        return places_[id]->coord;
    }
    return NO_COORD;
}

bool Datastructures::add_area(AreaID id, const Name &name, std::vector<Coord> coords)
{
    if (areas_.find(id) == areas_.end()) {
        Area area_to_Add = { id, name, coords, nullptr, {} };
        areas_[id] = std::make_shared<Area>(area_to_Add);
        return true;
    }

    return false;
}

Name Datastructures::get_area_name(AreaID id)
{
    if (areas_.find(id) != areas_.end())
    {
        return areas_[id]->name;
    }
    return NO_NAME;
}

std::vector<Coord> Datastructures::get_area_coords(AreaID id)
{
    if (areas_.find(id) != areas_.end())
    {
        return areas_[id]->coords;
    }
    return {NO_COORD};
}

void Datastructures::creation_finished()
{
    // Replace this comment with your implementation
    // NOTE!! It's quite ok to leave this empty, if you don't need operations
    // that are performed after all additions have been done.
}


std::vector<PlaceID> Datastructures::places_alphabetically()
{
    std::vector<std::shared_ptr<Place>> places_to_sort = get_place_vector();
    std::sort(places_to_sort.begin(), places_to_sort.end(),
              [](const std::shared_ptr<Place>& a, const std::shared_ptr<Place>& b)
               { return a->name < b->name; });

    std::vector<PlaceID> sorted;
    std::transform(places_to_sort.begin(), places_to_sort.end(), std::back_inserter(sorted),
                   [](std::shared_ptr<Place> const& p) -> PlaceID { return p->id; });
    return sorted;
}

std::vector<PlaceID> Datastructures::places_coord_order()
{
    std::vector<std::shared_ptr<Place>> places_to_sort = get_place_vector();
    std::sort(places_to_sort.begin(), places_to_sort.end(),
              [](const std::shared_ptr<Place>& a, const std::shared_ptr<Place>& b)
               { double dist_a = pow(a->coord.x, 2.0) + pow(a->coord.y, 2.0);
                 double dist_b = pow(b->coord.x, 2.0) + pow(b->coord.y, 2.0);
                 if (dist_a == dist_b)
                 {
                     return a->coord.y < b->coord.y;
                 }
                 return dist_a < dist_b; });

    std::vector<PlaceID> sorted;
    std::transform(places_to_sort.begin(), places_to_sort.end(), std::back_inserter(sorted),
                   [](std::shared_ptr<Place> const& p) -> PlaceID { return p->id; });
    return sorted;
}

std::vector<PlaceID> Datastructures::find_places_name(Name const& name)
{
    std::vector<PlaceID> place_ids;
    for (auto i : places_) {
        if (i.second->name == name) {
            place_ids.push_back(i.second->id);
        }
    }
    return place_ids;
}

std::vector<PlaceID> Datastructures::find_places_type(PlaceType type)
{
    std::vector<PlaceID> place_ids;
    for (auto i : places_) {
        if (i.second->type == type) {
            place_ids.push_back(i.second->id);
        }
    }
    return place_ids;
}

bool Datastructures::change_place_name(PlaceID id, const Name& newname)
{
    if(places_.find(id) != places_.end())
    {
        places_[id]->name = newname;
        return true;
    }

    return false;
}

bool Datastructures::change_place_coord(PlaceID id, Coord newcoord)
{
    if(places_.find(id) != places_.end())
    {
        places_[id]->coord = newcoord;
        return true;
    }

    return false;
}

std::vector<AreaID> Datastructures::all_areas()
{
    std::vector<AreaID> area_ids;
    for (auto i : areas_) {
        area_ids.push_back(i.first);
    }
    return area_ids;
}

bool Datastructures::add_subarea_to_area(AreaID id, AreaID parentid)
{
    if (areas_.find(id) != areas_.end()
            && areas_.find(parentid) != areas_.end()
            && areas_[id]->parent == nullptr)
    {
        areas_[id]->parent = areas_[parentid];
        areas_[parentid]->subareas.push_back(areas_[id]);
        return true;
    }
    return false;
}

std::vector<AreaID> Datastructures::subarea_in_areas(AreaID id)
{
    if (areas_.find(id) != areas_.end())
    {
        std::vector<AreaID> area_ids;
        std::vector<std::shared_ptr<Area>> parents = find_parent_areas_recursive(areas_[id]);
        for (auto i : parents)
        {
            area_ids.push_back(i->id);
        }

        return area_ids;
    }

    return {NO_AREA};
}

std::vector<PlaceID> Datastructures::places_closest_to(Coord xy, PlaceType type)
{
    std::vector<PlaceID> nearest_ids;
    std::vector<std::shared_ptr<Place>> nearest = find_nearest_brute_force(xy, type);
    std::sort(nearest.begin(), nearest.end(),
              [this, xy](const std::shared_ptr<Place>& a, const std::shared_ptr<Place>& b)
               { double dist_a = calculate_coord_distance(xy, a->coord);
                 double dist_b = calculate_coord_distance(xy, b->coord);
                 if (dist_a == dist_b)
                 {
                     return a->coord.y < b->coord.y;
                 }
                 return dist_a < dist_b; });

    std::transform(nearest.begin(), nearest.end(), std::back_inserter(nearest_ids),
                   [](std::shared_ptr<Place> const& p) -> PlaceID { return p->id; });

    return nearest_ids;
}

bool Datastructures::remove_place(PlaceID id)
{
    if (places_.find(id) != places_.end())
    {
        places_.erase(id);
        return true;
    }
    return false;
}

std::vector<AreaID> Datastructures::all_subareas_in_area(AreaID id)
{
    if (areas_.find(id) != areas_.end())
    {
        std::vector<AreaID> area_ids;
        std::vector<std::shared_ptr<Area>> subareas = find_subareas_recursive(areas_[id]);
        for (auto i : subareas)
        {
            area_ids.push_back(i->id);
        }
        return area_ids;
    }
    return {NO_AREA};
}

AreaID Datastructures::common_area_of_subareas(AreaID id1, AreaID id2)
{
    if (areas_.find(id1) != areas_.end()
            && areas_.find(id2) != areas_.end()
            && areas_[id1]->parent != nullptr
            && areas_[id2]->parent != nullptr)
    {
        std::vector<std::shared_ptr<Area>> parents = find_parent_areas_recursive(areas_[id1]);
        return find_common_parent_recursive(parents, areas_[id2]);
    }

    return NO_AREA;
}

std::vector<std::shared_ptr<Place>> Datastructures::get_place_vector()
{
    std::vector<std::shared_ptr<Place>> place_vector;
    for (auto elem : places_)
    {
        place_vector.push_back(elem.second);
    }
    return place_vector;
}

std::vector<std::shared_ptr<Area>> Datastructures::find_parent_areas_recursive(std::shared_ptr<Area> area)
{
    std::vector<std::shared_ptr<Area>> areas = {};
    if (area->parent != nullptr) {
        areas.push_back(area->parent);
        std::vector<std::shared_ptr<Area>> parents = find_parent_areas_recursive(area->parent);
        areas.insert(areas.end(), parents.begin(), parents.end());
    }
    return areas;
}

std::vector<std::shared_ptr<Area>> Datastructures::find_subareas_recursive(std::shared_ptr<Area> area)
{
    std::vector<std::shared_ptr<Area>> areas = {};
    if (!area->subareas.empty())
    {
        areas.insert(areas.end(), area->subareas.begin(), area->subareas.end());
        for (auto i : area->subareas)
        {
            std::vector<std::shared_ptr<Area>> subareas = find_subareas_recursive(i);
            areas.insert(areas.end(), subareas.begin(), subareas.end());
        }
    }

    return areas;
}

AreaID Datastructures::find_common_parent_recursive(std::vector<std::shared_ptr<Area>> &parents, std::shared_ptr<Area> area)
{
    if (area->parent == nullptr)
    {
        return NO_AREA;
    }
    if (std::find(parents.begin(), parents.end(), area->parent) != parents.end())
    {
        return area->parent->id;
    }
    return find_common_parent_recursive(parents, area->parent);
}

// really ugly -> do smth to this
std::vector<std::shared_ptr<Place>> Datastructures::find_nearest_brute_force(Coord xy, PlaceType type)
{
    std::vector<std::pair<unsigned, std::shared_ptr<Place>>> nearest;
    unsigned highest_dist;

    for (auto i : places_)
    {
        unsigned dist = calculate_coord_distance(xy, i.second->coord);
        if(nearest.size() < 3 && (type == PlaceType::NO_TYPE || type == i.second->type))
        {
            if (!highest_dist || dist > highest_dist)
            {
                highest_dist = dist;
            }
            nearest.push_back(std::make_pair(dist, i.second));
        }
        else if (type == PlaceType::NO_TYPE || type == i.second->type)
        {
            if (dist <= highest_dist)
            {
                auto it = std::find_if(nearest.begin(), nearest.end(),
                                       [highest_dist](const std::pair<unsigned, std::shared_ptr<Place>> p)
                                       { return p.first == highest_dist; });

                if (it != nearest.end()
                        && (dist < highest_dist
                            || i.second->coord.y < it->second->coord.y))
                {
                    *it = std::make_pair(dist, i.second);

                    // calculate highest
                    highest_dist = 0;
                    for (auto near : nearest)
                    {
                        if (near.first > highest_dist)
                        {
                            highest_dist = near.first;
                        }
                    }
                }
            }
        }
    }

    std::vector<std::shared_ptr<Place>> result;
    std::transform(nearest.begin(), nearest.end(), std::back_inserter(result),
                   [](std::pair<unsigned, std::shared_ptr<Place>> const& p)
            -> std::shared_ptr<Place>{ return p.second; });

    return result;
}

unsigned Datastructures::calculate_coord_distance(Coord c1, Coord c2)
{
    return pow(c1.x - c2.x, 2) + pow(c1.y - c2.y, 2);
}

Distance Datastructures::calculate_way_length(std::vector<Coord> coords)
{
    unsigned len = 0;
    for(unsigned i = 0; i < coords.size() - 1; i++)
    {
        len += sqrt(calculate_coord_distance(coords.at(i), coords.at(i+1)));
    }

    return (Distance)len;
}

std::vector<std::tuple<Coord, WayID, Distance>> Datastructures::astar(Coord c1, Coord c2)
{
    return {};
}

std::vector<std::tuple<Coord, WayID, Distance> > Datastructures::dfs(Coord c1, Coord c2)
{
    bool found = false;
    std::stack<Coord> stk;
    std::unordered_set<Coord, CoordHash> visited = {c1};
    std::unordered_map<Coord, std::tuple<Coord, WayID>, CoordHash> parent_map;
    stk.push(c1);

    Coord current_coord;

    while (!stk.empty() && !found)
    {
        current_coord = stk.top();
        stk.pop();
        if (current_coord == c2)
        {
            found = true;
            break;
        }

        for (auto &way_id : crossroads_[current_coord])
        {
            std::vector<Coord> coords = ways_[way_id]->coords;
            if(visited.find(coords.front()) == visited.end())
            {
                stk.push(coords.front());
                visited.insert(coords.front());
                parent_map[coords.front()] = std::make_tuple(current_coord, way_id);
            }
            else if(visited.find(coords.back()) == visited.end())
            {
                stk.push(coords.back());
                visited.insert(coords.back());
                parent_map[coords.back()] = std::make_tuple(current_coord, way_id);
            }
        }
    }

    if (found)
    {
        std::vector<std::tuple<Coord, WayID, Distance>> result;
        std::vector<std::tuple<Coord, WayID>> route;

        Coord current = c2;
        while(current != c1)
        {
            route.push_back(std::make_tuple(current, std::get<1>(parent_map.at(current))));
            current = std::get<0>(parent_map.at(current));
        }
        route.push_back(std::make_tuple(c1, NO_WAY));

        Distance tot_dist = 0;
        for (auto it = route.rbegin(); it != route.rend(); ++it)
        {
            WayID id = std::get<1>(*it);
            if (ways_.find(id) != ways_.end())
            {
                tot_dist += ways_[id]->length;
            }

            result.push_back(std::tuple_cat(*it, std::make_tuple(tot_dist)));
        }

        return result;
    }
    return {};
}

std::vector<WayID> Datastructures::all_ways()
{
    std::vector<WayID> way_ids;
    std::transform(ways_.begin(), ways_.end(), std::back_inserter(way_ids),
                   [](std::pair<WayID, std::shared_ptr<Way>> const& w)
            -> WayID { return w.first; });
    return way_ids;
}

bool Datastructures::add_way(WayID id, std::vector<Coord> coords)
{   
    if (ways_.find(id) == ways_.end())
    {
        Way way_to_add = {
            id,
            coords,
            calculate_way_length(coords)
        };
        ways_[id] = std::make_shared<Way>(way_to_add);

        // Add weak pointers to crossroads_
        if(crossroads_.find(coords.front()) == crossroads_.end())
        {
            crossroads_[coords.front()] = {id};
        }
        else
        {
            crossroads_[coords.front()].insert(id);
        }

        if(crossroads_.find(coords.back()) == crossroads_.end())
        {
            crossroads_[coords.back()] = {id};
        }
        else
        {
            crossroads_[coords.back()].insert(id);
        }

        return true;
    }
    return false;
}

std::vector<std::pair<WayID, Coord>> Datastructures::ways_from(Coord xy)
{
    std::vector<std::pair<WayID, Coord>> found_ways;
    for(auto way : ways_)
    {
        if(way.second->coords.front() == xy)
        {
            found_ways.push_back({way.first, way.second->coords.back()});
        }
        else if(way.second->coords.back() == xy)
        {
            found_ways.push_back({way.first, way.second->coords.front()});
        }
    }

    return found_ways;
}

std::vector<Coord> Datastructures::get_way_coords(WayID id)
{
    if (ways_.find(id) != ways_.end())
    {
        return ways_[id]->coords;
    }
    return {NO_COORD};
}

void Datastructures::clear_ways()
{
    ways_.clear();
    crossroads_.clear();
}

std::vector<std::tuple<Coord, WayID, Distance> > Datastructures::route_any(Coord fromxy, Coord toxy)
{
    if (crossroads_.find(fromxy) == crossroads_.end()
            || crossroads_.find(toxy) == crossroads_.end())
    {
        return {{NO_COORD, NO_WAY, NO_DISTANCE}};
    }

    return dfs(fromxy, toxy);
}

bool Datastructures::remove_way(WayID id)
{
    if(ways_.find(id) != ways_.end())
    {
        ways_.erase(id);
        return true;
    }
    return false;
}

std::vector<std::tuple<Coord, WayID, Distance> > Datastructures::route_least_crossroads(Coord fromxy, Coord toxy)
{
    // Replace this comment with your implementation
    return {{NO_COORD, NO_WAY, NO_DISTANCE}};
}

std::vector<std::tuple<Coord, WayID> > Datastructures::route_with_cycle(Coord fromxy)
{
    // Replace this comment with your implementation
    return {{NO_COORD, NO_WAY}};
}

std::vector<std::tuple<Coord, WayID, Distance> > Datastructures::route_shortest_distance(Coord fromxy, Coord toxy)
{
    // Replace this comment with your implementation
    return {{NO_COORD, NO_WAY, NO_DISTANCE}};
}

Distance Datastructures::trim_ways()
{
    // Replace this comment with your implementation
    return NO_DISTANCE;
}
