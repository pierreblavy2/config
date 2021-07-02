//============================================================================
// Author  : Pierre BLAVY 2018
// Version : 1.0
// License : GPL 3.0 or any later version :
//           https://www.gnu.org/licenses/gpl-3.0-standalone.html
//============================================================================

//This program (container) is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>

#ifndef LIB_CONTAINER_IMPL_COMPLEXITY_HPP_
#define LIB_CONTAINER_IMPL_COMPLEXITY_HPP_

namespace container{
	enum struct Complexity:int{compile_time, constant, log, linear, nlog, polynomial, exponential, unknown};
}

inline bool operator< (const container::Complexity &a, const container::Complexity&b){return static_cast<int>(a) <  static_cast<int>(b);}
inline bool operator> (const container::Complexity &a, const container::Complexity&b){return static_cast<int>(a) >  static_cast<int>(b);}
inline bool operator<=(const container::Complexity &a, const container::Complexity&b){return static_cast<int>(a) <= static_cast<int>(b);}
inline bool operator>=(const container::Complexity &a, const container::Complexity&b){return static_cast<int>(a) >= static_cast<int>(b);}
inline bool operator==(const container::Complexity &a, const container::Complexity&b){return static_cast<int>(a) == static_cast<int>(b);}
inline bool operator!=(const container::Complexity &a, const container::Complexity&b){return static_cast<int>(a) != static_cast<int>(b);}


#endif /* LIB_CONTAINER_IMPL_COMPLEXITY_HPP_ */
