//============================================================================
// Author  : Pierre BLAVY 2018
// Version : 1.0
// License : GPL 3.0 or any later version :
//           https://www.gnu.org/licenses/gpl-3.0-standalone.html
//============================================================================

//This program (container) is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>

#ifndef LIB_CONTAINER_SET_TPP_
#define LIB_CONTAINER_SET_TPP_


#include "container.hpp"
#include <set>



//=== set ===
namespace container{

template<typename X_t, typename...X> constexpr bool unique_values< std::set<X_t, X...> > = true;
template<typename X_t, typename...X> constexpr bool is_ordered < std::set<X_t, X...> >       = true;

//--- add_xxx ---

//add_front : UNIMPLEMENTED
//add_back  : UNIMPLEMENTED
//add_here  : UNIMPLEMENTED
//add_anywhere
template<typename X_t, typename ... X>
struct Add_anywhere_t< std::set<X_t, X...> >{
	Add_anywhere_t()=delete;

	typedef std::set<X_t, X...> container_t;

	template<typename Value_t>
	static void run(container_t &c, Value_t &&v){c.insert(v);}

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::log;
};




//--- emplace_xxx ---
//emplace_front : UNIMPLEMENTED
//emplace_back  : UNIMPLEMENTED
//emplace_here  : UNIMPLEMENTED

template<typename X_t, typename ... X>
struct Emplace_anywhere_t< std::set<X_t, X...> >{
	Emplace_anywhere_t()=delete;

	typedef std::set<X_t, X...> container_t;

	template< typename ... A>
	static void run(container_t &c, A&&... a){c.emplace(std::forward<A>(a)...);}

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::log;
};



//--- get ---
//get_front    : UNIMPLEMENTED (not allowed to modify set elements)
//get_back     : UNIMPLEMENTED (not allowed to modify set elements)
//get_anywhere : UNIMPLEMENTED (not allowed to modify set elements)
//get_here     : UNIMPLEMENTED (not allowed to modify set elements)
//cget_xxx     : IMPLEMENTED, as reading const value is OK


//cget_front
template<typename X_t, typename ... X>
struct Cget_front_t< std::set<X_t,X...> >{
	Cget_front_t()=delete;
	typedef std::set<X_t,X...> container_t;

	static decltype(auto) run(const container_t &c){return *(c.cbegin());}

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::constant;
};

//cget_back
template<typename X_t, typename ... X>
struct Cget_back_t< std::set<X_t,X...> >{
	Cget_back_t()=delete;
	typedef std::set<X_t,X...> container_t;

	static decltype(auto) run(const container_t &c){return *(c.crbegin());}

    static constexpr bool is_implemented   = true;
    static constexpr Complexity complexity = Complexity::constant;
};

//cget_anywhere
template<typename X_t, typename ... X>
struct Cget_anywhere_t<std::set<X_t,X...> > : Cget_back_t<std::set<X_t,X...>>{};


//cget_here
template<typename X_t, typename ... X>
struct Cget_here_t< std::set<X_t,X...> >{
	Cget_here_t()=delete;
	typedef std::set<X_t,X...> container_t;


	static decltype(auto) run(const container_t &c, size_t v){
		auto it = c.cbegin();
		std::advance(it,v);
		return *it;
	}

	template<typename ConstIterator_t>
	static decltype(auto) run(const container_t &c, ConstIterator_t v){
		static_assert( std::is_convertible< ConstIterator_t, typename container_t::const_iterator >::value, "You must pass an iterator,a const_iterator or a size_t");
		return *v;
	}

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::linear;
};


//--- remove ---
template<typename X_t, typename ... X>
struct Remove_front_t< std::set<X_t,X...> >{
	Remove_front_t()=delete;
	typedef std::set<X_t,X...> container_t;

	static void run(container_t &c){c.erase(c.begin());}

