#pragma once

#define VIAL_KEYBOARD_UID {0x89, 0x36, 0x2A, 0xC7, 0xFA, 0xD8, 0x89, 0x45}
#define VIAL_UNLOCK_COMBO_ROWS {0, 0}
#define VIAL_UNLOCK_COMBO_COLS {0, 1}
#define DYNAMIC_KEYMAP_LAYER_COUNT 5

#define DYNAMIC_MACRO_NO_NESTING
#define DYNAMIC_MACRO_DELAY 250

// Activate Command with Left Ctrl + Right Ctrl.
#define IS_COMMAND() (get_mods() == MOD_MASK_CTRL)
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD