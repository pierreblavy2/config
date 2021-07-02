//============================================================================
// Author  : Pierre BLAVY 2018
// Version : 1.0
// License : GPL 3.0 or any later version :
//           https://www.gnu.org/licenses/gpl-3.0-standalone.html
//============================================================================

//This program (container) is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>

#ifndef LIB_CONTAINER_IMPL_GET_TPP_
#define LIB_CONTAINER_IMPL_GET_TPP_
//get_front   , cget_front
//get_back    , cget_back
//get_here    , cget_here
//get_anywhere, cget_anywhere => MUST be constistent with xxx_anywhere

#include <utility>//forward

//NOTE : some implementation like std::vector<bool> returns PROXY instead of
//references to underlying values. Therefore we DO NEED to return decltype(auto)
//instead of auto& or const auto&

namespace container{

//get_front, cget_front
template<typename Container_t>
struct Get_front_t{
	Get_front_t()=delete;
	typedef Container_t container_t;

	static void  run(container_t &c)=delete; //UNIMPLEMENTED, should return a reference on value_t

    static constexpr bool is_implemented = false;
    static constexpr Complexity complexity = Complexity::unknown;
};
template<typename Container_t>
inline decltype(auto) get_front(Container_t &c){
	return Get_front_t<Container_t>::run(c);
}

template<typename Container_t>
struct Cget_front_t{
	Cget_front_t()=delete;
	typedef Container_t container_t;

	static void  run(const container_t &c)=delete; //UNIMPLEMENTED, should return a reference on const value_t

    static constexpr bool is_implemented = false;
    static constexpr Complexity complexity = Complexity::unknown;
};
template<typename Container_t>
inline decltype(auto) cget_front(const Container_t &c){
	return Cget_front_t<Container_t>::run(c);
}







//get_back, cget_back
template<typename Container_t>
struct Get_back_t{
	Get_back_t()=delete;
	typedef Container_t container_t;

	template<typename Place_t>
	static void  run(container_t &c)=delete; //UNIMPLEMENTED, should return a reference on value_t

    static constexpr bool is_implemented = false;
    static constexpr Complexity complexity = Complexity::unknown;
};
template<typename Container_t>
inline decltype(auto) get_back(Container_t &c){
	return Get_back_t<Container_t>::run(c);
}


template<typename Container_t>
struct Cget_back_t{
	Cget_back_t()=delete;
	typedef Container_t container_t;

	static void  run(const container_t &c)=delete; //UNIMPLEMENTED, should return a reference on const value_t

    static constexpr bool is_implemented = false;
    static constexpr Complexity complexity = Complexity::unknown;
};
template<typename Container_t>
inline decltype(auto) cget_back(const Container_t &c){
	return Cget_back_t<Container_t>::run(c);
}



//get_anywhere cget_anywhere
template<typename Container_t>
struct Get_anywhere_t{
	Get_anywhere_t()=delete;
	typedef Container_t container_t;

	static void run(container_t &c)=delete; //UNIMPLEMENTED, should return a reference on value_t

    static constexpr bool is_implemented = false;
    static constexpr Complexity complexity = Complexity::unknown;
};
template<typename Container_t>
inline decltype(auto) get_anywhere(Container_t &c){
	return Get_anywhere_t<Container_t>::run(c);
}

template<typename Container_t>
struct Cget_anywhere_t{
	Cget_anywhere_t()=delete;
	typedef Container_t container_t;

	static void run(const container_t &c)=delete; //UNIMPLEMENTED, should return a reference on const value_t

    static constexpr bool is_implemented = false;
    static constexpr Complexity complexity = Complexity::unknown;
};
template<typename Container_t>
inline decltype(auto) cget_anywhere(const Container_t &c){
	return Cget_anywhere_t<Container_t>::run(c);
}




//get_gere, cget_here
template<typename Container_t>
struct Get_here_t{
	Get_here_t()=delete;
	typedef Container_t container_t;

	template< typename Index_t>
	static void run(container_t &c, Index_t &&v)=delete; //UNIMPLEMENTED, should return a reference on value_t

    static constexpr bool is_implemented = false;
    static constexpr Complexity complexity = Complexity::unknown;
};

template<typename Container_t, typename Index_t>
inline decltype(auto) get_here(Container_t &c, Index_t &&v){
	return Get_here_t<Container_t>::run(c,std::forward<Index_t>(v));
}


template<typename Container_t>
struct Cget_here_t{
	Cget_here_t()=delete;
	typedef Container_t container_t;

	template< typename Index_t>
	static void run(const container_t &c, Index_t &&v)=delete; //UNIMPLEMENTED, should return a reference on value_t

    static constexpr bool is_implemented = false;
    static constexpr Complexity complexity = Complexity::unknown;
};

template<typename Container_t, typename Index_t>
inline decltype(auto) cget_here(const Container_t &c, Index_t &&v){
	return Cget_here_t<Container_t>::run(c,std::forward<Index_t>(v));
}




}



#endif /* LIB_CONTAINER_IMPL_GET_TPP_ */