    static constexpr bool is_implemented   = true;
    static constexpr Complexity complexity = Complexity::linear;
};


template<typename X_t, typename ... X>
struct Remove_back_t< std::set<X_t,X...> >{
	Remove_back_t()=delete;
	typedef std::set<X_t,X...> container_t;

	static void run(container_t &c){
		auto it = c.begin();
		std::advance(it, c.size()-1  );
		c.erase(it );
	}

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::linear;
};


template<typename X_t, typename ... X>
struct Remove_anywhere_t<std::set<X_t,X...> > : Remove_back_t<std::set<X_t,X...>>{};


template<typename X_t, typename ... X>
struct Remove_here_t< std::set<X_t,X...> >{
	Remove_here_t()=delete;
	typedef std::set<X_t,X...> container_t;

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
    static constexpr Complexity complexity = Complexity::linear; //linear for size_t, constant for Iterator_t
};



//--- mem_xxx ---
//mem_reserve  : DEFAULT (do nothing)
//mem_shrink   : DEFAULT (do nothing)
//mem_capacity : returns size

template<typename X_t, typename ... X>
struct Mem_capacity_t< std::set<X_t,X...> >{
	Mem_capacity_t()=delete;
	typedef std::set<X_t,X...> container_t;

	static size_t run(const container_t &c){return c.size();}

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::constant;
};



//--- count ---
template<typename X_t, typename ... X>
struct Count_empty_t< std::set<X_t,X...> >{
	Count_empty_t()=delete;
	typedef std::set<X_t,X...> container_t;

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::constant;
	static bool run(const container_t &c){return c.empty();}
};


template<typename X_t, typename ... X>
struct Count_all_t< std::set<X_t,X...> >{
	Count_all_t()=delete;
	typedef std::set<X_t,X...> container_t;

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::constant;
	static decltype(auto) run(const container_t &c){return c.size();}
};


template<typename X_t, typename ... X>
struct Count_element_t< std::set<X_t,X...> >{
	Count_element_t()=delete;
	typedef std::set<X_t,X...> container_t;

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::log;

    template<typename Value_t>
	static size_t run(const container_t &c, Value_t &&e){return c.count(std::forward<Value_t>(e) );}
};


}







//=== multiset ===
namespace container{

template<typename X_t, typename...X> constexpr bool unique_values< std::multiset<X_t, X...> > = false;
template<typename X_t, typename...X> constexpr bool is_ordered       < std::multiset<X_t, X...> > = true;

//--- add_xxx ---

//add_front : UNIMPLEMENTED
//add_back  : UNIMPLEMENTED
//add_here  : UNIMPLEMENTED

//add_anywhere
template<typename X_t, typename ... X>
struct Add_anywhere_t< std::multiset<X_t, X...> >{
	Add_anywhere_t()=delete;

	typedef std::multiset<X_t, X...> container_t;

	template<typename Value_t>
	static void run(container_t &c, Value_t &&v){c.insert(v);}

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::log;
};




//--- emplace_xxx ---
//emplace_front : UNIMPLEMENTED
//emplace_back  : UNIMPLEMENTED
//emplace_here  : UNIMPLEMENTED

template<typename X_t, typename ... X>
struct Emplace_anywhere_t< std::multiset<X_t, X...> >{
	Emplace_anywhere_t()=delete;

	typedef std::multiset<X_t, X...> container_t;

	template< typename ... A>
	static void run(container_t &c, A&&... a){c.emplace(std::forward<A>(a)...);}

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::log;
};



//--- get ---
//get_front    : UNIMPLEMENTED (not allowed to modify set elements)
//get_back     : UNIMPLEMENTED (not allowed to modify set elements)
//get_anywhere : UNIMPLEMENTED (not allowed to modify set elements)
//get_here     : UNIMPLEMENTED (not allowed to modify set elements)
//cget_xxx     : IMPLEMENTED, as reading const value is OK


//cget_front
template<typename X_t, typename ... X>
struct Cget_front_t< std::multiset<X_t,X...> >{
	Cget_front_t()=delete;
	typedef std::multiset<X_t,X...> container_t;

