// $Id: priority_node.h,v 1.2 2016/03/17 17:58:35 ist169481 Exp $ -*- c++ -*-
#ifndef __ZU_PRIORITY_NODE_H__
#define __ZU_PRIORITY_NODE_H__

namespace zu {

  /**
   * Class for describing priority nodes.
   */
  class priority_node: public cdk::expression_node {
    cdk::expression_node *_inner_value;

  public:
    inline priority_node(int lineno, cdk::expression_node *inner_value) :
        cdk::expression_node(lineno), _inner_value(inner_value) {
    }

  public:
    inline cdk::expression_node *inner_value() {
      return _inner_value;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_priority_node(this, level);
    }

  };

} // zu

#endif
