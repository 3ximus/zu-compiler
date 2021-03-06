// $Id: and_node.h,v 1.2 2016/03/17 17:58:34 ist169481 Exp $ -*- c++ -*-
#ifndef __ZU_AND_NODE_H__
#define __ZU_AND_NODE_H__

namespace zu {

  /**
   * Class for describing and nodes.
   */
  class and_node: public cdk::binary_expression_node {

  public:
    inline and_node(int lineno, cdk::expression_node *lvalue, cdk::expression_node *rvalue) :
        binary_expression_node(lineno, lvalue, rvalue) {
    }

  public:
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_and_node(this, level);
    }

  };

} // zu

#endif
