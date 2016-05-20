// $Id: postfix_writer.cpp,v 1.5 2016/03/18 13:03:56 ist169481 Exp $ -*- c++ -*-
#include <string>
#include <sstream>
#include "targets/type_checker.h"
#include "targets/postfix_writer.h"
#include "ast/all.h"  // all.h is automatically generated

// Uncomment for extra spam
#define __PFWRITER_DEBUG__

void zu::postfix_writer::debug(cdk::basic_node* const node, int lvl) {
#ifdef __PFWRITER_DEBUG__
	os() << ";" << std::string(10, '~');
	for(int i=0; i<lvl; i++) {
		os() << "  |";
	}
	os() << "--" << node->name() << std::endl;
#endif
}

//---------------------------------------------------------------------------
//     THIS IS THE VISITOR'S DEFINITION
//---------------------------------------------------------------------------

void zu::postfix_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
	for (size_t i = 0; i < node->size(); i++)
		if (node->node(i))
		  node->node(i)->accept(this, lvl+1);
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
	debug(node, lvl);
	CHECK_TYPES(_compiler, _symtab, node);

	if (_function_context)
		_pf.INT(node->value()); // push an integer
	else
		_pf.CONST(node->value()); // declare integer on selected segment
}

void zu::postfix_writer::do_double_node(cdk::double_node * const node, int lvl) {
	debug(node, lvl);
	int lbl1;
	CHECK_TYPES(_compiler, _symtab, node);

	if (!_function_context) {
		_pf.DOUBLE(node->value());
		return;
	}

	_pf.RODATA();
	_pf.ALIGN();
	_pf.LABEL(mklbl(lbl1 = ++_lbl));
	_pf.DOUBLE(node->value());

	_pf.TEXT();
	_pf.ADDR(mklbl(lbl1));
	_pf.DLOAD(); /* Replaces address at the top of the stack with the contents of the position it points to. This applies to any LoadFunction. */
}

void zu::postfix_writer::do_string_node(cdk::string_node * const node, int lvl) {
	debug(node, lvl);
	int lbl1 = ++_lbl;
	CHECK_TYPES(_compiler, _symtab, node);


	/* generate the string */
	_pf.RODATA(); // strings are DATA readonly
	_pf.ALIGN(); // make sure we are aligned
	_pf.LABEL(mklbl(lbl1)); // give the string a name
	_pf.STR(node->value()); // output string characters

	if (!_function_context) {
		_pf.DATA();
		_pf.ID(mklbl(lbl1));
	}
	else { /* leave the address on the stack */
		_pf.TEXT(); // return to the TEXT segment
		_pf.ADDR(mklbl(lbl1)); // the string to be printed
	}
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
	debug(node, lvl);
	CHECK_TYPES(_compiler, _symtab, node);
	node->argument()->accept(this, lvl+1); // determine the value
	if (node->argument()->type()->name() == basic_type::TYPE_INT)
		_pf.NEG(); // 2-complement
	else
		_pf.DNEG(); // symmetric for floats
}

void zu::postfix_writer::do_identity_node(zu::identity_node * const node, int lvl) {
	debug(node, lvl);
	CHECK_TYPES(_compiler, _symtab, node);
	node->argument()->accept(this, lvl+1); // determine the value
	/* FIXME DO NOTHING? */
}

void zu::postfix_writer::do_not_node(zu::not_node * const node, int lvl) {
	debug(node, lvl);
	CHECK_TYPES(_compiler, _symtab, node);
	node->argument()->accept(this, lvl+1); // determine the value
	_pf.NOT(); // logical negation
}

