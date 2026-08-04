#include <locale.h>
#include <p101_env/env.h>
#include <p101_error/error.h>
#include <p101_time/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

int main(void)
{
    struct p101_error *err;
    struct p101_env   *env;
    struct tm          parsed = {0};
    struct tm          value  = {0};
    locale_t           locale;
    char               output[32];
    char              *end;

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

    /* P101_TEST_CASE(p101_tzset) */
    p101_tzset(env);

    /* P101_TEST_CASE(p101_strptime) */
    end = p101_strptime(env, "2026-07-31", "%Y-%m-%d", &parsed);
    EXPECT(end != NULL && *end == '\0');
    EXPECT(parsed.tm_year == 126);
    EXPECT(parsed.tm_mon == 6);
    EXPECT(parsed.tm_mday == 31);

    locale = newlocale(LC_ALL_MASK, "C", (locale_t)0);
    EXPECT(locale != (locale_t)0);
    if(locale != (locale_t)0)
    {
        value.tm_year = 126;
        value.tm_mon  = 6;
        value.tm_mday = 31;
        EXPECT(p101_strftime_l(env, err, output, sizeof(output), "%Y-%m-%d", &value, locale) == 10);
        EXPECT(p101_error_has_no_error(err));
        EXPECT(strcmp(output, "2026-07-31") == 0);
        freelocale(locale);
    }

    p101_env_destroy(env);
    p101_error_destroy(err);
    return failures == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
