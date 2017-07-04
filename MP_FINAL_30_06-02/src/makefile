IDIR =../include
CXX=g++
CXXFLAGS=-I$(IDIR) -g

ODIR= ./obj

LIBS= -lform -lncurses -lpthread
LIBS_C = -ftest-coverage -fprofile-arcs

_DEPS = GraphicalUserInterface.h grafo.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = GraphicalUserInterface.o grafo.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(LIBS)

main: $(OBJ)
	$(CXX) $(CXXFLAGS) -o Gerenciador TelaInicial.c $(OBJ) $(LIBS)

.PHONY: teste

teste: $(OBJ)
	$(CXX) -o teste testes.cpp $(OBJ) $(CXXFLAGS) $(LIBS) 

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ 
