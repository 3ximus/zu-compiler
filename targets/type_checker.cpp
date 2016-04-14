// $Id: type_checker.cpp,v 1.5 2016/03/18 13:03:56 ist169481 Exp $ -*- c++ -*-
#include <string>
#include "targets/type_checker.h"
#include "ast/all.h"  // automatically generated
#include <iostream>

#define ASSERT_UNSPEC \
    { if (node->type() != nullptr && \
          node->type()->name() != basic_type::TYPE_UNSPEC) return; }

//---------------------------------------------------------------------------

void zu::type_checker::do_integer_node(cdk::integer_node * const node, int lvl) {
	ASSERT_UNSPEC;
	node->type(new basic_type(4, basic_type::TYPE_INT));
}

void zu::type_checker::do_double_node(cdk::double_node * const node, int lvl) {
	ASSERT_UNSPEC;
	node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
}

void zu::type_checker::do_string_node(cdk::string_node * const node, int lvl) {
	ASSERT_UNSPEC;
	node->type(new basic_type(4, basic_type::TYPE_STRING));
}

//---------------------------------------------------------------------------

inline void zu::type_checker::processUnaryExpression(cdk::unary_expression_node * const node, int lvl) {
	ASSERT_UNSPEC;
	node->argument()->accept(this, lvl + 2);
	if (node->argument()->type()->name() != basic_type::TYPE_INT && node->argument()->type()->name() != basic_type::TYPE_DOUBLE)
		throw std::string("wrong type in argument of unary expression");

	node->type(node->argument()->type());
}

void zu::type_checker::do_neg_node(cdk::neg_node * const node, int lvl) {
	processUnaryExpression(node, lvl);
}

void zu::type_checker::do_identity_node(zu::identity_node * const node, int lvl) {
	processUnaryExpression(node, lvl);
}

void zu::type_checker::do_not_node(zu::not_node * const node, int lvl) {
	ASSERT_UNSPEC;
	node->argument()->accept(this, lvl + 2);
	if (node->argument()->type()->name() != basic_type::TYPE_INT)
		throw std::string("wrong type in argument of unary expression");

	node->type(new basic_type(4, basic_type::TYPE_INT));
}

void zu::type_checker::do_position_node(zu::position_node * const node, int lvl) {
	ASSERT_UNSPEC;
	node->argument()->accept(this, lvl + 2);
	if (node->argument()->type()->name() != basic_type::TYPE_POINTER)
		throw std::string("wrong type in argument of unary expression");

	node->type(new basic_type(4, basic_type::TYPE_POINTER));
}

//---------------------------------------------------------------------------

void zu::type_checker::do_allocation_node(zu::allocation_node * const node, int lvl)  {
	ASSERT_UNSPEC;
	node->size()->accept(this, lvl + 2);
	if (node->size()->type()->name() != basic_type::TYPE_INT)
		throw std::string("wrong type in argument of allocation expression");

	node->type(new basic_type(4, basic_type::TYPE_POINTER));
	node->type()->_subtype = (new basic_type(0, basic_type::TYPE_UNSPEC));
}

void zu::type_checker::do_index_node(zu::index_node * const node, int lvl) {
	ASSERT_UNSPEC;
	node->lvalue()->accept(this, lvl + 2);
	if (node->lvalue()->type()->name() != basic_type::TYPE_POINTER)
		throw std::string("wrong type in argument of index expression");

	node->rvalue()->accept(this, lvl + 2);
	if (node->rvalue()->type()->name() != basic_type::TYPE_INT)
		throw std::string("wrong type in argument of index expression");

	node->type(node->lvalue()->type()->subtype());
}

void zu::type_checker::do_id_node(zu::id_node * const node, int lvl) {
	ASSERT_UNSPEC;
	const std::string &id = node->identifier();
	std::shared_ptr<zu::symbol> symbol = _symtab.find(id);
	if (!symbol)
		throw id + " undeclared";
	node->type(symbol->type());
}

void zu::type_checker::do_variable_node(zu::variable_node * const node, int lvl) {
	ASSERT_UNSPEC;
	const std::string &id = node->identifier();
	if (!_symtab.insert(id, std::make_shared<zu::symbol>(node->type(), id, 0)))
		throw id + " redeclared";

	if (node->value()) {
		node->value()->accept(this, lvl + 2);
		/* throw error if types dont match or it isnt a conversion from int to double */
		if ((node->type()->name() != basic_type::TYPE_DOUBLE && node->value()->type()->name() != basic_type::TYPE_INT) || node->type()->name() != node->value()->type()->name())
			throw std::string("wrong type for initializer");
	}

	node->type(node->zu_type());
}


//---------------------------------------------------------------------------

