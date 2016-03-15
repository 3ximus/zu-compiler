#ifndef __ZU_ORNODE_H__
#define __ZU_ORNODE_H__

namespace zu {

  /**
   * Class for describing or nodes.
   */
  class or_node: public cdk::expression_node {
    cdk::expression_node *_lvalue;
    cdk::expression_node *_rvalue;

  public:
    inline or_node(int lineno, cdk::expression_node *lvalue, cdk::expression_node *rvalue) :
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
      sp->do_or_node(this, level);
    }

  };

} // zu

#endif
