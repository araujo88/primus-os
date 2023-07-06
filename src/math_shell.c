#include "../include/math_shell.h"
#include "../include/math.h"
#include "../include/limits.h"
#include "../include/tty.h"
#include "../include/string.h"
#include "../include/parsing.h"
#include "../include/random.h"

boolean math_func(char *buffer)
{
    if (strlen(buffer) > 0 && strstr(buffer, "fact") != NULL)
    {
        return true;
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "exp") != NULL)
    {
        return true;
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "ln") != NULL)
    {
        return true;
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "log10") != NULL)
    {
        return true;
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "sqrt") != NULL)
    {
        return true;
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "abs") != NULL)
    {
        return true;
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "asinh") != NULL)
    {
        return true;
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "acosh") != NULL)
    {
        return true;
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "atanh") != NULL)
    {
        return true;
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "asin") != NULL)
    {
        return true;
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "acos") != NULL)
    {
        return true;
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "atan") != NULL)
    {
        return true;
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "sin") != NULL)
    {
        return true;
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "cos") != NULL)
    {
        return true;
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "tan") != NULL)
    {
        return true;
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "sinh") != NULL)
    {
        return true;
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "cosh") != NULL)
    {
        return true;
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "tanh") != NULL)
    {
        return true;
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "pow") != NULL)
    {
        return true;
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "log") != NULL)
    {
        return true;
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "srand") != NULL)
    {
        return true;
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "rand") != NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void math_shell(char *buffer)
{
    if (strlen(buffer) > 0 && strstr(buffer, "fact(") != NULL)
    {
        char *parser;
        uint32_t num;
        parser = strstr(buffer, "fact(");
        parser += strlen("fact(");
        num = parse_int(parser, ')');
        if (num != (int)NULL)
        {
            printk("\n%d", fact(num));
        }
        else
        {
            terminal_set_colors(COLOR_LIGHT_RED, COLOR_BLACK);
            printk("\nParsing error.");
            terminal_set_colors(default_font_color, COLOR_BLACK);
        }
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "exp(") != NULL)
    {
        char *parser;
        char *buff;
        double num;
        parser = strstr(buffer, "exp(");
        parser += strlen("exp(");
        num = parse_float(parser, ')');
        if (num != EPS)
        {
            printk("\n");
            printk(ftoa(buff, exp(num), 6));
        }
        else
        {
            terminal_set_colors(COLOR_LIGHT_RED, COLOR_BLACK);
            printk("\nParsing error.");
            terminal_set_colors(default_font_color, COLOR_BLACK);
        }
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "ln(") != NULL)
    {
        char *parser;
        char *buff;
        double num;
        parser = strstr(buffer, "ln(");
        parser += strlen("ln(");
        num = parse_float(parser, ')');
        if (num != EPS)
        {
            printk("\n");
            printk(ftoa(buff, ln(num), 6));
        }
        else
        {
            terminal_set_colors(COLOR_LIGHT_RED, COLOR_BLACK);
            printk("\nParsing error.");
            terminal_set_colors(default_font_color, COLOR_BLACK);
        }
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "log10(") != NULL)
    {
        char *parser;
        char *buff;
        double num;
        parser = strstr(buffer, "log10(");
        parser += strlen("log10(");
        num = parse_float(parser, ')');
        if (num != EPS)
        {
            printk("\n");
            printk(ftoa(buff, log10(num), 6));
        }
        else
        {
            terminal_set_colors(COLOR_LIGHT_RED, COLOR_BLACK);
            printk("\nParsing error.");
            terminal_set_colors(default_font_color, COLOR_BLACK);
        }
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "sqrt(") != NULL)
    {
        char *parser;
        char *buff;
        double num;
        parser = strstr(buffer, "sqrt(");
        parser += strlen("sqrt(");
        num = parse_float(parser, ')');
        if (num != EPS)
        {
            printk("\n");
            printk(ftoa(buff, sqrt(num), 6));
        }
        else
        {
            terminal_set_colors(COLOR_LIGHT_RED, COLOR_BLACK);
            printk("\nParsing error.");
            terminal_set_colors(default_font_color, COLOR_BLACK);
        }
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "abs(") != NULL)
    {
        char *parser;
        char *buff;
        double num;
        parser = strstr(buffer, "abs(");
        parser += strlen("abs(");
        num = parse_float(parser, ')');
        if (num != EPS)
        {
            printk("\n");
            printk(ftoa(buff, abs(num), 6));
        }
        else
        {
            terminal_set_colors(COLOR_LIGHT_RED, COLOR_BLACK);
            printk("\nParsing error.");
            terminal_set_colors(default_font_color, COLOR_BLACK);
        }
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "asinh(") != NULL)
    {
        char *parser;
        char *buff;
        double num;
        parser = strstr(buffer, "asinh(");
        parser += strlen("asinh(");
        num = parse_float(parser, ')');
        if (num != EPS)
        {
            printk("\n");
            printk(ftoa(buff, asinh(num), 6));
        }
        else
        {
            terminal_set_colors(COLOR_LIGHT_RED, COLOR_BLACK);
            printk("\nParsing error.");
            terminal_set_colors(default_font_color, COLOR_BLACK);
        }
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "acosh(") != NULL)
    {
        char *parser;
        char *buff;
        double num;
        parser = strstr(buffer, "acosh(");
        parser += strlen("acosh(");
        num = parse_float(parser, ')');
        if (num != EPS)
        {
            printk("\n");
            printk(ftoa(buff, acosh(num), 6));
        }
        else
        {
            terminal_set_colors(COLOR_LIGHT_RED, COLOR_BLACK);
            printk("\nParsing error.");
            terminal_set_colors(default_font_color, COLOR_BLACK);
        }
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "atanh(") != NULL)
    {
        char *parser;
        char *buff;
        double num;
        parser = strstr(buffer, "atanh(");
        parser += strlen("atanh(");
        num = parse_float(parser, ')');
        if (num != EPS)
        {
            printk("\n");
            printk(ftoa(buff, atanh(num), 6));
        }
        else
        {
            terminal_set_colors(COLOR_LIGHT_RED, COLOR_BLACK);
            printk("\nParsing error.");
            terminal_set_colors(default_font_color, COLOR_BLACK);
        }
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "asin(") != NULL)
    {
        char *parser;
        char *buff;
        double num;
        parser = strstr(buffer, "asin(");
        parser += strlen("asin(");
        num = parse_float(parser, ')');
        if (num != EPS)
        {
            printk("\n");
            printk(ftoa(buff, asin(num), 6));
        }
        else
        {
            terminal_set_colors(COLOR_LIGHT_RED, COLOR_BLACK);
            printk("\nParsing error.");
            terminal_set_colors(default_font_color, COLOR_BLACK);
        }
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "acos(") != NULL)
    {
        char *parser;
        char *buff;
        double num;
        parser = strstr(buffer, "acos(");
        parser += strlen("acos(");
        num = parse_float(parser, ')');
        if (num != EPS)
        {
            printk("\n");
            printk(ftoa(buff, acos(num), 6));
        }
        else
        {
            terminal_set_colors(COLOR_LIGHT_RED, COLOR_BLACK);
            printk("\nParsing error.");
            terminal_set_colors(default_font_color, COLOR_BLACK);
        }
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "atan(") != NULL)
    {
        char *parser;
        char *buff;
        double num;
        parser = strstr(buffer, "atan(");
        parser += strlen("atan(");
        num = parse_float(parser, ')');
        if (num != EPS)
        {
            printk("\n");
            printk(ftoa(buff, atan(num), 6));
        }
        else
        {
            terminal_set_colors(COLOR_LIGHT_RED, COLOR_BLACK);
            printk("\nParsing error.");
            terminal_set_colors(default_font_color, COLOR_BLACK);
        }
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "sin(") != NULL)
    {
        char *parser;
        char *buff;
        double num;
        parser = strstr(buffer, "sin(");
        parser += strlen("sin(");
        num = parse_float(parser, ')');
        if (num != EPS)
        {
            printk("\n");
            printk(ftoa(buff, sin(num), 6));
        }
        else
        {
            terminal_set_colors(COLOR_LIGHT_RED, COLOR_BLACK);
            printk("\nParsing error.");
            terminal_set_colors(default_font_color, COLOR_BLACK);
        }
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "cos(") != NULL)
    {
        char *parser;
        char *buff;
        double num;
        parser = strstr(buffer, "cos(");
        parser += strlen("cos(");
        num = parse_float(parser, ')');
        if (num != EPS)
        {
            printk("\n");
            printk(ftoa(buff, cos(num), 6));
        }
        else
        {
            terminal_set_colors(COLOR_LIGHT_RED, COLOR_BLACK);
            printk("\nParsing error.");
            terminal_set_colors(default_font_color, COLOR_BLACK);
        }
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "tan(") != NULL)
    {
        char *parser;
        char *buff;
        double num;
        parser = strstr(buffer, "tan(");
        parser += strlen("tan(");
        num = parse_float(parser, ')');
        if (num != EPS)
        {
            printk("\n");
            printk(ftoa(buff, tan(num), 6));
        }
        else
        {
            terminal_set_colors(COLOR_LIGHT_RED, COLOR_BLACK);
            printk("\nParsing error.");
            terminal_set_colors(default_font_color, COLOR_BLACK);
        }
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "sinh(") != NULL)
    {
        char *parser;
        char *buff;
        double num;
        parser = strstr(buffer, "sinh(");
        parser += strlen("sinh(");
        num = parse_float(parser, ')');
        if (num != EPS)
        {
            printk("\n");
            printk(ftoa(buff, sinh(num), 6));
        }
        else
        {
            terminal_set_colors(COLOR_LIGHT_RED, COLOR_BLACK);
            printk("\nParsing error.");
            terminal_set_colors(default_font_color, COLOR_BLACK);
        }
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "cosh(") != NULL)
    {
        char *parser;
        char *buff;
        double num;
        parser = strstr(buffer, "cosh(");
        parser += strlen("cosh(");
        num = parse_float(parser, ')');
        if (num != EPS)
        {
            printk("\n");
            printk(ftoa(buff, cosh(num), 6));
        }
        else
        {
            terminal_set_colors(COLOR_LIGHT_RED, COLOR_BLACK);
            printk("\nParsing error.");
            terminal_set_colors(default_font_color, COLOR_BLACK);
        }
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "tanh(") != NULL)
    {
        char *parser;
        char *buff;
        double num;
        parser = strstr(buffer, "tanh(");
        parser += strlen("tanh(");
        num = parse_float(parser, ')');
        if (num != EPS)
        {
            printk("\n");
            printk(ftoa(buff, tanh(num), 6));
        }
        else
        {
            terminal_set_colors(COLOR_LIGHT_RED, COLOR_BLACK);
            printk("\nParsing error.");
            terminal_set_colors(default_font_color, COLOR_BLACK);
        }
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "pow(") != NULL)
    {
        char *parser;
        char *buff;
        double num;
        double n;
        parser = strstr(buffer, "pow(");
        parser += strlen("pow(");
        num = parse_float(parser, ',');
        if (num != EPS)
        {
            while (parser[0] != ',')
            {
                parser++;
            }
            parser++;
            n = parse_float(parser, ')');
            printk("\n");
            printk(ftoa(buff, pow(num, n), 6));
        }
        else
        {
            terminal_set_colors(COLOR_LIGHT_RED, COLOR_BLACK);
            printk("\nParsing error.");
            terminal_set_colors(default_font_color, COLOR_BLACK);
        }
    }
    else if (strlen(buffer) > 0 && strstr(buffer, "log(") != NULL)
    {
        char *parser;
        char *buff;
        double num;
        double n;
        parser = strstr(buffer, "log(");
        parser += strlen("log(");
        num = parse_float(parser, ',');
        if (num != EPS)
        {
            while (parser[0] != ',')
            {
                parser++;
            }
            parser++;
            n = parse_float(parser, ')');
            printk("\n");
            printk(ftoa(buff, log(num, n), 6));
        }
        else
        {
            terminal_set_colors(COLOR_LIGHT_RED, COLOR_BLACK);
            printk("\nParsing error.");
            terminal_set_colors(default_font_color, COLOR_BLACK);
        }
    }
    else if (strlen(buffer) > 0 && strcmp(buffer, "srand()") == 0)
    {
        printk("\nGenerated seed for random number generator.");
        srand();
    }
    else if (strlen(buffer) > 0 && strcmp(buffer, "rand()") == 0)
    {
        char *buff;
        printk("\n");
        printk(ftoa(buff, rand(), 6));
    }
}