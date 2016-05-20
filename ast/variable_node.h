// $Id: variable_node.h,v 1.3 2016/03/18 12:33:18 ist169481 Exp $
#ifndef __ZU_VARIABLE_NODE_H__
#define __ZU_VARIABLE_NODE_H__

#include <string>
#include "assignment_node.h"
#include "id_node.h"

namespace zu {

  class variable_node: public cdk::expression_node {
	basic_type *_zu_type;
	std::string _identifier;
	bool _isPublic;
	bool _isImported;
	cdk::expression_node *_value;
	bool _isFarg;

  public:
    inline variable_node(int lineno, basic_type *zu_type, const char *s, bool isPublic, bool isImported, cdk::expression_node *value, bool isFarg) :
        cdk::expression_node(lineno), _zu_type(zu_type), _identifier(s), _isPublic(isPublic), _isImported(isImported), _value(value), _isFarg(isFarg) {
	}
    inline variable_node(int lineno, basic_type *zu_type, const std::string &s, bool isPublic, bool isImported, cdk::expression_node *value, bool isFarg) :
        cdk::expression_node(lineno), _zu_type(zu_type), _identifier(s), _isPublic(isPublic), _isImported(isImported), _value(value) , _isFarg(isFarg) {
    }
    inline variable_node(int lineno, basic_type *zu_type, const std::string *s, bool isPublic, bool isImported, cdk::expression_node *value, bool isFarg) :
       cdk::expression_node(lineno), _zu_type(zu_type), _identifier(*s), _isPublic(isPublic), _isImported(isImported), _value(value) , _isFarg(isFarg) {
    }

  public:
	inline basic_type *zu_type() {
		return _zu_type;
	}

    inline std::string identifier() {
      return _identifier;
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

	inline bool isFunctionArgument() {
		return _isFarg;
	}

	inline zu::assignment_node* assignment_handler() {
		return new zu::assignment_node(lineno(), new zu::id_node(lineno(), identifier()), value());
	}

    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    virtual void accept(basic_ast_visitor *sp, int level) {
      sp->do_variable_node(this, level);
    }

  };

} // zu

#endif