void zu::postfix_writer::do_position_node(zu::position_node * const node, int lvl) {
	debug(node, lvl);
	CHECK_TYPES(_compiler, _symtab, node);
	node->argument()->accept(this, lvl+1); // determine the value
	/* FIXME DO NOTHING */
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_and_node(zu::and_node * const node, int lvl) {
	debug(node, lvl);
	CHECK_TYPES(_compiler, _symtab, node);
	int lbl1 = _lbl++;

	node->left()->accept(this,lvl+1); // visit left child

	_pf.DUP(); // duplicate to get the value for jmp, if its zero jump is taken
	_pf.JZ(mklbl(lbl1)); // jump over right node

	if (node->left()->name().compare("index_node") == 0 || node->left()->name().compare("id_node") == 0)
		_pf.LOAD(); // load

	node->right()->accept(this,lvl+1);

	if (node->right()->name().compare("index_node") == 0 || node->right()->name().compare("id_node") == 0)
		_pf.LOAD(); // load

	_pf.AND();
	_pf.ALIGN(); // align symbols
	_pf.LABEL(mklbl(lbl1));
}

void zu::postfix_writer::do_or_node(zu::or_node * const node, int lvl) {
	debug(node, lvl);
	CHECK_TYPES(_compiler, _symtab, node);
	int lbl1 = _lbl++;

	node->left()->accept(this,lvl+1); // visit left child

	_pf.DUP(); // duplicate to get the value for jmp, if its non zero jump is taken
	_pf.JNZ(mklbl(lbl1)); // jump over right node

	if (node->left()->name().compare("index_node") == 0 || node->left()->name().compare("id_node") == 0)
		_pf.LOAD(); // load

	node->right()->accept(this,lvl+1);

	if (node->right()->name().compare("index_node") == 0 || node->right()->name().compare("id_node") == 0)
		_pf.LOAD(); // load

	_pf.AND();
	_pf.ALIGN(); // align symbols
	_pf.LABEL(mklbl(lbl1));
}

void zu::postfix_writer::do_allocation_node(zu::allocation_node * const node, int lvl)  {
	debug(node, lvl);
	CHECK_TYPES(_compiler, _symtab, node);

	_pf.INT(node->type()->subtype()->size());
	node->size()->accept(this, lvl+1);
	if (node->size()->name().compare("index_node") == 0 || node->size()->name().compare("id_node") == 0)
		_pf.LOAD();

	_pf.MUL();
	_pf.ALLOC();
	_pf.SP();
}

void zu::postfix_writer::do_index_node(zu::index_node * const node, int lvl) {
	debug(node, lvl);
	CHECK_TYPES(_compiler, _symtab, node);
	/* TODO */
}

void zu::postfix_writer::do_id_node(zu::id_node * const node, int lvl) {
	debug(node, lvl);
	CHECK_TYPES(_compiler, _symtab, node);

	std::shared_ptr<zu::symbol> s = _symtab.find(node->identifier());

	if (s->local_offset() != -1) // variable is local
		_pf.LOCAL(s->local_offset());
	else 						// variable is global
		_pf.ADDR(s->global_label());

}

void zu::postfix_writer::do_variable_node(zu::variable_node * const node, int lvl) {
	debug(node, lvl);
	CHECK_TYPES(_compiler, _symtab, node);

	std::shared_ptr<zu::symbol> s = _symtab.find(node->identifier());

	if (node->isFunctionArgument()) {
		s->local_offset(_local_arg_offset);
		_local_arg_offset += node->type()->size();
		return;
	}

	if (_function_context) {
		_local_dec_offset -= node->type()->size();
		s->local_offset(_local_dec_offset);
		if (node->value())
			node->assignment_handler()->accept(this, lvl+1);
	}

	else {
		std::string label = (node->isPublic()) ? node->identifier() : mklbl(++_lbl);

		if (node->value() == NULL) {
			_pf.BSS();
			_pf.ALIGN();
			_pf.LABEL(label);
			_pf.BYTE(node->type()->size());
		}
		else {

			_pf.DATA();
			_pf.ALIGN();
			_pf.LABEL(label);

			if ((node->type()->name() == basic_type::TYPE_DOUBLE) && (node->value()->type()->name() == basic_type::TYPE_INT))
				_pf.DOUBLE(((cdk::simple_value_node<int>*)node->value())->value());
			else
				node->value()->accept(this, lvl+1);

		}
		s->global_label(label);
	}
}

void zu::postfix_writer::do_lvalue_node(zu::lvalue_node * const node, int lvl) {}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_add_node(cdk::add_node * const node, int lvl) {
	debug(node,lvl);
	CHECK_TYPES(_compiler, _symtab, node);
	checkExpressionsForBinaryInstruction(node,lvl);

	// ADD result is a double?
	if(node->type()->name() == basic_type::TYPE_DOUBLE) {
		_pf.DADD(); // yup.
	}
	else {
		// No. regular integer ADD
		_pf.ADD();
	}
}

void zu::postfix_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
	debug(node,lvl);
	CHECK_TYPES(_compiler, _symtab, node);
	checkExpressionsForBinaryInstruction(node,lvl);

	// SUB result is a double?
	if(node->type()->name() == basic_type::TYPE_DOUBLE) {
		_pf.DSUB(); // yup.
	}
	else {
		// No. regular integer SUB
		_pf.SUB();
	}
}

