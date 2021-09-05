/*
	Closes a magic cookie. For example:

		> cookie = LibmagicRb.new(file: '/usr/share/dict/words')
		# => #<LibmagicRb:0x00005581019fa7e0 @closed=false, @db=nil, @file="/usr/share/dict/words", @mode=1106>

		> cookie.close
		# => #<LibmagicRb:0x00005581019fa7e0 @closed=true, @db=nil, @file="/usr/share/dict/words", @mode=1106>

	Returns self.
*/

VALUE _closeGlobal_(volatile VALUE self) {
	RB_UNWRAP(cookie) ;

	magic_close(*cookie) ;
	*cookie = NULL ;
	rb_ivar_set(self, rb_intern("@closed"), Qtrue) ;
	return self ;
}

/*
	Changes the database path. For example:
		> cookie = LibmagicRb.new(file: '/usr/share/dict/words')
		# => #<LibmagicRb:0x00005581019181b0 @closed=false, @db=nil, @file="/usr/share/dict/words", @mode=1106>

		> cookie.db = '/usr/share/file/misc/magic.mgc'
		# => "/usr/share/file/misc/magic.mgc"

		> cookie.check
		# => "text/plain; charset=utf-8"

		> cookie.close
		# => #<LibmagicRb:0x00005581019181b0 @closed=true, @db="/usr/share/file/misc/magic.mgc", @file="/usr/share/dict/words", @mode=1106>

	Returns self.
*/

VALUE _loadGlobal_(volatile VALUE self, volatile VALUE dbPath) {
	char *databasePath = NULL ;

	if (RB_TYPE_P(dbPath, T_STRING)) {
		databasePath = StringValuePtr(dbPath) ;
		rb_iv_set(self, "@db", dbPath) ;
	} else if(RB_TYPE_P(dbPath, T_STRING)) {
		rb_iv_set(self, "@db", Qnil) ;
	}

	// Check if the database is a valid file or not
	// Raises ruby error which will return.
	RB_UNWRAP(cookie) ;

	if(databasePath) magic_validate_db(*cookie, databasePath) ;
	magic_load(*cookie, databasePath) ;

	return self ;
}

/*
	Check a file with the magic database. For example:
		> cookie = LibmagicRb.new(file: '/usr/share/dict/words')
		# => #<LibmagicRb:0x00005581019181b0 @closed=false, @db=nil, @file="/usr/share/dict/words", @mode=1106>

		> cookie.check
		# => "text/plain; charset=utf-8"

		> cookie.close
		# => #<LibmagicRb:0x00005581019181b0 @closed=true, @db="/usr/share/file/misc/magic.mgc", @file="/usr/share/dict/words", @mode=1106>

		Returns String or nil.
*/

VALUE _checkGlobal_(volatile VALUE self) {
	RB_UNWRAP(cookie) ;

	// Database path
	VALUE db = rb_iv_get(self, "@db") ;

	char *database = NULL ;
	if(RB_TYPE_P(db, T_STRING)) {
		database = StringValuePtr(db) ;
	}

	// File path
	VALUE f = rb_iv_get(self, "@file") ;
	char *file = StringValuePtr(f) ;

	if(database) magic_validate_db(*cookie, database) ;
	magic_load(*cookie, database) ;

	fileReadable(file) ;
	const char *mt = magic_file(*cookie, file) ;

	return mt ? rb_str_new_cstr(mt) : Qnil ;
}

/*
	Get parameters for a cookie. For example:
		cookie = LibmagicRb.new(file: '/usr/share/dict/words')
		# => #<LibmagicRb:0x00005581018f35e0 @closed=false, @db=nil, @file="/usr/share/dict/words", @mode=1106>

		> cookie.getparam(LibmagicRb::MAGIC_PARAM_NAME_MAX)
		# => 50

		> cookie.close
		# => #<LibmagicRb:0x00005581018f35e0 @closed=true, @db=nil, @file="/usr/share/dict/words", @mode=1106>
*/

VALUE _getParamGlobal_(volatile VALUE self, volatile VALUE param) {
	#if MAGIC_VERSION > 525
		RB_UNWRAP(cookie) ;

		unsigned int _param = NUM2UINT(param) ;
		unsigned long value ;

		int status = magic_getparam(*cookie, _param, &value) ;
		if (status) return Qnil ;
		return ULONG2NUM(value) ;
	#else
		return Qnil ;
	#endif
}

/*
	Sets parameter for a cookie. For example:

		> cookie = LibmagicRb.new(file: '/usr/share/dict/words')
		# => #<LibmagicRb:0x00005581019f9840 @closed=false, @db=nil, @file="/usr/share/dict/words", @mode=1106>

		> cookie.getparam(LibmagicRb::MAGIC_PARAM_NAME_MAX)
		=> 50

		> cookie.setparam(LibmagicRb::MAGIC_PARAM_NAME_MAX, 101)
		# => 101

		> cookie.getparam(LibmagicRb::MAGIC_PARAM_NAME_MAX)
		# => 101

		> cookie.close
		# => #<LibmagicRb:0x00005581019f9840 @closed=true, @db=nil, @file="/usr/share/dict/words", @mode=1106>

	Returns Integer or nil on failure.
*/

