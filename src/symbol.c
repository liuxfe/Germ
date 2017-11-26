/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "germ.h"

Symbol* newSymbol(uint type){
	Symbol* ret=xmalloc(sizeof(Symbol));
	ret->symType=type;
	return ret;
}

struct kwCodeWithString{
	uint  code;
	char* str;
};
static struct kwCodeWithString kwStrMap[]={
	{ TKw_package,  "package" },
	{ TKw_import,   "import"  },
	{ TKw_as,       "as"      },
	{ TKw_bool,     "bool"    },
	{ TKw_int,      "int"     },
	{ TKw_uint,     "uint"    },
	{ TKw_int8,     "int8"    },
	{ TKw_uint8,    "uint8"   },
	{ TKw_int16,    "int16"   },
	{ TKw_uint16,   "uint16"  },
	{ TKw_int32,    "int32"   },
	{ TKw_uint32,   "uint32"  },
	{ TKw_int64,    "int64"   },
	{ TKw_uint64,   "uint64"  },
	{ TKw_float,    "float"   },
	{ TKw_float32,  "float32" },
	{ TKw_float64,  "float64" },
	{ TKw_char,     "char"    },
	{ TKw_void,     "void"    },
	{ TKw_func,     "func"    },
	{ TKw_typedef,  "typedef" },
	{ TKw_struct,   "struct"  },
	{ TKw_union,    "union"   },
	{ TKw_if,       "if"      },
	{ TKw_elif,     "elif"    },
	{ TKw_else,     "else"    },
	{ TKw_switch,   "switch"  },
	{ TKw_case,     "case"    },
	{ TKw_default,  "default" },
	{ TKw_for,      "for"     },
	{ TKw_while,    "while"   },
	{ TKw_continue, "continue"},
	{ TKw_break,    "break"   },
	{ TKw_throw,    "throw"   },
	{ TKw_return,   "return"  },
	{ TKw_goto,     "goto"    },
	{ TKw_const,    "const"   },
	{ 0, NULL}
};

// 给关键字够建符号表，并将关键字字符串插入到字符串散列表中
void initKeyWordSymbol(){
	Symbol* symbol;
	struct kwCodeWithString* tmp;

	for(tmp=kwStrMap; tmp->code; tmp++){
		//symstr = insertSymStr(tmp->str, tmp->str + strlen(tmp->str));
		symbol = newSymbol(ST_KeyWord);
		//symbol->keystr = symstr;
		symbol->symValue.i = tmp->code;
		//symstr->symList = symbol;
	}
}
