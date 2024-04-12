//============================================================================
// Author  : Pierre BLAVY 2018
// Version : 1.0
// License : GPL 3.0 or any later version :
//           https://www.gnu.org/licenses/gpl-3.0-standalone.html
//============================================================================

//This program (container) is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>

#ifndef LIB_CONTAINER_IMPL_COUNT_TPP_
#define LIB_CONTAINER_IMPL_COUNT_TPP_

//count_empty   (const Container&); => true if count_all==0
//count_all     (const Container&); => size
//MAYBE : count_distinct(const Container&); => size for unique containers

#include <cstddef>


namespace container{

template<typename Container_t>
struct Count_empty_t{
	Count_empty_t()=delete;
	typedef Container_t container_t;

    static constexpr bool is_implemented = false;
    static constexpr Complexity complexity = Complexity::unknown;
	static bool run(const container_t &c)=delete; //UNIMPLEMENTED
};

template<typename Container_t>
inline bool count_empty(const Container_t&c){
	return Count_empty_t<Container_t>::run(c);
}




template<typename Container_t>
struct Count_all_t{
	Count_all_t()=delete;
	typedef Container_t container_t;

    static constexpr bool is_implemented = false;
    static constexpr Complexity complexity = Complexity::unknown;
	static void run(const container_t &c)=delete; //UNIMPLEMENTED, should return size_t
};

template<typename Container_t>
inline decltype(auto) count_all(const Container_t&c){
	return Count_all_t<Container_t>::run(c);
}




template<typename Container_t>
struct Count_element_t{
	Count_element_t()=delete;
	typedef Container_t container_t;

    static constexpr bool is_implemented = false;
    static constexpr Complexity complexity = Complexity::unknown;

    template<typename Value_t>
	static size_t run(const container_t &c, Value_t &&e)=delete; //UNIMPLEMENTED, should return size_t
};
template<typename Container_t, typename Value_t >
inline decltype(auto) count_element(const Container_t&c, Value_t&&e){
	return Count_element_t<Container_t>::run(c, std::forward<Value_t>(e) );
}




//TODO latter : count_distinct

}





#endif /* LIB_CONTAINER_IMPL_COUNT_TPP_ */
