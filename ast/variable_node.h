// $Id: variable_node.h,v 1.1 2016/02/19 19:29:48 david Exp $ -*- c++ -*-
#ifndef __ZU_VARIABLENODE_H__
#define __ZU_VARIABLENODE_H__

#include <string>

namespace zu {

  /**
   * Class for describing variable nodes.
   */
  class variable_node: public cdk::identifier_node {
    zu::lvalue_node* _value;

  public:
    inline variable_node(int lineno, const std::string &s, zu::lvalue_node* value):
	identifier_node(lineno,s), _value(value) {
    }

    inline zu::lvalue_node* value(){
    	return _value;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_variable_node(this, level);
    }

  };

} // zu

#endif
