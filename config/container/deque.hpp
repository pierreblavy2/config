/*
 * vector.hpp
 *
 *  Created on: 11 déc. 2014
 *      Author: pierre
 */

#ifndef UNICONT_DEQUE_HPP_
#define UNICONT_DEQUE_HPP_

#include "container.hpp"

#include <deque>
#include <algorithm>

namespace unicont{




	template<typename T >
	struct add_t<std::deque,T>{
		static void run(std::deque<T> & target, const T& t){	target.push_back(t);}
	};

	template<typename T >
	struct move_in_t<std::deque,T>{
		static void run(std::deque<T> & target, T&& t){	target.emplace_back(t);}
	};



	template<typename T >
	struct reserve_t<std::deque,T>{
		static void run(std::deque<T> & target, size_t i){}
	};


	template<
		typename T1,
		typename T2,
		template<typename, typename...>class Cont2
	>
	struct merge_t<std::deque,T1,Cont2,T2>{
		static void run(std::deque<T1> & target, const Cont2<T2> &data){
			//target.insert(target.end, data.begin(),data.end());
			std::copy(data.begin(), data.end(), std::back_inserter(target));
		}
	};




	template<typename T>
	struct unique_t<std::deque,T>{
		static void run(std::deque<T> & target){
			std::sort(target.begin(),target.end());
			auto it = std::unique(target.begin(),target.end());
			target.resize( std::distance(target.begin(),it));
		}
	};


	template<
			typename T1,
			template<typename, typename...>class Cont2,
			typename T2,
			template<typename, typename...>class Cont3,
			typename T3

	>
	struct set_difference_t<std::deque,T1,Cont2,T2,Cont3,T3>{
		static void run(std::deque<T1> & target, const Cont2<T2> &a, const Cont3<T3> &b){
			target.resize((a.size()));
			auto it=std::set_difference (
					a.begin(), a.end(),
					b.begin(), b.end(),
					target.begin());
			target.resize(it-target.begin());
		}
	};



}



#endif /* UNICONT_DEQUE_HPP_ */