void zu::postfix_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
	debug(node,lvl);
	CHECK_TYPES(_compiler, _symtab, node);
	checkExpressionsForBinaryInstruction(node,lvl);

	// MUL result is a double?
	if(node->type()->name() == basic_type::TYPE_DOUBLE) {
		_pf.DMUL(); // yup.
	}
	else {
		// No. regular integer MUL
		_pf.MUL();
	}
}

void zu::postfix_writer::do_div_node(cdk::div_node * const node, int lvl) {
	debug(node,lvl);
	CHECK_TYPES(_compiler, _symtab, node);
	checkExpressionsForBinaryInstruction(node,lvl);

	// DIV result is a double?
	if(node->type()->name() == basic_type::TYPE_DOUBLE) {
		_pf.DDIV(); // yup.
	}
	else {
		// No. regular integer DIV
		_pf.DIV();
	}
}

void zu::postfix_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
	debug(node,lvl);
	CHECK_TYPES(_compiler, _symtab, node);

	node->left()->accept(this, lvl);

	// --left-- Replace address with value
	if(node->left()->type()->name() == basic_type::TYPE_POINTER)
		_pf.LOAD();

	node->right()->accept(this, lvl);

	// --right--  Replace address with value
	if(node->right()->type()->name() == basic_type::TYPE_POINTER)
		_pf.LOAD();

	_pf.MOD();
}

void zu::postfix_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
	debug(node,lvl);
	CHECK_TYPES(_compiler, _symtab, node);
        checkExpressionsForLogicalBinaryInstruction(node,lvl);

	_pf.LT();
}

void zu::postfix_writer::do_le_node(cdk::le_node * const node, int lvl) {
	debug(node,lvl);
	CHECK_TYPES(_compiler, _symtab, node);
        checkExpressionsForLogicalBinaryInstruction(node,lvl);

	_pf.LE();
}

void zu::postfix_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
	debug(node,lvl);
	CHECK_TYPES(_compiler, _symtab, node);
        checkExpressionsForLogicalBinaryInstruction(node,lvl);

	_pf.GE();
}

void zu::postfix_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
	debug(node,lvl);
	CHECK_TYPES(_compiler, _symtab, node);
        checkExpressionsForLogicalBinaryInstruction(node,lvl);

	_pf.GT();
}

void zu::postfix_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
	debug(node,lvl);
	CHECK_TYPES(_compiler, _symtab, node);
        checkExpressionsForLogicalBinaryInstruction(node,lvl);

	_pf.NE();
}

void zu::postfix_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
	debug(node,lvl);
	CHECK_TYPES(_compiler, _symtab, node);
        checkExpressionsForLogicalBinaryInstruction(node,lvl);

	_pf.EQ();
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_assignment_node(zu::assignment_node * const node, int lvl) {
	debug(node, lvl);
	CHECK_TYPES(_compiler, _symtab, node);

	node->rvalue()->accept(this, lvl+1);

	// If the right value is a left value, it only places
	// its address on top of the stack
	if (node->rvalue()->name().compare("index_node") == 0 || node->rvalue()->name().compare("id_node") == 0) {
		if(node->rvalue()->type()->name() == basic_type::TYPE_DOUBLE)
			_pf.DLOAD();
		else
			_pf.LOAD();
	}

	// If assigning an integer to a double... we must convert!
	if(node->type()->name() == basic_type::TYPE_DOUBLE && node->rvalue()->type()->name() == basic_type::TYPE_INT) {
		// convert top of stack to double if node has type double
		_pf.I2D();
	}

        // Duplicate right child value (based on size of left value)
	if(node->type()->name() == basic_type::TYPE_DOUBLE)
		_pf.DDUP();
	else
		_pf.DUP();

	node->lvalue()->accept(this, lvl+1);

        // Store the value!
	if(node->lvalue()->type()->name() == basic_type::TYPE_DOUBLE)
		_pf.DSTORE();
	else
		_pf.STORE();
}

//---------------------------------------------------------------------------

