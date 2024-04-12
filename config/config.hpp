//============================================================================
// Author  : Pierre BLAVY 2018
// Version : 1.1
// License : GPL 3.0 or any later version :
//           https://www.gnu.org/licenses/gpl-3.0-standalone.html
//============================================================================

//This program (config) is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>

#ifndef LIB_CONFIG2_CONFIG_HPP_
#define LIB_CONFIG2_CONFIG_HPP_

#include <string>
#include <ostream>
#include <vector>
#include <unordered_map>
#include <memory>

#include <container/vector.hpp> //for convenience only

//#include <convert/convert_bool.hpp>        //for convenience only
//#include <convert/convert_chrono.hpp>      //for convenience only
//#include <convert/convert_lexical.hpp>      //for convenience only



namespace config{

typedef size_t Line_number;

//This tag is used to identify that we're instanciating template in the config context
//see convert/convert.hpp or config/convert_lexical.hpp for an example of tag usage.
struct Config_tag{Config_tag()=delete;};



//name =  value
struct Value{
	std::string name;
	std::string value;
	Line_number line=0;
	explicit Value(const std::string &name_,const std::string &value_):name(name_),value(value_){}

	void save(std::ostream &out, size_t indent=0);
	std::string debug_str()const{return "value line "+std::to_string(line)+", key="+name;}

	//call convert in the Convert_tag context, throw meaningfull errors with context
	template<typename To_t, typename Context_t=Config_tag> To_t to()const;
	template<typename To_t, typename Context_t=Config_tag> void to(To_t & write_here)const;

private:
	template<typename To_t, typename Context_t=Config_tag>
	[[noreturn]] void throw_convert(const std::string &error="")const;



};


//As Block and Value are stored internally in unique_ptr, this iterator dereference one more time
struct Block;
typedef std::unique_ptr<Block> Block_ptr;

struct Value;
typedef std::unique_ptr<Value> Value_ptr;


//--- Iterators and range ---

//Dereference twice instead of once (usefull for iterators on pointers)
template<typename It_t>
struct Derefernce_iterator_t : It_t {
	typedef It_t Base_t;
	explicit Derefernce_iterator_t(const It_t&x):It_t(x){}

	//dereference twice
	decltype(auto) operator* (){return *(Base_t::operator*()) ;}
	decltype(auto) operator->(){return *(Base_t::operator->()) ;}

	//don't convert to base, we inherit for implementation only
	operator Base_t()=delete;
};


template<typename It_t>
struct Range_t{
	Range_t(const It_t b, const It_t e):begin_v(b),end_v(e){}
	It_t begin_v;
	It_t end_v;
	const It_t & begin(){return begin_v;}
	const It_t & end()  {return end_v;}
};






struct Block_v{
	explicit Block_v (Block * enclosing_block_ = nullptr):enclosing_block(enclosing_block_){}
	Block_v(const Block_v&)=delete;
	Block_v& operator =(const Block_v&)=delete;

	Block & create(const std::string &name);
	Block & move(Block_ptr &&b);

	void save(std::ostream &out, size_t indent=0);



	//--- all blocks (by index) ---
	typedef Derefernce_iterator_t < std::vector<Block_ptr>::iterator >       AllBlocks_iterator;
	typedef Derefernce_iterator_t < std::vector<Block_ptr>::const_iterator > AllBlocks_const_iterator;
	typedef Range_t<AllBlocks_iterator>       AllBlocks_range;
	typedef Range_t<AllBlocks_const_iterator> AllBlocks_const_range;

	size_t  size()           const{return blocks.size();}
	Block & at(size_t index)const{return *blocks.at(index);}

	AllBlocks_const_iterator begin ()const{return static_cast<AllBlocks_const_iterator>(blocks.begin());}
	AllBlocks_const_iterator end   ()const{return static_cast<AllBlocks_const_iterator>(blocks.end  ());}
	AllBlocks_const_iterator cbegin()const{return static_cast<AllBlocks_const_iterator>(blocks.cbegin());}
	AllBlocks_const_iterator cend  ()const{return static_cast<AllBlocks_const_iterator>(blocks.cend  ());}
	AllBlocks_const_range    crange()const{return AllBlocks_const_range( cbegin (), cend() ); }
	//AllBlocks_iterator       begin ()     {return static_cast<AllBlocks_iterator>      (blocks.begin());}
	//AllBlocks_iterator       end   ()     {return static_cast<AllBlocks_iterator>      (blocks.end  ());}
	//AllBlocks_range          range ()     {return AllBlocks_range      (  begin (), end() ); }


