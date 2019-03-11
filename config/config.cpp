//============================================================================
// Author  : Pierre BLAVY 2018
// Version : 1.0
// License : GPL 3.0 or any later version :
//           https://www.gnu.org/licenses/gpl-3.0-standalone.html
//============================================================================

//This program (config) is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>


#include "config.hpp"
#include "convert_bool.hpp"

#include <cassert>
#include <string>
#include <fstream>
#include <regex>
#include <string>

namespace{

	[[noreturn]] void throw_xxx(const std::string &key, config::Block* context, const std::string base_msg){
		if(context==nullptr){
			throw std::runtime_error(base_msg+", key="+key);
		}else{
			throw std::runtime_error(
					base_msg+", key="+key
					+", block_lines "
					+    std::to_string(context->begin_line)
					+":"+std::to_string(context->end_line));
		}
	}
}

namespace config{

void Value_v::throw_missing_value  (const std::string &key, config::Block* context){throw_xxx(key,context,"Missing value");}
void Value_v::throw_multiple_values(const std::string &key, config::Block* context){throw_xxx(key,context,"Multiple values");}
void Block_v::throw_missing_block  (const std::string &key, config::Block* context){throw_xxx(key,context,"Missing block");}
void Block_v::throw_multiple_blocks(const std::string &key, config::Block* context){throw_xxx(key,context,"Multiple blocks");}


namespace{
std::string indent_str(size_t level){
	std::string r;
	for(size_t i=0;i<level; ++i){r+="  ";}
	return r;
}
}


//--- Value ---
void Value::save(std::ostream &out, size_t indent){
	std::string iii = indent_str(indent);
	out << iii << name <<" = "<<value;
	if(line !=0){out << " #"<<line;}
	out << "\n";
}

const std::string &  Value_v::get_unique(const std::string &key)const{
	auto f = name_to_value.find(key);
	if   (f==name_to_value.end()){throw_missing_value  (key,enclosing_block);}
	if   (f->second.size()==0)   {throw_missing_value  (key,enclosing_block);}
	if   (f->second.size()> 1)   {throw_multiple_values(key,enclosing_block);}
	return f->second[0]->value;
}

const std::string  & Value_v::get_unique(const std::string &key, const std::string &default_v)const{
	auto f = name_to_value.find(key);
	if   (f==name_to_value.end()){return default_v;}
	if   (f->second.size()==0)   {return default_v;}
	if   (f->second.size()> 1)   {throw_multiple_values(key,enclosing_block);}
	return f->second[0]->value;
}




//--- Value_v ---
Value & Value_v::create(const std::string &key, const std::string &value){
	Value_ptr v = std::make_unique<Value>(key,value);
	Value *r = v.get();
	name_to_value[key].emplace_back(r);
	values.emplace_back(std::move(v));
	return *r;
}

Value & Value_v::move(Value_ptr &&b){
	assert(b!=nullptr);
	auto r = b.get();
	name_to_value[b->name].emplace_back(r);
	values.emplace_back(std::move(b));
	return *r;
}

size_t Value_v::size(const std::string &key, bool must_exists)  const{
	auto f = name_to_value.find(key);
	if(must_exists){
		if(f==name_to_value.end()){throw_missing_value(key,enclosing_block);}
	}else{
		if(f==name_to_value.end()){return 0;}
	}
	return f->second.size();
}

const Value  & Value_v::at(const std::string &key, size_t index)const{
	auto f = name_to_value.find(key);
	if(f==name_to_value.end()){throw_missing_value(key,enclosing_block);}
	return *(f->second.at(index));
}

Value  & Value_v::at(const std::string &key, size_t index)     {
  auto f = name_to_value.find(key);
  if(f==name_to_value.end()){throw_missing_value(key,enclosing_block);}
  return *(f->second.at(index));
}



auto Value_v::begin (const std::string &key, bool must_exists)const->Value_const_iterator{
	auto f = name_to_value.find(key);
	if(must_exists){
		if   (f==name_to_value.end()){throw_missing_value(key,enclosing_block);}
		if   (f->second.size()==0)   {throw_missing_value(key,enclosing_block);}
	}else{
		if   (f==name_to_value.end()){return static_cast<Value_const_iterator> (Value_v::empty_values.begin()) ;}
	}
	return static_cast<Value_const_iterator> (f->second.begin());
}

auto Value_v::end (const std::string &key, bool must_exists)const->Value_const_iterator{
	auto f = name_to_value.find(key);
	if(must_exists){
		if   (f==name_to_value.end()){throw_missing_value(key,enclosing_block);}
		if   (f->second.size()==0)   {throw_missing_value(key,enclosing_block);}
	}else{
		if   (f==name_to_value.end()){return static_cast<Value_const_iterator> (Value_v::empty_values.end()) ;}
	}
	return static_cast<Value_const_iterator> (f->second.end());
}

auto Value_v::cbegin (const std::string &key, bool must_exists)const->Value_const_iterator{
	auto f = name_to_value.find(key);
	if(must_exists){
		if   (f==name_to_value.end()){throw_missing_value(key,enclosing_block);}
		if   (f->second.size()==0)   {throw_missing_value(key,enclosing_block);}
	}else{
		if   (f==name_to_value.end()){return static_cast<Value_const_iterator> (Value_v::empty_values.cbegin()) ;}
	}
	return static_cast<Value_const_iterator> (f->second.cbegin());
}

auto Value_v::cend (const std::string &key, bool must_exists)const->Value_const_iterator{
	auto f = name_to_value.find(key);

	if(must_exists){
		if   (f==name_to_value.end()){throw_missing_value(key,enclosing_block);}
		if   (f->second.size()==0)   {throw_missing_value(key,enclosing_block);}
	}else{
		if   (f==name_to_value.end()){return static_cast<Value_const_iterator> (Value_v::empty_values.cend()) ;}
	}
	return static_cast<Value_const_iterator> (f->second.cend());
}

auto Value_v::crange(const std::string &key, bool must_exists)const->Value_const_range{
	auto f = name_to_value.find(key);
	if(must_exists){
		if   (f==name_to_value.end()){throw_missing_value(key,enclosing_block);}
		if   (f->second.size()==0)   {throw_missing_value(key,enclosing_block);}
	}else{
		if   (f==name_to_value.end()){
			auto b =  static_cast<Value_const_iterator> (Value_v::empty_values.cbegin());
			auto e =  static_cast<Value_const_iterator> (Value_v::empty_values.cend());
			return Value_const_range(b,e);
		}
	}
	auto b =  static_cast<Value_const_iterator> (f->second.cbegin());
	auto e =  static_cast<Value_const_iterator> (f->second.cend());
	return Value_const_range(b,e);
}

/*
auto Value_v::begin (const std::string &key)->Value_iterator{
	auto f = name_to_value.find(key);
	if   (f==name_to_value.end()){throw_missing_value(key,enclosing_block);}
	if   (f->second.size()==0)   {throw_missing_value(key,enclosing_block);}
	return static_cast<Value_iterator> (f->second.begin());
}

auto Value_v::end (const std::string &key)->Value_iterator{
	auto f = name_to_value.find(key);
	if   (f==name_to_value.end()){throw_missing_value(key,enclosing_block);}
	if   (f->second.size()==0)   {throw_missing_value(key,enclosing_block);}
	return static_cast<Value_iterator> (f->second.end());
}

auto Value_v::range (const std::string &key)->Value_range{
	auto f = name_to_value.find(key);
	if   (f==name_to_value.end()){throw_missing_value(key,enclosing_block);}
	if   (f->second.size()==0)   {throw_missing_value(key,enclosing_block);}
	auto b =  static_cast<Value_iterator> (f->second.begin());
	auto e =  static_cast<Value_iterator> (f->second.end());
	return Value_range(b,e);
}
*/



void Value_v::load_unique(std::string &write_here, const std::string &key)const{
	auto f = name_to_value.find(key);
	if   (f==name_to_value.end()){throw_missing_value(key,enclosing_block);}
	if   (f->second.size()==0)   {throw_missing_value(key,enclosing_block);}
	if   (f->second.size()> 1)   {throw_multiple_values(key,enclosing_block);}
	write_here = (f->second[0])->value;
}

void Value_v::load_unique(std::string &write_here, const std::string &key, const std::string &default_v)const{
	auto f = name_to_value.find(key);
	if   (f==name_to_value.end()){write_here =  default_v; return;}
	if   (f->second.size()==0)   {write_here =  default_v; return;}
	if   (f->second.size()> 1)   {throw_multiple_values(key,enclosing_block);}
	write_here = (f->second[0])->value;
}


void Value_v::save(std::ostream &out, size_t indent){
	for(const auto &v : values){
		v->save(out,indent);
	}
}

bool Value_v::get_yes_no(const std::string &key        )const{
	bool t;
	load_unique(t,key);
	return t;
}

bool Value_v::get_yes_no(const std::string &key, bool b)const{
	bool t;
	load_unique(t,key,b);
	return t;
}



std::string Value_v::debug_str()const{
	std::string r="value ";
	r+="at:"+std::to_string(line);
	return r;
}




//--- Block ---



//--- Block_v ---
void Block_v::save(std::ostream &out, size_t indent){
	for(const auto &b : blocks){
		b->save(out,indent);
	}
}

size_t Block_v::size(const std::string &key, bool must_exists)  const{
	auto f = name_to_block.find(key);
	if(must_exists){
		if(f==name_to_block.end()){throw_missing_block(key,enclosing_block);}
	}else{
		if(f==name_to_block.end()){return 0;}
	}
	return f->second.size();
}

const Block  & Block_v::at(const std::string &key, size_t index)const{
	auto f = name_to_block.find(key);
	if(f==name_to_block.end()){throw_missing_block(key,enclosing_block);}
	return *(f->second.at(index));
}

Block  & Block_v::at(const std::string &key, size_t index)     {
	auto f = name_to_block.find(key);
	if(f==name_to_block.end()){throw_missing_block(key,enclosing_block);}
	return *(f->second.at(index));
}





auto Block_v::begin (const std::string &key, bool must_exist)const->Block_const_iterator{
	auto f = name_to_block.find(key);
	if(must_exist){
		if   (f==name_to_block.end()){throw_missing_block(key,enclosing_block);}
		if   (f->second.size()==0)   {throw_missing_block(key,enclosing_block);}
	}else{
		if   (f==name_to_block.end()){return static_cast<Block_const_iterator> (Block_v::empty_blocks.begin()) ;}

	}
	return static_cast<Block_const_iterator> (f->second.begin());
}


auto Block_v::end (const std::string &key, bool must_exist)const->Block_const_iterator{
	auto f = name_to_block.find(key);
	if(must_exist){
		if   (f==name_to_block.end()){throw_missing_block(key,enclosing_block);}
		if   (f->second.size()==0)   {throw_missing_block(key,enclosing_block);}
	}else{
		if   (f==name_to_block.end()){return static_cast<Block_const_iterator> (Block_v::empty_blocks.end()) ;}
	}
	return static_cast<Block_const_iterator> (f->second.end());
}


auto Block_v::cbegin (const std::string &key, bool must_exist)const->Block_const_iterator{
	auto f = name_to_block.find(key);
	if(must_exist){
		if   (f==name_to_block.end()){throw_missing_block(key,enclosing_block);}
		if   (f->second.size()==0)   {throw_missing_block(key,enclosing_block);}
	}else{
		if   (f==name_to_block.end()){return static_cast<Block_const_iterator> (Block_v::empty_blocks.cbegin()) ;}
	}
	return static_cast<Block_const_iterator> (f->second.cbegin());
}


auto Block_v::cend (const std::string &key, bool must_exist)const->Block_const_iterator{
	auto f = name_to_block.find(key);
	if(must_exist){
		if   (f==name_to_block.end()){throw_missing_block(key,enclosing_block);}
		if   (f->second.size()==0)   {throw_missing_block(key,enclosing_block);}
	}else{
		if   (f==name_to_block.end()){return static_cast<Block_const_iterator> (Block_v::empty_blocks.cend()) ;}
	}
	return static_cast<Block_const_iterator> (f->second.cend());
}


auto Block_v::crange (const std::string &key, bool must_exist)const->Block_const_range{
	auto f = name_to_block.find(key);
	if(must_exist){
		if   (f==name_to_block.end()){throw_missing_block(key,enclosing_block);}
		if   (f->second.size()==0)   {throw_missing_block(key,enclosing_block);}
	}else{
		if   (f==name_to_block.end()){
			auto b = static_cast<Block_const_iterator> (Block_v::empty_blocks.cbegin());
			auto e = static_cast<Block_const_iterator> (Block_v::empty_blocks.cend());
			return Block_const_range(b,e);
		}
	}

	auto b = static_cast<Block_const_iterator> (f->second.cbegin());
	auto e = static_cast<Block_const_iterator> (f->second.cend());
	return Block_const_range(b,e);
}


/*
auto Block_v::begin (const std::string &key)->Block_iterator{
	auto f = name_to_block.find(key);
	if   (f==name_to_block.end()){throw_missing_block(key,enclosing_block);}
	if   (f->second.size()==0)   {throw_missing_block(key,enclosing_block);}
	return static_cast<Block_iterator> (f->second.begin());
}

auto Block_v::end (const std::string &key)->Block_iterator{
	auto f = name_to_block.find(key);
	if   (f==name_to_block.end()){throw_missing_block(key,enclosing_block);}
	if   (f->second.size()==0)   {throw_missing_block(key,enclosing_block);}
	return static_cast<Block_iterator> (f->second.end());
}


auto Block_v::range (const std::string &key)->Block_range{
	auto f = name_to_block.find(key);
	if   (f==name_to_block.end()){throw_missing_block(key,enclosing_block);}
	if   (f->second.size()==0)   {throw_missing_block(key,enclosing_block);}
	auto b = static_cast<Block_iterator> (f->second.begin());
	auto e = static_cast<Block_iterator> (f->second.end());
	return Block_range(b,e);
}*/



Block & Block_v::create(const std::string &key){
	Block_ptr v = std::make_unique<Block>(key);
	Block *r = v.get();
	name_to_block[key].emplace_back(r);
	blocks.emplace_back(std::move(v));
	return *r;

}

Block & Block_v::move(Block_ptr &&b){
	assert(b!=nullptr);
	auto r = b.get();
	name_to_block[b->name].emplace_back(r);
	blocks.emplace_back(std::move(b));
	return *r;
}



Block & Block_v::get_unique(const std::string &key){
	auto f = name_to_block.find(key);
	if   (f==name_to_block.end()){throw_missing_block  (key,enclosing_block);}
	if   (f->second.size()==0)   {throw_missing_block  (key,enclosing_block);}
	if   (f->second.size()> 1)   {throw_multiple_blocks(key,enclosing_block);}
	return *(f->second[0]);
}

const Block & Block_v::get_unique(const std::string &key)const{
	auto f = name_to_block.find(key);
	if   (f==name_to_block.end()){throw_missing_block  (key,enclosing_block);}
	if   (f->second.size()==0)   {throw_missing_block  (key,enclosing_block);}
	if   (f->second.size()> 1)   {throw_multiple_blocks(key,enclosing_block);}
	return *(f->second[0]);
}





//--- Block (load) ---
void Block::throw_file_open(const std::string &path_info){
	throw std::runtime_error("config::Block cannot open file, file_path="+path_info);
}

void Block::throw_file_read(const std::string &path_info){
	if(path_info!=""){throw std::runtime_error("config::Block error while reading file, file_path="+path_info); }
	else             {throw std::runtime_error("config::Block error while reading file"); }
}

void  Block::throw_parse_out_of_block(Line_number line, const std::string &path_info){
	std::string err = "config::Block parse error, we're supposed to be in a block";
	if(line!=0){err += ", line="+std::to_string(line);}
	if(path_info!=""){err+=", file_path="+path_info; }
	throw std::runtime_error(err);
}

void  Block::throw_parse_unexpected_end_of_block(Line_number line, const std::string &path_info){
	std::string err = "config::Block parse error, unexpected end of block";
	if(line!=0){err += ", line="+std::to_string(line);}
	if(path_info!=""){err+=", file_path="+path_info; }
	throw std::runtime_error(err);
}

void  Block::throw_parse_missing_end_of_block(Line_number start_line, const std::string &path_info){
	std::string err = "config::Block parse error, missing end of block";
	if(start_line!=0){err += ", block_begin_line="+std::to_string(start_line);}
	if(path_info!=""){err+=", file_path="+path_info; }
	throw std::runtime_error(err);
}

void  Block::throw_parse_unexpected_line (Line_number line, const std::string &line_str, const std::string &path_info){
	std::string err = "config::Block parse error, wrong line, line_string='"+line_str+"'";
	if(line!=0){err += ", line="+std::to_string(line);}
	if(path_info!=""){err+=", file_path="+path_info; }
	throw std::runtime_error(err);
}



void Block::load(const std::string  & file_path){
	std::ifstream in(file_path.c_str());
	if(!in){throw_file_open(file_path);}
	load(in,file_path);
}





#include <algorithm>
#include <cctype>
#include <locale>


namespace{
    //https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring

