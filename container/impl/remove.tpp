//============================================================================
// Author  : Pierre BLAVY 2018
// Version : 1.0
// License : GPL 3.0 or any later version :
//           https://www.gnu.org/licenses/gpl-3.0-standalone.html
//============================================================================

//This program (container) is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>

#ifndef LIB_CONTAINER_IMPL_REMOVE_TPP_
#define LIB_CONTAINER_IMPL_REMOVE_TPP_

//--- remove elements
//remove_front  => pop_front
//remove_back   => pop_back
//remove_here   => erase
//remove_anywhere  => MUST be constistent with xxx_anywhere

#include <utility>//forward

namespace container{


template<typename Container_t>
struct Remove_front_t{
	Remove_front_t()=delete;


	static void run(Container_t &c)=delete; //UNIMPLEMENTED

    static constexpr bool is_implemented = false;
    static constexpr Complexity complexity = Complexity::unknown;
};


template<typename Container_t>
inline decltype(auto) remove_front(Container_t &c){
	return Remove_front_t<Container_t>::run(c);
}




template<typename Container_t>
struct Remove_back_t{
	Remove_back_t()=delete;


	static void run(Container_t &c)=delete; //UNIMPLEMENTED

    static constexpr bool is_implemented = false;
    static constexpr Complexity complexity = Complexity::unknown;
};


template<typename Container_t>
inline decltype(auto) remove_back(Container_t &c){
	return Remove_front_t<Container_t>::run(c);
}




template<typename Container_t>
struct Remove_anywhere_t{
	Remove_anywhere_t()=delete;


	static void run(Container_t &c)=delete; //UNIMPLEMENTED

    static constexpr bool is_implemented = false;
    static constexpr Complexity complexity = Complexity::unknown;
};


template<typename Container_t>
inline decltype(auto) remove_anywhere(Container_t &c){
	return Remove_anywhere_t<Container_t>::run(c);
}




template<typename Container_t>
struct Remove_here_t{
	Remove_here_t()=delete;

	template< typename Index_t>
	static void run(Container_t &c, Index_t &&v)=delete; //UNIMPLEMENTED, should return a reference on value_t

    static constexpr bool is_implemented = false;
    static constexpr Complexity complexity = Complexity::unknown;
};

template<typename Container_t, typename Index_t>
inline decltype(auto) remove_here(Container_t &c, Index_t &&v){
	return Remove_here_t<Container_t>::run(c,std::forward<Index_t>(v));
}




}



#endif /* LIB_CONTAINER_IMPL_REMOVE_TPP_ */
