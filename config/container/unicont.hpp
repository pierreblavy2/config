//unified interface for writing template code with containers


#ifndef UNICONT_HPP_
#define UNICONT_HPP_


namespace unicont{
    //partial template specialization do not work for functions, therefore:
    //for each unicont function xxx, a class xxx_t with a static run function is created
    //specialize xxx_t for your own types
    //do not touch xxx.



	//add an element at any position in a continer
	template<
		template<typename, typename...>class Cont,
		typename T
	>
	struct add_t;//unimplemented

	template<
		template<typename, typename...>class Cont,
		typename T
	>
	void  add(Cont<T> & target, const T& t){add_t<Cont,T>::run(target,t);}


	//idem, but moves the element instead of adding it
	template<
		template<typename, typename...>class Cont,
		typename T
	>
	struct move_in_t;//unimplemented

	template<
		template<typename, typename...>class Cont,
		typename T
	>
	void  move_in(Cont<T> & target, T&& t){move_in_t<Cont,T>::run(target,std::move(t));}





	//merge two (differents) containers
	template<
		template<typename, typename...>class Cont1,
		typename T1,
		template<typename, typename...>class Cont2,
		typename T2
	>
	struct merge_t{
		static void run(Cont1<T1> & target, const Cont2<T2> &data){
			//less efficient, if possible specialize
			std::copy (data.begin(), data.end(), std::back_inserter(target));
		}
	};
	template<
		typename T1,
		template<typename, typename...>class Cont1,
		typename T2,
		template<typename, typename...>class Cont2
	>
	void merge(Cont1<T1> & target, const Cont2<T2> &data){merge_t<Cont1,T1,Cont2,T2>::run(target,data);}




	//keep only unique elements of a container.
	//reordering container is allowed
	//continer is resized to discard not unique elements
	template<
		template<typename, typename...>class Cont,
		typename T
	>
	struct unique_t; //unimplemented.
	template<
		template<typename, typename...>class Cont,
		typename T
	>
	void unique(Cont<T> & target){unique_t<Cont,T>::run(target);}





	//if possible : reserve memory, else do nothing
	template<
		template<typename, typename...>class Cont,
		typename T
	>
	struct reserve_t;//unimplemented

	template<
		template<typename, typename...>class Cont,
		typename T
	>
	void reserve(Cont<T> & target, size_t i){reserve_t<Cont,T>::run(target,i);}




	//target = elements of a that are not in b
	//a and b MUST BE sorted
	//note that target CAN be a
	template<
		template<typename, typename...>class Cont1,
		typename T1,
		template<typename, typename...>class Cont2,
		typename T2,
		template<typename, typename...>class Cont3,
		typename T3
	>
	struct set_difference_t;

	template<
		template<typename, typename...>class Cont1,
		typename T1,
		template<typename, typename...>class Cont2,
		typename T2,
		template<typename, typename...>class Cont3,
		typename T3
	>
	void set_difference(Cont1<T1> & target, const Cont2<T2> &a, const Cont3<T3> &b){set_difference_t<Cont1,T1,Cont2,T2,Cont3,T3>::run(target,a,b);}


}






#endif /* UNICONT_HPP_ */
