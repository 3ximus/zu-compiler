// $Id: allocation_node.h,v 1.1 2016/02/19 19:29:48 david Exp $ -*- c++ -*-
#ifndef __ZU_ALLOCATIONNODE_H__
#define __ZU_ALLOCATIONNODE_H__

namespace zu {

  /**
   * Class for describing allocation nodes.
   */
  class allocation_node: public cdk::expression_node {
    cdk::expression_node *_lvalue;
    cdk::expression_node *_rvalue;

  public:
    inline allocation_node(int lineno, cdk::expression_node *lvalue, cdk::expression_node *rvalue) :
        cdk::expression_node(lineno), _lvalue(lvalue), _rvalue(rvalue) {
    }

  public:
    inline cdk::expression_node *lvalue() {
      return _lvalue;
    }
    inline cdk::expression_node *rvalue() {
      return _rvalue;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_allocation_node(this, level);
    }

  };

} // zu

#endif
