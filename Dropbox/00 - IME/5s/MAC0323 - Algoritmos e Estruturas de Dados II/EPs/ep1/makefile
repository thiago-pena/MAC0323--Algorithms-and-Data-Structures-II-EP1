# Makefile para MAC0328 (2019).
# CodificaÃ§Ã£o: UTF-8.
# Modifique Ã  vontade!
########################################################################


# STD = c++11
STD = -std=c++11

OP1  = -Wall -Wextra -Wpedantic -Wshadow

OP2 = -Wno-unused-result -Wno-unused-function

## optimization
OPTM = -O0
# OPTM = -O2

# GDB = -g

# onde compilador deve procurar as estruturas de dados
INC = -I./bib

LM =
# LM = -lm
##  in case you use sqrt, sin, cos, etc.

# serÃ£o compilados junto com programa-cliente
BIB = \
bib/vetorDes.hpp \
bib/vetorOrd.hpp \
bib/listaDes.hpp \
bib/listaOrd.hpp \
bib/arvoreBin.hpp \
bib/treap.hpp \
bib/arvore23.hpp \
bib/arvoreRN.hpp \
bib/hashTable.hpp


VERBOSE = -v

.FORCE :

default :
	@echo "Para compilar ep1.cpp diga make ep1"
	@echo ""

% : %.c .FORCE
	@echo "-------"
	g++ -std=c++11 -Wall -g -O0 -c ep1.cpp
	g++ -Wall -g -O0 -c unit_test.cpp
	g++ -Wall -g -O0 -c util.cpp
	g++ util.o ep1.o unit_test.o -o unit_test -lm
	gcc $(STD) $(OP1) $(OP2) $(OPTM) $(INC) $< $(BIB) -o $@ $(LM)
	@echo "-------"
	@echo ""
