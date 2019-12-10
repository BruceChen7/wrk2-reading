// Copyright (C) 2012 - Will Glozer.  All rights reserved.

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *aprintf(char **s, const char *fmt, ...) {
    char *c = NULL;
    int n, len;
    va_list ap;

    va_start(ap, fmt);
    // 计算fmt中的长度，包含了NULL的值
    n = vsnprintf(NULL, 0, fmt, ap) + 1;
    va_end(ap);

    len = *s ? strlen(*s) : 0;

    if ((*s = realloc(*s, (len + n) * sizeof(char)))) {
        // 前面放s
        c = *s + len;
        va_start(ap, fmt);
        // 后面放格式化的字符串
        vsnprintf(c, n, fmt, ap);
        va_end(ap);
    }

    // 返回的是malloc后的地址
    return c;
}
