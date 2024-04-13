//============================================================================
// Author  : Pierre BLAVY 2018
// Version : 1.1
// License : GPL 3.0 or any later version :
//           https://www.gnu.org/licenses/gpl-3.0-standalone.html
//============================================================================

//This program (config) is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>


#include "container/container.hpp"
#include "convert/convert.hpp"

namespace config{
template<typename To_t, typename Context_t>
void Value::throw_convert(const std::string & error)const{
	std::string msg;
	if constexpr (std::is_same<Context_t,Config_tag>::value ){
		msg = std::string("Cannot convert value to type ") + typeid(To_t).name();
	}else{
		msg = std::string("Cannot convert value to type ") + typeid(To_t).name() + " witnin context " + typeid(Context_t).name();
	}

	if(line !=0 ){msg+=", line=" +std::to_string(line);}
	msg+=", value="+value;
	if(error!=""){msg+=", error="+error;}

	throw std::runtime_error(msg);

}


//call convert in the Convert_tag context, throw meaningfull errors with context
template<typename To_t, typename Context_t>
To_t Value::to()const{
	try{return convert<To_t,Context_t>(this->value);}
	catch(std::exception &e){throw_convert<To_t,Context_t>(e.what());}
	catch(...)              {throw_convert<To_t,Context_t>();}
}

template<typename To_t, typename Context_t>
void Value::to(To_t & write_here)const{

	static_assert(!std::is_const<To_t>::value,"write_here must be writable but it's const");

	try{convert<Context_t>(write_here, this->value);}
	catch(std::exception &e){throw_convert<To_t,Context_t>(e.what());}
	catch(...)              {throw_convert<To_t,Context_t>();}
}


//--- xxx_unique ---

template<typename Context_t, typename T>
void Value_v::load_unique(T&write_here, const std::string &name)const{
	auto f = name_to_value.find(name);
	if   (f==name_to_value.end()){throw_missing_value  (name,enclosing_block);}
	if   (f->second.size()==0)   {throw_missing_value  (name,enclosing_block);}
	if   (f->second.size()> 1)   {throw_multiple_values(name,enclosing_block);}
	f->second[0]->to<T,Context_t>(write_here);
}


template<typename Context_t, typename T>
void Value_v::load_unique(T&write_here, const std::string &name, const T& default_v)const{
	auto f = name_to_value.find(name);
	if   (f==name_to_value.end()){write_here =  default_v; return;}
	if   (f->second.size()==0)   {write_here =  default_v; return;}
	if   (f->second.size()> 1)   {throw_multiple_values(name,enclosing_block);}
	f->second[0]->to<T,Context_t>(write_here);
}

template<typename T,typename Context_t>
T Value_v::get_unique(const std::string &name, const T& default_v)const{
	auto f = name_to_value.find(name);
	if   (f==name_to_value.end()){return default_v;}
	if   (f->second.size()==0)   {return default_v;}
	if   (f->second.size()> 1)   {throw_multiple_values(name,enclosing_block);}
	return f->second[0]->to<T,Context_t>();
}



//--- xxx_multiple ---


template<typename Context_t, typename Container_t>
size_t Value_v::load_multiple(Container_t& write_here, const std::string &name)const{
	typedef container::value_type<Container_t> value_type;

	static_assert(
	    container::is_implemented<container::Add_back_t    ,Container_t>
	  | container::is_implemented<container::Add_anywhere_t, Container_t>,
	  "container::add_back or container::add_anywhere must be implemented for your container. "
	  "See container/container.hpp for details."
	);

	auto f = name_to_value.find(name);
	if(f==name_to_value.end()){return 0;}

	for(const auto val_ptr : f->second){
		//get and convert
		const std::string value_str = val_ptr->value;
		const auto value = val_ptr->to<value_type,Context_t>();

		//if possible add_back, if not add_anywhere
		if constexpr(container::is_implemented<container::Add_back_t, Container_t>){
			container::add_back(write_here, std::move(value));
		}else{
			container::add_anywhere(write_here, std::move(value));
		}
	}

	return f->second.size();

}


template<typename Container_t, typename Context_t>
Container_t  Value_v::get_multiple(const std::string &name)const{
	Container_t t;
	load_multiple<Container_t,Context_t>(t,name);
	return t;
}




//--- get optional ---

template<typename Context_t, typename T>
bool Value_v::load_try(T &write_here, const std::string &name)const{
	auto f = name_to_value.find(name);
	if   (f==name_to_value.end()){return false;}
	if   (f->second.size()==0)   {return false;}
	if   (f->second.size()> 1)   {throw_multiple_values(name,enclosing_block);}
	f->second[0]->to<T,Context_t>(write_here);
	return true;
}

#if __cplusplus >= 201703L
template<typename Context_t, typename T>
void Value_v::load_optional(std::optional<T> &write_here, const std::string &name)const{
	auto f = name_to_value.find(name);
	if   (f==name_to_value.end()){write_here=std::nullopt;}
	if   (f->second.size()==0)   {write_here=std::nullopt;}
	if   (f->second.size()> 1)   {throw_multiple_values(name,enclosing_block);}
	write_here = f->second[0]->to<T,Context_t>();
}

inline std::optional<std::string> Value_v::get_optional(const std::string &name)const{ 
  return this->template get_optional<std::string,Config_tag >(name); 
}


template<typename T, typename Context_t> 
std::optional<T> Value_v::get_optional(const std::string &name)const{
  std::optional<T> t; 
  this->template load_optional<Context_t>(t,name); 
  return t;
}
#endif


}//end namesapce config
