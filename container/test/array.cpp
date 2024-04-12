//============================================================================
// Author  : Pierre BLAVY 2018
// Version : 1.0
// License : GPL 3.0 or any later version :
//           https://www.gnu.org/licenses/gpl-3.0-standalone.html
//============================================================================

//This program (container) is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>


#include "../array.hpp"


namespace{
[[maybe_unused]] void array_test(){
	std::array<int,64> c;

	static_assert(! container::unique_values< decltype(c) >,"" );
	static_assert(! container::is_ordered       < decltype(c) >,"" );

	//UNIMPLEMENTED
	/*
	container::add_front(c,1);
	container::add_back(c,1);
	container::add_anywhere(c,1);
	container::add_here(c,c.begin(),1);
	container::add_here(c,size_t(1) , 1 );

	container::emplace_front(c,1);
	container::emplace_back(c,1);
	container::emplace_anywhere(c,1);
	container::emplace_here(c,c.begin(),1);
	container::emplace_here(c,size_t(1),1);
	*/

	{  [[maybe_unused]] int & g = container::get_front(c);  }
	{  [[maybe_unused]] int & g = container::get_back(c);  }
	{  [[maybe_unused]] int & g = container::get_anywhere(c);  }
	{  [[maybe_unused]] int & g = container::get_here(c, size_t(0)  );  }
	{  [[maybe_unused]] int & g = container::get_here(c, c.begin()  );  }

	{  [[maybe_unused]] const int & g = container::cget_front(c);  }
	{  [[maybe_unused]] const int & g = container::cget_back(c);  }
	{  [[maybe_unused]] const int & g = container::cget_anywhere(c);  }
	{  [[maybe_unused]] const int & g = container::cget_here(c, size_t(0)  );  }
	{  [[maybe_unused]] const int & g = container::cget_here(c, c.cbegin()  );  }

	container::mem_reserve(c,size_t(10));
	container::mem_shrink(c);
	{  [[maybe_unused]] size_t g= container::mem_capacity(c); }


	{  [[maybe_unused]] bool   g= container::count_empty(c); }
	{  [[maybe_unused]] size_t g= container::count_all(c); }
	{  [[maybe_unused]] size_t g= container::count_element(c,1); }

}
}
