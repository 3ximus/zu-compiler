#ifndef __ZU_SIMETRY_NODE_H__
#define __ZU_SIMETRY_NODE_H__

namespace zu {

  /**
   * Class for describing and nodes.
   */
  class simetry_node: public cdk::unary_expression_node {

  public:
    inline simetry_node(int lineno, expression_node *arg): cdk::unary_expression_node(lineno, arg) {}

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_simetry_node(this, level);
    }

  };

} // zu

#endif
