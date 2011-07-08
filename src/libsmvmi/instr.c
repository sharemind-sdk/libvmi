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

const struct SMVMI_Instruction * SMVMI_Instruction_from_code(uint64_t code) {
    switch (code) {
#include "../m4/instruction_from_code_cases.h"
        default:
            return NULL;
    }
}


const struct SMVMI_Instruction * SMVMI_Instruction_from_name(const char * name) {
    assert(name);

#define N name
#include "../m4/instruction_from_name_cases.h"
#undef N

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
