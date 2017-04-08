#
# Les variables d'environnement libG3X, incG3X
# sont definies dans le fichier ~/.bashrc par le script ../install.sh
#
#compilateur
CC = gcc

CCEXT=
ifeq ($(CC),g++) #en mode debug
  CCEXT=++
endif

#compil en mode 'debug' ou optmis�e (-O2)
DBG = no

ifeq ($(DBG),yes) #en mode debug
  CFLAGS = -g -Wpointer-arith -Wall -ansi
else               #en mode normal
  CFLAGS = -O2 -ansi
endif

# assemblage des infos de lib. et inc.
lib =   $(libG3X)$(CCEXT)
# fichiers *.c locaux
src = src/
# fichiers *.h locaux et lib.
inc = -I./include $(incG3X)

exec = g3x_skeleton g3x_example demo_scene3D g3x_solaire g3x_geometrics_forms g3x_test

all : $(exec) clean

# r�gle g�n�rique de cr�ation de xxx.o � partir de src/xxx.c
%.o : $(src)%.c
	@echo "module $@"
	@$(CC) $(CFLAGS) $(inc) -c $< -o $@
	@echo "------------------------"

# r�gle g�n�rique de cr�ation de l'executable xxx � partir de src/xxx.c (1 seul module)
% : %.o
	@echo "assemblage [$^]->$@"
	@$(CC) $^ $(lib) -o $@
	@echo "------------------------"

.PHONY : clean cleanall ?

# informations sur les param�tres de compilation
? :
	@echo "---------compilation informations----------"
	@echo "  processor      : $(PROCBIT)"
	@echo "  compiler       : $(CC)"
	@echo "  options        : $(CFLAGS)"
	@echo "  lib g3x/OpenGl : $(lib)"
	@echo "  headers        : $(incG3X)"
clean :
	@rm -f *.o
cleanall :
	@rm -f *.o $(exec) *~ */*~
