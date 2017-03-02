
TARGET = collatz
##path to libraries:
SAFEDIR = "../safely/"
##configuration of C++ console application
include("$$SAFEDIR/consoleapp.pro")
##basic cpp conveniences
include("$$SAFEDIR/cppext.pro")

#this projects files
SOURCES += main.cpp
