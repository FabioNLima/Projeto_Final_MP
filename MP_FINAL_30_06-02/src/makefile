IDIR =../include
CXX=g++
CXXFLAGS=-I$(IDIR) -g

ODIR= ./obj

LIBS= -lncurses -lgtest -lpthread -lgtest_main
LIBS_C = -ftest-coverage -fprofile-arcs

_DEPS = GraphicalUserInterface.hpp grafo.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = GraphicalUserInterface.o grafo.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cc $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(LIBS)

main: $(OBJ)
	$(CXX) $(CXXFLAGS) -o Gerenciador TelaInicial.cc $(OBJ) $(LIBS) $(LIBS_C)

.PHONY: teste

teste: $(OBJ)
	$(CXX) -o teste testes.cc $(OBJ) $(CXXFLAGS) $(LIBS_C) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ 
