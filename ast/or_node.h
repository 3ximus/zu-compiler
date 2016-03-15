#ifndef __ZU_ORNODE_H__
#define __ZU_ORNODE_H__

namespace zu {

  /**
   * Class for describing or nodes.
   */
  class or_node: public cdk::binary_expression_node {

  public:
    inline or_node(int lineno, cdk::expression_node *lvalue, cdk::expression_node *rvalue) :
        binary_expression_node(lineno, lvalue, rvalue) {
    }

  public:
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_or_node(this, level);
    }

  };

} // zu

#endif