//void zu::postfix_writer::do_program_node(zu::program_node * const node, int lvl) {
//  // Note that Zu doesn't have functions. Thus, it doesn't need
//  // a function node. However, it must start in the main function.
//  // The ProgramNode (representing the whole program) doubles as a
//  // main function node.
//
//  // generate the main function (RTS mandates that its name be "_main")
//  _pf.TEXT();
//  _pf.ALIGN();
//  _pf.GLOBAL("_main", _pf.FUNC());
//  _pf.LABEL("_main");
//  _pf.ENTER(0);  // Zu doesn't implement local variables
//
//  node->statements()->accept(this, lvl);
//
//  // end the main function
//  _pf.INT(0);
//  _pf.POP();
//  _pf.LEAVE();
//  _pf.RET();
//
//  // these are just a few library function imports
//  _pf.EXTERN("readi");
//  _pf.EXTERN("printi");
//  _pf.EXTERN("prints");
//  _pf.EXTERN("println");
//}

void zu::postfix_writer::do_function_declaration_node(zu::function_declaration_node * const node, int lvl){
	debug(node, lvl);
	CHECK_TYPES(_compiler, _symtab, node);
}

void zu::postfix_writer::do_function_body_node(zu::function_body_node * const node, int lvl){
	debug(node, lvl);
	CHECK_TYPES(_compiler, _symtab, node);
	int dec_size = 0;
	//node->function_declaration()->accept(this, lvl+1);

	_symtab.push();
	_function_context = true;
	_local_arg_offset = 8;
	_local_dec_offset = 0;

	_pf.TEXT();

	if(node->isPublic())
		_pf.GLOBAL(zuFunctionName(node->identifier()), _pf.FUNC());

	_pf.ALIGN();
	_pf.LABEL(zuFunctionName(node->identifier()));

	if (node->block()->declarations())
		for (size_t i=0; i < node->block()->declarations()->size(); i++)
			dec_size += ((zu::variable_node*)node->block()->declarations()->node(i))->zu_type()->size();

	_pf.ENTER(dec_size);

	node->block()->accept(this, lvl+1);

	_pf.LABEL(mklbl(_function_return_lbl = ++_lbl));

	if(node->type()->name() != basic_type::TYPE_VOID) {
		int return_offset = 0 - node->type()->size();
		_pf.LOCV(return_offset); // put return value on stack
		_pf.POP(); // pop value from stack
	}

	_pf.LEAVE();
	_pf.RET();
	_symtab.pop();

	if (node->identifier() == "zu") {
		_pf.EXTERN("readi");
		_pf.EXTERN("readd");
		_pf.EXTERN("printi");
		_pf.EXTERN("printd");
		_pf.EXTERN("prints");
		_pf.EXTERN("println");
	}
	_function_context = false;
}

void zu::postfix_writer::do_function_call_node(zu::function_call_node * const node, int lvl){
	debug(node, lvl);
	CHECK_TYPES(_compiler, _symtab, node);
	int arg_size = 0;

	if (node->args())
		for (size_t i=0; i < node->args()->size(); i++)
			arg_size += ((zu::variable_node*)node->args()->node(i))->zu_type()->size();

	node->args()->accept(this, lvl+1);

	_pf.CALL(zuFunctionName(node->identifier())); // call function
	_pf.TRASH(arg_size); // remove arguments from the stack

	std::shared_ptr<zu::symbol> s = _symtab.find(node->identifier());
	if (s->type()->name() == basic_type::TYPE_INT || s->type()->name() == basic_type::TYPE_DOUBLE || s->type()->name() == basic_type::TYPE_STRING)
		_pf.PUSH(); // allocate ret val
	else if (s->type()->name() == basic_type::TYPE_DOUBLE)
		_pf.DPUSH(); // allocate double val
	// else it must be void
}

