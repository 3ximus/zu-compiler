
// $Id: block_node.h,v 1.3 2016/03/18 12:33:18 ist169481 Exp $
#ifndef __ZU_BLOCK_NODE_H__
#define __ZU_BLOCK_NODE_H__

#include <string>

namespace zu {

  /**
   * Class for describing syntactic tree leaves for holding lvalues.
   */
  class block_node: public cdk::basic_node {
	  cdk::sequence_node *_declarations, *_instructions;

  public:
    inline block_node(int lineno, cdk::sequence_node *declarations, cdk::sequence_node *instructions) :
        cdk::basic_node(lineno), _declarations(declarations), _instructions(instructions) {
    }

  public:
	inline cdk::sequence_node *declarations() {
		return _declarations;
	}

	inline cdk::sequence_node *instructions() {
		return _instructions;
	}

    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    virtual void accept(basic_ast_visitor *sp, int level) {
      sp->do_lvalue_node(this, level);
    }

  };

} // zu

#endif
