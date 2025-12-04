CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = programme
DISTDIR = dist

# Fichiers objets dans dist/
OBJS = $(DISTDIR)/principal.o $(DISTDIR)/circonference.o $(DISTDIR)/surface.o

# Règle par défaut
all: $(DISTDIR) $(DISTDIR)/$(TARGET)

# Créer le répertoire dist s'il n'existe pas
$(DISTDIR):
	mkdir -p $(DISTDIR)

# Lier tous les objets
$(DISTDIR)/$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -lm

# Compiler chaque fichier .c en .o dans dist/
$(DISTDIR)/%.o: %.c pi.h
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyer
clean:
	rm -rf $(DISTDIR)

# Recompiler
rebuild: clean all

.PHONY: all clean rebuild