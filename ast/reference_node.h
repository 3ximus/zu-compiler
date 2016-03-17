#ifndef __ZU_REFERENCE_NODE_H__
#define __ZU_REFERENCE_NODE_H__

namespace zu {

  /**
   * Class for describing and nodes.
   */
  class reference_node: public cdk::unary_expression_node {

  public:
    inline reference_node(int lineno, expression_node *arg): cdk::unary_expression_node(lineno, arg){}

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_reference_node(this, level);
    }

  };

} // zu

#endif
