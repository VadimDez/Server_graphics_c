#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <stack>
#include <deque>
#include <queue>
#include <stdlib.h>
#include <cstring>
#include <stdio.h>
#include <string>
#include <math.h>
using namespace std;
class parser
{
public:
    parser();
    stack<string> ops;
    queue<string> temp;
    deque<string> output;
    string tmp;
    void insert(string str);
    int precedence();
    void operators();
    double result();
};

#endif // PARSER_H
