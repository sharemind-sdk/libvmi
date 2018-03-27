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

#ifndef SHAREMIND_LIBVMI_INSTR_H
#define SHAREMIND_LIBVMI_INSTR_H

#include <stddef.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    const char fullName[64];
    const uint64_t code;
    const size_t numArgs;
} SharemindVmInstruction;

const SharemindVmInstruction * sharemind_vm_instruction_from_code(uint64_t code) __attribute__ ((warn_unused_result));
const SharemindVmInstruction * sharemind_vm_instruction_from_name(const char * name) __attribute__ ((nonnull(1),warn_unused_result));
const char * sharemind_vm_instruction_fullname_to_name(const char * fullName) __attribute__ ((nonnull(1),warn_unused_result));

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* SHAREMIND_LIBVMI_INSTR_H */