inline void zu::type_checker::processBinaryExpression(cdk::binary_expression_node * const node, int lvl) {
	ASSERT_UNSPEC;
	/* operation cannot be performed on a string */
	node->left()->accept(this, lvl + 2);
	if (node->left()->type()->name() != basic_type::TYPE_INT || node->left()->type()->name() != basic_type::TYPE_DOUBLE || node->left()->type()->name() != basic_type::TYPE_POINTER)
		throw std::string("string not supported on");
	node->right()->accept(this, lvl + 2);
	if (node->right()->type()->name() != basic_type::TYPE_INT || node->right()->type()->name() != basic_type::TYPE_DOUBLE || node->right()->type()->name() != basic_type::TYPE_POINTER)
		throw std::string("string not supported on");
}

inline void zu::type_checker::processSameTypes(cdk::binary_expression_node * const node) {
	if (node->right()->type()->name() != node->left()->type()->name())
		throw std::string("diferent types on binary expression");
}

inline void zu::type_checker::processNotPointer(cdk::binary_expression_node * const node) {
	if (node->left()->type()->name() == basic_type::TYPE_POINTER && node->right()->type()->name() == basic_type::TYPE_POINTER)
		throw std::string("pointer not allowed on binary expression");
}


void zu::type_checker::do_add_node(cdk::add_node * const node, int lvl) {
	processBinaryExpression(node, lvl);
	/* if one of the operands is a pointer the other must be an integer to calculate offset */
	if ((node->left()->type()->name() == basic_type::TYPE_POINTER && node->right()->type()->name() == basic_type::TYPE_INT) || (node->right()->type()->name() == basic_type::TYPE_POINTER && node->left()->type()->name() == basic_type::TYPE_INT))  {
		node->type(new basic_type(4, basic_type::TYPE_POINTER));
		return;
	}
	if(node->left()->type()->name() == basic_type::TYPE_DOUBLE || node->right()->type()->name() == basic_type::TYPE_DOUBLE) {
		node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
		return;
	}
	if (node->right()->type()->name() == node->left()->type()->name()) {
		node->type(node->left()->type());
		return;
	}
	throw std::string("wrong types in arguments of binary expression");
}

void zu::type_checker::do_sub_node(cdk::sub_node * const node, int lvl) {
	processBinaryExpression(node, lvl);
	/* if both operands are pointer the type is int represententing distance between them */
	if (node->left()->type()->name() == basic_type::TYPE_POINTER && node->right()->type()->name() == basic_type::TYPE_POINTER) {
		if (node->left()->type()->subtype() == node->right()->type()->subtype())
			node->type(new basic_type(4, basic_type::TYPE_INT));
			return;
	}
	if(node->left()->type()->name() == basic_type::TYPE_DOUBLE || node->right()->type()->name() == basic_type::TYPE_DOUBLE) {
		node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
		return;
	}
	if (node->right()->type()->name() == node->left()->type()->name()) {
		node->type(node->left()->type());
		return;
	}
	throw std::string("wrong types in arguments of binary expression");
}

void zu::type_checker::do_mul_node(cdk::mul_node * const node, int lvl) {
	processBinaryExpression(node, lvl);
	processNotPointer(node);

	if(node->left()->type()->name() == basic_type::TYPE_DOUBLE || node->right()->type()->name() == basic_type::TYPE_DOUBLE) {
		node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
		return;
	}
	processSameTypes(node);
	node->type(node->left()->type());
}

void zu::type_checker::do_div_node(cdk::div_node * const node, int lvl) {
	processBinaryExpression(node, lvl);
	processNotPointer(node);

	if(node->left()->type()->name() == basic_type::TYPE_DOUBLE || node->right()->type()->name() == basic_type::TYPE_DOUBLE) {
		node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
		return;
	}
	processSameTypes(node);
	node->type(node->left()->type());
}

void zu::type_checker::do_mod_node(cdk::mod_node * const node, int lvl) {
	processBinaryExpression(node, lvl);
	processNotPointer(node);

	if (node->left()->type()->name() == basic_type::TYPE_DOUBLE && node->right()->type()->name() == basic_type::TYPE_DOUBLE)
		throw std::string("wrong types in arguments of binary expression");
	processSameTypes(node);
	node->type(node->left()->type());
}

void zu::type_checker::do_lt_node(cdk::lt_node * const node, int lvl) {
	processBinaryExpression(node, lvl);
	processNotPointer(node);
	processSameTypes(node);

	node->type(new basic_type(4, basic_type::TYPE_INT));
}

void zu::type_checker::do_le_node(cdk::le_node * const node, int lvl) {
	processBinaryExpression(node, lvl);
	processNotPointer(node);
	processSameTypes(node);

	node->type(new basic_type(4, basic_type::TYPE_INT));
}

void zu::type_checker::do_ge_node(cdk::ge_node * const node, int lvl) {
	processBinaryExpression(node, lvl);
	processNotPointer(node);
	processSameTypes(node);

	node->type(new basic_type(4, basic_type::TYPE_INT));
}

void zu::type_checker::do_gt_node(cdk::gt_node * const node, int lvl) {
	processBinaryExpression(node, lvl);
	processNotPointer(node);
	processSameTypes(node);

	node->type(new basic_type(4, basic_type::TYPE_INT));
}

