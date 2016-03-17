// $Id: integer_node.h,v 1.3 2014/02/26 18:53:32 david Exp $ -*- c++ -*-
#ifndef __ZU_AST_EXPRESSION_POINTER_H__
#define __ZU_AST_EXPRESSION_POINTER_H__


namespace zu {

  /**
   * Class for describing pointers in zu.
   */
  template<typename StoredType>
  class pointer_node: public cdk::integer_node {
    StoredType _value; 

  public:
    inline pointer_node(int lineno, int i, const StoredType &value) :
        integer_node(lineno, i), _value(value) {
    }

    inline const StoredType &value() const {
      return _value;
    }

    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_pointer_node(this, level);
    }

  };

} // zu

#endif
