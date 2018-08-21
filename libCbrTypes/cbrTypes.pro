include (../config/cbrlib.pro)

TARGET  = cbrTypes

# Input
HEADERS +=	src/Array3D.h \
		src/Array5D.h \
		src/ArrayDefs.h \
		src/BArrays.h \
		src/BoundsCheck.h \
		src/Matrix.h \
		src/MatrixOperations.h

SOURCES += src/MatrixOperations.cpp
