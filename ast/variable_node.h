// $Id: variable_node.h,v 1.2 2016/03/17 17:58:35 ist169481 Exp $ -*- c++ -*-
#ifndef __ZU_VARIABLE_NODE_H__
#define __ZU_VARIABLE_NODE_H__

#include <string>
#include "lvalue_node.h"

namespace zu {

  /**
   * Class for describing variable nodes.
   */
  class variable_node: public lvalue_node {

  public:
    inline variable_node(int lineno, const std::string &s):
	lvalue_node(lineno,s) {
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_variable_node(this, level);
    }

  };

} // zu

#endif
