//============================================================================
// Author  : Pierre BLAVY 2018
// Version : 1.0
// License : GPL 3.0 or any later version :
//           https://www.gnu.org/licenses/gpl-3.0-standalone.html
//============================================================================

//This program (config, convert and container) is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>

#include <iostream>

//require to use config::Block
//conversions are handled trough the default implementation that tries to static_cast from std::strings
#include <config/config.hpp>

//extend configuration  conversion rules, by using boost::lexical_cast for numeric types
//NOTE : custom types conversions can be added the same way
#include <config/convert_lexical.hpp>

//extend configuration  conversion rules, by using yes/no or y/n conversion to true/false
//case insensitive
#include <config/convert_bool.hpp>


//extend configuration container support for loading values into a std::vector
//see container folder for a list of supported containers
//see container/container.hpp for the full container interface
#include <container/vector.hpp>



//--- Custom contexts ---
//If for obscure reasons, you don't want to use the Config_tag context to
//do conversions, you can pass your own context.
struct My_context{};
template<>
struct Convert_t<bool,std::string, My_context>{
	static bool run(const std::string s){return s=="OK";}
};




int main(int,char**){

	//-------------------
	//--- load a file ---
	//-------------------
	config::Block b;
	b.load("src/example.txt");

	/*
	#-- summary of doc-web/example.txt  --
	my_house{
	  name = Pierre's house
	  cat  = caterpilar
	  cat  = catastrophy
	  door_size = 2.1     #meters
	  is_nice   = yes
	}
	tree{}
	tree{}
	*/

	//print the example file as seen after parsing.
	// #xx are lines numbers from the input file
	b.save(std::cout);


	//--------------
	//--- blocks ---
	//--------------
	//count blocks;
	size_t number_all_blocks = b.blocks.size();
	size_t number_trees      = b.blocks.size("tree");

	//get block by index:
	const config::Block &first_block = b.blocks.at(0);        //among all blocks
	const config::Block &first_tree =  b.blocks.at("tree",0); //among blocks named tree

	//get a unique sub_block
	const config::Block &my_house = b.blocks.get_unique("my_house");

	//iterate trough all blocks
	for(const config::Block &a_block : b.blocks.crange() ){}

	//iterate trough blocks named "tree"
	for(const config::Block &tree : b.blocks.crange("tree") ){}


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

	//--- custom context ---
	//see custom context sextion just before main for My_context and string to bool conversion definition
	//
	//Value::to, Value_v::get_unique, Value_v::load_unique, Value_v::get_multiple, Value_v::load_multiple
	//template function can accept a context tag, as extra optional template argument.
	//This argument will be use as convert context to decide which Convert_t implementation should be
	//called. This is the correct way to override default conversion rules.
	bool is_ok = my_house.values.get_unique<bool,My_context>  ("is_nice", false);
	     //instead of using yes/no, we use the custom rule : OK=>true, everything else => false






	std::cout << "\n---\n"<<std::endl;



}