VALUE _setParamGlobal_(volatile VALUE self, volatile VALUE param, volatile VALUE paramVal) {
	#if MAGIC_VERSION > 525
		unsigned int _param = NUM2UINT(param) ;
		unsigned long _paramVal = NUM2ULONG(paramVal) ;

		RB_UNWRAP(cookie) ;

		unsigned long value ;
		magic_setparam(*cookie, _param, &_paramVal) ;

		int status = magic_getparam(*cookie, _param, &value) ;
		if (status) return Qnil ;

		return ULONG2NUM((int)value) ;
	#else
		return Qnil ;
	#endif
}

/*
	Returns a textual description of the contents of the buffer argument with length bytes size.

	For example:

		> cookie = LibmagicRb.new(file: '.')
		# => #<LibmagicRb:0x00005582de0d1bf8 @closed=false, @db=nil, @file=".", @mode=1106>

		> cookie.magic_buffer("%PDF-1.3\r\n")
		# => "application/pdf; charset=us-ascii"

		> cookie.close
		# => #<LibmagicRb:0x00005582de0d1bf8 @closed=true, @db=nil, @file=".", @mode=1106>

	Note that it automatically loads the database.

	Returns either String or nil.
*/

VALUE _bufferGlobal_(volatile VALUE self, volatile VALUE string) {
	RB_UNWRAP(cookie) ;

	VALUE db = rb_iv_get(self, "@db") ;

	char *database = NULL ;
	if(RB_TYPE_P(db, T_STRING)) {
		database = StringValuePtr(db) ;
	}

	if(database) magic_validate_db(*cookie, database) ;
	magic_load(*cookie, database) ;

	char *buffer = StringValuePtr(string) ;
	const char *buf = magic_buffer(*cookie, buffer, strlen(buffer)) ;

	return buf ? rb_str_new_cstr(buf) : Qnil ;
}

/*
	Dumps all magic entries in a human
	readable format, dumping first the entries that are matched against
	binary files and then the ones that match text files.

	For example:


		> cookie = LibmagicRb.new(file: '.')
		# => #<LibmagicRb:0x000055cf280a9b30 @closed=false, @db=nil, @file=".", @mode=1106>

		> cookie.magic_list
		Set 0:
		Binary patterns:
		Strength = 500@47: Biosig/Brainvision Marker file [biosig/brainvision]
		Strength = 490@122: Biosig/TMSiLOG [biosig/tmsilog]
		Strength = 461@127: Biosig/SYNERGY [biosig/synergy]
		Strength = 460@46: Biosig/Brainvision V-Amp file []
		Strength = 410@45: Biosig/Brainvision data file []
		Strength = 380@6: OpenSSH private key []
		Strength = 370@1266: Novell message librarian data []
		.
		.
		.
		# => 0

		> cookie.close
		=> #<LibmagicRb:0x000055cf280a9b30 @closed=true, @db=nil, @file=".", @mode=1106>
*/

VALUE _listGlobal_(volatile VALUE self) {
	RB_UNWRAP(cookie) ;

	VALUE db = rb_iv_get(self, "@db") ;

	char *database = NULL ;
	if (RB_TYPE_P(db, T_STRING)) {
		database = StringValuePtr(db) ;
	}

	if(database) magic_validate_db(*cookie, database) ;
	int status = magic_list(*cookie, database) ;

	return INT2FIX(status) ;
}

/*
	Set flags/modes for a cookie (not to be confused with params).
	It's same setting mode through the setter cookie.mode = mode.

	For example:

		> cookie = LibmagicRb.new(file: '.')
		# => #<LibmagicRb:0x00005583732e1070 @closed=false, @db=nil, @file=".", @mode=1106>

		> cookie.check
		# => "inode/directory; charset=binary"

		> cookie.setflags(LibmagicRb::MAGIC_RAW)
		# => 256

		> cookie.check
		# => "directory"

		#### Similarly you can also do this ####

		> cookie.mode = LibmagicRb::MAGIC_MIME
		# => 1040

		> cookie.check
		# => "inode/directory; charset=binary"

		#### Close the cookie when done ####
		> cookie.close
		# => #<LibmagicRb:0x00005583732e1070 @closed=true, @db=nil, @file=".", @mode=256>
*/

VALUE _setflagsGlobal_(volatile VALUE self, volatile VALUE flags) {
	unsigned int flag = NUM2UINT(flags) ;

	RB_UNWRAP(cookie) ;
	int status = magic_setflags(*cookie, flag) ;

	if (status) {
		return Qnil ;
	} else {
		rb_ivar_set(self, rb_intern("@mode"), flags) ;
		return flags ;
	}
}
