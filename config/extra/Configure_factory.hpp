#ifndef LIB_CONFIG_CONFIGURE_FACTORY_HPP_
#define LIB_CONFIG_CONFIGURE_FACTORY_HPP_


//Generic class that allow to easily build configure factories
// The factory call the ::configure static member function of all members in Congigure_me
// And returns the first not null created object (chain of responsability)


// USAGE : CREATE OBJECTS
//
// -- step 1 : create Configure_me Objects --
// All Configure_me class must derive from What_t
// All Configure_me class must have a static member function
//    static std::unique_ptr<What_t> configure(const Configure_from_t& conf);
//    note : std::unique_ptr<What_t> can be replaced by std::unique_ptr<something_that_derive_from_What_t>
// This function must either return a pointer (config is valid, this object is constructed) or nullptr
//
// struct Test_abstract{virtual ~Test(){} };
// struct T1:Test_abstract{
//    static std::unique_ptr<T1>configure(const std::string& conf);
//    static std::unique_ptr<T1>configure(const bconfig::BConfig& conf);
// };
// struct T2 { //you don't need to inherit anything
//  static std::unique_ptr<Test_abstract> configure(const std::string& conf);
//  static std::unique_ptr<Test_abstract> configure(const bconfig::BConfig& conf);
// };
//
// -- step 2 : create a factory --
// To do so use : Configure_factory<Configure_from_t ,Test_abstract, Configure_me...>;
//
// typedef Configure_factory<std::string      ,Test_abstract, T1,T2> Fact_str;
// typedef Configure_factory<bconfig::BConfig ,Test_abstract, T1,T2> Fact_conf;
//
// -- step 3 : mix factories (optional) --
// The factories of step 2 are usable as is, but if you need to mix them :
//
// struct Fact_t : Fact_str,Fact_conf{ using Fact_str::configure; using Fact_conf::configure;};
//
// -- step 4 : use factories --
// Use : std::unique_ptr<What_t> p = Fact_t::configure(const Configure_from_t&);
// don't forget to test (p==nullptr), because construction may fail
//
// std::unique_ptr<Test_abstract> p Fact_t::configure(some_string);
// if(p==nullptr){throw something;}


// USAGE : CONFIGURE ONLY
//This version is a simple template chain of responsability, that do not create objects.
//It's simply call configure, until one configure function returns true.
//
// -- step 1 : create Configure_me Objects --
// struct T1{  static bool configure(const std::string& conf); };
// struct T2{  static bool configure(const std::string& conf); };
//
// -- step 2 : create a factory --
// typedef Configure_only<std::string, T1,T2> Fact_str;
//
// -- step 3 : mix factories (optional) --
//  idem see step 3 in CREATE OBJECTS
//
// -- step 4 : use factories --
// bool ok = Fact_str::configure(some_string);



#include <memory>

//--- Configure_factory ---
namespace Configure_factory_impl{
	template<typename Configure_from_t, typename What_t ,typename ... Configure_me>
	struct Configure_factory_r;

	template<typename Configure_from_t, typename What_t ,typename T, typename ... Configure_me>
	struct Configure_factory_r<Configure_from_t,What_t,T,Configure_me...>{
		static std::unique_ptr<What_t> configure(const Configure_from_t& conf){
			auto r = T::configure(conf); //Error here : configure is missing in one of the Configure_me class
			if(r!=nullptr){return r;}
			else          {return Configure_factory_r<Configure_from_t,What_t,Configure_me...>::configure(conf);}
		}
	};

	template<typename Configure_from_t, typename What_t>
	struct Configure_factory_r<Configure_from_t,What_t>{
		static std::unique_ptr<What_t> configure(const Configure_from_t& conf){
			return nullptr;
		}
	};
}

template<typename Configure_from_t, typename What_t ,typename ... Configure_me>
struct Configure_factory{
	static std::unique_ptr<What_t> configure(const Configure_from_t& conf){
		return Configure_factory_impl::Configure_factory_r<Configure_from_t,What_t,Configure_me...>::configure(conf);
	}
};



//--- Configure_factory ---
namespace Configure_only_impl{
	template<typename Configure_from_t ,typename ... Configure_me>
	struct Configure_only_r;

	template<typename Configure_from_t, typename T, typename ... Configure_me>
	struct Configure_only_r<Configure_from_t,T,Configure_me...>{
		static bool configure(const Configure_from_t& conf){
			bool r = T::configure(conf); //Error here : configure is missing in one of the Configure_me class
			if(r==true){return true;}
			else       {return Configure_only_r<Configure_from_t,Configure_me...>::configure(conf);}
		}
	};

	template<typename Configure_from_t>
	struct Configure_only_r<Configure_from_t>{
		static bool configure(const Configure_from_t& conf){
			return false;
		}
	};
}

template<typename Configure_from_t, typename ... Configure_me>
struct Configure_only{
	static bool configure(const Configure_from_t& conf){
		return Configure_only_impl::Configure_only_r<Configure_from_t,Configure_me...>::configure(conf);
	}
};




//--- EXAMPLE ---

/*
struct Test_abstract{
	virtual ~Test_abstract(){}
	protected:
	Test_abstract()=default;
};
typedef std::unique_ptr<Test_abstract> Test_ptr;


#include <iostream>
struct Test_configurable1 :  Test_abstract{

	static Test_ptr configure(const std::string &s){
		std::cout << "configure1 from string";
		return Test_ptr(nullptr);
	}

	static Test_ptr configure(const bconfig::BConfig &s){
		std::cout << "configure1 from bconfig";
		return Test_ptr(nullptr);
	}
};

struct Test_configurable2 :  Test_abstract{

	static std::unique_ptr<Test_configurable2> configure(const std::string &s){
		std::cout << "configure2 from string";
		return std::make_unique<Test_configurable2>();
	}

	static std::unique_ptr<Test_configurable2> configure(const bconfig::BConfig &s){
		std::cout << "configure2 from bconfig";
		return std::make_unique<Test_configurable2>();
	}
};


int main(int,char**){
	typedef Configure_factory<std::string     ,Test_abstract, Test_configurable1,Test_configurable2> Fact_str;
	typedef Configure_factory<bconfig::BConfig,Test_abstract, Test_configurable1,Test_configurable2> Fact_bconf;
	struct Fact_t : Fact_str,Fact_bconf{ using Fact_str::configure; using Fact_bconf::configure;};

	Test_ptr a = Fact_t::configure("AAA");
}
*/







#endif /* LIB_CONFIG_CONFIGURE_FACTORY_HPP_ */
