#
#  Makefile f�r GNU C++
#
#  Anwendung:
#
#  make      - Erzeugung des ausfuehrbaren Programms
#

#************************************************************
#
# CC: Name des C++ Compilers:
#
CC = g++
INCPATH      = ../include
LIBPATH      = ../lib
#
#************************************************************
#
# Liste der C++ SourceFiles
#
CCFILES  = main.cpp \
           $(LIBPATH)/CFileIO2.cpp \
           $(LIBPATH)/NStringTool.cpp

#************************************************************
#
# Liste der Library Files
#
LINKSTARTUP = 
LINKLIBS    =              


#************************************************************
#
# C++ Flags:
#
# -c  = nur compilieren, nicht linken
# -O2 = Optimierung: schnellen Code erzeugen
#
# Assembler-Flags:
#
# -ml = Case-Sensitiv f�r alle Symbole
#
# CCFLAGS  = -O -static-libgcc -L. -I$(INCPATH) -I$(INCSTE)
#
CCFLAGS  = -std=c++17 -O2 -I$(INCPATH)


#************************************************************
#
# Regeln zur Erzeugung eines .obj-Files aus C++ Quelldateien
# und aus Assembler-Dateien:
#
# $@ = Dateiname des Ziels
# $< = Der Name der ersten Abh�ngigkeit.
#        
.cpp.o:
	$(CC) -c $(CCFLAGS) -o$@ $<  
    

#************************************************************
#
# Liste der Objekt-Dateien
# Die Liste der Objekt-Dateien entspricht der Liste der 
# Quellcode-Dateien, nur dass die Endung .cpp durch .obj
# ersetzt wird (Ersetzungregel)
#
CCOBJECTS  = $(CCFILES:.cpp=.o)


#************************************************************
#
# Name des Ziels
#
TARGET = replaceinfile

#************************************************************
#
# Wenn make ohne Parameter gestartet wird, wird "default"
# gemacht.
#
default: $(TARGET)
#
clean:
	rm -fv *.o
	rm -fv $(LIBPATH)/*.o


install:
	cp -v $(TARGET).exe /bin


#************************************************************
#
# Regel zur Erzeugung des Targets aus den Objekt-Dateien.
#
$(TARGET): $(CCOBJECTS)
	$(CC) -s -o $(TARGET) $(CCFLAGS) $(CCOBJECTS)	
