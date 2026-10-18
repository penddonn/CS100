/* CS100 Fall 2026 - HW2 Problem 4: GCC argument descriptor
 *
 * Read GCC-style command-line arguments (argv) and print a description
 * for each of them, in order. No standard input in this problem.
 * Do not rename this file.
 */
#include <stdio.h>
#include <string.h>

/* Returns 1 if str starts with prefix. */
static int starts_with(const char *str, const char *prefix)
{
    return strncmp(str, prefix, strlen(prefix)) == 0;
}

static void describe_std(const char *arg)
{
    const char *value = arg + strlen("-std=");
    /* Check the longer prefixes first: "gnu++" before "gnu", "c++" before "c". */
    if (starts_with(value, "gnu++"))
        printf("%s: Set the language standard to GNU dialect of C++%s.\n", arg, value + 5);
    else if (starts_with(value, "gnu"))
        printf("%s: Set the language standard to GNU dialect of C%s.\n", arg, value + 3);
    else if (starts_with(value, "c++"))
        printf("%s: Set the language standard to ISO C++%s.\n", arg, value + 3);
    else /* "cN" */
        printf("%s: Set the language standard to ISO C%s.\n", arg, value + 1);
}

static void describe_file(const char *name)
{
    const char *dot = strrchr(name, '.');
    const char *ext = dot ? dot + 1 : "";
    const char *type;

    if (strcmp(ext, "c") == 0)
        type = "C source code";
    else if (strcmp(ext, "h") == 0)
        type = "C/C++ header file";
    else if (strcmp(ext, "cpp") == 0 || strcmp(ext, "C") == 0 ||
             strcmp(ext, "cc") == 0 || strcmp(ext, "cxx") == 0)
        type = "C++ source code";
    else /* "hpp" or "hxx" */
        type = "C++ header file";

    printf("%s: %s as input file.\n", name, type);
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i) {
        const char *arg = argv[i];

        if (strcmp(arg, "-Wall") == 0) {
            printf("-Wall: Enable all the warnings about constructions that some users "
                   "consider questionable, and that are easy to avoid (or modify to "
                   "prevent the warning).\n");
        } else if (strcmp(arg, "-Wpedantic") == 0) {
            printf("-Wpedantic: Issue all the warnings demanded by strict ISO C and ISO C++ "
                   "and reject all programs that use forbidden extensions.\n");
        } else if (strcmp(arg, "-Wextra") == 0) {
            printf("-Wextra: Enable some extra warning flags that are not enabled by -Wall.\n");
        } else if (strcmp(arg, "-Werror") == 0) {
            printf("-Werror: Make all warnings into errors.\n");
        } else if (strcmp(arg, "-o") == 0 && i + 1 < argc) {
            ++i;
            printf("-o %s: Place the primary output in file %s.\n", argv[i], argv[i]);
        } else if (strcmp(arg, "-I") == 0 && i + 1 < argc) {
            ++i;
            printf("-I %s: Add the directory %s to the list of directories to be "
                   "searched for header files during preprocessing.\n", argv[i], argv[i]);
        } else if (starts_with(arg, "-std=")) {
            describe_std(arg);
        } else {
            describe_file(arg);
        }
    }
    return 0;
}
