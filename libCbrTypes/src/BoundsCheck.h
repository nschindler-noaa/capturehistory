#ifndef BoundsCheck_H
#define BoundsCheck_H

// Bounds checking macro for Vector, Matrix, Array3D, Array4D.  It
// would have been nice to use an inline function, but it wouldn't
// report a useful line number on a failed assertion (JL 5/15/98)

#include <assert.h>
#ifndef NDEBUG
#define BOUNDSCHECKVEC(i) (assert((i < length_) && (i >= 0)))
#define BOUNDSCHECK(i,j) (assert((i < length_(j)) && (i >= 0)))
#define BOUNDSCHECKMAT0(i) (assert((i < rows_) && (i >= 0)))
#define BOUNDSCHECKMAT1(i) (assert((i < cols_) && (i >= 0)))
#endif

#endif
