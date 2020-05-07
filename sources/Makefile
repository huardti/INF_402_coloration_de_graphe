# Paths
DSRC = src
DOBJ = obj
DBIN = bin
 
# Compiler flags
CFLAGS = -g -Wall -Wextra #-D_DEBUG
 
# Commands
CC = gcc -c $(CFLAGS)
LK = gcc
RM = del
 
# Project list conv
OBJSC =      \
$(DOBJ)/main_conversion.o  \
$(DOBJ)/option.o   \
$(DOBJ)/graphe.o   \
$(DOBJ)/dimacs_w.o   \


# Project list Aff
OBJSA =      \
$(DOBJ)/main_affichage.o  \
$(DOBJ)/option.o   \
$(DOBJ)/graphe.o   \
$(DOBJ)/bmp.o   \
$(DOBJ)/ecrire_graphe.o \
 
#Rebuild all target
all: $(DBIN)/DIMACS_conversion $(DBIN)/affichage
 
# main target (OBJS + init code + library)
$(DBIN)/DIMACS_conversion: $(OBJSC)
	@echo "============================================="
	@echo "DIMACS_conversion"
	$(LK) -o $(DBIN)/DIMACS_conversion $(OBJSC)
	@echo "============================================="

$(DBIN)/affichage: $(OBJSA)
	@echo "============================================="
	@echo "affichage"
	$(LK) -o $(DBIN)/affichage $(OBJSA) -lm
	@echo "============================================="
 
# objects
 
# The option.c file
$(DOBJ)/option.o : $(DSRC)/option.c $(DSRC)/option.h
	@echo "============================================="
	@echo "option.o"
	$(CC) $(DSRC)/option.c -o $(DOBJ)/option.o
	@echo "============================================="

# The graphe.c file
$(DOBJ)/graphe.o : $(DSRC)/graphe.c $(DSRC)/graphe.h
	@echo "============================================="
	@echo "graphe.o"
	$(CC) $(DSRC)/graphe.c -o $(DOBJ)/graphe.o
	@echo "============================================="

# The dimacs_w.c file
$(DOBJ)/dimacs_w.o : $(DSRC)/dimacs_w.c $(DSRC)/dimacs_w.h
	@echo "============================================="
	@echo "dimac_w.o"
	$(CC) $(DSRC)/dimacs_w.c -o $(DOBJ)/dimacs_w.o
	@echo "============================================="

# The bmp.c file
$(DOBJ)/bmp.o : $(DSRC)/bmp.c $(DSRC)/bmp.h
	@echo "============================================="
	@echo "bmp.o"
	$(CC) $(DSRC)/bmp.c -o $(DOBJ)/bmp.o
	@echo "============================================="

# The ecrire_graphe.c file
$(DOBJ)/ecrire_graphe.o : $(DSRC)/ecrire_graphe.c $(DSRC)/ecrire_graphe.h $(DSRC)/bmp.h
	@echo "============================================="
	@echo "ecrire_graphe.o"
	$(CC) $(DSRC)/ecrire_graphe.c -o $(DOBJ)/ecrire_graphe.o
	@echo "============================================="
 
# The main_conversion.c file
$(DOBJ)/main_conversion.o : $(DSRC)/main_conversion.c $(DSRC)/option.h $(DSRC)/graphe.h $(DSRC)/dimacs_w.h
	@echo "============================================="
	@echo "main_conversion.o"
	$(CC) $(DSRC)/main_conversion.c -o $(DOBJ)/main_conversion.o
	@echo "============================================="

# The main_affichage.c file
$(DOBJ)/main_affichage.o : $(DSRC)/main_affichage.c $(DSRC)/option.h $(DSRC)/graphe.h $(DSRC)/bmp.h $(DSRC)/ecrire_graphe.h
	@echo "============================================="
	@echo "main_affichage.o"
	$(CC) $(DSRC)/main_affichage.c -o $(DOBJ)/main_affichage.o
	@echo "============================================="

# Clean all target
clean:
	rm $(DOBJ)/*.o
	rm $(DBIN)/DIMACS_conversion $(DBIN)/affichage