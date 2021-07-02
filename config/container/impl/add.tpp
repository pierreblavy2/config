//============================================================================
// Author  : Pierre BLAVY 2018
// Version : 1.0
// License : GPL 3.0 or any later version :
//           https://www.gnu.org/licenses/gpl-3.0-standalone.html
//============================================================================

//This program (container) is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>


#ifndef LIB_CONTAINER_IMPL_ADD_TPP_
#define LIB_CONTAINER_IMPL_ADD_TPP_

#include <utility>//forward

namespace container{



template<typename Container_t>
struct Add_front_t{
	Add_front_t()=delete;
	typedef Container_t container_t;

	template<typename Value_t>
	static void run(container_t &c, Value_t &&v)=delete; //UNIMPLEMENTED

    static constexpr bool is_implemented = false;
    static constexpr Complexity complexity = Complexity::unknown;
};

template<typename Container_t, typename Value_t>
void add_front(Container_t &c, Value_t &&v ){
	Add_front_t<Container_t>::run(c,std::forward<Value_t>(v) );
}





template<typename Container_t>
struct Add_back_t{
	Add_back_t()=delete;
	typedef Container_t container_t;

	template<typename Value_t>
	static void run(container_t &c, Value_t &&v)=delete; //UNIMPLEMENTED

    static constexpr bool is_implemented = false;
    static constexpr Complexity complexity = Complexity::unknown;
};

template<typename Container_t, typename Value_t>
void add_back(Container_t &c, Value_t && v ){
	Add_back_t<Container_t>::run(c,std::forward<Value_t>(v) );
}


template<typename Container_t>
struct Add_anywhere_t{
	Add_anywhere_t()=delete;
	typedef Container_t container_t;

	template< typename Value_t>
	static void run(container_t &c, Value_t &&v)=delete; //UNIMPLEMENTED

    static constexpr bool is_implemented = false;
    static constexpr Complexity complexity = Complexity::unknown;
};

template<typename Container_t,  typename Value_t>
void add_anywhere(Container_t &c, Value_t && v ){
	Add_anywhere_t<Container_t>::run(c, std::forward<Value_t>(v) );
}




template<typename Container_t>
struct Add_here_t{
	Add_here_t()=delete;
	typedef Container_t container_t;

	template<typename Place_t, typename Value_t>
	static void run(container_t &c,Place_t &&pl,  Value_t &&v)=delete; //UNIMPLEMENTED

    static constexpr bool is_implemented = false;
    static constexpr Complexity complexity = Complexity::unknown;
};

template<typename Container_t, typename Place_t, typename Value_t>
void add_here(Container_t &c,Place_t&& pl, Value_t && v ){
	Add_here_t<Container_t>::run(c,std::forward<Place_t>(pl), std::forward<Value_t>(v) );
}





}//end namespace container
#endif /* LIB_CONTAINER_IMPL_ADD_TPP_ */
