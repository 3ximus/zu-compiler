#ifndef __CDK_FORNODE_H__
#define __CDK_FORNODE_H__

#include <cdk/ast/expression_node.h>

namespace zu {

  /**
   * Class for describing while-cycle nodes.
   */
  class for_node: public cdk::basic_node {
    cdk::expression_node *_init, *_test, *_step;
    cdk::basic_node *_block;

  public:
    inline for_node(int lineno, cdk::expression_node *init,cdk::expression_node *test,cdk::expression_node *step, cdk::basic_node *block) :
        basic_node(lineno), _init(init),_test(test),_step(step), _block(block) {
    }

  public:
    inline cdk::expression_node *init() {
      return _init;
    }
    inline cdk::expression_node *test() {
      return _test;
    }
    inline cdk::expression_node *step() {
      return _step;
    }
    inline cdk::basic_node *block() {
      return _block;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_for_node(this, level);
    }

  };

} // zu

#endif
