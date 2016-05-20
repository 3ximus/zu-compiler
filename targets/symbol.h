// $Id: symbol.h,v 1.1 2016/02/19 19:29:48 david Exp $ -*- c++ -*-
#ifndef __ZU_SEMANTICS_SYMBOL_H__
#define __ZU_SEMANTICS_SYMBOL_H__

#include <string>
#include <cdk/basic_type.h>

namespace zu {

	class symbol {
		basic_type *_type;
		std::string _name;
		long _value; // hack!
		int _local_offset = -1;
		std::string _global_label;

		public:
		inline symbol(basic_type *type, const std::string &name, long value) :
			_type(type), _name(name), _value(value) {
			}

		virtual ~symbol() {
			delete _type;
		}

		inline basic_type *type() const {
			return _type;
		}
		inline const std::string &name() const {
			return _name;
		}
		inline long value() const {
			return _value;
		}
		inline long value(long v) {
			return _value = v;
		}

		inline int local_offset() const{
			return _local_offset;
		}
		inline void local_offset(int v) {
			_local_offset = v;
		}

		inline std::string global_label() const{
			return _global_label;
		}
		inline void global_label(std::string v) {
			_global_label = v;
		}

	};

} // zu

#endif
