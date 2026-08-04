/*
 * Copyright 2021-2024 D'Arcy Smith.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "p101_time/time.h"
#include <p101_env/wrapper.h>

int p101_clock_getres(const struct p101_env *env, struct p101_error *err, clockid_t clock_id, struct timespec *res)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN(env, err, ret_val, -1);
    errno   = 0;
    ret_val = clock_getres(clock_id, res);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

int p101_clock_gettime(const struct p101_env *env, struct p101_error *err, clockid_t clock_id, struct timespec *tp)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN(env, err, ret_val, -1);
    errno   = 0;
    ret_val = clock_gettime(clock_id, tp);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

int p101_clock_settime(const struct p101_env *env, struct p101_error *err, clockid_t clock_id, const struct timespec *tp)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN(env, err, ret_val, -1);
    errno   = 0;
    ret_val = clock_settime(clock_id, tp);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

struct tm *p101_gmtime_r(const struct p101_env *env, struct p101_error *err, const time_t *restrict timer, struct tm *restrict result)
{
    struct tm *ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN(env, err, ret_val, NULL);
    errno   = 0;
    ret_val = gmtime_r(timer, result);

    if(ret_val == NULL)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

struct tm *p101_localtime_r(const struct p101_env *env, struct p101_error *err, const time_t *restrict timer, struct tm *restrict result)
{
    struct tm *ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN(env, err, ret_val, NULL);
    errno   = 0;
    ret_val = localtime_r(timer, result);

    if(ret_val == NULL)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

int p101_nanosleep(const struct p101_env *env, struct p101_error *err, const struct timespec *rqtp, struct timespec *rmtp)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN(env, err, ret_val, -1);
    errno   = 0;
    ret_val = nanosleep(rqtp, rmtp);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

size_t p101_strftime_l(const struct p101_env *env, struct p101_error *err, char *restrict s, size_t maxsize, const char *restrict format, const struct tm *restrict timeptr, locale_t locale)
{
    size_t ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN(env, err, ret_val, 0U);
    errno = 0;
#if defined(__GNUC__) && !defined(__clang__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wformat-nonliteral"
#endif
    ret_val = strftime_l(s, maxsize, format, timeptr, locale);
#if defined(__GNUC__) && !defined(__clang__)
    #pragma GCC diagnostic pop
#endif

    P101_WRAPPER_DONE(env);
    return ret_val;
}

void p101_tzset(const struct p101_env *env)
{
    P101_TRACE(env);
    errno = 0;
    tzset();
    P101_TRACE_EXIT(env);
}
