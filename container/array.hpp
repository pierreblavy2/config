//============================================================================
// Author  : Pierre BLAVY 2018
// Version : 1.0
// License : GPL 3.0 or any later version :
//           https://www.gnu.org/licenses/gpl-3.0-standalone.html
//============================================================================

//This program (container) is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>

#ifndef LIB_CONTAINER_ARRAY_HPP_
#define LIB_CONTAINER_ARRAY_HPP_


#include "container.hpp"
#include <array>


namespace container{

template<class X, std::size_t X_n> constexpr bool unique_values<std::array<X,X_n> > = false;
template<class X, std::size_t X_n> constexpr bool is_ordered <std::array<X,X_n> >       = false;

//--- add_xxx ---

//add_front    : UNIMPLEMENTED
//add_back     : UNIMPLEMENTED
//add_anywhere : UNIMPLEMENTED
//add_here     : UNIMPLEMENTED

//--- emplace_xxx ---
//emplace_font     : UNIMPLEMENTED
//emplace_back     : UNIMPLEMENTED
//emplace_anywhere : UNIMPLEMENTED
//emplace_here     : UNIMPLEMENTED

//--- remove_xxx ---
//remove_font     : UNIMPLEMENTED
//remove_back     : UNIMPLEMENTED
//remove_anywhere : UNIMPLEMENTED
//remove_here     : UNIMPLEMENTED

//--- get ---

//get_front, cget_front
template<class X, std::size_t X_n>
struct Get_front_t< std::array<X,X_n> >{
	Get_front_t()=delete;
	typedef std::array<X,X_n> container_t;

	static decltype(auto) run(container_t &c){return c.front();}

    static constexpr bool is_implemented   = true;
    static constexpr Complexity complexity = Complexity::constant;
};

template<class X, std::size_t X_n>
struct Cget_front_t< std::array<X,X_n> >{
	Cget_front_t()=delete;
	typedef std::array<X,X_n> container_t;

	static decltype(auto) run(const container_t &c){return c.front();}

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::constant;
};


//get_back, cget_back
template<class X, std::size_t X_n>
struct Get_back_t< std::array<X,X_n> >{
	Get_back_t()=delete;
	typedef std::array<X,X_n> container_t;

	static decltype(auto) run(container_t &c){return c.back();}

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::constant;
};


template<class X, std::size_t X_n>
struct Cget_back_t< std::array<X,X_n> >{
	Cget_back_t()=delete;
	typedef std::array<X,X_n> container_t;

	static decltype(auto) run(const container_t &c){return c.back();}

    static constexpr bool is_implemented   = true;
    static constexpr Complexity complexity = Complexity::constant;
};

//get_anywhere cget_anywhere
template<class X, std::size_t X_n>
struct Get_anywhere_t<std::array<X,X_n> > : Get_back_t<std::array<X,X_n>>{};

template<class X, std::size_t X_n>
struct Cget_anywhere_t<std::array<X,X_n> > : Cget_back_t<std::array<X,X_n>>{};



//get_here, cget_here
template<class X, std::size_t X_n>
struct Get_here_t< std::array<X,X_n> >{
	Get_here_t()=delete;
	typedef std::array<X,X_n> container_t;

	static decltype(auto) run(container_t &c, size_t v){return c[v];}

	template<typename Iterator_t>
	static decltype(auto) run(container_t &c, Iterator_t &&v){
		static_assert( std::is_convertible< Iterator_t, typename container_t::iterator >::value, "You must pass an iterator or a size_t");
		return *v;
	}


    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::constant;
};



template<class X, std::size_t X_n>
struct Cget_here_t< std::array<X,X_n> >{
	Cget_here_t()=delete;
	typedef std::array<X,X_n> container_t;

	static decltype(auto) run(const container_t &c, size_t v){return c[v];}

	template<typename ConstIterator_t>
	static decltype(auto) run(const container_t &c, ConstIterator_t &&v){
		static_assert( std::is_convertible< ConstIterator_t, typename container_t::const_iterator >::value, "You must pass an iterator,a const_iterator or a size_t");
		return *v;
	}


    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::constant;
};



//--- mem_xxx ---
// mem_reserve : Default (do nothing)
// mem_shrink  : Default (do nothing)

template<class X, std::size_t X_n>
struct Mem_capacity_t< std::array<X,X_n> >{
	Mem_capacity_t()=delete;
	typedef std::array<X,X_n> container_t;

	static constexpr size_t run(const container_t &){return X_n;}

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::compile_time;
};



//--- count ---
template<class X, std::size_t X_n>
struct Count_empty_t<  std::array<X,X_n> >{
	Count_empty_t()=delete;
	typedef std::array<X,X_n> container_t;

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::compile_time;
	static constexpr bool run(const container_t &c){return X_n== std::size_t(0);}
};


template<class X, std::size_t X_n>
struct Count_all_t<  std::array<X,X_n> >{
	Count_all_t()=delete;
	typedef std::array<X,X_n> container_t;

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::compile_time;
	static constexpr std::size_t run(const container_t &){return X_n;}
};


template<class X, std::size_t X_n>
struct Count_element_t< std::array<X,X_n> >{
	Count_element_t()=delete;
	typedef std::array<X,X_n> container_t;

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::linear;

    template<typename Value_t>
	static size_t run(const container_t &c, Value_t &&e){
    	size_t r = 0;
    	for(const auto &x : c){
    		if(x==e){++r;}
    	}
    	return(r);
    }
};



}


#endif /* LIB_CONTAINER_IMPL_ARRAY_HPP_ */
