#include "p101_time/time.h"
#include <p101_env/wrapper.h>

char *p101_strptime(const struct p101_env *env, const char *restrict buf, const char *restrict format, struct tm *restrict tm)
{
    char *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = strptime(buf, format, tm);

    P101_TRACE_EXIT(env);
    return ret_val;
}
