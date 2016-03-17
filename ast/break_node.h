// $Id: break_node.h,v 1.1 2016/03/17 17:58:34 ist169481 Exp $ -*- c++ -*-
#ifndef __ZU_BREAK_NODE_H__
#define __ZU_BREAK_NODE_H__


namespace zu {

  /**
   * Class for describing break nodes.
   */
  class break_node: public cdk::basic_node {

  public:
    inline break_node(int lineno) :
        cdk::basic_node(lineno) {
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_break_node(this, level);
    }

  };

} // zu

#endif
