/** @file
 * Copyright (c) 2019-2022, Arm Limited or its affiliates. All rights reserved.
 * SPDX-License-Identifier : Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
**/

#include "val_crypto.h"

typedef struct {
    char                    test_desc[75];
    psa_key_type_t          key_type;
    uint8_t                 key_data[32];
    uint32_t                key_length;
    psa_key_usage_t         usage;
    psa_algorithm_t         key_alg;
    psa_algorithm_t         alg;
    uint8_t                 plaintext[30];
    uint8_t                 additional_data[32];
    uint8_t                 nonce[32];
    size_t                  nonce_size;
    size_t                  ad_length;
    size_t                  plaintext_length;
    size_t                  input_length;
    size_t                  output_size;
    uint8_t                 ciphertext[45];
    size_t                  ciphertext_length;
    uint8_t                 tag[64];
    size_t                  tag_length;
    psa_status_t            expected_status[2];
} test_data;

static const test_data check1[] = {
#ifdef ARCH_TEST_CCM
#ifdef ARCH_TEST_AES_128
{"Test psa_aead_verify - AES-CCM\n", PSA_KEY_TYPE_AES,
{0x41, 0x89, 0x35, 0x1B, 0x5C, 0xAE, 0xA3, 0x75, 0xA0, 0x29, 0x9E, 0x81, 0xC6,
 0x21, 0xBF, 0x43},
 AES_16B_KEY_SIZE, PSA_KEY_USAGE_DECRYPT, PSA_ALG_CCM, PSA_ALG_CCM,
{0x45, 0x35, 0xd1, 0x2b, 0x43, 0x77, 0x92, 0x8a, 0x7c, 0x0a, 0x61, 0xc9, 0xf8,
 0x25, 0xa4, 0x86, 0x71, 0xea, 0x05, 0x91, 0x07, 0x48, 0xc8, 0xef},
{0x40, 0xa2, 0x7c, 0x1d, 0x1e, 0x23, 0xea, 0x3d, 0xbe, 0x80, 0x56, 0xb2, 0x77,
 0x48, 0x61, 0xa4, 0xa2, 0x01, 0xcc, 0xe4, 0x9f, 0x19, 0x99, 0x7d, 0x19, 0x20,
 0x6d, 0x8c, 0x8a, 0x34, 0x39, 0x51},
{0x48, 0xc0, 0x90, 0x69, 0x30, 0x56, 0x1e, 0x0a, 0xb0, 0xef, 0x4c, 0xd9, 0x72},
 13, 32, 24, 24, BUFFER_SIZE,
{0x26, 0xc5, 0x69, 0x61, 0xc0, 0x35, 0xa7, 0xe4, 0x52, 0xcc, 0xe6, 0x1b, 0xc6,
 0xee, 0x22, 0x0d, 0x77, 0xb3, 0xf9, 0x4d, 0x18, 0xfd, 0x10, 0xb6},
 24,
{0xd8, 0x0e, 0x8b, 0xf8, 0x0f, 0x4a, 0x46, 0xca, 0xb0, 0x6d, 0x43, 0x13, 0xf0,
 0xdb, 0x9b, 0xe9}, 16,
{PSA_SUCCESS, PSA_SUCCESS}
},

{"Test psa_aead_verify - AES-CCM 24 bytes Tag length = 4\n", PSA_KEY_TYPE_AES,
{0x41, 0x89, 0x35, 0x1B, 0x5C, 0xAE, 0xA3, 0x75, 0xA0, 0x29, 0x9E, 0x81, 0xC6,
 0x21, 0xBF, 0x43}, AES_16B_KEY_SIZE, PSA_KEY_USAGE_DECRYPT,
 PSA_ALG_AEAD_WITH_SHORTENED_TAG(PSA_ALG_CCM, 4),
 PSA_ALG_AEAD_WITH_SHORTENED_TAG(PSA_ALG_CCM, 4),
{0x45, 0x35, 0xd1, 0x2b, 0x43, 0x77, 0x92, 0x8a, 0x7c, 0x0a, 0x61, 0xc9, 0xf8,
 0x25, 0xa4, 0x86, 0x71, 0xea, 0x05, 0x91, 0x07, 0x48, 0xc8, 0xef},
{0x40, 0xa2, 0x7c, 0x1d, 0x1e, 0x23, 0xea, 0x3d, 0xbe, 0x80, 0x56, 0xb2, 0x77,
 0x48, 0x61, 0xa4, 0xa2, 0x01, 0xcc, 0xe4, 0x9f, 0x19, 0x99, 0x7d, 0x19, 0x20,
 0x6d, 0x8c, 0x8a, 0x34, 0x39, 0x51},
{0x48, 0xc0, 0x90, 0x69, 0x30, 0x56, 0x1e, 0x0a, 0xb0, 0xef, 0x4c, 0xd9, 0x72},
 13, 32, 24, 24, BUFFER_SIZE,
{0x26, 0xc5, 0x69, 0x61, 0xc0, 0x35, 0xa7, 0xe4, 0x52, 0xcc, 0xe6, 0x1b, 0xc6,
 0xee, 0x22, 0x0d, 0x77, 0xb3, 0xf9, 0x4d, 0x18, 0xfd, 0x10, 0xb6},
 24, {0x64, 0x3b, 0x4f, 0x39}, 4,
{PSA_SUCCESS, PSA_SUCCESS}
},

{"Test psa_aead_verify - Small buffer size\n", PSA_KEY_TYPE_AES,
{0x41, 0x89, 0x35, 0x1B, 0x5C, 0xAE, 0xA3, 0x75, 0xA0, 0x29, 0x9E, 0x81, 0xC6,
 0x21, 0xBF, 0x43},
 AES_16B_KEY_SIZE, PSA_KEY_USAGE_DECRYPT, PSA_ALG_CCM, PSA_ALG_CCM,
{0x45, 0x35, 0xd1, 0x2b, 0x43, 0x77, 0x92, 0x8a, 0x7c, 0x0a, 0x61, 0xc9, 0xf8,
 0x25, 0xa4, 0x86, 0x71, 0xea, 0x05, 0x91, 0x07, 0x48, 0xc8, 0xef},
{0x40, 0xa2, 0x7c, 0x1d, 0x1e, 0x23, 0xea, 0x3d, 0xbe, 0x80, 0x56, 0xb2, 0x77,
 0x48, 0x61, 0xa4, 0xa2, 0x01, 0xcc, 0xe4, 0x9f, 0x19, 0x99, 0x7d, 0x19, 0x20,
 0x6d, 0x8c, 0x8a, 0x34, 0x39, 0x51},
{0x48, 0xc0, 0x90, 0x69, 0x30, 0x56, 0x1e, 0x0a, 0xb0, 0xef, 0x4c, 0xd9, 0x72},
 13, 32, 24, 24, 0,
{0x26, 0xc5, 0x69, 0x61, 0xc0, 0x35, 0xa7, 0xe4, 0x52, 0xcc, 0xe6, 0x1b, 0xc6,
 0xee, 0x22, 0x0d, 0x77, 0xb3, 0xf9, 0x4d, 0x18, 0xfd, 0x10, 0xb6},
 24,
{0xd8, 0x0e, 0x8b, 0xf8, 0x0f, 0x4a, 0x46, 0xca, 0xb0, 0x6d, 0x43, 0x13, 0xf0,
 0xdb, 0x9b, 0xe9}, 16,
{PSA_ERROR_BUFFER_TOO_SMALL, PSA_SUCCESS}
},

{"Test psa_aead_verify - Input length is less than plaintext length\n", PSA_KEY_TYPE_AES,
{0x41, 0x89, 0x35, 0x1B, 0x5C, 0xAE, 0xA3, 0x75, 0xA0, 0x29, 0x9E, 0x81, 0xC6,
 0x21, 0xBF, 0x43},
 AES_16B_KEY_SIZE, PSA_KEY_USAGE_DECRYPT, PSA_ALG_CCM, PSA_ALG_CCM,
{0},
{0x40, 0xa2, 0x7c, 0x1d, 0x1e, 0x23, 0xea, 0x3d, 0xbe, 0x80, 0x56, 0xb2, 0x77,
 0x48, 0x61, 0xa4, 0xa2, 0x01, 0xcc, 0xe4, 0x9f, 0x19, 0x99, 0x7d, 0x19, 0x20,
 0x6d, 0x8c, 0x8a, 0x34, 0x39, 0x51},
{0x48, 0xc0, 0x90, 0x69, 0x30, 0x56, 0x1e, 0x0a, 0xb0, 0xef, 0x4c, 0xd9, 0x72},
 13, 32, 0, 30, BUFFER_SIZE,
{0x26, 0xc5, 0x69, 0x61, 0xc0, 0x35, 0xa7, 0xe4, 0x52, 0xcc, 0xe6, 0x1b, 0xc6,
 0xee, 0x22, 0x0d, 0x77, 0xb3, 0xf9, 0x4d, 0x18, 0xfd, 0x10, 0xb6},
 24,
{0xd8, 0x0e, 0x8b, 0xf8, 0x0f, 0x4a, 0x46, 0xca, 0xb0, 0x6d, 0x43, 0x13, 0xf0,
 0xdb, 0x9b, 0xe9}, 16,
{PSA_ERROR_INVALID_ARGUMENT, PSA_ERROR_INVALID_ARGUMENT}
},
#endif
#endif

#ifdef ARCH_TEST_GCM
#ifdef ARCH_TEST_AES_128
{"Test psa_aead_verify - GCM - 16B AES - 12B Nounce & 12B addi data\n", PSA_KEY_TYPE_AES,
{0x3d, 0xe0, 0x98, 0x74, 0xb3, 0x88, 0xe6, 0x49, 0x19, 0x88, 0xd0, 0xc3, 0x60,
 0x7e, 0xae, 0x1f}, AES_16B_KEY_SIZE, PSA_KEY_USAGE_DECRYPT, PSA_ALG_GCM, PSA_ALG_GCM,
{0x45, 0x00, 0x00, 0x1c, 0x42, 0xa2, 0x00, 0x00, 0x80, 0x01, 0x44, 0x1f, 0x40,
 0x67, 0x93, 0xb6, 0xe0, 0x00, 0x00, 0x02, 0x0a, 0x00, 0xf5, 0xff, 0x01, 0x02,
 0x02, 0x01},
{0x42, 0xf6, 0x7e, 0x3f, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10},
{0x57, 0x69, 0x0e, 0x43, 0x4e, 0x28, 0x00, 0x00, 0xa2, 0xfc, 0xa1, 0xa3},
 12, 12, 28, 28, BUFFER_SIZE,
{0xFB, 0xA2, 0xCA, 0x84, 0x5E, 0x5D, 0xF9, 0xF0, 0xF2, 0x2C, 0x3E, 0x6E, 0x86,
 0xDD, 0x83, 0x1E, 0x1F, 0xC6, 0x57, 0x92, 0xCD, 0x1A, 0xF9, 0x13, 0x0E, 0x13,
 0x79, 0xED}, 28,
{0x36, 0x9F, 0x07, 0x1F, 0x35, 0xE0, 0x34, 0xBE, 0x95, 0xF1, 0x12, 0xE4, 0xE7,
 0xD0, 0x5D, 0x35}, 16,
{PSA_SUCCESS, PSA_SUCCESS}
},
#endif
#endif
};
