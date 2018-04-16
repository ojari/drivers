#include "hw.h"
#include "hal.h"
#include "keyboard.h"

uint8_t layouts[KEYBOARD_LAYOUTS][KEYBOARD_ROWS][KEYBOARD_COLS] = {
/*    {
	{ K_ESC,    K_1, K_2, K_3, K_4, K_5, K_6, K_7, K_8, K_9, K_0  },
	{ K_TAB,    K_Q, K_W, K_E, K_R, K_T, K_Y, K_U, K_I, K_O, K_P  },
	{ K_LCTRL,  K_A, K_S, K_D, K_F, K_G, K_H, K_J, K_K, K_L, K_O  },
	{ K_LSHIFT, K_?, K_Z, K_X, K_C, K_V, K_B, K_N, K_M, K_?, K_?  },
	{ 2, 3, 4 },
    }, */
    {
	{ K_A, K_B },
	{ K_C, K_D }
    },
    {
	{ K_1, K_2 },
	{ K_3, K_4 }
    },
    {
	{ K_E, K_F },
	{ K_G, K_H }
    }
};
	

void keyboard_init(keyboard *self)
{
    for (uint8_t r=0; r<KEYBOARD_ROWS; r++) {
	self->matrix[r] = 0;
	self->matrix_debounce[r] = 0;
    }
    self->modifiers = 0;
}

uint8_t keyboard_map(keyboard *self, uint8_t row, uint8_t col)
{
    //@todo select correct layer
    //
    return layouts[0][row][col];
}

void keyboard_scan(keyboard *self, func_keychange evKeyChange)
{
    uint8_t colval;

    for (uint8_t row=0; row<KEYBOARD_ROWS; row++) {
	io_set(self->pin_rows[row]);
	// delay_us(10);
	
	colval = 0;
	for (uint8_t col=0; col<KEYBOARD_COLS; col++) {
	    if (io_read(self->pin_cols[col])) {
		colval |= 1 << col;
	    }
	}

	if (colval != self->matrix_debounce[row]) {
	    self->matrix_debounce[row] = colval;
	}
	else {
	    if (colval != self->matrix[row]) {

		// check which bit is changed
		//
		for (uint8_t col=0; col<KEYBOARD_COLS; col++) {
		    uint8_t bit = 1 << col;
		    if ((colval & bit) != (self->matrix[row] & bit)) {
			(*evKeyChange)(col, row, colval & bit);
		    }
		}

		self->matrix[row] = colval;
	    }
	}
	io_clear(self->pin_rows[row]);
    }
}

void keyboard_dump(keyboard *self, buffer_t *buf)
{
    
}
