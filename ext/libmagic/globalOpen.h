VALUE _closeGlobal_(volatile VALUE self) {
	RB_UNWRAP(cookie) ;

	magic_close(*cookie) ;
	*cookie = NULL ;
	rb_ivar_set(self, rb_intern("@closed"), Qtrue) ;
	return self ;
}

VALUE _loadGlobal_(volatile VALUE self, volatile VALUE dbPath) {
	char *databasePath = StringValuePtr(dbPath) ;

	// Check if the database is a valid file or not
	// Raises ruby error which will return.
	RB_UNWRAP(cookie) ;

	magic_validate_db(*cookie, databasePath) ;
	magic_load(cookie, databasePath) ;

	return self ;
}

VALUE _checkGlobal_(volatile VALUE self) {
	RB_UNWRAP(cookie) ;

	// Database path
	VALUE db = rb_iv_get(self, "@db") ;
	char *database = StringValuePtr(db) ;

	// File path
	VALUE f = rb_iv_get(self, "@file") ;
	char *file = StringValuePtr(f) ;

	magic_validate_db(*cookie, database) ;
	magic_load(*cookie, database) ;

	fileReadable(file) ;
	const char *mt = magic_file(*cookie, file) ;

	return mt ? rb_str_new_cstr(mt) : Qnil ;
}

VALUE _getParamGlobal_(volatile VALUE self, volatile VALUE param) {
	RB_UNWRAP(cookie) ;

	unsigned int _param = NUM2UINT(param) ;
	unsigned long value ;

	int status = magic_getparam(*cookie, _param, &value) ;
	if (status) return Qnil ;
	return ULONG2NUM(value) ;
}

VALUE _setParamGlobal_(volatile VALUE self, volatile VALUE param, volatile VALUE paramVal) {
	unsigned int _param = NUM2UINT(param) ;
	unsigned long _paramVal = NUM2ULONG(paramVal) ;

	RB_UNWRAP(cookie) ;

	unsigned long value ;
	magic_setparam(*cookie, _param, &_paramVal) ;

	int status = magic_getparam(*cookie, _param, &value) ;

	if (status) return Qnil ;
	return ULONG2NUM((int)value) ;
}

VALUE _bufferGlobal_(volatile VALUE self, volatile VALUE string) {
	RB_UNWRAP(cookie) ;

	char *buffer = StringValuePtr(string) ;
	const char *buf = magic_buffer(*cookie, buffer, sizeof(buffer)) ;

	return rb_str_new_cstr(buf) ;
}

VALUE _listGlobal_(volatile VALUE self) {
	RB_UNWRAP(cookie) ;

	VALUE db = rb_iv_get(self, "@db") ;
	char *database = StringValuePtr(db) ;

	int status = magic_list(*cookie, database) ;
	return INT2FIX(status) ;
}
