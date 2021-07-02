//============================================================================
// Author  : Pierre BLAVY 2018
// Version : 1.0
// License : GPL 3.0 or any later version :
//           https://www.gnu.org/licenses/gpl-3.0-standalone.html
//============================================================================

//This program (container) is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>

#ifndef LIB_CONTAINER_IMPL_MEM_TPP_
#define LIB_CONTAINER_IMPL_MEM_TPP_



//--- mem_reserve ---
//give a hint, to reserve memory space.
//reserve always INCREASE the container reserved size
//NOTE : if the container is not able to reserve memory, reserve does nothing
//NOTE : if there is a way to throw an error, when you're sure that the reserve
//  requirement cannot be met, the implementation is encouraged to do so. This
//  is typically the case, for a reserve in std::array, when we reserve
//  more than the array size.

#include <utility>//forward

namespace container{
template<typename Container_t>
struct Mem_reserve_t{
	Mem_reserve_t()=delete;

	template<typename S>
	static void run(Container_t &, S&&){}//Default do nothing

    static constexpr bool is_implemented = true;
    static constexpr bool do_something   = false;
    static constexpr Complexity complexity = Complexity::constant;

};

template<typename Container_t, typename Size_t>
void mem_reserve(Container_t &c, Size_t i ){
	Mem_reserve_t<Container_t>::run(c, i );
}



//--- mem_shrink ---
//--- if possible, if the underlying implementation actually do it, shring
//    to the current size
//    WARNING : do_something is set to true, if the underlying implementation
//    of the container provide a shrink function. This function may still do
//    nothing.
template<typename Container_t>
struct Mem_shrink_t{
	Mem_shrink_t()=delete;

	static void run(Container_t &){}//Default do nothing

    static constexpr bool is_implemented = true;
    static constexpr bool do_something   = false;
    static constexpr Complexity complexity = Complexity::constant;

};

template<typename Container_t>
void mem_shrink(Container_t &c){
	Mem_shrink_t<Container_t>::run(c);
}


//--- mem capacity ---
//returns the already reserved capacity.
//WARNING : There is no clever value to return, when computing capacity
//doesn't make sense.
//WARNING : few containers will implement this template
// ==> don't forget
//     constexpr if(Mem_capacity_t<YourContainer>::is_implemented){}else{}

template<typename Container_t>
struct Mem_capacity_t{
	Mem_capacity_t()=delete;
	typedef Container_t container_t;

	static void run(const container_t &)=delete;//UNIMPLEMENTED, should return a size (typically size_t)

    static constexpr bool is_implemented = false;
    static constexpr Complexity complexity = Complexity::unknown;
};


template<typename Container_t>
auto mem_capacity(Container_t &c){
	return Mem_capacity_t<Container_t>::run(c);
}



}







#endif /* LIB_CONTAINER_IMPL_MEM_TPP_ */
