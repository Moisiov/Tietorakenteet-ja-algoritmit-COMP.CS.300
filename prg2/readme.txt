Unordered map is used to store Way objects. Key is the WayID for quick access.
A lot of standard library functions were used to maintain decent performance.
The crossroads are kept in unordered map which has Coord type as key and unordered
set of WayIDs as a value. I planned to use weak pointers to Way objects instead
of ids but run to a problem with coord operators when experimenting with that. 

Function route_any uses depth first search. Pretty ugly implementation but
does the work.
