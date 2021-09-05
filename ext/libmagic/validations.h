void fileReadable(char *filePath) {
	if(access(filePath, F_OK)) rb_raise(rb_eFileNotFoundError, "%s", filePath) ;
	if(access(filePath, R_OK)) rb_raise(rb_eFileNotReadableError, "%s", filePath) ;
}

void magic_validate_db(magic_t cookie, char *databasePath) {
	struct stat statbuf ;

	if (stat(databasePath, &statbuf) != 0)
		rb_raise(rb_eFileNotFoundError, "%s", databasePath) ;

	if(S_ISDIR(statbuf.st_mode))
		rb_raise(rb_eIsDirError, "%s", databasePath) ;

	if(access(databasePath, R_OK)) rb_raise(rb_eFileNotReadableError, "%s", databasePath) ;

	int validFile = magic_check(cookie, databasePath) ;

	if (validFile != 0) {
		const char *err = magic_error(cookie) ;
		rb_raise(rb_eInvalidDBError, "%s (%s is not a valid magic file)", err, databasePath) ;
	}
}
