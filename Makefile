#-------------------------------------------------------------------------------
# User-defined part start
#

# note: ILE RPG compilers don't support UTF-8, so we use win-1252; However ILE C supports UTF-8

# BIN_LIB is the destination library for the service program.
# The rpg modules and the binder source file are also created in BIN_LIB.
# Binder source file and rpg module can be remove with the clean step 
# (make clean).
BIN_LIB=ILESHA1
LIBLIST=$(BIN_LIB)


# The shell we use
SHELL=/QOpenSys/usr/bin/qsh

#
# The folder where the copy books for ILEsha1 will be copied to with the 
# install step (make install).
#
USRINCDIR='/usr/local/include'  

#
# User-defined part end
#-------------------------------------------------------------------------------


# system and application include folder
INCLUDE='/QIBM/include' './.' 

# CCFLAGS = C compiler parameter
CCFLAGS2=OPTION(*STDLOGMSG) OUTPUT(*NONE) OPTIMIZE(10) ENUM(*INT) TERASPACE(*YES) STGMDL(*INHERIT) SYSIFCOPT(*IFSIO) DBGVIEW(*ALL) INCDIR($(INCLUDE)) 
	
all: env compile bind

env:
	-system -q "CRTLIB $(BIN_LIB) TYPE(*TEST) TEXT('ILEsha1: sha-1 implementation ')"                                          
	-system -q "CRTBNDDIR BNDDIR($(BIN_LIB)/ILEsha1)"
	-system -q "ADDBNDDIRE BNDDIR($(BIN_LIB)/ILEsha1) OBJ((ILEsha1))"
	system "CHGATR OBJ('./*') ATR(*CCSID) VALUE(1208)"

compile: .PHONY
	system "CRTCMOD MODULE($(BIN_LIB)/sha1) SRCSTMF('sha1.c') $(CCFLAGS2) "
		
bind:
	liblist -a $(LIBLIST);\
	system -q "CRTSRCPF FILE($(BIN_LIB)/QSRVSRC) RCDLEN(112)";\
	system "CPYFRMSTMF FROMSTMF('ILEsha1.bnd') TOMBR('/QSYS.lib/$(BIN_LIB).lib/QSRVSRC.file/ILEsha1.mbr') MBROPT(*replace)";\
	system -q "DLTOBJ OBJ($(BIN_LIB)/ILEsha1) OBJTYPE(*SRVPGM)";\
	system -kpieb "CRTSRVPGM SRVPGM($(BIN_LIB)/ILEsha1) MODULE($(BIN_LIB)/sha1) OPTION(*DUPPROC) DETAIL(*BASIC) STGMDL(*INHERIT) SRCFILE($(BIN_LIB)/QSRVSRC) TEXT('ILEsha1 - sha 1 implementation')";

clean:
	-system -q "CLRLIB $(BIN_LIB)"

test: .PHONY
	cd unittests && make
	
# For vsCode 
current: env
	system "CRTCMOD MODULE($(BIN_LIB)/$(SRC)) SRCSTMF('src/$(SRC).c') $(CCFLAGS2) "

install:
	-mkdir $(USRINCDIR)/ILEsha1
	cp headers/ILEsha1.rpgle $(USRINCDIR)/ILEsha1/

.PHONY:
