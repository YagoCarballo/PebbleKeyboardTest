#include <pebble.h>

static const char letters [27][2] = {
	"Q", "W", "E", "R", "T", "Y", "U", 
	"I", "O", "P", "A", "S", "D", "F", 
	"G", "H", "J", "K", "L", "Z", "X", 
	"C", "V", "B", "N", "M", " "
};

static const char baseGroups [9][10] = {
	"Q W E", "R T Y", "U I O",
	"P A S", "D F G", "H J K",
	"L Z X", "C V B", "N M  "
};

static const char symbols [27][2] = {
	"~", "!", "@", "#", "$", "%", "^", 
	"&", "*", "(", ")", "_", "-", "+", 
	"=", "{", "}", "[", "]", ",", ".", 
	";", ":", "'", "\"", "?", "<"
};

static const char baseSymbols [9][10] = {
	"~ ! @", "# $ %", "^ & *",
	"( ) _", "- + =", "{ } [",
	"] , .", "; : '", "\" ? <"
};

static const char numbers [27][2] = {
	"1", "2", "3", "4", "5", "6", "7", 
	"8", "9", "0", "+", "-", "=", "/", 
	"*", "%", ".", "^", "(", ")", "",
	"", "", "", "", "", ""
};

static const char baseNumbers [9][10] = {
	"1 2 3", "4 5 6", "7 8 9",
	"0 + -", "= / *", "% . ^",
	"( )  ", "     ", "     "
};
	
static struct KeyboardUI
{
	Window * window;
	Layer  * windowLayer;
	TextLayer * inputLayer;
	TextLayer * letterLayers [3][3];
} ui;

static struct ScoresNameStatus
{
	bool symbols;
	bool numbers;
	int step;
	int row;
	int col;
	char text[140];
} status;

void keyboard_window_appear (Window *window) {}

