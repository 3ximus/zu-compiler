#ifndef __CDK_FORNODE_H__
#define __CDK_FORNODE_H__

#include <cdk/ast/expression_node.h>

namespace zu {

  /**
   * Class for describing while-cycle nodes.
   */
  class for_node: public cdk::basic_node {
	/* TODO add more conditions */
    cdk::expression_node *_condition;
    cdk::basic_node *_block;

  public:
    inline for_node(int lineno, cdk::expression_node *condition, cdk::basic_node *block) :
        basic_node(lineno), _condition(condition), _block(block) {
    }

  public:
    inline cdk::expression_node *condition() {
      return _condition;
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
