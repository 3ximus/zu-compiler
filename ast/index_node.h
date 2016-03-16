// $Id: index_node.h,v 1.1 2016/02/19 19:29:48 david Exp $ -*- c++ -*-
#ifndef __ZU_INDEXNODE_H__
#define __ZU_INDEXNODE_H__

#include <string>

namespace zu {

  /**
   * Class for describing index nodes.
   */
  class index_node: public zu::lvalue_node {
    cdk::expression_node *_lvalue;
    cdk::expression_node *_rvalue;

  public:
    inline index_node(int lineno, cdk::expression_node *lvalue, cdk::expression_node *rvalue) :
        zu::left_value(lineno, new std::string("")), _lvalue(lvalue), _rvalue(rvalue) {
    }

  public:
    inline cdk::expression_node *lvalue() {
      return _lvalue;
    }
    inline cdk::expression_node *rvalue() {
      return _rvalue;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_index_node(this, level);
    }

  };

} // zu

#endif
