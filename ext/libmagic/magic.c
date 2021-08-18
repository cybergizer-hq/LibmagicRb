#include <magic.h>
#include <stdio.h>
#include <unistd.h>
#include "ruby.h"

/*
* LibmagicRB Header files
*/
#include "modes.h"
#include "params.h"
#include "definitions.h"

/*
* Errors
*/
VALUE rb_eFileNotFoundError ;
VALUE rb_eFileNotReadableError ;
VALUE rb_eInvalidDBError ;
VALUE rb_eIsDirError ;
VALUE rb_eFileClosedError ;

// Garbage collect
void file_free(void **data) {
	if(*data) {
		magic_close(*data) ;
		*data = NULL ;
	}
	free(data) ;
}

// Filetype
static rb_data_type_t fileType = {
	.wrap_struct_name = "file",

	.function = {
		.dmark = NULL,
		.dfree = file_free,
	},

	.data = NULL,
	.flags = RUBY_TYPED_FREE_IMMEDIATELY,
} ;

#include "globalOpen.h"

#include "validations.h"

VALUE _check_(volatile VALUE obj, volatile VALUE args) {
	if(!RB_TYPE_P(args, T_HASH)) {
		rb_raise(rb_eArgError, "Expected hash as argument.") ;
	}

	// Database Path
	VALUE argDBPath = rb_hash_aref(args, ID2SYM(rb_intern("db"))) ;

	if (RB_TYPE_P(argDBPath, T_NIL)) {
		rb_raise(rb_eArgError, "Expected `db:\" key as a string, got nil instead") ;
	} else if (!RB_TYPE_P(argDBPath, T_STRING)) {
		rb_raise(rb_eArgError, "Database name must be an instance of String.") ;
	}
	char *databasePath = StringValuePtr(argDBPath) ;

	// File path
	VALUE argFilePath = rb_hash_aref(args, ID2SYM(rb_intern("file"))) ;
	if (RB_TYPE_P(argFilePath, T_NIL)) {
		rb_raise(rb_eArgError, "Expected `file:\" key as a string, got nil instead") ;
	} else if (!RB_TYPE_P(argFilePath, T_STRING)) {
		rb_raise(rb_eArgError, "Filename must be an instance of String.") ;
	}
	char *checkPath = StringValuePtr(argFilePath) ;

	// Modes
	VALUE argModes = rb_hash_aref(args, ID2SYM(rb_intern("mode"))) ;
	unsigned int modes ;
	if(RB_TYPE_P(argModes, T_NIL)) {
		modes = MAGIC_MIME | MAGIC_CHECK | MAGIC_SYMLINK ;
	} else if (!RB_TYPE_P(argModes, T_FIXNUM)) {
		rb_raise(rb_eArgError, "Modes must be an instance of Integer. Check LibmagicRb.constants() or LibmagicRb.lsmodes().") ;
	} else {
		modes = FIX2UINT(argModes) ;
	}

	// Checks
	struct magic_set *magic = magic_open(modes) ;

	// Check if the database is a valid file or not
	// Raises ruby error which will return.
	fileReadable(checkPath) ;
	magic_validate_db(magic, databasePath) ;

	magic_load(magic, databasePath) ;
	const char *mt = magic_file(magic, checkPath) ;

	VALUE retStr = rb_str_new_cstr(mt) ;
	magic_close(magic) ;

	return retStr ;
}