	//--- named blocks ---
    typedef Derefernce_iterator_t < std::vector<Block*>::iterator >      Block_iterator;
    typedef Derefernce_iterator_t < std::vector<Block*>::const_iterator >Block_const_iterator;
	typedef Range_t<Block_iterator>       Block_range;
	typedef Range_t<Block_const_iterator> Block_const_range;

	size_t size(const std::string &name, bool must_exists=false)  const;

	//return the index-th block named  key. If doesn't exists => throw
	const Block  & at(const std::string &key, size_t index)const;
	      Block  & at(const std::string &key, size_t index);

	      Block & get_unique(const std::string &name);
	const Block & get_unique(const std::string &name)const;

	//iterate trough values at a particular name
	//must_exists=true  : if there is no value named key => throw
	//must_exists=false : if there is no value named key => returns iterators on an empty vector

    Block_const_iterator begin (const std::string &key, bool must_exists=false)const;
    Block_const_iterator end   (const std::string &key, bool must_exists=false)const;
    Block_const_iterator cbegin(const std::string &key, bool must_exists=false)const;
    Block_const_iterator cend  (const std::string &key, bool must_exists=false)const;
    Block_const_range    crange(const std::string &key, bool must_exists=false)const;

    //Block_iterator       begin (const std::string &key);
    //Block_iterator       end   (const std::string &key);
    //Block_range          range (const std::string &key);


	//data
	std::vector<Block_ptr> blocks;
	std::unordered_map <std::string, std::vector<Block*> > name_to_block;
	Block * enclosing_block = nullptr;

	private:
    [[noreturn]] static void throw_missing_block  (const std::string &name, config::Block* context=nullptr);
    [[noreturn]] static void throw_multiple_blocks(const std::string &name, config::Block* context=nullptr);

    static const inline std::vector<Block*> empty_blocks;

};

struct Value_v{
	typedef std::unique_ptr<Value> Value_ptr;


	explicit Value_v (Block * enclosing_block_ = nullptr):enclosing_block(enclosing_block_){}
	Value_v(const Value_v&)=delete;
	Value_v& operator =(const Value_v&)=delete;

	Value & create(const std::string &name, const std::string &value="");
	Value & move(Value_ptr &&b);

	void save(std::ostream &out, size_t indent=0);
	std::string debug_str()const;


	//--- all values ---
    typedef Derefernce_iterator_t < std::vector<Value_ptr>::iterator >       AllValues_iterator;
    typedef Derefernce_iterator_t < std::vector<Value_ptr>::const_iterator > AllValues_const_iterator;
	typedef Range_t<AllValues_iterator>       AllValues_range;
	typedef Range_t<AllValues_const_iterator> AllValues_const_range;


	size_t size()const {return values.size();}
	const Value  & at(size_t index)const{return *values.at(index);}
	      Value  & at(size_t index)     {return *values.at(index);}


	AllValues_const_iterator begin ()const{return static_cast<AllValues_const_iterator>(values.begin());}
	AllValues_const_iterator end   ()const{return static_cast<AllValues_const_iterator>(values.end  ());}
	AllValues_const_iterator cbegin()const{return static_cast<AllValues_const_iterator>(values.cbegin());}
	AllValues_const_iterator cend  ()const{return static_cast<AllValues_const_iterator>(values.cend  ());}
	AllValues_const_range    crange()const{return AllValues_const_range( cbegin (), cend() ); }

	//AllValues_iterator       begin ()     {return static_cast<AllValues_iterator>      (values.begin());}
	//AllValues_iterator       end   ()     {return static_cast<AllValues_iterator>      (values.end  ());}
	//AllValues_range          range ()     {return AllValues_range      (  begin (), end() ); }

	//--- named values ---
	//if must_exist == true  => throw if the key is missing
	//if must_exist == false => return iterators on a dummy empty vector if the key doesn't exists.

	typedef Derefernce_iterator_t < std::vector<Value*>::iterator >      Value_iterator;
    typedef Derefernce_iterator_t < std::vector<Value*>::const_iterator >Value_const_iterator;
	typedef Range_t<Value_iterator>       Value_range;
	typedef Range_t<Value_const_iterator> Value_const_range;

	size_t size(const std::string &key, bool must_exists=false)  const;
	const Value  & at(const std::string &key, size_t index)const;
          Value  & at(const std::string &key, size_t index);

