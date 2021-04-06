Data structures:
    Structs Place and Area are used to get simple access to needed attributes.
    Pointers to parent and subareas are also stored in Area struct for quick access to them.

    Pointers to Place and Area objects are stored in private attributes
    unordered_map<PlaceID, shared_ptr<Place>> places_ and
    unordered_map<AreaID, shared_ptr<Area>> areas_.
    Unordered map is the chosen container type because using the PlaceID and AreaID as keys
    allows quick access to wanted objects since the main program mainly passes the ID as a
    parameter to Datastructures class member functions.

Operations:
    The compulsory operations are quite straight-forward and no unnecessary gimmickry was needed.
    Finding the parent and subareas were implemented as recursive operations.

    Non-compulsory operations were finished in quite a hurry as the programmer ran out of time
    (skiing accident and a broken wrist, finally got the plaster off a couple of days ago).
