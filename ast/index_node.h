// $Id: index_node.h,v 1.2 2016/03/17 17:58:35 ist169481 Exp $ -*- c++ -*-
#ifndef __ZU_INDEX_NODE_H__
#define __ZU_INDEX_NODE_H__

#include "lvalue_node.h"

namespace zu {

  /**
   * Class for describing index nodes.
   */
  class index_node: public zu::lvalue_node {
    cdk::expression_node *_lvalue;
    cdk::expression_node *_rvalue;

  public:
    inline index_node(int lineno, cdk::expression_node *lvalue, cdk::expression_node *rvalue) :
       zu::lvalue_node(lineno), _lvalue(lvalue), _rvalue(rvalue) {
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