//---------------------------------------------------------------------------

void zu::type_checker::do_ne_node(cdk::ne_node * const node, int lvl) {
	processBinaryExpression(node, lvl);
	processSameTypes(node);

	node->type(new basic_type(4, basic_type::TYPE_INT));
}

void zu::type_checker::do_eq_node(cdk::eq_node * const node, int lvl) {
	processBinaryExpression(node, lvl);
	processSameTypes(node);

	node->type(new basic_type(4, basic_type::TYPE_INT));
}

void zu::type_checker::do_and_node(zu::and_node * const node, int lvl) {
	processBinaryExpression(node, lvl);
	if(node->left()->type()->name() != basic_type::TYPE_INT || node->right()->type()->name() != basic_type::TYPE_INT)
		throw std::string("wrong types in arguments of binary expression");

	node->type(new basic_type(4, basic_type::TYPE_INT));
}

void zu::type_checker::do_or_node(zu::or_node * const node, int lvl) {
	processBinaryExpression(node, lvl);
	if(node->left()->type()->name() != basic_type::TYPE_INT || node->right()->type()->name() != basic_type::TYPE_INT)
		throw std::string("wrong types in arguments of binary expression");

	node->type(new basic_type(4, basic_type::TYPE_INT));
}

//---------------------------------------------------------------------------

void zu::type_checker::do_lvalue_node(zu::lvalue_node * const node, int lvl) {
	ASSERT_UNSPEC;
	node->accept(this, lvl + 2);
}

void zu::type_checker::do_function_declaration_node(zu::function_declaration_node * const node, int lvl){
	ASSERT_UNSPEC;
	const std::string &id = node->identifier();
	if (!_symtab.insert(id, std::make_shared<zu::symbol>(node->type(), id, 0)))
		throw id + " redeclared";

	if (node->literal()) {
		node->literal()->accept(this, lvl + 2);
		/* throw error if types dont match or it isnt a conversion from int to double */
		if ((node->type()->name() != basic_type::TYPE_DOUBLE && node->literal()->type()->name() != basic_type::TYPE_INT) || node->type()->name() != node->literal()->type()->name())
			throw std::string("wrong type for initializer");
	}
	node->type(node->zu_type());
}

void zu::type_checker::do_function_body_node(zu::function_body_node * const node, int lvl){
	/* EMPTY */
}

void zu::type_checker::do_function_call_node(zu::function_call_node * const node, int lvl){

}

void zu::type_checker::do_block_node(zu::block_node * const node, int lvl){

}

//---------------------------------------------------------------------------

void zu::type_checker::do_assignment_node(zu::assignment_node * const node, int lvl) {
	//ASSERT_UNSPEC;

	//// DAVID: horrible hack!
	//// (this is caused by Zu not having explicit variable declarations)
	//const std::string &id = node->lvalue()->value();
	//if (!_symtab.find(id)) {
	//  _symtab.insert(id, std::make_shared<zu::symbol>(new basic_type(4, basic_type::TYPE_INT), id, -1)); // put in the symbol table
	//}

	//node->lvalue()->accept(this, lvl + 2);
	//if (node->lvalue()->type()->name() != basic_type::TYPE_INT)
	//  throw std::string("wrong type in left argument of assignment expression");

	//node->rvalue()->accept(this, lvl + 2);
	//if (node->rvalue()->type()->name() != basic_type::TYPE_INT)
	//  throw std::string("wrong type in right argument of assignment expression");

	//// in Zu, expressions are always int
	//node->type(new basic_type(4, basic_type::TYPE_INT));
}

//---------------------------------------------------------------------------

void zu::type_checker::do_evaluation_node(zu::evaluation_node * const node, int lvl) {
	node->argument()->accept(this, lvl + 2);
}

void zu::type_checker::do_print_node(zu::print_node * const node, int lvl) {
	node->argument()->accept(this, lvl + 2);
}

//---------------------------------------------------------------------------

void zu::type_checker::do_read_node(zu::read_node * const node, int lvl) {
	//node->argument()->accept(this, lvl + 2);
}

//---------------------------------------------------------------------------

void zu::type_checker::do_for_node(zu::for_node * const node, int lvl) {
	//node->condition()->accept(this, lvl + 4);
}

//---------------------------------------------------------------------------

void zu::type_checker::do_if_node(zu::if_node * const node, int lvl) {
	node->condition()->accept(this, lvl + 4);
}

void zu::type_checker::do_if_else_node(zu::if_else_node * const node, int lvl) {
	node->condition()->accept(this, lvl + 4);
}
void zu::type_checker::do_return_node(zu::return_node * const node, int lvl) {/*TODO*/}
void zu::type_checker::do_continue_node(zu::continue_node * const node, int lvl) {/*TODO*/}
void zu::type_checker::do_break_node(zu::break_node * const node, int lvl) {/*TODO*/}
