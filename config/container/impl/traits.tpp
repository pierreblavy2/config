//============================================================================
// Author  : Pierre BLAVY 2018
// Version : 1.0
// License : GPL 3.0 or any later version :
//           https://www.gnu.org/licenses/gpl-3.0-standalone.html
//============================================================================

//This program (container) is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>

#ifndef LIB_CONTAINER_IMPL_TRAITS_TPP_
#define LIB_CONTAINER_IMPL_TRAITS_TPP_


//--- traits ---
namespace container{
  namespace impl{
  	  template<typename... T> struct Unimplemented{};
  }

  //The compiler requires an initialiser, even if the template is not implemented.
  //ERROR here : you must specialise the template for your class
  template<typename Container> constexpr bool unique_values = impl::Unimplemented<Container>::value;
  template<typename Container> constexpr bool is_ordered    = impl::Unimplemented<Container>::value;
}

//--- wrap implementation traits ---
namespace container{
	template<template<typename> class What,typename Container>
	constexpr bool is_implemented = What<Container>::is_implemented;

	template<template<typename> class What,typename Container>
	constexpr Complexity complexity     = What<Container>::complexity;
}

//--- value_type ---
namespace container{
  template<typename Container>
  struct Value_type_t{
	  typedef typename Container::value_type type;
	  //Error here -> you must write your own specification
  };

  template<typename Container>
  using value_type = typename Value_type_t<Container>::type;
}



#endif /* LIB_CONTAINER_IMPL_TRAITS_TPP_ */
