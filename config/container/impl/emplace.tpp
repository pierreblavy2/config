//============================================================================
// Author  : Pierre BLAVY 2018
// Version : 1.0
// License : GPL 3.0 or any later version :
//           https://www.gnu.org/licenses/gpl-3.0-standalone.html
//============================================================================

//This program (container) is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>

#ifndef LIB_CONTAINER_IMPL_EMPLACE_TPP_
#define LIB_CONTAINER_IMPL_EMPLACE_TPP_


namespace container{


template<typename Container_t>
struct Emplace_front_t{
	Emplace_front_t()=delete;
	typedef Container_t container_t;

	template<typename... Args>
	static void run(container_t &c, Args&& ... v)=delete; //UNIMPLEMENTED

    static constexpr bool is_implemented    = false;
    static constexpr Complexity complexity  = Complexity::unknown;
};

template<typename Container_t, typename... Args>
void emplace_front(Container_t &c, Args&& ... a ){
	Emplace_front_t<Container_t>::run(c,std::forward<Args>(a)...);
}






template<typename Container_t>
struct Emplace_back_t{
	Emplace_back_t()=delete;
	typedef Container_t container_t;

	template<typename... Args>
	static void run(container_t &c, Args&& ... v)=delete; //UNIMPLEMENTED

    static constexpr bool is_implemented    = false;
    static constexpr Complexity complexity  = Complexity::unknown;

};

template<typename Container_t, typename... Args>
void emplace_back(Container_t &c, Args&& ... a ){
	Emplace_back_t<Container_t>::run(c,std::forward<Args>(a)...);
}









template<typename Container_t>
struct Emplace_anywhere_t{
	Emplace_anywhere_t()=delete;
	typedef Container_t container_t;

	template<typename... A>
	static void run(container_t &c, A&& ... v)=delete; //UNIMPLEMENTED

    static constexpr bool is_implemented = false;
    static constexpr Complexity complexity = Complexity::unknown;
};

template<typename Container_t, typename... A>
void emplace_anywhere(Container_t &c, A&& ... v ){
	Emplace_anywhere_t<Container_t>::run(c, std::forward<A>(v)... );
}



template<typename Container_t>
struct Emplace_here_t{
	Emplace_here_t()=delete;
	typedef Container_t container_t;

	template<typename Place_t, typename... A>
	static void run(container_t &c,Place_t &&pl,  A&& ... v)=delete; //UNIMPLEMENTED

    static constexpr bool is_implemented = false;
    static constexpr Complexity complexity = Complexity::unknown;
};

template<typename Container_t, typename Place_t, typename... A>
void emplace_here(Container_t &c,Place_t&& pl, A&& ... v ){
	Emplace_here_t<Container_t>::run(c,std::forward<Place_t>(pl), std::forward<A>(v)... );
}



}

#endif /* LIB_CONTAINER_IMPL_EMPLACE_TPP_ */
