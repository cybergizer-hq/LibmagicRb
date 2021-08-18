void params(volatile VALUE rb_klass) {
	rb_define_const(rb_klass, "MAGIC_PARAM_INDIR_MAX", UINT2NUM(MAGIC_PARAM_INDIR_MAX)) ;
	rb_define_const(rb_klass, "MAGIC_PARAM_NAME_MAX", UINT2NUM(MAGIC_PARAM_NAME_MAX)) ;
	rb_define_const(rb_klass, "MAGIC_PARAM_ELF_NOTES_MAX", UINT2NUM(MAGIC_PARAM_ELF_NOTES_MAX)) ;
	rb_define_const(rb_klass, "MAGIC_PARAM_ELF_PHNUM_MAX", UINT2NUM(MAGIC_PARAM_ELF_PHNUM_MAX)) ;
	rb_define_const(rb_klass, "MAGIC_PARAM_ELF_SHNUM_MAX", UINT2NUM(MAGIC_PARAM_ELF_SHNUM_MAX)) ;
	rb_define_const(rb_klass, "MAGIC_PARAM_REGEX_MAX", UINT2NUM(MAGIC_PARAM_REGEX_MAX)) ;

	#ifdef MAGIC_PARAM_BYTES_MAX
		rb_define_const(rb_klass, "MAGIC_PARAM_BYTES_MAX", UINT2NUM(MAGIC_PARAM_BYTES_MAX)) ;
	#endif
}

VALUE lsparams() {
	VALUE hash = rb_hash_new() ;

	rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_PARAM_INDIR_MAX")), UINT2NUM(MAGIC_PARAM_INDIR_MAX)) ;
	rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_PARAM_NAME_MAX")), UINT2NUM(MAGIC_PARAM_NAME_MAX)) ;
	rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_PARAM_ELF_NOTES_MAX")), UINT2NUM(MAGIC_PARAM_ELF_NOTES_MAX)) ;
	rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_PARAM_ELF_PHNUM_MAX")), UINT2NUM(MAGIC_PARAM_ELF_PHNUM_MAX)) ;
	rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_PARAM_ELF_SHNUM_MAX")), UINT2NUM(MAGIC_PARAM_ELF_SHNUM_MAX)) ;
	rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_PARAM_REGEX_MAX")), UINT2NUM(MAGIC_PARAM_REGEX_MAX)) ;

	#ifdef MAGIC_PARAM_BYTES_MAX
		rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_PARAM_BYTES_MAX")), UINT2NUM(MAGIC_PARAM_BYTES_MAX)) ;
	#endif

	return hash ;
}
