#pragma once

#define LGRP_RFM12  'R'
#define LGRP_APP    'A'
#define LGRP_DS1820 'D'
#define LGRP_KEYB   'K'

extern void log_init(uint8_t uart);
extern void log_msg(uint8_t module, char message);
