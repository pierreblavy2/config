//============================================================================
// Author  : Pierre BLAVY 2018
// Version : 1.0
// License : GPL 3.0 or any later version :
//           https://www.gnu.org/licenses/gpl-3.0-standalone.html
//============================================================================

//This program (container) is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>

#ifndef LIB_CONTAINER_DEQUE_HPP_
#define LIB_CONTAINER_DEQUE_HPP_

#include "container.hpp"
#include <deque>
#include <type_traits>

namespace container{

template<typename X_t, typename...X> constexpr bool unique_values< std::deque<X_t, X...> > = false;
template<typename X_t, typename...X> constexpr bool is_ordered < std::deque<X_t, X...> >       = false;


//--- add_xxx ---

//add_front
template<typename X_t, typename...X>
struct Add_front_t< std::deque<X_t, X...> >{
	Add_front_t()=delete;

	typedef std::deque<X_t, X...> container_t;

	template<typename Value_t>
	static void run(container_t &c, Value_t &&v){
		c.push_front( std::forward<Value_t>(v) );
	}

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::constant;
};

//add_back
template<typename X_t, typename...X>
struct Add_back_t< std::deque<X_t, X...> >{
	Add_back_t()=delete;

	typedef std::deque<X_t, X...> container_t;

	template<typename Value_t>
	static void run(container_t &c, Value_t &&v){
		c.push_back( std::forward<Value_t>(v) );
	}

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::constant;
};

//add_anywhere
template<typename X_t, typename ... X>
struct Add_anywhere_t<std::deque<X_t,X...> > : Add_back_t<std::deque<X_t,X...>>{};


//add_here
template<typename X_t, typename ... X>
struct Add_here_t<std::deque<X_t,X...> >{
	Add_here_t()=delete;
	typedef std::deque<X_t,X...> container_t;

	template<typename Interator_t, typename Value_t>
	static void run(container_t &c,Interator_t &&pl,  Value_t &&v){
		c.insert(std::forward<Interator_t>(pl), std::forward<Value_t>(v) );
	}

	template<typename Value_t>
	static void run(container_t &c, size_t pl,  Value_t &&v){
		c.insert(c.begin() + pl, std::forward<Value_t>(v) );
	}


    static constexpr bool is_implemented = false;
    static constexpr Complexity complexity = Complexity::linear;
};



//--- emplace_xxx ---

//emplace_front
template<typename Value_t, typename ... X>
struct Emplace_front_t< std::deque<Value_t, X...>  > {
	Emplace_front_t()=delete;
	typedef std::deque<Value_t, X...>  container_t;

	template<typename... Args>
	static void run(container_t &c, Args&& ... a){
		c.emplace_front( std::forward<Args>(a)... );
	}

    static constexpr bool is_implemented    = true;
    static constexpr Complexity complexity  = Complexity::constant;
};


//emplace_back
template<typename Value_t, typename ... X>
struct Emplace_back_t< std::deque<Value_t, X...>  > {
	Emplace_back_t()=delete;
	typedef std::deque<Value_t, X...>  container_t;

	template<typename... Args>
	static void run(container_t &c, Args&& ... a){
		c.emplace_back( std::forward<Args>(a)... );
	}

    static constexpr bool is_implemented    = true;
    static constexpr Complexity complexity  = Complexity::constant;

};


//emplace_anywhere
template<typename X_t, typename ... X>
struct Emplace_anywhere_t<std::deque<X_t,X...> > : Emplace_back_t<std::deque<X_t,X...>>{};


//emplace_here
template<typename X_t, typename ... X>
struct Emplace_here_t< std::deque<X_t,X...> >{
	Emplace_here_t()=delete;
	typedef std::deque<X_t,X...> container_t;

	template<typename Place_t, typename... A>
	static void run(container_t &c,Place_t &&pl,  A&& ... v){
		c.emplace(std::forward<Place_t>(pl), std::forward<A>(v)... );
	}

	template<typename Value_t>
	static void run(container_t &c, size_t pl,  Value_t &&v){
		c.emplace(c.begin() + pl, std::forward<Value_t>(v) );
	}

    static constexpr bool is_implemented = false;
    static constexpr Complexity complexity = Complexity::linear;
};






//--- get ---

//get_front, cget_front
template<typename X_t, typename ... X>
struct Get_front_t< std::deque<X_t,X...> >{
	Get_front_t()=delete;
	typedef std::deque<X_t,X...> container_t;

	static decltype(auto) run(container_t &c){return c.front();}

    static constexpr bool is_implemented   = true;
    static constexpr Complexity complexity = Complexity::constant;
};

template<typename X_t, typename ... X>
struct Cget_front_t< std::deque<X_t,X...> >{
	Cget_front_t()=delete;
	typedef std::deque<X_t,X...> container_t;

