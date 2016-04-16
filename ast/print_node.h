// $Id: print_node.h,v 1.2 2016/03/17 17:58:35 ist169481 Exp $ -*- c++ -*-
#ifndef __ZU_PRINT_NODE_H__
#define __ZU_PRINT_NODE_H__

#include <cdk/ast/expression_node.h>

namespace zu {

  /**
   * Class for describing print nodes.
   */
  class print_node: public cdk::basic_node {
    cdk::expression_node *_argument;
	bool _newLine;

  public:
    inline print_node(int lineno, cdk::expression_node *argument, bool newLine) :
        cdk::basic_node(lineno), _argument(argument), _newLine(newLine) {
    }

  public:
    inline cdk::expression_node *argument() {
      return _argument;
    }

	inline bool newLine() {
		return _newLine;
	}

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_print_node(this, level);
    }

  };

} // zu

#endif
