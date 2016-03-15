// $Id: priority_node.h,v 1.1 2016/02/19 19:29:48 david Exp $ -*- c++ -*-
#ifndef __ZU_PRIORITYNODE_H__
#define __ZU_PRIORITYNODE_H__

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
