// Copyright 2025 Ira Cooper <ira@wakeful.net>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "viable.h"
#include "viable_definition_data.h"
#include <string.h>

// Get the size of the compressed keyboard definition
uint32_t viable_get_definition_size(void) {
    return VIABLE_DEFINITION_SIZE;
}

// Get a chunk of the compressed keyboard definition
// Returns the number of bytes copied (up to 28)
uint8_t viable_get_definition_chunk(uint16_t offset, uint8_t *buffer) {
    if (offset >= VIABLE_DEFINITION_SIZE) {
        return 0;
    }

    uint16_t remaining = VIABLE_DEFINITION_SIZE - offset;
    uint8_t chunk_size = remaining < VIABLE_DEFINITION_CHUNK_SIZE ? remaining : VIABLE_DEFINITION_CHUNK_SIZE;

    // Copy from PROGMEM
    memcpy_P(buffer, &viable_definition_data[offset], chunk_size);

    return chunk_size;
}
