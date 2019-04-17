# Features
* Parse simple hierarchical config files, see example.cpp and example.txt
* Can be extended to custom types, see example-extend-convert.hpp
* Can be extended to custom containers, see example-extend-container.hpp

# How to install
* Download the source code
* Extract src/lib/* to your library folder
* #include <config/config.hpp> to read config
* #include <config/convert_lexical.hpp> to add string to number conversions to config (require boost/lexical_cast)
* #include <container/xxx.hpp> to add support for the xxx container. xxx=array, deque, set, unordered_set, vector

# License
* Copyright : Pierre Blavy
* License : [GPL 3.0](https://www.gnu.org/licenses/lgpl-3.0.txt) or any later version
 
# Developpement versions 
The developpement version can be downloaded on
https://tentacule.be/fossil/cpp-config

# Example
```
#example.txt
#I'm a comment

my_house{
  name = pierre's house
  cat  = caterpilar
  cat  = catastrophy
  door_size = 2.1     #meters
  is_nice = yes
}

forest{
  tree{
    name = oak
    branch = a_branch
    branch = an_other_branch
  }
  tree{
    name = ash
    branch = a_branch
  }  
}
```


```cpp
#include <config/config.hpp>
#include <config/convert_lexical.hpp>//extend configuration  conversion rules, by using boost::lexical_cast for numeric types. NOTE : custom types conversions can be added the same way
#include <config/convert_bool.hpp> //extend configuration  conversion rules, by using yes/no or y/n conversion to true/false ; case insensitive.
#include <container/vector.hpp> //extend configuration container support for loading values into a std::vector, see container folder for a list of supported containers. see container/container.hpp for the full container interface

#include <iostream>

int main(int,char**){

	//-------------------
	//--- load a file ---
	//-------------------
	config::Block b;
	b.load("src/example.txt");

	//print the example file as seen after parsing. #xx are lines numbers from the input file
	b.save(std::cout);


	//--------------
	//--- blocks ---
	//--------------
	//count blocks;
	size_t number_all_blocks = b.blocks.size();
	size_t number_trees      = b.blocks.get_unique("forest").blocks.size("tree");

	//get block by index:
	const config::Block &first_block = b.blocks.at(0);        //among all blocks
	const config::Block &first_tree =  b.blocks.at("tree",0); //among blocks named tree

	//get a unique sub_block
	const config::Block &my_house = b.blocks.get_unique("my_house");

	//iterate trough all blocks
	for(const config::Block &a_block : b.blocks.crange() ){}

	//iterate trough blocks named "tree" in "forest"
	for(const config::Block &tree : b.blocks.get_unique("forest").blocks.crange("tree") ){}


	//--------------
	//--- values ---
	//--------------

	//--- count values ---
	size_t number_of_cats =  my_house.values.size("cat");

	//--- get values by index --
	const config::Value &first_value = my_house.values.at(0);        //among all values in my_house
	const config::Value &first_cat  =  my_house.values.at("cat",0); //among all values named cat in my_house

	//--- iterate trough values ---
	for(const config::Value &a_value :my_house.values.crange() ){}

	//--- convert a value ---
	const config::Value door_size_v = my_house.values.at("door_size", 0);
	double door_size_d = door_size_v.to<double>(); //see convert/convert.hpp

	//--- get values ---
	//[1] The not template version works on std::string
	//[2] The template version works on any type supported by convert
	//    here it's double supported by convert_lexical.hpp
	//[3] idem, but require #include <config/convert_bool.hpp>
	//    y and yes => true. n and no => false.
	//
	//get_unique returns a value
	//load_unique(write_here,...) write the returned value in write_here
	std::string house_name;
	double door_size;

	//get a unique value, throw if doesn't exists.
	house_name = my_house.values.get_unique("name");             //[1]
	door_size  = my_house.values.get_unique<double>("door_size");//[2]
	bool is_nice=my_house.values.get_unique<bool>("is_nice");    //[3]

	my_house.values.load_unique(house_name, "name");     //[1]
	my_house.values.load_unique(door_size , "door_size");//[2]
	my_house.values.load_unique(is_nice   , "is_nice");  //[3]


	//get a unique value, use default if doesn't exists
	house_name = my_house.values.get_unique        ("name"      ,"Someone house");//[1]
	door_size  = my_house.values.get_unique<double>("door_size" ,2.0);            //[2]
	is_nice    = my_house.values.get_unique<bool>  ("is_nice", true);             //[3]

	my_house.values.load_unique(house_name, "name"     , "Someone house");//[1]
	my_house.values.load_unique(door_size , "door_size", 2.0);            //[2]
	my_house.values.load_unique(is_nice   , "is_nice"  , true);           //[3]


	//add multiple values into a container.
	// - containers are handled trough the container/container.hpp interface
	//   see example-extend-container.hpp for details
    // - if possible (ex: vector), values are loaded in the same order as the
	//   input file. see container::Add_back_t in container/container.hpp
	// - if not (ex: set), values are loaded in any order.
	//   see container::Add_anywhere_t in container/container.hpp .
	// - loaded values are automatically converted to the container value type
	//   (see container::Value_type_t and convert/convert.hpp).
    // - load_multiple returns the number of loaded values, which is the number
	//   of lines in the current block that has a value for the required name.
	//   If the container does deduplication (ex set) the return of load_multiple
	//   can be higher than the increase in container size.
	// - load_multiple ADD values to the container without cleaning it first.

	std::vector<std::string> cats_v = my_house.values.get_multiple< std::vector<std::string> >("cat");
	my_house.values.load_multiple(cats_v, "cat");
}

```

## Extend convert to support custom conversions
Custom values are handled troug the generic convert template interface. User can extend this class by specializing 
```cpp
#include <convert/convert.hpp>
template<>
struct convert::Convert_t<To_t, From_t , Context_t>{
	static To_t run(const From_t s){return ??? s converted to To_t ???;}
};
```
- To_t is then type you wants to convert to
- From_t is the type you wants to convert from. For config, it's always `std::string`
- Context_t is a dummy type, that allows to disanbigush the convert contexts. For config it's `config::Config_tag`. If for some reason you want to specify the convert context the `config::Value.to()`, `config::Values::load_unique(...)`, `config::Values::load_multiple(...)` and `config::Values::get_multiple(...)` functions take an optional context as a second template argument.


## Extend cont to support custom containers
Config uses the container library to interface with container. To support a custom container, you need to define the way data is added to your container. To do so specialize either `cont::Add_back_t` (prefered) or `cont::Add_anywhere_t` (if you cannot do otherwise) for your container. For an example, have a look at `container/vector.hpp`.