	static decltype(auto) run(const container_t &c){return c.front();}

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::constant;
};


//get_back, cget_back
template<typename X_t, typename ... X>
struct Get_back_t< std::deque<X_t,X...> >{
	Get_back_t()=delete;
	typedef std::deque<X_t,X...> container_t;

	static decltype(auto) run(container_t &c){return c.back();}

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::constant;
};


template<typename X_t, typename ... X>
struct Cget_back_t< std::deque<X_t,X...> >{
	Cget_back_t()=delete;
	typedef std::deque<X_t,X...> container_t;

	static decltype(auto) run(const container_t &c){return c.back();}

    static constexpr bool is_implemented   = true;
    static constexpr Complexity complexity = Complexity::constant;
};

//get_anywhere cget_anywhere
template<typename X_t, typename ... X>
struct Get_anywhere_t<std::deque<X_t,X...> > : Get_back_t<std::deque<X_t,X...>>{};

template<typename X_t, typename ... X>
struct Cget_anywhere_t<std::deque<X_t,X...> > : Cget_back_t<std::deque<X_t,X...>>{};


//get_here, cget_here
template<typename X_t, typename ... X>
struct Get_here_t< std::deque<X_t,X...> >{
	Get_here_t()=delete;
	typedef std::deque<X_t,X...> container_t;

	static decltype(auto) run(container_t &c, size_t v){return c[v];}

	template<typename Iterator_t>
	static decltype(auto) run(container_t &c, Iterator_t &&v){
		static_assert( std::is_convertible< Iterator_t, typename container_t::iterator >::value, "You must pass an iterator or a size_t");
		return *v;
	}

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::constant;
};



template<typename X_t, typename ... X>
struct Cget_here_t< std::deque<X_t,X...> >{
	Cget_here_t()=delete;
	typedef std::deque<X_t,X...> container_t;

	static decltype(auto) run(const container_t &c, size_t v){return c[v];}

	template<typename ConstIterator_t>
	static decltype(auto) run(const container_t &c, ConstIterator_t &&v){
		static_assert( std::is_convertible< ConstIterator_t, typename container_t::const_iterator >::value, "You must pass an iterator,a const_iterator or a size_t");
		return *v;
	}

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::constant;
};


//--- remove_xxx ---
template<typename X_t, typename ... X>
struct Remove_front_t< std::deque<X_t,X...> >{
	Remove_front_t()=delete;
	typedef std::deque<X_t,X...> container_t;

	static void run(container_t &c){c.erase(c.begin());}

    static constexpr bool is_implemented   = true;
    static constexpr Complexity complexity = Complexity::constant;
};

template<typename X_t, typename ... X>
struct Remove_back_t< std::deque<X_t,X...> >{
	Remove_back_t()=delete;
	typedef std::deque<X_t,X...> container_t;

	static void run(container_t &c){c.erase(c.end()-1 );}

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::constant;
};


template<typename X_t, typename ... X>
struct Remove_anywhere_t<std::deque<X_t,X...> > : Remove_back_t<std::deque<X_t,X...>>{};


template<typename X_t, typename ... X>
struct Remove_here_t< std::deque<X_t,X...> >{
	Remove_here_t()=delete;
	typedef std::deque<X_t,X...> container_t;

	static decltype(auto) run(container_t &c, size_t v){
		auto it = c.begin();
		std::advance(it,v);
		c.erase(it);
	}

	template<typename Iterator_t>
	static decltype(auto) run(container_t &c, Iterator_t &&v){
		c.erase(v);
	}

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::linear;
};



//--- mem_xxx ---
//mem_reserve : DEFAULT (do nothing)
//mem_shrink  : DEFAULT (do nothing)
//mem_capacity: return size


template<typename X_t, typename ... X>
struct Mem_capacity_t< std::deque<X_t,X...> >{
	Mem_capacity_t()=delete;
	typedef std::deque<X_t,X...> container_t;

	static size_t run(const container_t &c){return c.size();}

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::constant;
};



//--- count ---
template<typename X_t, typename ... X>
struct Count_empty_t< std::deque<X_t,X...> >{
	Count_empty_t()=delete;
	typedef std::deque<X_t,X...> container_t;

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::constant;
	static bool run(const container_t &c){return c.empty();}
};


template<typename X_t, typename ... X>
struct Count_all_t< std::deque<X_t,X...> >{
	Count_all_t()=delete;
	typedef std::deque<X_t,X...> container_t;

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::constant;
	static decltype(auto) run(const container_t &c){return c.size();}
};


template<typename X_t, typename ... X>
struct Count_element_t< std::deque<X_t,X...> >{
	Count_element_t()=delete;
	typedef std::deque<X_t,X...> container_t;

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

#endif /* LIB_CONTAINER_deque_HPP_ */
