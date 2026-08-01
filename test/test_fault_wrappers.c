#include <errno.h>
#include <p101_env/env.h>
#include <p101_error/error.h>
#include <p101_time/time.h>
#include <stdio.h>
#include <stdlib.h>

static int failures;

#define EXPECT(condition)                                                                                                                                                                                                                                          \
    do                                                                                                                                                                                                                                                             \
    {                                                                                                                                                                                                                                                              \
        if(!(condition))                                                                                                                                                                                                                                           \
        {                                                                                                                                                                                                                                                          \
            fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #condition);                                                                                                                                                                                   \
            failures++;                                                                                                                                                                                                                                            \
        }                                                                                                                                                                                                                                                          \
    } while(0)

struct fault_state
{
    int checks;
    int errnum;
};

static int fail_next_call(const struct p101_env *env, const char *call_name, void *user_data)
{
    struct fault_state *state;

    (void)env;
    (void)call_name;
    state = user_data;
    state->checks++;
    return state->errnum;
}

/* P101_TEST_CASE(p101_clock_getres) */
static void test_p101_clock_getres(struct p101_env *env, struct p101_error *err)
{
#ifdef __linux__
    static const int errors[] = {EACCES, EFAULT, EINVAL, ENODEV, ENOTSUP, EOVERFLOW, EPERM};
#elif defined(__APPLE__)
    static const int errors[] = {EFAULT, EINVAL, EPERM};
#elif defined(__FreeBSD__)
    static const int errors[] = {EINVAL, EPERM};
#else
    static const int errors[] = {EINVAL, EOVERFLOW, EPERM};
#endif

    for(size_t index = 0U; index < sizeof(errors) / sizeof(errors[0]); index++)
    {
        struct fault_state state = {0, errors[index]};

        p101_env_set_fault_injector(env, fail_next_call, &state);
        int result = p101_clock_getres(env, err, 0, NULL);
        (void)result;
        EXPECT(state.checks == 1);
        EXPECT(p101_error_is_errno(err, state.errnum));
        p101_error_reset(err);
    }
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_clock_gettime) */
static void test_p101_clock_gettime(struct p101_env *env, struct p101_error *err)
{
#ifdef __linux__
    static const int errors[] = {EACCES, EFAULT, EINVAL, ENODEV, ENOTSUP, EOVERFLOW, EPERM};
#elif defined(__APPLE__)
    static const int errors[] = {EFAULT, EINVAL, EPERM};
#elif defined(__FreeBSD__)
    static const int errors[] = {EINVAL, EPERM};
#else
    static const int errors[] = {EINVAL, EOVERFLOW, EPERM};
#endif

    for(size_t index = 0U; index < sizeof(errors) / sizeof(errors[0]); index++)
    {
        struct fault_state state = {0, errors[index]};

        p101_env_set_fault_injector(env, fail_next_call, &state);
        int result = p101_clock_gettime(env, err, 0, NULL);
        (void)result;
        EXPECT(state.checks == 1);
        EXPECT(p101_error_is_errno(err, state.errnum));
        p101_error_reset(err);
    }
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_clock_settime) */
static void test_p101_clock_settime(struct p101_env *env, struct p101_error *err)
{
#ifdef __linux__
    static const int errors[] = {EACCES, EFAULT, EINVAL, ENODEV, ENOTSUP, EOVERFLOW, EPERM};
#elif defined(__APPLE__)
    static const int errors[] = {EFAULT, EINVAL, EPERM};
#elif defined(__FreeBSD__)
    static const int errors[] = {EINVAL, EPERM};
#else
    static const int errors[] = {EINVAL, EOVERFLOW, EPERM};
#endif

    for(size_t index = 0U; index < sizeof(errors) / sizeof(errors[0]); index++)
    {
        struct fault_state state = {0, errors[index]};

        p101_env_set_fault_injector(env, fail_next_call, &state);
        int result = p101_clock_settime(env, err, 0, NULL);
        (void)result;
        EXPECT(state.checks == 1);
        EXPECT(p101_error_is_errno(err, state.errnum));
        p101_error_reset(err);
    }
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_gmtime_r) */
static void test_p101_gmtime_r(struct p101_env *env, struct p101_error *err)
{
#ifdef __linux__
    static const int errors[] = {EOVERFLOW};
#elif defined(__APPLE__)
    static const int errors[] = {EIO};
#elif defined(__FreeBSD__)
    static const int errors[] = {EIO};
#else
    static const int errors[] = {EOVERFLOW};
#endif

    for(size_t index = 0U; index < sizeof(errors) / sizeof(errors[0]); index++)
    {
        struct fault_state state = {0, errors[index]};

        p101_env_set_fault_injector(env, fail_next_call, &state);
        struct tm *result = p101_gmtime_r(env, err, NULL, NULL);
        (void)result;
        EXPECT(state.checks == 1);
        EXPECT(p101_error_is_errno(err, state.errnum));
        p101_error_reset(err);
    }
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_localtime_r) */
static void test_p101_localtime_r(struct p101_env *env, struct p101_error *err)
{
#ifdef __linux__
    static const int errors[] = {EOVERFLOW};
#elif defined(__APPLE__)
    static const int errors[] = {EIO};
#elif defined(__FreeBSD__)
    static const int errors[] = {EIO};
#else
    static const int errors[] = {EOVERFLOW};
#endif

    for(size_t index = 0U; index < sizeof(errors) / sizeof(errors[0]); index++)
    {
        struct fault_state state = {0, errors[index]};

        p101_env_set_fault_injector(env, fail_next_call, &state);
        struct tm *result = p101_localtime_r(env, err, NULL, NULL);
        (void)result;
        EXPECT(state.checks == 1);
        EXPECT(p101_error_is_errno(err, state.errnum));
        p101_error_reset(err);
    }
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_nanosleep) */
static void test_p101_nanosleep(struct p101_env *env, struct p101_error *err)
{
#ifdef __linux__
    static const int errors[] = {EFAULT, EINTR, EINVAL};
#elif defined(__APPLE__)
    static const int errors[] = {EINTR, EINVAL};
#elif defined(__FreeBSD__)
    static const int errors[] = {EFAULT, EINTR, EINVAL, ENOTSUP};
#else
    static const int errors[] = {EINTR, EINVAL};
#endif

    for(size_t index = 0U; index < sizeof(errors) / sizeof(errors[0]); index++)
    {
        struct fault_state state = {0, errors[index]};

        p101_env_set_fault_injector(env, fail_next_call, &state);
        int result = p101_nanosleep(env, err, NULL, NULL);
        (void)result;
        EXPECT(state.checks == 1);
        EXPECT(p101_error_is_errno(err, state.errnum));
        p101_error_reset(err);
    }
    p101_env_set_fault_injector(env, NULL, NULL);
}

int main(void)
{
    struct p101_error *err;
    struct p101_env   *env;

    err = p101_error_create(false);
    if(err == NULL)
    {
        return EXIT_FAILURE;
    }
    env = p101_env_create(err, NULL);
    if(env == NULL)
    {
        p101_error_destroy(err);
        return EXIT_FAILURE;
    }
    test_p101_clock_getres(env, err);
    test_p101_clock_gettime(env, err);
    test_p101_clock_settime(env, err);
    test_p101_gmtime_r(env, err);
    test_p101_localtime_r(env, err);
    test_p101_nanosleep(env, err);
    p101_env_destroy(env);
    p101_error_destroy(err);
    return failures == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
