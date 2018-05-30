#include <stdint.h>
#include <stdbool.h>
#include "eeprom.h"
#include "eeconfig.h"


/** \brief eeconfig enable
 *
 * FIXME: needs doc
 */
__attribute__ ((weak))
void eeconfig_init_user(void) {
  // Reset user EEPROM value to blank, rather than to a set value
  eeprom_update_dword(EECONFIG_USER, 0);
}

__attribute__ ((weak))
void eeconfig_init_kb(void) {
  // Reset Keyboard EEPROM value to blank, rather than to a set value
  eeprom_update_dword(EECONFIG_KEYBOARD, 0);

  eeconfig_init_user();
}


/** \brief eeconfig initialization
 *
 * FIXME: needs doc
 */
void eeconfig_init_quantum(void) {
  eeprom_update_word(EECONFIG_MAGIC,          EECONFIG_MAGIC_NUMBER);
  eeprom_update_byte(EECONFIG_DEBUG,          0);
  eeprom_update_byte(EECONFIG_DEFAULT_LAYER,  0);
  eeprom_update_byte(EECONFIG_KEYMAP,         0);
  eeprom_update_byte(EECONFIG_MOUSEKEY_ACCEL, 0);
#ifdef BACKLIGHT_ENABLE
  eeprom_update_byte(EECONFIG_BACKLIGHT,      0);
#endif
#ifdef AUDIO_ENABLE
  eeprom_update_byte(EECONFIG_AUDIO,             0xFF); // On by default
#endif
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
  eeprom_update_dword(EECONFIG_RGBLIGHT,      0);
#endif
#ifdef STENO_ENABLE
  eeprom_update_byte(EECONFIG_STENOMODE,      0);
#endif

  eeconfig_init_kb();
}

void eeconfig_init(void) {
  eeconfig_init_quantum();
}

/** \brief eeconfig enable
 *
 * FIXME: needs doc
 */
void eeconfig_enable(void)
{
    eeprom_update_word(EECONFIG_MAGIC, EECONFIG_MAGIC_NUMBER);
}

/** \brief eeconfig disable
 *
 * FIXME: needs doc
 */
void eeconfig_disable(void)
{
    eeprom_update_word(EECONFIG_MAGIC, EECONFIG_MAGIC_NUMBER_OFF);
}

/** \brief eeconfig is enabled
 *
 * FIXME: needs doc
 */
bool eeconfig_is_enabled(void)
{
    return (eeprom_read_word(EECONFIG_MAGIC) == EECONFIG_MAGIC_NUMBER);
}

/** \brief eeconfig is disabled
 *
 * FIXME: needs doc
 */
bool eeconfig_is_disabled(void)
{
    return (eeprom_read_word(EECONFIG_MAGIC) == EECONFIG_MAGIC_NUMBER_OFF);
}

/** \brief eeconfig read debug
 *
 * FIXME: needs doc
 */
uint8_t eeconfig_read_debug(void)      { return eeprom_read_byte(EECONFIG_DEBUG); }
/** \brief eeconfig update debug
 *
 * FIXME: needs doc
 */
void eeconfig_update_debug(uint8_t val) { eeprom_update_byte(EECONFIG_DEBUG, val); }

/** \brief eeconfig read default layer
 *
 * FIXME: needs doc
 */
uint8_t eeconfig_read_default_layer(void)      { return eeprom_read_byte(EECONFIG_DEFAULT_LAYER); }
/** \brief eeconfig update default layer
 *
 * FIXME: needs doc
 */
void eeconfig_update_default_layer(uint8_t val) { eeprom_update_byte(EECONFIG_DEFAULT_LAYER, val); }

/** \brief eeconfig read keymap
 *
 * FIXME: needs doc
 */
uint8_t eeconfig_read_keymap(void)      { return eeprom_read_byte(EECONFIG_KEYMAP); }
/** \brief eeconfig update keymap
 *
 * FIXME: needs doc
 */
void eeconfig_update_keymap(uint8_t val) { eeprom_update_byte(EECONFIG_KEYMAP, val); }

#ifdef BACKLIGHT_ENABLE
/** \brief eeconfig read backlight
 *
 * FIXME: needs doc
 */
uint8_t eeconfig_read_backlight(void)      { return eeprom_read_byte(EECONFIG_BACKLIGHT); }
/** \brief eeconfig update backlight
 *
 * FIXME: needs doc
 */
void eeconfig_update_backlight(uint8_t val) { eeprom_update_byte(EECONFIG_BACKLIGHT, val); }
#endif

#ifdef AUDIO_ENABLE
/** \brief eeconfig read audio
 *
 * FIXME: needs doc
 */
uint8_t eeconfig_read_audio(void)      { return eeprom_read_byte(EECONFIG_AUDIO); }
/** \brief eeconfig update audio
 *
 * FIXME: needs doc
 */
void eeconfig_update_audio(uint8_t val) { eeprom_update_byte(EECONFIG_AUDIO, val); }
#endif

/** \brief eeconfig read kb
 *
 * FIXME: needs doc
 */
uint32_t eeconfig_read_kb(void)      { return eeprom_read_dword(EECONFIG_KEYBOARD); }
/** \brief eeconfig update kb
 *
 * FIXME: needs doc
 */

void eeconfig_update_kb(uint32_t val) { eeprom_update_dword(EECONFIG_KEYBOARD, val); }
/** \brief eeconfig read user
 *
 * FIXME: needs doc
 */
uint32_t eeconfig_read_user(void)      { return eeprom_read_dword(EECONFIG_USER); }
/** \brief eeconfig update user
 *
 * FIXME: needs doc
 */
void eeconfig_update_user(uint32_t val) { eeprom_update_dword(EECONFIG_USER, val); }


