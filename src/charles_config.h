#ifndef _CHARLES_CONFIG_H
#define _CHARLES_CONFIG_H
/**
 * File: charles_config.h
 * Description: Charles's json format config loading interface
 * Author: Charles, Liu. 2017-5-15
 * Mailto: charlesliu.cn.bj@gmail.com
 */
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <errno.h>
#include <string.h>
#include "json.h"
using std::string;
using std::vector;

#define charles_err(fmt, ...) do {\
    fprintf(stderr, fmt, ##__VA_ARGS__);\
    fprintf(stderr, "\n");\
} while (0)

class CharlesConfig {
public:
    CharlesConfig() {}
    ~CharlesConfig() {}
private:
    string stripComments(vector<string> &lines);
    int stripSpaces(string &config);
    int parseJson(string &config);
public:
    int loadConfig(const char *conf);
};

#endif
