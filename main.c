#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <math.h>
struct point_t {
    int x;
    int y;
};
int getlength(int x)
{
    int i;
    for(i = 0 ; ; i++)
    {
        if(x == 0)  break;
        x/=10;
    }
    return i;
}
int my_printf(char *format, ...)
{
    if(!format) return 0;
    va_list arg;
    va_start(arg,format);
    int counter = 0;
    for(int i = 0 ; i < (int)strlen(format) ; i++)
    {
        if(*(format + i) == '%')
        {
            i++;
            if(*(format + i) == 's')
            {
                char *s = va_arg(arg,char*);
                for(int j = 0 ; ; j++)
                {
                    if(*(s+j) == '\0')  break;
                    putchar(*(s+j));
                    counter++;
                }
            }
            if(*(format + i) == 'd')
            {
                int negative = 0;
                long long num = 0;
                long long source = va_arg(arg,int);
                if(source == 0)
                {
                    putchar('0');
                    counter++;
                } else{
                    if(source < 0)  negative = 1;
                    int length = getlength(source);
                    while(1)
                    {
                        num *= 10;
                        num +=  abs(source % 10);
                        source /= 10;
                        if(source == 0) break;
                    }
                    if(negative == 1)
                    {
                        putchar('-');
                        counter ++;
                    }
                    for(int k = 0 ; k < length ; k++)
                    {
                        putchar(num % 10 + '0');
                        counter ++;
                        num /= 10;
                    }
                }
            }
            if(*(format + i) == 'f')
            {
                int negative = 0;
                long long num = 0;
                double source = va_arg(arg,double);
                long long source_int = source;
                long long source_int_copy = source_int;
                if(source < 0)  negative = 1;
                if(negative)
                {
                    putchar('-');
                    counter ++;
                }
                int length = getlength(source_int);
                if(source_int == 0)
                {
                    putchar('0');
                    counter++;
                } else
                {
                    while(1)
                    {
                        num +=  abs(source_int) % 10;
                        source_int /= 10;
                        if(source_int == 0) break;
                        num *= 10;
                    }
                    for(int k = 0 ; k < length ; k++)
                    {
                        putchar(num % 10 + '0');
                        counter ++;
                        num /= 10;
                    }
                }
                source -= source_int_copy;
                putchar('.');
                counter++;
                for(int j = 0 ; j < 5 ; j++)
                {
                    source *=10;
                    putchar(abs(((int)source)) % 10 + '0');
                    counter ++;
                }
            }
            if(*(format + i) == 'p')
            {
                struct point_t p = va_arg(arg,struct point_t);
                int length;
                int negative = 0;
                long long num = 0;
                long long source = p.x;
                putchar('(');
                counter ++;
                if(source == 0)
                {
                    putchar('0');
                    counter++;
                } else{
                    if(source < 0)  negative = 1;
                    length = getlength(source);
                    while(1)
                    {
                        num *= 10;
                        num +=  abs(source % 10);
                        source /= 10;
                        if(source == 0) break;
                    }
                    if(negative == 1)
                    {
                        putchar('-');
                        counter ++;
                    }
                    for(int k = 0 ; k < length ; k++)
                    {
                        putchar(num % 10 + '0');
                        counter ++;
                        num /= 10;
                    }
                }
                putchar(' ');
                counter ++;
                negative = 0;
                num = 0;
                source = p.y;
                if(source == 0)
                {
                    putchar('0');
                    counter++;
                } else{
                    if(source < 0)  negative = 1;
                    length = getlength(source);
                    while(1)
                    {
                        num *= 10;
                        num +=  abs(source % 10);
                        source /= 10;
                        if(source == 0) break;
                    }
                    if(negative == 1)
                    {
                        putchar('-');
                        counter ++;
                    }
                    for(int k = 0 ; k < length ; k++)
                    {
                        putchar((num % 10) + '0');
                        counter ++;
                        num /= 10;
                    }
                }
                putchar(')');
                counter ++;
            }
        } else
        {
            putchar(*(format + i));
            counter++;
        }
    }
    return counter;
}
int my_scanf(char *format, ...)
{
    if(!format) return 0;
    va_list arg;
    va_start(arg,format);
    int counter = 0;
    for(int i = 0 ; i < (int)strlen(format) ; i++)
    {
        if(*(format + i) == '%')
        {
            i++;
            if(*(format + i) == 'd')
            {
                int negative = 0;
                int temp;
                int res = 0;
                int *source = va_arg(arg,int*);
                int count = 0;
                while (1)
                {
                    temp = getchar();
                    if(!isdigit(temp))
                    {
                        if(temp == '-')
                        {
                            negative = 1;
                            continue;
                        }
                        else break;
                    }
                    res *= 10;
                    res += temp - '0';
                    count ++;
                }
                if(count == 0)
                {
                    while(isdigit(getchar()));
                    continue;
                }
                if(negative == 1)   res *=-1;
                *source = res;
                counter++;
            }
            if(*(format + i) == 'f')
            {
                int negative = 0;
                int temp;
                int res = 0;
                double *source = va_arg(arg,double*);
                int count = 0;
                while (1)
                {
                    temp = getchar();
                    if(!isdigit(temp))
                    {
                        if(temp == '-')
                        {
                            negative = 1;
                            continue;
                        }
                        else break;
                    }
                    res *= 10;
                    res += temp - '0';
                    count++;
                }
                if(count == 0)
                {
                    while(isdigit(getchar()));
                    continue;
                }
                if(negative == 1)   res *= -1;
                *source = res;
                res = 0;
                int j = 0;
                int bylkoniec = 0;
                for(; j < 5 ; j++)
                {
                    temp = getchar();
                    if(!isdigit(temp))
                    {
                        bylkoniec =1;
                        break;
                    }
                    res *= 10;
                    res += temp - '0';
                }
                if(negative == 1)   res *= -1;
                *source += res/ pow(10,j);
                counter++;
                if(bylkoniec == 0)while(isdigit(getchar()));
            }
            if(*(format + i) == 'p')
            {
                {
                    getchar();
                    int negative = 0;
                    int temp;
                    int res = 0;
                    struct point_t *source = va_arg(arg,struct point_t*);
                    while (1)
                    {
                        temp = getchar();
                        if(!isdigit(temp))
                        {
                            if(temp == '-')
                            {
                                negative = 1;
                                continue;
                            }
                            else break;
                        }
                        res *= 10;
                        res += temp - '0';
                    }
                    if(negative == 1)   res *= -1;
                    (*source).x = res;
                    negative = 0;
                    res = 0;
                    int count = 0;
                    while (1)
                    {
                        temp = getchar();
                        if(!isdigit(temp))
                        {
                            if(temp == '-')
                            {
                                negative = 1;
                                continue;
                            }
                            else break;
                        }
                        res *= 10;
                        res += temp - '0';
                        count ++;
                    }
                    if(count == 0)
                    {
                        while(isdigit(getchar()));
                        continue;
                    }
                    if(negative == 1)   res *= -1;
                    (*source).y = res;
                    counter+=2;
                    getchar();
                }
            }
        }
    }
    return counter;
}
int main()
{
    return 0;
}

