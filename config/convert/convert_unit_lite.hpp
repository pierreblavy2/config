#ifndef LIB_CONFIG_CONVERT_UNIT_LITE_HPP_
#define LIB_CONFIG_CONVERT_UNIT_LITE_HPP_

#include <convert/convert.hpp>
#include <unit_lite/unit_lite.hpp>

namespace config{
  struct Config_tag;
}

//convert from any to unit_lite::Quantity
template<typename Unit_tag, typename Unit_value, typename From_tt>
struct Convert_t<unit_lite::Quantity<Unit_tag,Unit_value> , From_tt, config::Config_tag >{
	typedef unit_lite::Quantity<Unit_tag,Unit_value> To_t;
	typedef From_tt From_t;
	typedef config::Config_tag Context_tag_t;

	static To_t run(const From_t &f){
		unit_lite::Quantity<Unit_tag,Unit_value> r;
		r.value=convert<Unit_value,Context_tag_t >(f);
		return r;
	}
};


#endif /* LIB_CONFIG_CONVERT_UNIT_LITE_HPP_ */
