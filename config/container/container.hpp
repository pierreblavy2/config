//============================================================================
// Author  : Pierre BLAVY 2018
// Version : 1.0
// License : GPL 3.0 or any later version :
//           https://www.gnu.org/licenses/gpl-3.0-standalone.html
//============================================================================

//This program (container) is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>

#ifndef LIB_CONTAINER_CONTAINER_HPP_
#define LIB_CONTAINER_CONTAINER_HPP_

#include "impl/Complexity.hpp"
// complexity enum. This is the worse case complexity, according to container length
// WARNING : check complexity, as some things are really inefficient (ex get_back in a set)


#include "impl/traits.tpp"
// unique_values     : true if the value in the container are unique (set, unordered set)
// is_ordered        : true if the value are ordered (set, multiset)
// is_implemented<XXXX,Container>, where XXXX is an implementation like Get_front_t;
// complexity    <XXXX,Container>, where XXXX is an implementation like Get_front_t;
// value_type    <Container> : the kind of value inside the container


//NOTE : xxx_anywhere consistency :
//  get_anywhere must return the same element as the one deleted by remove_anywhere
//  this is required to use the container as a stack. (FIFO, FILO, or ANY order)
//  If there is a reasonably fast implementation,
//  add_anywhere and emplace_anywhere should add to back so calling them will
//  preserve order
//  If there is a reasonably fast implementation,
//  get_anywhere and remove_anywhere should get/remove to the back so calling
//  them is consistent with add_anywhere and emplace_anywhere AND with the use
//  of the container as a first in LAST out.


#include "impl/add.tpp"
//add_front   , get_front   , cget_front    => push_front
//add_back    , get_back    , cget_back     => push_back
//add_here    , get_here    , cget_here     => insert(here)
//add_anywhere, get_anywhere, cget_anywhere => push,pop,  see xxx_anywhere consistency

#include "impl/emplace.tpp"
//emplace_front   , cget_front    => front
//emplace_back    , cget_back     => back
//emplace_here    , cget_here     => insert(here)
//emplace_anywhere, cget_anywhere => see xxx_anywhere consistency

#include "impl/get.tpp"
//get_front   , cget_front
//get_back    , cget_back
//get_here    , cget_here
//get_anywhere, cget_anywhere => see xxx_anywhere consistency

#include "impl/remove.tpp"
//remove_front     => pop_front
//remove_back      => pop_back
//remove_here      => erase
//remove_anywhere  => erase,  see xxx_anywhere consistency

#include "impl/count.tpp"
//count_empty   (const Container&); => true if count_all==0
//count_all     (const Container&); => size
//count_element => count the number of element that equal to something

#include "impl/mem.tpp"
//mem_reserve
//mem_shrink
//mem_capacity








//--- TODO associative containers ---
//map, unordered_map, boost::multi_map ...


//Trait : is_bidirectional
//Trait : unique_keys

//map_has_key     => contains()
//count_key       => number of keys
//count_values    => number of values
//count_values_at => number of values at key ?

//=> what does get should do for multi map => see map_find_all


// => TODO const corectness : try this code on both const and non const map
//  check if non const value can be changed.
//map_find_one(key) => return an iterator at key
//map_find_all(key) => return a range of iterator, to all values, at key
//  http://www.cplusplus.com/reference/map/multimap/equal_range/

//map_rfind_one(value) => idem, reverse order
//map_rfind_all(value) => idem, reverse order
//  http://www.cplusplus.com/reference/map/multimap/equal_range/

//
//map_get  , map_cget  : get value from key
//map_rget , map_crget : get key   from value (if is_bidirectional )
//=> can be default implemented on top of find.




//map_has_key
//map_has_value


//Template magic for easy emplace key AND value
// map_emplace< std::tuple<...> key_arg,  std::tuple<...> value_arg );




#endif /* LIB_CONTAINER_CONTAINER_HPP_ */
