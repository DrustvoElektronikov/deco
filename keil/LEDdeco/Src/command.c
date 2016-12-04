/**
  ******************************************************************************
  * @file    command.c
  * @brief   Command line interpreter.
  ******************************************************************************
  * @attention
  *
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
#include <stdio.h>
#include <string.h>  // strcmp
#include <ctype.h>   // toupper
#include <stdlib.h>

#include "usbd_cdc_if.h"
#include "CDC_receiver.h"


#define MAX_CMD_LEN 128

/** Globals */
static char cmdstr_buf [1 + MAX_CMD_LEN];
static char argstr_buf [1 + MAX_CMD_LEN];
char newline [1 + MAX_CMD_LEN];



/**
 *
 * Command identifiers
 */
enum
  {
  		CMD_LIST,
		CMD_RUN,
		CMD_STOP,
		CMD_BEEP,
// Add more 
CMD_LAST
};


// command table
struct cmd_st
{
const char *cmdstr;
int id;
};

/**
* @brief Help text 
*/
const char helptext[] = 
"Commands:\n\r"		" LIST \n\r"
		" RUN \n\r"
		" STOP \n\r"
		" BEEP \n\r"
;
/**
*
*/
const struct cmd_st cmd_tbl [] =
{    { "LIST", 	 CMD_LIST,  }, 
    { "RUN", 	 CMD_RUN,  }, 
    { "STOP", 	 CMD_STOP,  }, 
    { "BEEP", 	 CMD_BEEP,  }, 
};

#define CMD_TBL_LEN (sizeof (cmd_tbl) / sizeof (cmd_tbl [0]))

/********** Command functions ***********/void cmd_LIST(char *argstr_buf);
void cmd_RUN(char *argstr_buf);
void cmd_STOP(char *argstr_buf);
void cmd_BEEP(char *argstr_buf);
void cmd_unknown(char *argstr_buf);


/*********************************************************************
 * Function:        static unsigned char cmdid_search
 * PreCondition:    -
 * Input:           command string  
 * Output:          command identifier
 * Side Effects:    -
 * Overview:        This function searches the cmd_tbl for a specific 
 *          command and returns the ID associated with that 
 *          command or CID_LAST if there is no matching command.
 * Note:            None
 ********************************************************************/
static int cmdid_search (char *cmdstr) {
  const struct cmd_st *ctp;

  for (ctp = cmd_tbl; ctp < &cmd_tbl [CMD_TBL_LEN]; ctp++) {
    if (strcmp (ctp->cmdstr, cmdstr) == 0) return (ctp->id);
  }

  return (CMD_LAST);
}

/*********************************************************************
 * Function:        char *strupr ( char *src)
 * PreCondition:    -
 * Input:           string  
 * Output:          Uppercase of string
 * Side Effects:    -
 * Overview:        change to uppercase
 * Note:            None
 ********************************************************************/
char *strupr (char *src) {
  char *s;

  for (s = src; *s != '\0'; s++)
    *s = toupper (*s);

  return (src);
}

/*********************************************************************
 * Function:        void cmd_proc (const char *cmd)
 * PreCondition:    -
 * Input:           command line  
 * Output:           None
 * Side Effects:    Depends on command
 * Overview:        This function processes the cmd command.
 * Note:            The "big case" is here
 ********************************************************************/
void cmd_proc (char *cmd)
{
  char *argsep;
  unsigned int id;
/*------------------------------------------------
First, copy the command and convert it to all
uppercase.
------------------------------------------------*/
  strncpy (cmdstr_buf, cmd, sizeof (cmdstr_buf) - 1);
  cmdstr_buf [sizeof (cmdstr_buf) - 1] = '\0';
  strupr (cmdstr_buf);
  //skip empty commands
  if (cmdstr_buf[0] == '\0')
    return;
/*------------------------------------------------
Next, find the end of the first thing in the
buffer.  Since the command ends with a space,
we'll look for that.  NULL-Terminate the command
and keep a pointer to the arguments.
------------------------------------------------*/
  argsep = strchr (cmdstr_buf, ' ');  
  if (argsep == NULL) {
    argstr_buf [0] = '\0';
  } else {
    strcpy (argstr_buf, argsep + 1);
    *argsep = '\0';
  }

/*------------------------------------------------
Search for a command ID, then switch on it.  Each
function invoked here.
------------------------------------------------*/
  id = cmdid_search (cmdstr_buf);
  
  switch (id)
  {    case CMD_LIST:
      cmd_LIST(argstr_buf);
    break;

    case CMD_RUN:
      cmd_RUN(argstr_buf);
    break;

    case CMD_STOP:
      cmd_STOP(argstr_buf);
    break;

    case CMD_BEEP:
      cmd_BEEP(argstr_buf);
    break;

    case CMD_LAST:
      cmd_unknown(cmdstr_buf);
    break;
  }
}/**
   * CMD_LIST
   * @brief 
   * @param Arguments string from LIST command
   * @param None
   * @retval None
   */
void cmd_LIST(char *argstr_buf)

{
  
  // add code here --------
  
  
  
}
  
  
  /**
   * CMD_RUN
   * @brief 
   * @param Arguments string from RUN command
   * @param None
   * @retval None
   */
void cmd_RUN(char *argstr_buf)

{
  
  // add code here --------
  
  
  
}
  
  
  /**
   * CMD_STOP
   * @brief 
   * @param Arguments string from STOP command
   * @param None
   * @retval None
   */
void cmd_STOP(char *argstr_buf)

{
  
  // add code here --------
  
  
  
}
  
  
  /**
   * CMD_BEEP
   * @brief 
   * @param Arguments string from BEEP command
   * @param None
   * @retval None
   */
void cmd_BEEP(char *argstr_buf)

{
  
  // add code here --------
  
  
  
}
  

  void cmd_unknown(char * argstr_buf)
{
	char txt[64];
	snprintf(txt, 64, "Unknown command.\n");
	CDC_Transmit_FS((uint8_t *)txt, strlen(txt));
    /// print out helptext[] or something like that
	
}

/*** End of file command.c */