void keyboard_window_load (Window *window)
{
	GRect letterBounds = GRect(4, 4, 136, 70);
	ui.inputLayer = text_layer_create(letterBounds);
	text_layer_set_text_color(ui.inputLayer, GColorBlack);
	text_layer_set_background_color(ui.inputLayer, GColorWhite);
	text_layer_set_text(ui.inputLayer, "");
	text_layer_set_font(ui.inputLayer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
	text_layer_set_text_alignment(ui.inputLayer, GTextAlignmentCenter);
	layer_add_child(ui.windowLayer, text_layer_get_layer(ui.inputLayer));
	
	int row, col, x = 8, y = 80, index = 0;
	for (row=0;row<3;row++)
	{
		x = 8;
		y = ( row * 20 ) + 4 + 80;
		
		for (col=0;col<3;col++)
		{
			x = ( col * 40 ) + 4 + 8;
		
			GRect letterBounds = GRect(x, y, 40, 20);
			ui.letterLayers[row][col] = text_layer_create(letterBounds);
			text_layer_set_text_color(ui.letterLayers[row][col], GColorWhite);
			text_layer_set_background_color(ui.letterLayers[row][col], GColorBlack);
			text_layer_set_text(ui.letterLayers[row][col], baseGroups[index]);
			text_layer_set_font(ui.letterLayers[row][col], fonts_get_system_font(FONT_KEY_GOTHIC_14));
			text_layer_set_text_alignment(ui.letterLayers[row][col], GTextAlignmentCenter);
			layer_add_child(ui.windowLayer, text_layer_get_layer(ui.letterLayers[row][col]));
			
			index++;
		}
	}
}

void updateLevel0 ()
{
	if (status.symbols == true)
	{
		text_layer_set_text(ui.letterLayers[0][0], baseSymbols[0]);
		text_layer_set_text(ui.letterLayers[0][1], baseSymbols[1]);
		text_layer_set_text(ui.letterLayers[0][2], baseSymbols[2]);
		
		text_layer_set_text(ui.letterLayers[1][0], baseSymbols[3]);
		text_layer_set_text(ui.letterLayers[1][1], baseSymbols[4]);
		text_layer_set_text(ui.letterLayers[1][2], baseSymbols[5]);
		
		text_layer_set_text(ui.letterLayers[2][0], baseSymbols[6]);
		text_layer_set_text(ui.letterLayers[2][1], baseSymbols[7]);
		text_layer_set_text(ui.letterLayers[2][2], baseSymbols[8]);
	}
	else if (status.numbers == true)
	{
		text_layer_set_text(ui.letterLayers[0][0], baseNumbers[0]);
		text_layer_set_text(ui.letterLayers[0][1], baseNumbers[1]);
		text_layer_set_text(ui.letterLayers[0][2], baseNumbers[2]);
		
		text_layer_set_text(ui.letterLayers[1][0], baseNumbers[3]);
		text_layer_set_text(ui.letterLayers[1][1], baseNumbers[4]);
		text_layer_set_text(ui.letterLayers[1][2], baseNumbers[5]);
		
		text_layer_set_text(ui.letterLayers[2][0], baseNumbers[6]);
		text_layer_set_text(ui.letterLayers[2][1], baseNumbers[7]);
		text_layer_set_text(ui.letterLayers[2][2], baseNumbers[8]);
	}
	else
	{
		text_layer_set_text(ui.letterLayers[0][0], baseGroups[0]);
		text_layer_set_text(ui.letterLayers[0][1], baseGroups[1]);
		text_layer_set_text(ui.letterLayers[0][2], baseGroups[2]);
		
		text_layer_set_text(ui.letterLayers[1][0], baseGroups[3]);
		text_layer_set_text(ui.letterLayers[1][1], baseGroups[4]);
		text_layer_set_text(ui.letterLayers[1][2], baseGroups[5]);
		
		text_layer_set_text(ui.letterLayers[2][0], baseGroups[6]);
		text_layer_set_text(ui.letterLayers[2][1], baseGroups[7]);
		text_layer_set_text(ui.letterLayers[2][2], baseGroups[8]);
	}
	
	status.step = 0;
}

void updateLevel2 ()
{
	if (status.symbols == true)
	{
		text_layer_set_text(ui.letterLayers[0][0], symbols[( 9 * status.row )]);
		text_layer_set_text(ui.letterLayers[0][1], symbols[( 9 * status.row ) + 1]);
		text_layer_set_text(ui.letterLayers[0][2], symbols[( 9 * status.row ) + 2]);
		
		text_layer_set_text(ui.letterLayers[1][0], symbols[( 9 * status.row ) + 3]);
		text_layer_set_text(ui.letterLayers[1][1], symbols[( 9 * status.row ) + 4]);
		text_layer_set_text(ui.letterLayers[1][2], symbols[( 9 * status.row ) + 5]);
		
		text_layer_set_text(ui.letterLayers[2][0], symbols[( 9 * status.row ) + 6]);
		text_layer_set_text(ui.letterLayers[2][1], symbols[( 9 * status.row ) + 7]);
		text_layer_set_text(ui.letterLayers[2][2], symbols[( 9 * status.row ) + 8]);
	}
	else if (status.numbers == true)
	{
		text_layer_set_text(ui.letterLayers[0][0], numbers[( 9 * status.row )]);
		text_layer_set_text(ui.letterLayers[0][1], numbers[( 9 * status.row ) + 1]);
		text_layer_set_text(ui.letterLayers[0][2], numbers[( 9 * status.row ) + 2]);
		
		text_layer_set_text(ui.letterLayers[1][0], numbers[( 9 * status.row ) + 3]);
		text_layer_set_text(ui.letterLayers[1][1], numbers[( 9 * status.row ) + 4]);
		text_layer_set_text(ui.letterLayers[1][2], numbers[( 9 * status.row ) + 5]);
		
		text_layer_set_text(ui.letterLayers[2][0], numbers[( 9 * status.row ) + 6]);
		text_layer_set_text(ui.letterLayers[2][1], numbers[( 9 * status.row ) + 7]);
		text_layer_set_text(ui.letterLayers[2][2], numbers[( 9 * status.row ) + 8]);
	}
	else
	{
		text_layer_set_text(ui.letterLayers[0][0], letters[( 9 * status.row )]);
		text_layer_set_text(ui.letterLayers[0][1], letters[( 9 * status.row ) + 1]);
		text_layer_set_text(ui.letterLayers[0][2], letters[( 9 * status.row ) + 2]);

		text_layer_set_text(ui.letterLayers[1][0], letters[( 9 * status.row ) + 3]);
		text_layer_set_text(ui.letterLayers[1][1], letters[( 9 * status.row ) + 4]);
		text_layer_set_text(ui.letterLayers[1][2], letters[( 9 * status.row ) + 5]);

		text_layer_set_text(ui.letterLayers[2][0], letters[( 9 * status.row ) + 6]);
		text_layer_set_text(ui.letterLayers[2][1], letters[( 9 * status.row ) + 7]);
		text_layer_set_text(ui.letterLayers[2][2], letters[( 9 * status.row ) + 8]);
	}
	
	status.step = 1;
}

void updateLevel3 ()
{
	if (status.symbols == true)
	{
		text_layer_set_text(ui.letterLayers[0][0], "");
		text_layer_set_text(ui.letterLayers[0][1], symbols[( 9 * status.row ) + (status.col * 3)]);
		text_layer_set_text(ui.letterLayers[0][2], "");

		text_layer_set_text(ui.letterLayers[1][0], "");
		text_layer_set_text(ui.letterLayers[1][1], symbols[( 9 * status.row ) + 1 + (status.col * 3)]);
		text_layer_set_text(ui.letterLayers[1][2], "");

		text_layer_set_text(ui.letterLayers[2][0], "");
		text_layer_set_text(ui.letterLayers[2][1], symbols[( 9 * status.row ) + 2 + (status.col * 3)]);
		text_layer_set_text(ui.letterLayers[2][2], "");
	}
	else if (status.numbers == true)
	{
		text_layer_set_text(ui.letterLayers[0][0], "");
		text_layer_set_text(ui.letterLayers[0][1], numbers[( 9 * status.row ) + (status.col * 3)]);
		text_layer_set_text(ui.letterLayers[0][2], "");

		text_layer_set_text(ui.letterLayers[1][0], "");
		text_layer_set_text(ui.letterLayers[1][1], numbers[( 9 * status.row ) + 1 + (status.col * 3)]);
		text_layer_set_text(ui.letterLayers[1][2], "");

		text_layer_set_text(ui.letterLayers[2][0], "");
		text_layer_set_text(ui.letterLayers[2][1], numbers[( 9 * status.row ) + 2 + (status.col * 3)]);
		text_layer_set_text(ui.letterLayers[2][2], "");
	}
	else
	{
		text_layer_set_text(ui.letterLayers[0][0], "");
		text_layer_set_text(ui.letterLayers[0][1], letters[( 9 * status.row ) + (status.col * 3)]);
		text_layer_set_text(ui.letterLayers[0][2], "");

		text_layer_set_text(ui.letterLayers[1][0], "");
		text_layer_set_text(ui.letterLayers[1][1], letters[( 9 * status.row ) + 1 + (status.col * 3)]);
		text_layer_set_text(ui.letterLayers[1][2], "");

		text_layer_set_text(ui.letterLayers[2][0], "");
		text_layer_set_text(ui.letterLayers[2][1], letters[( 9 * status.row ) + 2 + (status.col * 3)]);
		text_layer_set_text(ui.letterLayers[2][2], "");
	}
	
	status.step = 2;
}

void ParseLetter (int pos)
{
	if (status.symbols == true)
	{
		snprintf(status.text, 140, "%s%s", status.text, symbols[( 9 * status.row ) + pos + (status.col * 3)]);
	}
	else if (status.numbers == true)
	{
		snprintf(status.text, 140, "%s%s", status.text, numbers[( 9 * status.row ) + pos + (status.col * 3)]);
	}
	else
	{
		if (status.row == 2 && status.col == 2 && pos == 2)
		{
			snprintf(status.text, 140, "%s ", status.text);
		}
		else
		{
			snprintf(status.text, 140, "%s%s", status.text, letters[( 9 * status.row ) + pos + (status.col * 3)]);
		}
	}
}

/**
 * Handles the Up Button Presses
 */
void keyboard_up_click_handler(ClickRecognizerRef recognizer, void *context)
{
	if (status.step == 0)
	{
		status.row = 0;
		updateLevel2();
	}
	else if (status.step == 1)
	{
		status.col = 0;
		updateLevel3 ();
	} else {
		ParseLetter (0);
		text_layer_set_text(ui.inputLayer, status.text);
		
		status.symbols = false;
		status.numbers = false;
		updateLevel0 ();
		
		status.row = 0;
		status.col = 0;
	}
}

/**
 * Handles the Select Button Presses
 */
void keyboard_select_click_handler(ClickRecognizerRef recognizer, void *context)
{
	if (status.step == 0)
	{
		status.row = 1;
		updateLevel2();
	}
	else if (status.step == 1)
	{
		if (status.numbers == true && status.row == 2)
		{
			status.symbols = false;
			status.numbers = false;
			updateLevel0 ();

			status.row = 0;
			status.col = 0;
		}
		else
		{
			status.col = 1;
			updateLevel3 ();
		}
	} else {
		ParseLetter (1);
		text_layer_set_text(ui.inputLayer, status.text);
		
		status.symbols = false;
		status.numbers = false;
		updateLevel0 ();
		
		status.row = 0;
		status.col = 0;
	}
}

/**
 * Handles the Down Button Presses
 */
void keyboard_down_click_handler(ClickRecognizerRef recognizer, void *context)
{
	if (status.step == 0)
	{
		status.row = 2;
		updateLevel2();
	}
	else if (status.step == 1)
	{
		if (status.numbers == true && status.row == 2)
		{
			status.symbols = false;
			status.numbers = false;
			updateLevel0 ();

			status.row = 0;
			status.col = 0;
		}
		else
		{
			status.col = 2;
			updateLevel3 ();
		}
	} else {
		if (status.numbers == false || status.row != 2)
		{
			ParseLetter (2);
			text_layer_set_text(ui.inputLayer, status.text);
		}
		
		status.symbols = false;
		status.numbers = false;
		updateLevel0 ();
		
		status.row = 0;
		status.col = 0;
	}
}

/**
 * Handles the Back Button Presses
 */
void keyboard_back_click_handler(ClickRecognizerRef recognizer, void *context)
{
	if (status.step == 0)
	{
		window_stack_pop(true);
	}
	else
	{
		status.symbols = false;
		status.numbers = false;
		updateLevel0 ();
		status.row = 0;
		status.col = 0;
	}
}

void keyboard_select_long_click_handler(ClickRecognizerRef recognizer, void *context) {
	status.symbols = true;
	status.numbers = false;
	updateLevel0 ();
	status.row = 0;
	status.col = 0;
}

void keyboard_select_long_click_release_handler(ClickRecognizerRef recognizer, void *context) {}

void keyboard_up_long_click_handler(ClickRecognizerRef recognizer, void *context) {
	status.text[strlen(status.text)-1] = 0;
	text_layer_set_text(ui.inputLayer, status.text);
}

void keyboard_up_long_click_release_handler(ClickRecognizerRef recognizer, void *context) {}

void keyboard_down_long_click_handler(ClickRecognizerRef recognizer, void *context) {
	status.symbols = false;
	status.numbers = true;
	updateLevel0 ();
	status.row = 0;
	status.col = 0;
}

void keyboard_down_long_click_release_handler(ClickRecognizerRef recognizer, void *context) {}

/**
 * Adds listeners for the Buttons
 */
static void keyboard_click_config_provider(void *context) {
	window_single_click_subscribe(BUTTON_ID_SELECT, keyboard_select_click_handler);
	window_single_click_subscribe(BUTTON_ID_UP, 	keyboard_up_click_handler);
	window_single_click_subscribe(BUTTON_ID_DOWN, 	keyboard_down_click_handler);
	window_single_click_subscribe(BUTTON_ID_BACK, 	keyboard_back_click_handler);
	
	window_long_click_subscribe(BUTTON_ID_UP, 700, keyboard_up_long_click_handler, keyboard_up_long_click_release_handler);
	window_long_click_subscribe(BUTTON_ID_SELECT, 700, keyboard_select_long_click_handler, keyboard_select_long_click_release_handler);
	window_long_click_subscribe(BUTTON_ID_DOWN, 700, keyboard_down_long_click_handler, keyboard_down_long_click_release_handler);
	// void select_long_click_handler(ClickRecognizerRef recognizer, void *context)
}

void handle_init(void)
{
	// Creates the Window and saves the Layer for later Use
	ui.window		= window_create();
	ui.windowLayer	= window_get_root_layer(ui.window);
	
	// Adds the Window Listeners
	window_set_window_handlers(ui.window, (WindowHandlers) {
    	.load	= keyboard_window_load,
		.appear	= keyboard_window_appear
	});
	
	// Adds the Button Listeners
	window_set_click_config_provider(ui.window, keyboard_click_config_provider);
	
	// Makes the Window Vissible with an animation
	const bool animated = true;
	window_stack_push(ui.window, animated);
}

void handle_deinit(void)
{
	window_destroy(ui.window);
}

int main(void)
{
  handle_init();
  app_event_loop();
  handle_deinit();
}

