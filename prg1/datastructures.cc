// Datastructures.cc

#include "datastructures.hh"

#include <random>

#include <cmath>
#include <algorithm>
#include <iterator>

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
    : places_(), areas_()
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
    // Replace this comment with your implementation
    std::vector<PlaceID> place_ids;
    for (auto place : places_) {
        place_ids.push_back(place.first);
    }

    return place_ids;
}

bool Datastructures::add_place(PlaceID id, const Name& name, PlaceType type, Coord xy)
{
    // Replace this comment with your implementation
    if (places_.find(id) == places_.end()) {
        Place place_to_add = { id, name, type, xy };
        places_[id] = std::make_shared<Place>(place_to_add);
        return true;
    }

    return false;
}

std::pair<Name, PlaceType> Datastructures::get_place_name_type(PlaceID id)
{
    // Replace this comment with your implementation

    return {places_[id]->name, places_[id]->type};
}

Coord Datastructures::get_place_coord(PlaceID id)
{
    // Replace this comment with your implementation
    return places_[id]->coord;
}

bool Datastructures::add_area(AreaID id, const Name &name, std::vector<Coord> coords)
{
    // Replace this comment with your implementation
    return false;
}

Name Datastructures::get_area_name(AreaID id)
{
    // Replace this comment with your implementation
    return NO_NAME;
}

std::vector<Coord> Datastructures::get_area_coords(AreaID id)
{
    // Replace this comment with your implementation
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

// check this
std::vector<PlaceID> Datastructures::places_coord_order()
{
    std::vector<std::shared_ptr<Place>> places_to_sort = get_place_vector();
    std::sort(places_to_sort.begin(), places_to_sort.end(),
              [](const std::shared_ptr<Place>& a, const std::shared_ptr<Place>& b)
               { return a->coord < b->coord; });

    std::vector<PlaceID> sorted;
    std::transform(places_to_sort.begin(), places_to_sort.end(), std::back_inserter(sorted),
                   [](std::shared_ptr<Place> const& p) -> PlaceID { return p->id; });
    return sorted;
}

std::vector<PlaceID> Datastructures::find_places_name(Name const& name)
{
    // Replace this comment with your implementation
    return {};
}

std::vector<PlaceID> Datastructures::find_places_type(PlaceType type)
{
    // Replace this comment with your implementation
    return {};
}

bool Datastructures::change_place_name(PlaceID id, const Name& newname)
{
    // Replace this comment with your implementation
    return false;
}

bool Datastructures::change_place_coord(PlaceID id, Coord newcoord)
{
    // Replace this comment with your implementation
    return false;
}

std::vector<AreaID> Datastructures::all_areas()
{
    // Replace this comment with your implementation
    return {};
}

bool Datastructures::add_subarea_to_area(AreaID id, AreaID parentid)
{
    // Replace this comment with your implementation
    return false;
}

std::vector<AreaID> Datastructures::subarea_in_areas(AreaID id)
{
    // Replace this comment with your implementation
    return {NO_AREA};
}

std::vector<PlaceID> Datastructures::places_closest_to(Coord xy, PlaceType type)
{
    // Replace this comment with your implementation
    return {};
}

bool Datastructures::remove_place(PlaceID id)
{
    // Replace this comment with your implementation
    return false;
}

std::vector<AreaID> Datastructures::all_subareas_in_area(AreaID id)
{
    // Replace this comment with your implementation
    return {NO_AREA};
}

AreaID Datastructures::common_area_of_subareas(AreaID id1, AreaID id2)
{
    // Replace this comment with your implementation
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