void zu::postfix_writer::do_block_node(zu::block_node * const node, int lvl){
	debug(node, lvl);
	_symtab.push();

	if(node->declarations() != NULL)
		node->declarations()->accept(this, lvl+1);
	if(node->instructions() != NULL)
		node->instructions()->accept(this, lvl+1);

	_symtab.pop();
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_evaluation_node(zu::evaluation_node * const node, int lvl) {
	debug(node, lvl);
	CHECK_TYPES(_compiler, _symtab, node);

	node->argument()->accept(this, lvl); // determine the value

	if (node->argument()->type()->name() == basic_type::TYPE_INT)
		_pf.TRASH(4); // delete the evaluated value
	else if (node->argument()->type()->name() == basic_type::TYPE_STRING)
		_pf.TRASH(4); // delete the evaluated value's address
	else if (node->argument()->type()->name() == basic_type::TYPE_DOUBLE)
		_pf.TRASH(8); // delete the evaluated value
	else if (node->argument()->type()->name() == basic_type::TYPE_POINTER)
		_pf.TRASH(4); // delete the evaluated
	else {
		std::cerr << "ERROR: CANNOT HAPPEN!" << std::endl;
		exit(1);
	}
}

void zu::postfix_writer::do_print_node(zu::print_node * const node, int lvl) {
	debug(node, lvl);
	CHECK_TYPES(_compiler, _symtab, node);

	node->argument()->accept(this, lvl); // determine the value to print
	if (node->argument()->name().compare("index_node") == 0 || node->argument()->name().compare("id_node") == 0)
		_pf.LOAD(); // load

	if (node->argument()->type()->name() == basic_type::TYPE_INT) {
		_pf.CALL("printi");
		_pf.TRASH(4); // delete the printed value
	}
	else if (node->argument()->type()->name() == basic_type::TYPE_DOUBLE) {
		_pf.CALL("printd");
		_pf.TRASH(4); // delete the printed value
	}
	else if (node->argument()->type()->name() == basic_type::TYPE_STRING) {
		_pf.CALL("prints");
		_pf.TRASH(4); // delete the printed value's address
	}
	else {
		std::cerr << "ERROR: trying to print unprintable value!" << std::endl; // invalid types, should be handled by CHECK_TYPES
		exit(1);
	}

	if (node->newLine())
		_pf.CALL("println"); // print a newline
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_read_node(zu::read_node * const node, int lvl) {
	/* TODO */
  //CHECK_TYPES(_compiler, _symtab, node);
  //_pf.CALL("readi");
  //_pf.PUSH();
  //node->argument()->accept(this, lvl);
  //_pf.STORE();
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_for_node(zu::for_node * const node, int lvl) {
	debug(node, lvl);
	CHECK_TYPES(_compiler, _symtab, node);

	// Labels
	std::string L_cond = mklbl(++_lbl);
	std::string L_end = mklbl(++_lbl);
	std::string L_step = mklbl(++_lbl);

	struct zu::labels l = zu::labels(L_step, L_end);
	_labels.push_back(l);

	node->init()->accept(this, lvl); // initial declaration

	_pf.ALIGN();
	_pf.LABEL(L_cond);
	node->test()->accept(this, lvl); // evaluate condition

	_pf.JZ(L_end); // end for loop if condition is false

	node->block()->accept(this, lvl+1);

	_pf.ALIGN();
	_pf.LABEL(L_step);
	node->step()->accept(this, lvl); // step
	_pf.JMP(L_cond); // loop

	_pf.ALIGN();
	_pf.LABEL(L_end);
	_labels.pop_back();
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_if_node(zu::if_node * const node, int lvl) {
	debug(node, lvl);
	CHECK_TYPES(_compiler, _symtab, node);
	int lbl1;

	node->condition()->accept(this, lvl);
	_pf.JZ(mklbl(lbl1 = ++_lbl));

	node->block()->accept(this, lvl+1);
	_pf.LABEL(mklbl(lbl1));
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_if_else_node(zu::if_else_node * const node, int lvl) {
	debug(node, lvl);
	CHECK_TYPES(_compiler, _symtab, node);
	int lbl1, lbl2;

	node->condition()->accept(this, lvl);
	_pf.JZ(mklbl(lbl1 = ++_lbl));

	node->thenblock()->accept(this, lvl+1);
	_pf.JMP(mklbl(lbl2 = ++_lbl));
	_pf.LABEL(mklbl(lbl1));

	node->elseblock()->accept(this, lvl+1);
	_pf.LABEL(mklbl(lbl1 = lbl2));
}

void zu::postfix_writer::do_return_node(zu::return_node * const node, int lvl) {
	debug(node, lvl);
	_pf.JMP(mklbl(_function_return_lbl));  // jump to the end of the function body
}

void zu::postfix_writer::do_continue_node(zu::continue_node * const node, int lvl) {
	debug(node, lvl);
	struct zu::labels l = _labels.back();
	_pf.JMP(l.continue_label); // loop
}

void zu::postfix_writer::do_break_node(zu::break_node * const node, int lvl) {
	debug(node, lvl);
	struct zu::labels l = _labels.back();
	_pf.JMP(l.end_label); // loop
}

