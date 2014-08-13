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


// Instruction structs list
#ifdef __GNUC__
#pragma GCC visibility push(hidden)
#endif
#include <sharemind/m4/instruction_index.h>
#ifdef __GNUC__
#pragma GCC visibility pop
#endif

const SharemindVmInstruction * sharemind_vm_instruction_from_code(uint64_t code) {
    const SharemindVmInstruction * instr = &sharemindVmInstructionIndex[0];
    while (instr->fullName[0]) {
        if (instr->code == code)
            return instr;
        ++instr;
    }

    return NULL;
}


const SharemindVmInstruction * sharemind_vm_instruction_from_name(const char * name) {
    assert(name);

    const SharemindVmInstruction * instr = &sharemindVmInstructionIndex[0];
    while (instr->fullName[0]) {
        const char * instrName = instr->fullName;

        do {
            if (strcmp(instrName, name) == 0)
                return instr;

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

    return NULL;
}

const char * sharemind_vm_instruction_fullname_to_name(const char * fullname) {
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
