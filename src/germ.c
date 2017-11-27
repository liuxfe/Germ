/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "germ.h"

struct tCodeStringMap{
	uint  code;
	char* str;
};
struct tCodeStringMap keyWordMap[]={
	{ TKw_package,  "package" },
	{ TKw_import,   "import"  },
	{ TKw_as,       "as"      },
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
	{ TKw_bool,     "bool"    },
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
struct tCodeStringMap resWordMap[]={
	{ TRw_true,     "true"    },
	{ TRw_false,    "false"   },
	{ TRw_NULL,     "NULL"    },
	{ TRw___FILE__, "__FILE__"},
	{ TRw___LINE__, "__LINE__"},
	{ TRw___DATA__, "__DATE__"},
	{ TRw___TIME__, "__TIME__"},
	{ 0, NULL}
};

// 给关键字够建符号表，并将关键字字符串插入到字符串散列表中
void initKeyWordSymbol(){
	String* string;
	Symbol* symbol;
	struct tCodeStringMap* tmp;

	for(tmp=keyWordMap; tmp->code; tmp++){
		string= storeString(tmp->str, strlen(tmp->str));
		symbol = newSymbol(ST_KeyWord);
		string->symbol = symbol;
		symbol->sID = string;
		symbol->sValue.i = tmp->code;
	}
}

void initResWordSymbol(){
	String* string;
	Symbol* symbol;
	struct tCodeStringMap* tmp;

	for(tmp=resWordMap; tmp->code; tmp++){
		string= storeString(tmp->str, strlen(tmp->str));
		symbol = newSymbol(ST_ResWord);
		string->symbol = symbol;
		symbol->sID = string;
		symbol->sValue.i = tmp->code;
	}
}

int doComplie(char* file){
	Token* tlist = scanFile(file);
	except(&tlist, TokenStart);
	PackageStmt* st = parsePackageStmt(&tlist);
	printPackageStmt(st);

	return 0;
}

int main(int argc, char* argv[]){
	FILE* in;
	FILE* out = stdout;

	if(argc != 2){
		printf("Usage: germ <source-file>\n");
		exit(-1);
	}

	setvbuf(out, NULL, _IONBF, 0);

	initKeyWordSymbol();
	initResWordSymbol();
	return doComplie(argv[1]);
}