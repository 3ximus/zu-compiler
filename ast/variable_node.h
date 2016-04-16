// $Id: variable_node.h,v 1.3 2016/03/18 12:33:18 ist169481 Exp $
#ifndef __ZU_VARIABLE_NODE_H__
#define __ZU_VARIABLE_NODE_H__

#include <string>

namespace zu {

  /**
   * Class for describing syntactic tree leaves for holding lvalues.
   */
  class variable_node: public cdk::expression_node {
	basic_type *_zu_type;
	std::string _name;
	cdk::expression_node *_value;
	bool _isPublic;
	bool _isImported;

  public:
    inline variable_node(int lineno, basic_type *zu_type, const char *s, bool isPublic, bool isImported, cdk::expression_node *value) :
        cdk::expression_node(lineno), _zu_type(zu_type), _name(s), _isPublic(isPublic), _isImported(isImported), _value(value) {
	}
    inline variable_node(int lineno, basic_type *zu_type, const std::string &s, bool isPublic, bool isImported, cdk::expression_node *value) :
        cdk::expression_node(lineno), _zu_type(zu_type), _name(s), _isPublic(isPublic), _isImported(isImported), _value(value) {
    }
    inline variable_node(int lineno, basic_type *zu_type, const std::string *s, bool isPublic, bool isImported, cdk::expression_node *value) :
       cdk::expression_node(lineno), _zu_type(zu_type), _name(*s), _isPublic(isPublic), _isImported(isImported), _value(value) {
    }

  public:
	inline basic_type *zu_type() {
		return _zu_type;
	}

    inline std::string name() {
      return _name;
    }

	inline bool isPublic() {
		return _isPublic;
	}

	inline bool isImported() {
		return _isImported;
	}

	inline cdk::expression_node *value() {
		return _value;
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
