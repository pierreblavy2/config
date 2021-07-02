/*
 * set.hpp
 *
 *  Created on: 11 déc. 2014
 *      Author: pierre
 */

#ifndef UNICONT_SET_HPP_
#define UNICONT_SET_HPP_

#include "unicont.hpp"
#include <set>


namespace unicont{




	template<typename T >
	struct add_t<std::set,T>{
		static void run(std::set<T> & target, const T& t){	target.insert(t);}
	};

	template<typename T >
	struct move_in_t<std::set,T>{
		static void run(std::set<T> & target, T&& t){	target.insert(t);}
	};


	template<typename T >
	struct reserve_t<std::set,T>{
		static void run(std::set<T> & target, size_t i){}
	};



	template<
		typename T1,
		typename T2,
		template<typename, typename...>class Cont2
	>
	struct merge_t<std::set,T1,Cont2,T2>{
		static void run(std::set<T1> & target, const Cont2<T2> &data){
			target.insert(data.begin(),data.end()); //todo test me!
		}
	};




	template<typename T>
	struct unique_t<std::set,T>{
		static void run(std::set<T> & target){}//sets have unique elements
	};



}




#endif /* UNICONT_SET_HPP_ */