VALUE rb_libmagicRb_initialize(volatile VALUE self, volatile VALUE args) {
	// Database Path
	if(!RB_TYPE_P(args, T_HASH)) {
		rb_raise(rb_eArgError, "Expected hash as argument.") ;
	}

	VALUE argDBPath = rb_hash_aref(args, ID2SYM(rb_intern("db"))) ;
	if (RB_TYPE_P(argDBPath, T_NIL)) {
		rb_raise(rb_eArgError, "Expected `db:\" key as a string, got nil instead") ;
	} else if (!RB_TYPE_P(argDBPath, T_STRING)) {
		rb_raise(rb_eArgError, "Database name must be an instance of String.") ;
	}
	rb_ivar_set(self, rb_intern("@db"), argDBPath) ;

	// File path
	VALUE argFilePath = rb_hash_aref(args, ID2SYM(rb_intern("file"))) ;
	if (RB_TYPE_P(argFilePath, T_NIL)) {
		rb_raise(rb_eArgError, "Expected `file:\" key as a string, got nil instead") ;
	} else if (!RB_TYPE_P(argFilePath, T_STRING)) {
		rb_raise(rb_eArgError, "Filename must be an instance of String.") ;
	}
	rb_ivar_set(self, rb_intern("@file"), argFilePath) ;

	// Modes
	VALUE argModes = rb_hash_aref(args, ID2SYM(rb_intern("mode"))) ;
	unsigned int modes ;
	if(RB_TYPE_P(argModes, T_NIL)) {
		modes = MAGIC_MIME | MAGIC_CHECK | MAGIC_SYMLINK ;
	} else if (!RB_TYPE_P(argModes, T_FIXNUM)) {
		rb_raise(rb_eArgError, "Modes must be an instance of Integer. Check LibmagicRb.constants() or LibmagicRb.lsmodes().") ;
	} else {
		modes = FIX2UINT(argModes) ;
	}
	rb_ivar_set(self, rb_intern("@mode"), UINT2NUM(modes)) ;

	rb_ivar_set(self, rb_intern("@closed"), Qfalse) ;

	RB_UNWRAP(cookie) ;
	*cookie = magic_open(modes) ;

	return self ;
}

VALUE initAlloc(volatile VALUE self) {
	magic_t *cookie ;
	cookie = malloc(sizeof(*cookie)) ;

	return TypedData_Wrap_Struct(self, &fileType, cookie) ;
}

void Init_main() {
	rb_global_variable(&rb_eFileNotFoundError) ;
	rb_global_variable(&rb_eFileNotReadableError) ;
	rb_global_variable(&rb_eInvalidDBError) ;
	rb_global_variable(&rb_eIsDirError) ;
	rb_global_variable(&rb_eFileClosedError) ;

	/*
	* Libmagic Errors
	*/
	VALUE cLibmagicRb = rb_define_class("LibmagicRb", rb_cObject) ;

	rb_eFileNotFoundError = rb_define_class_under(cLibmagicRb, "FileNotFound", rb_eRuntimeError) ;
	rb_eFileNotReadableError = rb_define_class_under(cLibmagicRb, "FileUnreadable", rb_eRuntimeError) ;
	rb_eInvalidDBError = rb_define_class_under(cLibmagicRb, "InvalidDBError", rb_eRuntimeError) ;
	rb_eIsDirError = rb_define_class_under(cLibmagicRb, "IsDirError", rb_eRuntimeError) ;
	rb_eFileClosedError = rb_define_class_under(cLibmagicRb, "FileClosedError", rb_eRuntimeError) ;

	/*
	* Constants
	*/
	modes(cLibmagicRb) ;
	params(cLibmagicRb) ;

	char version[6] ;
	sprintf(version, "%0.2f", magic_version() / 100.0) ;
	rb_define_const(cLibmagicRb, "MAGIC_VERSION", rb_str_new_cstr(version)) ;

	/*
	* Singleton Methods
	*/
	rb_define_singleton_method(cLibmagicRb, "_check_", _check_, 1) ;

	/*
	* Instance Methods
	*/
	rb_define_alloc_func(cLibmagicRb, initAlloc) ;


	rb_define_method(cLibmagicRb, "initialize", rb_libmagicRb_initialize, 1) ;

	rb_define_attr(cLibmagicRb, "closed", 1, 0) ;

	rb_define_attr(cLibmagicRb, "file", 1, 1) ;
	rb_define_attr(cLibmagicRb, "db", 1, 1) ;

	rb_define_alias(cLibmagicRb, "closed?", "closed") ;

	rb_define_method(cLibmagicRb, "close", _closeGlobal_, 0) ;
	rb_define_method(cLibmagicRb, "load", _loadGlobal_, 1) ;

	rb_define_method(cLibmagicRb, "check", _checkGlobal_, 0) ;

	rb_define_method(cLibmagicRb, "getparam", _getParamGlobal_, 1) ;
	rb_define_method(cLibmagicRb, "setparam", _setParamGlobal_, 2) ;

	rb_define_method(cLibmagicRb, "magic_buffer", _bufferGlobal_, 1) ;
	rb_define_method(cLibmagicRb, "magic_list", _listGlobal_, 0) ;
}
