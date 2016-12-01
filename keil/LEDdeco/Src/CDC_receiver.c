/**
  ******************************************************************************
  * @file    CDC_receiver.c
  * @brief   Comm Device Class based Line editor
  ******************************************************************************
  * @attention
  *
			This is free and unencumbered software released into the public domain.

			Anyone is free to copy, modify, publish, use, compile, sell, or
			distribute this software, either in source code form or as a compiled
			binary, for any purpose, commercial or non-commercial, and by any
			means.

			In jurisdictions that recognize copyright laws, the author or authors
			of this software dedicate any and all copyright interest in the
			software to the public domain. We make this dedication for the benefit
			of the public at large and to the detriment of our heirs and
			successors. We intend this dedication to be an overt act of
			relinquishment in perpetuity of all present and future rights to this
			software under copyright law.

			THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
			EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
			MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
			IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
			OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
			ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
			OTHER DEALINGS IN THE SOFTWARE.

			For more information, please refer to <http://unlicense.org>
			*
  ******************************************************************************
  */ 


/**
 * Command line edit chars
 */
#define CNTLQ      0x11
#define CNTLS      0x13
#define DEL        0x7F
#define BACKSPACE  0x08
#define CR         0x0D
#define LF         0x0A

static unsigned char line_flag; 			// Flag to indicate new received line
char line_buf[256];
int line_idx = 0;
#ifdef AUTORUN
  extern void abort_autorun(void);
#endif

#ifdef LOCALECHO
	#undef LOCALECHO
#endif

/**
 * Process received char, check if LF or CR received
 * Set flag when line is done
 */
void process_rx_char(char rx_char)
{
#ifdef AUTORUN
		abort_autorun();
#endif
	
    if (rx_char == CR)  rx_char = LF;   
    if (rx_char == BACKSPACE  ||  rx_char == DEL) 
    {    // process backspace
      	if (line_idx != 0)  
      	{            
        	line_idx--;                      // decrement index
        	#ifdef LOCALECHO
        		putchar (BACKSPACE);               // echo backspace
        		putchar (' ');
        		putchar (BACKSPACE);
        	#endif
      	}
    }
    else 
    {
      	#ifdef LOCALECHO
      		putchar (rx_char);                   // echo 
      	#endif 
      	line_buf[line_idx++] = rx_char; 	   // store character and increment index
    }
    
    // check limit and end line feed
  	if ((line_idx == 0xff)  ||  (rx_char == LF))
  	{
  		line_buf[line_idx-1] = 0;                  // mark end of string
  		line_idx = 0;
			line_flag = 1;
  	}
}

/**
 * Indicate new line received via UART. 
 * Return 1 when new line received. Status flag is cleared to 0.
 * Return 0 if new line is not received yet
 */
unsigned char is_line_received(void)
{
	if (line_flag == 1)
	{
		line_flag = 0;
		return 1;
	}
	else
	{
		return 0;
	}
}

char *get_line_buffer(void)
{
	return line_buf;
}