	static decltype(auto) run(const container_t &c){return *(c.cbegin());}

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::constant;
};

//cget_back
template<typename X_t, typename ... X>
struct Cget_back_t< std::multiset<X_t,X...> >{
	Cget_back_t()=delete;
	typedef std::multiset<X_t,X...> container_t;

	static decltype(auto) run(const container_t &c){return *(c.crbegin());}

    static constexpr bool is_implemented   = true;
    static constexpr Complexity complexity = Complexity::constant;
};

//cget_anywhere
template<typename X_t, typename ... X>
struct Cget_anywhere_t<std::multiset<X_t,X...> > : Cget_back_t<std::multiset<X_t,X...>>{};


//cget_here
template<typename X_t, typename ... X>
struct Cget_here_t< std::multiset<X_t,X...> >{
	Cget_here_t()=delete;
	typedef std::multiset<X_t,X...> container_t;


	static decltype(auto) run(const container_t &c, size_t v){
		auto it = c.cbegin();
		std::advance(it,v);
		return *it;
	}

	template<typename ConstIterator_t>
	static decltype(auto) run(const container_t &c, ConstIterator_t v){
		static_assert( std::is_convertible< ConstIterator_t, typename container_t::const_iterator >::value, "You must pass an iterator,a const_iterator or a size_t");
		return *v;
	}

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::linear;
};



//--- mem_xxx ---
//mem_reserve  : DEFAULT (do nothing)
//mem_shrink   : DEFAULT (do nothing)
//mem_capacity : returns size

template<typename X_t, typename ... X>
struct Mem_capacity_t< std::multiset<X_t,X...> >{
	Mem_capacity_t()=delete;
	typedef std::multiset<X_t,X...> container_t;

	static size_t run(const container_t &c){return c.size();}

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::constant;
};



//--- count ---
template<typename X_t, typename ... X>
struct Count_empty_t< std::multiset<X_t,X...> >{
	Count_empty_t()=delete;
	typedef std::multiset<X_t,X...> container_t;

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::constant;
	static bool run(const container_t &c){return c.empty();}
};


template<typename X_t, typename ... X>
struct Count_all_t< std::multiset<X_t,X...> >{
	Count_all_t()=delete;
	typedef std::multiset<X_t,X...> container_t;

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::constant;
	static decltype(auto) run(const container_t &c){return c.size();}
};


template<typename X_t, typename ... X>
struct Count_element_t< std::multiset<X_t,X...> >{
	Count_element_t()=delete;
	typedef std::multiset<X_t,X...> container_t;

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::log;

    template<typename Value_t>
	static size_t run(const container_t &c, Value_t &&e){return c.count(std::forward<Value_t>(e) );}
};




//--- remove ---
template<typename X_t, typename ... X>
struct Remove_front_t< std::multiset<X_t,X...> >{
	Remove_front_t()=delete;
	typedef std::multiset<X_t,X...> container_t;

	static void run(container_t &c){c.erase(c.begin());}

    static constexpr bool is_implemented   = true;
    static constexpr Complexity complexity = Complexity::linear;
};


template<typename X_t, typename ... X>
struct Remove_back_t< std::multiset<X_t,X...> >{
	Remove_back_t()=delete;
	typedef std::multiset<X_t,X...> container_t;

	static void run(container_t &c){
		auto it = c.begin();
		std::advance(it, c.size()-1  );
		c.erase(it );
	}

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::linear;
};


template<typename X_t, typename ... X>
struct Remove_anywhere_t<std::multiset<X_t,X...> > : Remove_back_t<std::multiset<X_t,X...>>{};


template<typename X_t, typename ... X>
struct Remove_here_t< std::multiset<X_t,X...> >{
	Remove_here_t()=delete;
	typedef std::multiset<X_t,X...> container_t;

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
    static constexpr Complexity complexity = Complexity::linear; //linear for size_t, constant for Iterator_t
};



}




#endif
