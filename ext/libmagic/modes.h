void modes(volatile VALUE _module_) {
     rb_define_const(_module_, "MAGIC_NONE", INT2FIX(MAGIC_NONE)) ;
     rb_define_const(_module_, "MAGIC_DEBUG", INT2FIX(MAGIC_DEBUG)) ;
     rb_define_const(_module_, "MAGIC_SYMLINK", INT2FIX(MAGIC_SYMLINK)) ;
     rb_define_const(_module_, "MAGIC_COMPRESS", INT2FIX(MAGIC_COMPRESS)) ;
     rb_define_const(_module_, "MAGIC_DEVICES", INT2FIX(MAGIC_DEVICES)) ;
     rb_define_const(_module_, "MAGIC_MIME_TYPE", INT2FIX(MAGIC_MIME_TYPE)) ;
     rb_define_const(_module_, "MAGIC_MIME_ENCODING", INT2FIX(MAGIC_MIME_ENCODING)) ;
     rb_define_const(_module_, "MAGIC_MIME", INT2FIX(MAGIC_MIME)) ;
     rb_define_const(_module_, "MAGIC_CONTINUE", INT2FIX(MAGIC_CONTINUE)) ;
     rb_define_const(_module_, "MAGIC_CHECK", INT2FIX(MAGIC_CHECK)) ;
     rb_define_const(_module_, "MAGIC_PRESERVE_ATIME", INT2FIX(MAGIC_PRESERVE_ATIME)) ;
     rb_define_const(_module_, "MAGIC_RAW", INT2FIX(MAGIC_RAW)) ;
     rb_define_const(_module_, "MAGIC_ERROR", INT2FIX(MAGIC_ERROR)) ;
     rb_define_const(_module_, "MAGIC_APPLE", INT2FIX(MAGIC_APPLE)) ;
     rb_define_const(_module_, "MAGIC_EXTENSION", INT2FIX(MAGIC_EXTENSION)) ;
     rb_define_const(_module_, "MAGIC_COMPRESS_TRANSP", INT2FIX(MAGIC_COMPRESS_TRANSP)) ;
     rb_define_const(_module_, "MAGIC_NO_CHECK_APPTYPE", INT2FIX(MAGIC_NO_CHECK_APPTYPE)) ;
     rb_define_const(_module_, "MAGIC_NO_CHECK_CDF", INT2FIX(MAGIC_NO_CHECK_CDF)) ;
     rb_define_const(_module_, "MAGIC_NO_CHECK_COMPRESS", INT2FIX(MAGIC_NO_CHECK_COMPRESS)) ;
     rb_define_const(_module_, "MAGIC_NO_CHECK_ELF", INT2FIX(MAGIC_NO_CHECK_ELF)) ;
     rb_define_const(_module_, "MAGIC_NO_CHECK_ENCODING", INT2FIX(MAGIC_NO_CHECK_ENCODING)) ;
     rb_define_const(_module_, "MAGIC_NO_CHECK_SOFT", INT2FIX(MAGIC_NO_CHECK_SOFT)) ;
     rb_define_const(_module_, "MAGIC_NO_CHECK_TAR", INT2FIX(MAGIC_NO_CHECK_TAR)) ;
     rb_define_const(_module_, "MAGIC_NO_CHECK_TEXT", INT2FIX(MAGIC_NO_CHECK_TEXT)) ;
     rb_define_const(_module_, "MAGIC_NO_CHECK_TOKENS", INT2FIX(MAGIC_NO_CHECK_TOKENS)) ;
     rb_define_const(_module_, "MAGIC_NO_CHECK_JSON", INT2FIX(MAGIC_NO_CHECK_JSON)) ;
     rb_define_const(_module_, "MAGIC_NO_CHECK_CSV", INT2FIX(MAGIC_NO_CHECK_CSV)) ;
}

VALUE lsmodes(volatile VALUE obj) {
     VALUE hash = rb_hash_new() ;

     rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_NONE")), INT2FIX(MAGIC_NONE)) ;
     rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_DEBUG")), INT2FIX(MAGIC_DEBUG)) ;
     rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_SYMLINK")), INT2FIX(MAGIC_SYMLINK)) ;
     rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_COMPRESS")), INT2FIX(MAGIC_COMPRESS)) ;
     rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_DEVICES")), INT2FIX(MAGIC_DEVICES)) ;
     rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_MIME_TYPE")), INT2FIX(MAGIC_MIME_TYPE)) ;
     rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_MIME_ENCODING")), INT2FIX(MAGIC_MIME_ENCODING)) ;
     rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_MIME")), INT2FIX(MAGIC_MIME)) ;
     rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_CONTINUE")), INT2FIX(MAGIC_CONTINUE)) ;
     rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_CHECK")), INT2FIX(MAGIC_CHECK)) ;
     rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_PRESERVE_ATIME")), INT2FIX(MAGIC_PRESERVE_ATIME)) ;
     rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_RAW")), INT2FIX(MAGIC_RAW)) ;
     rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_ERROR")), INT2FIX(MAGIC_ERROR)) ;
     rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_APPLE")), INT2FIX(MAGIC_APPLE)) ;
     rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_EXTENSION")), INT2FIX(MAGIC_EXTENSION)) ;
     rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_COMPRESS_TRANSP")), INT2FIX(MAGIC_COMPRESS_TRANSP)) ;
     rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_NO_CHECK_APPTYPE")), INT2FIX(MAGIC_NO_CHECK_APPTYPE)) ;
     rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_NO_CHECK_CDF")), INT2FIX(MAGIC_NO_CHECK_CDF)) ;
     rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_NO_CHECK_COMPRESS")), INT2FIX(MAGIC_NO_CHECK_COMPRESS)) ;
     rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_NO_CHECK_ELF")), INT2FIX(MAGIC_NO_CHECK_ELF)) ;
     rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_NO_CHECK_ENCODING")), INT2FIX(MAGIC_NO_CHECK_ENCODING)) ;
     rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_NO_CHECK_SOFT")), INT2FIX(MAGIC_NO_CHECK_SOFT)) ;
     rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_NO_CHECK_TAR")), INT2FIX(MAGIC_NO_CHECK_TAR)) ;
     rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_NO_CHECK_TEXT")), INT2FIX(MAGIC_NO_CHECK_TEXT)) ;
     rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_NO_CHECK_TOKENS")), INT2FIX(MAGIC_NO_CHECK_TOKENS)) ;
     rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_NO_CHECK_JSON")), INT2FIX(MAGIC_NO_CHECK_JSON)) ;
     rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_NO_CHECK_CSV")), INT2FIX(MAGIC_NO_CHECK_CSV)) ;

     return hash ;
}
