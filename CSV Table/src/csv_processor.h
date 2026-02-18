#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isNumber(const char*);

int countCommas(const char*);

int processCSV(const char*, const char*);
