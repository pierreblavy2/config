//============================================================================
// Author  : Pierre BLAVY 2018
// Version : 1.0
// License : GPL 3.0 or any later version :
//           https://www.gnu.org/licenses/gpl-3.0-standalone.html
//============================================================================

//This program (convert) is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>

#ifndef LIB_CONFIG2_CONVERT_HPP_
#define LIB_CONFIG2_CONVERT_HPP_

#include <type_traits>

//todo can_convert<To, From, Context>

template<typename To_tt, typename From_tt, typename Context_tag_tt> struct Convert_t{
	typedef To_tt To_t;
	typedef From_tt From_t;
	typedef Context_tag_tt Context_tag_t;

	static constexpr bool is_implemented =
		   std::is_constructible<To_tt,From_tt>::value
		or std::is_same<To_tt,From_tt>::value;

	static To_t run(const From_t &f){
		return static_cast<To_t>(f);
	}
};

//Dipsatch : do nothing on trivial conversions
namespace Convert_impl{

	template<typename To_t> struct Convert_nothing{
		static const To_t &run(const To_t &f){
			return f;
		}
	};

	template<bool is_trivial, typename To_t, typename From_t, typename Context_tag> struct Convert_dispatch{
		typedef Convert_t<To_t,From_t,Context_tag> type;
	};

	template<typename To_t, typename From_t, typename Context_tag> struct Convert_dispatch<true,To_t,From_t,Context_tag >{
		typedef Convert_nothing<To_t> type;
	};
}



template<typename To_t, typename Context_tag=void, typename From_t> decltype(auto) convert(const From_t &f){
	static constexpr bool is_trivial = std::is_same<To_t,From_t>::value;
    typedef typename Convert_impl::Convert_dispatch<is_trivial,To_t,From_t,Context_tag>::type convert_type;
	return convert_type::run(f);
}

template<typename Context_tag=void, typename To_t, typename From_t> void convert(To_t &write_here, const From_t &f){
	static_assert(!std::is_const<To_t>::value,"write_here must be writable but it's const");

	static constexpr bool is_trivial = std::is_same<To_t,From_t>::value;
	typedef typename Convert_impl::Convert_dispatch<is_trivial,To_t,From_t,Context_tag>::type convert_type;
	write_here=convert_type::run(f);
}








#endif /* LIB_CONFIG2_CONVERT_HPP_ */
