/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#include "instr.h"

#include <assert.h>
#include <string.h>

#include "../m4/instruction_structs.h"
#ifdef SMVMI_FAST_BUILD
#include "../m4/instruction_index.h"
#endif

const SMVMI_Instruction * SMVMI_Instruction_from_code(uint64_t code) {
#ifndef SMVMI_FAST_BUILD
    switch (code) {
#include "../m4/instruction_from_code_cases.h"
        default:
            break;
    }
#else
    const SMVMI_Instruction * const * instr = &SMVMI_instructions_index[0];
    while (*instr) {
        if ((*instr)->code == code)
            return *instr;
        ++instr;
    }
#endif

    return NULL;
}


const SMVMI_Instruction * SMVMI_Instruction_from_name(const char * name) {
    assert(name);

#ifndef SMVMI_FAST_BUILD
#define N name
#include "../m4/instruction_from_name_cases.h"
#undef N
#else
    const SMVMI_Instruction * const * instr = &SMVMI_instructions_index[0];
    while (*instr) {
        const char * instrName = (*instr)->fullname;

        do {
            if (strcmp(instrName, name) == 0)
                return *instr;

            do {
                ++instrName;
                if (*instrName == '.') {
                    ++instrName;
                    break;
                }
            } while (*instrName);
        } while (*instrName);
        ++instr;
    }
#endif

    return NULL;
}

const char * SMVMI_Instruction_fullname_to_name(const char * fullname) {
    assert(fullname);
    const char * r = fullname;
    while (*r != '\0') {
        if (*r == '.') {
            fullname = r + 1;
        }
        r++;
    }
    return fullname;
}
