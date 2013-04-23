#ifndef ENUMS_DOT_H__
#define ENUMS_DOT_H__

/* From parser.h */
enum statement_type_t {
	ST_EXPRESSION,
	ST_IF,
	ST_WHILE,
	ST_RETURN,
	ST_PRINT
};

enum value_type_t {
	VT_EXPRESSION,
	VT_CNUMBER,
	VT_CSTRING,
	VT_FUNCCALL,
	VT_IDENT,
	VT_INLINE_FUNC,
	VT_INLINE_OBJ,
	VT_LIST,
	VT_LISTINDEX,
};


/* From runtime.h */
enum object_type_t {
	OBJ_BASE,
	OBJ_NUMBER,
	OBJ_STRING,
	OBJ_FUNCTION,
	OBJ_LIST,
};

/* From token.h */
enum token_type_t {
	TT_NONE       =  0,
	TT_IDENT      =  1,
	TT_NUMBER     =  2,
	TT_STRING     =  3,
	TT_EOF        =  4,
	TT_UNKNOWN    =  5,

	// binary operators
	TT_OP_AND     = 10,
	TT_OP_OR      = 11,
	TT_OP_ADD     = 12,
	TT_OP_SUB     = 13,
	TT_OP_MUL     = 14,
	TT_OP_DIV     = 15,
	TT_OP_ASSIGN  = 16,
	TT_OP_GT      = 17,
	TT_OP_LT      = 18,
	TT_OP_GTE     = 19,
	TT_OP_LTE     = 20,
	TT_OP_EQUAL   = 21,
	TT_OP_DOT     = 22,

	// unary operators
	TT_OP_UNARYSUB= 30,

	TT_OP_COMMA   = 40,
	TT_OP_POPEN   = 41,
	TT_OP_PCLOSE  = 42,
	TT_OP_BOPEN   = 43,
	TT_OP_BCLOSE  = 44,
	TT_OP_COPEN   = 45,
	TT_OP_CCLOSE  = 46,
	TT_OP_COLON   = 47,
	TT_NOP        = 50,

	// keywords
	TT_END        = 80,
	TT_IF         = 81,
	TT_WHILE      = 82,
	TT_DEF        = 83,
	TT_RETURN     = 84,
	TT_PRINT      = 85,
};


/* From seatest.c */
enum seatest_action_t
{
        SEATEST_DISPLAY_TESTS,
        SEATEST_RUN_TESTS,
        SEATEST_DO_NOTHING,
        SEATEST_DO_ABORT
};


#endif /* ENUMS_DOT_H__ */
