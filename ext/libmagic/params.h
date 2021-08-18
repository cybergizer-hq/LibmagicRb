void params(volatile VALUE _module_) {
	rb_define_const(_module_, "MAGIC_PARAM_INDIR_MAX", UINT2NUM(MAGIC_PARAM_INDIR_MAX)) ;
	rb_define_const(_module_, "MAGIC_PARAM_NAME_MAX", UINT2NUM(MAGIC_PARAM_NAME_MAX)) ;
	rb_define_const(_module_, "MAGIC_PARAM_ELF_NOTES_MAX", UINT2NUM(MAGIC_PARAM_ELF_NOTES_MAX)) ;
	rb_define_const(_module_, "MAGIC_PARAM_ELF_PHNUM_MAX", UINT2NUM(MAGIC_PARAM_ELF_PHNUM_MAX)) ;
	rb_define_const(_module_, "MAGIC_PARAM_ELF_SHNUM_MAX", UINT2NUM(MAGIC_PARAM_ELF_SHNUM_MAX)) ;
	rb_define_const(_module_, "MAGIC_PARAM_REGEX_MAX", UINT2NUM(MAGIC_PARAM_REGEX_MAX)) ;
	rb_define_const(_module_, "MAGIC_PARAM_BYTES_MAX", UINT2NUM(MAGIC_PARAM_BYTES_MAX)) ;
}

VALUE lsparams() {
	VALUE hash = rb_hash_new() ;

	rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_PARAM_INDIR_MAX")), UINT2NUM(MAGIC_PARAM_INDIR_MAX)) ;
	rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_PARAM_NAME_MAX")), UINT2NUM(MAGIC_PARAM_NAME_MAX)) ;
	rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_PARAM_ELF_NOTES_MAX")), UINT2NUM(MAGIC_PARAM_ELF_NOTES_MAX)) ;
	rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_PARAM_ELF_PHNUM_MAX")), UINT2NUM(MAGIC_PARAM_ELF_PHNUM_MAX)) ;
	rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_PARAM_ELF_SHNUM_MAX")), UINT2NUM(MAGIC_PARAM_ELF_SHNUM_MAX)) ;
	rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_PARAM_REGEX_MAX")), UINT2NUM(MAGIC_PARAM_REGEX_MAX)) ;
	rb_hash_aset(hash, ID2SYM(rb_intern("MAGIC_PARAM_BYTES_MAX")), UINT2NUM(MAGIC_PARAM_BYTES_MAX)) ;

	return hash ;
}
