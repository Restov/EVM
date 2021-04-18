#ifndef MYSIGNAL
#define MYSIGNAL
#pragma once

#include <stdio.h>
#include "printConsole.h"
#include <signal.h>
#include <sys/time.h>
#include "mySimpleComputer.h"

void signalhangle(int signal);
void reset_signalhagle(int signal);
void create_timer(double interval);

#endif