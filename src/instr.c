/*
 * Copyright (C) 2015 Cybernetica
 *
 * Research/Commercial License Usage
 * Licensees holding a valid Research License or Commercial License
 * for the Software may use this file according to the written
 * agreement between you and Cybernetica.
 *
 * GNU General Public License Usage
 * Alternatively, this file may be used under the terms of the GNU
 * General Public License version 3.0 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU General Public License version 3.0 requirements will be
 * met: http://www.gnu.org/copyleft/gpl-3.0.html.
 *
 * For further information, please contact us at sharemind@cyber.ee.
 */

#include "instr.h"

#include <assert.h>
#include <string.h>


// Instruction structs list
#define SHAREMIND_HANDLE_VMI_INSTRUCTION(iFullname, iCode, iNumArgs) \
    { .fullName = iFullname, .code = iCode, .numArgs = iNumArgs ## u },
#ifdef __GNUC__
#pragma GCC visibility push(hidden)
#endif
static const SharemindVmInstruction sharemindVmInstructionIndex[] = {
#include <sharemind/m4/instruction_index.h>
    { .fullName = "", .code = 0u, .numArgs = 0u }
};
#ifdef __GNUC__
#pragma GCC visibility pop
#endif
#undef SHAREMIND_HANDLE_VMI_INSTRUCTION

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
