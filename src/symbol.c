/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "germ.h"

#define HASH_MAX 17
symStr* hashTable[HASH_MAX];

/* ELF_hash */
uint hashValue(char* start, char* end){
	uint h = 0;
	uint x = 0;

	while(start < end){
		h = *start + h<< 4;
		if( h & 0xF0000000){
			x = h >> 24;
			h ^= x;
			h &= ~x;
		}
		start++;
	}
	return h;
}

symStr* newSymStr(char* start, char* end, uint hash){
	symStr* ret = malloc(sizeof(symStr) + (int)(end - start + 1));
	char* p = ret->data;
	
	while( start < end ){
		*p++ = *start++;
	}
	*p = '\0';

	ret->hashKey = hash;
	ret->symList = null;

	return ret;
}

symStr* lookUpSymStr(char* start, char* end, uint hash){
	symStr* find;

	for(find = hashTable[hash%HASH_MAX]; find; find = find->hashNext){
		if(find->hashKey != hash){
			continue;
		}
		if(xstrcmp(find->data, start, end)){
			break;
		}
	}
	return find;
}

/* 如果字符串已经在散列表中，则直接返回
   如果不在散列表中，新建一个字符串，插入到符号表中 */
symStr* insertSymStr(char* start, char* end){
	uint hash=hashValue(start, end);
	symStr* ret;

	ret = lookUpSymStr(start, end, hash);
	if( ret ){
		return ret;
	}

	ret = newSymStr(start, end, hash);
	ret->hashNext= hashTable[hash%HASH_MAX];
	hashTable[hash%HASH_MAX] = ret;
	return ret;
}

void printHashTable(){
	int i;
	symStr* tmp;

	printf("--------------Dump String HashTable -------------------\n");
	for(i=0; i<HASH_MAX;i++){
		printf("---hash:%d---\n",i);
		tmp = hashTable[i];
		while(tmp){
			printf("%s\n", tmp->data);
			tmp = tmp->hashNext;
		}
	}
	printf("---------------------------------------------------------\n");
}

Symbol* newSymbol(uint type){
	Symbol* ret;

	ret=xmalloc(sizeof(Symbol));
	memset(ret, 0, sizeof(Symbol));
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
	symStr* symstr;
	Symbol* symbol;
	struct kwCodeWithString* tmp;

	for(tmp=kwStrMap; tmp->code; tmp++){
		symstr = insertSymStr(tmp->str, tmp->str + strlen(tmp->str));
		symbol = newSymbol(ST_KeyWord);
		//symbol->keystr = symstr;
		symbol->symValue.i = tmp->code;
		symstr->symList = symbol;
	}
}
