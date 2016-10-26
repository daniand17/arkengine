#include <assert.h>

#ifdef _DEBUG
#define ARK_ASSERT(expr, msg) assert(expr && msg)
#else
#define ARK_ASSERT(expr, msg)
#endif

