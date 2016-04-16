// $Id: id_node.h,v 1.2 2016/03/17 17:58:35 ist169481 Exp $ -*- c++ -*-
#ifndef __ZU_IDENTIFIER_NODE_H__
#define __ZU_IDENTIFIER_NODE_H__

#include "lvalue_node.h"

namespace zu {

  class id_node: public zu::lvalue_node {
	std::string _identifier;

  public:
    inline id_node(int lineno, const char *s) :
        zu::lvalue_node(lineno), _identifier(s) {
	}
    inline id_node(int lineno, const std::string &s) :
        zu::lvalue_node(lineno), _identifier(s) {
    }
    inline id_node(int lineno, const std::string *s) :
        zu::lvalue_node(lineno), _identifier(*s) {
    }

  public:
    inline std::string name() {
      return _identifier;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_id_node(this, level);
    }

  };

} // zu

#endif