	// trim from start (in place)
	[[maybe_unused]] static inline void ltrim(std::string &s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
			return !std::isspace(ch);
		}));
	}

	// trim from end (in place)
	[[maybe_unused]] static inline void rtrim(std::string &s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
			return !std::isspace(ch);
		}).base(), s.end());
	}

	// trim from both ends (in place)
	[[maybe_unused]] static inline void trim(std::string &s) {
		ltrim(s);
		rtrim(s);
	}

	// trim from start (copying)
	[[maybe_unused]] static inline std::string ltrim_copy(std::string s) {
		ltrim(s);
		return s;
	}

	// trim from end (copying)
	[[maybe_unused]] static inline std::string rtrim_copy(std::string s) {
		rtrim(s);
		return s;
	}

	// trim from both ends (copying)
	[[maybe_unused]] static inline std::string trim_copy(std::string s) {
		trim(s);
		return s;
	}
}



void Block::load(std::istream & in, const std::string &path_info){


    //--- context ---
	size_t line_count = 0;

	//https://regex101.com/
	std::regex regex_comment("([^#]*?)#(.*)"              ,std::regex::optimize); //[1]=code, [2]=comment, no comment=>no match
	std::regex regex_value  ("([^=]*?)\\s*=\\s*(.*)"      ,std::regex::optimize); //[1]=name, [2]=value, matches "name  = value"

	std::regex regex_block_begin("([^\\s\\{]+)\\s*\\{"          ,std::regex::optimize); //[1]=name, matches "name {"
	std::regex regex_block_empty("([^\\s\\{]+)\\s*(\\{\\s*\\})" ,std::regex::optimize); //[1]=name, matches "name { }"
	std::regex regex_block_end  ("[\\}]"                        ,std::regex::optimize);


	//--- line helpers ---
	auto remove_comment=[&](std::string &s){
		std::smatch m;
		std::regex_match(s,m,regex_comment);
		if(std::regex_match(s,m,regex_comment)){
			s=m[1];
		}
	};


	//--- block stack ---
	std::vector<Block *> block_stack;

	auto block_current=[&]()-> Block& {
		if(block_stack.empty() ){return *this;}
		return *block_stack.back();
	};

	auto block_push=[&](Block &me){
		block_stack.emplace_back(&me);
	};

	auto block_pop=[&](){
		if(block_stack.empty() ){
			throw_parse_unexpected_end_of_block(line_count, path_info);
		}
		block_stack.pop_back();
	};



	std::string line;
	while( getline(in,line) ){
		++line_count;
		if(!in){throw_file_read(path_info);}

		//trim & comments
		if(line==""){continue;}
		remove_comment(line);
		trim(line);
		if(line==""){continue;}

		{//value
			std::smatch m;
			if(std::regex_match(line,m,regex_value)){

				if(block_stack.size()==0){
					throw_parse_out_of_block(line_count, path_info);
				}
				Value & r = block_current().values.create(m[1],m[2]);
				r.line = line_count;
				continue;
			}
		}

		{//block_begin
			std::smatch m;
			if(std::regex_match(line,m,regex_block_begin)){
				Block & r = block_current().blocks.create(m[1]);
				r.begin_line = line_count;
				r.blocks.enclosing_block = &block_current();
				r.values.enclosing_block = &r;
				block_push (r);
				continue;
			}
		}

		{//block_end
			std::smatch m;
			std::regex_match(line,m,regex_block_end);
			if( std::regex_match(line,m,regex_block_end) ){
				block_current().end_line = line_count;
				block_pop();
				continue;
			}
		}

		{//block_empty
			std::smatch m;
			std::regex_match(line,m,regex_block_empty);
			if( std::regex_match(line,m,regex_block_empty) ){
				Block & r = block_current().blocks.create(m[1]);
				r.begin_line = line_count;
				r.end_line = line_count;
				r.blocks.enclosing_block = &block_current();
				r.values.enclosing_block = &r;
				continue;
			}
		}

		//something else => throw
		throw_parse_unexpected_line(line_count,line,path_info);
	}

	//unclosed blocks
	if(block_stack.size()!=0){
		throw_parse_missing_end_of_block   ( block_current().begin_line, path_info);
	}

	if(!in.eof()){throw_file_read(path_info);}


}

void Block::save(std::ostream &out, size_t indent){

	std::string iii = indent_str(indent);
	bool level_zero = indent==0 and name=="";

	if(!level_zero){ out << iii << name << "{ #"<<begin_line<<":"<<end_line<<"\n"; }

	values.save(out,indent+1);
	out << "\n";
	blocks.save(out,indent+1);

	if(!level_zero){out << iii << "} #end:"<<name<<"\n"; }
	out << "\n";
}


/*
void Config::load(const std::string  & file_path_){
	file_path=file_path_;Block::load(file_path_);
}

void Config::load(std::istream & in, const std::string& path_info){
	file_path=path_info;Block::load(in,path_info);
}
*/


}//end namesapce config


