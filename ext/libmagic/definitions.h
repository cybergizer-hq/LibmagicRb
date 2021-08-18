#define RB_UNWRAP(cookie) \
	magic_t *cookie ; \
	TypedData_Get_Struct(self, magic_t, &fileType, cookie) ; \
	if(!*cookie) rb_raise(rb_eFileClosedError, "Magic cookie already closed") ;

#define RB_UNWRAP_OPEN(cookie) \
	magic_t *cookie ; \
	TypedData_Get_Struct(self, magic_t, &fileType, cookie) ;