    Value_const_iterator begin (const std::string &key, bool must_exists=false)const;
    Value_const_iterator end   (const std::string &key, bool must_exists=false)const;
    Value_const_iterator cbegin(const std::string &key, bool must_exists=false)const;
    Value_const_iterator cend  (const std::string &key, bool must_exists=false)const;
    Value_const_range    crange(const std::string &key, bool must_exists=false)const;

    //Value_iterator       begin (const std::string &key);
    //Value_iterator       end   (const std::string &key);
    //Value_range          range (const std::string &key);


	//load_unique : write the requested value in write_here
	//throw if multiple values
	//throw if no default_v and no value
	//the template version loads and converts to T
	void load_unique(std::string &write_here, const std::string &name) const;
	void load_unique(std::string &write_here, const std::string &name, const std::string & default_v)const;
	template<typename Context_t = Config_tag, typename T> void load_unique(T&write_here, const std::string &name) const;
	template<typename Context_t = Config_tag, typename T> void load_unique(T&write_here, const std::string &name, const T& default_v)const;


	//load_multiple : APPEND the requested values in write_here
	//return the number of loaded values.
	//    note that is the same value is added n times to a
	//    container of uniques (like set), it counts as n for calculating the
	//    return value.
	//values are converted to Container_t::value_type before insertion
	//    conversion context is Convert_tag
	//    for details see convert/convert.hpp
	//write_here can be any container supported by cont (see container/container.hpp)
	//    if possible values are added in order    (cont::add_back)
	//    if not possible, they are added anywhere (cont::add_anywhere).
	template<typename Context_t = Config_tag, typename Container_t> size_t       load_multiple(Container_t& write_here, const std::string &name)const;
	template<typename Container_t , typename Context_t = Config_tag> Container_t  get_multiple( const std::string &name)const;


	//Get a value,
	//throw if multiple
	//throw if no default, and missing
	const std::string    & get_unique(const std::string &name)const;
	template<typename T, typename Context_t = Config_tag> T get_unique(const std::string &name)const{T t; this->template load_unique<Context_t>(t,name); return t;}

	const std::string    & get_unique(const std::string &name, const std::string &default_v)const;
	template<typename T, typename Context_t = Config_tag> T get_unique(const std::string &name, const T &default_v)const;


	//Get yes_no
	//throw if missing
	bool get_yes_no(const std::string &name        )const;
	bool get_yes_no(const std::string &name, bool b)const;


	//TODO Get an optional unique value
	//throw if not unique
	//return an emprty optional if doesn't exists




	//--- data ---
	Line_number line=0;
	std::vector<Value_ptr> values;
	std::unordered_map <std::string, std::vector<Value*> > name_to_value;
	Block * enclosing_block = nullptr;


private:
	[[noreturn]] static void throw_missing_value  (const std::string &name, config::Block* context=nullptr);
	[[noreturn]] static void throw_multiple_values(const std::string &name, config::Block* context=nullptr);

	//used to generate iterators on nothing
	static const inline std::vector<Value*> empty_values;


};









//name{...}
struct Block{
	explicit Block(const std::string &name_=""):name(name_){}
	Block(const Block&)=delete;
	Block& operator =(const Block&)=delete;


	std::string name;
	Line_number begin_line=0;
	Line_number end_line  =0;

	Block_v     blocks{this};
	Value_v     values{this};

	void load(const std::string  & file_path);
	void load(std::istream & in, const std::string& path_info="");
	void save(std::ostream &out, size_t indent=0);

	std::string debug_str()const{
		std::string r="block ";
		if(name!=""){r+=name+" ";}
		r+="from:"+std::to_string(begin_line)+" ";
		r+="to:"+std::to_string(end_line);
		return r;
	}


	private:
	[[noreturn]] static void throw_file_open(const std::string &path_info);
	[[noreturn]] static void throw_file_read(const std::string &path_info="");

	[[noreturn]] static void  throw_parse_out_of_block           (Line_number line, const std::string &path_info="");
	[[noreturn]] static void  throw_parse_unexpected_end_of_block(Line_number line, const std::string &path_info="");
	[[noreturn]] static void  throw_parse_missing_end_of_block   (Line_number start_line, const std::string &path_info="");
	[[noreturn]] static void  throw_parse_unexpected_line        (Line_number line, const std::string &line_str, const std::string &path_info="");

};


typedef Block Config;


}






#include "../config/config.tpp"

#endif /* LIB_CONFIG2_CONFIG_HPP_ */
