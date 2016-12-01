/**
  ******************************************************************************
  * @file    command.c
  * @brief   Command line interpreter.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 S54MTB</center></h2>
  *
  ******************************************************************************
  */
#include <stdio.h>
#include <string.h>  // strcmp
#include <ctype.h>   // toupper
#include <stdlib.h>
#include "usbd_cdc_if.h"


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
		CMD_ERASE,
		CMD_MOVE,
		CMD_BLINK,
		CMD_TEST,
		CMD_INIT,
		CMD_RUN,
		CMD_SEND,
		CMD_FADE,
		CMD_ID,
		CMD_BEEP,
		CMD_SOUND,
		CMD_NOTE,
		CMD_PAUSE,
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
		" ERASE \n\r"
		" MOVE \n\r"
		" BLINK \n\r"
		" TEST \n\r"
		" INIT \n\r"
		" RUN \n\r"
		" SEND \n\r"
		" FADE \n\r"
		" ID \n\r"
		" BEEP \n\r"
		" SOUND \n\r"
		" NOTE \n\r"
		" PAUSE \n\r"
;
/**
*
*/
const struct cmd_st cmd_tbl [] =
{    { "LIST", 	 CMD_LIST,  }, 
    { "ERASE", 	 CMD_ERASE,  }, 
    { "MOVE", 	 CMD_MOVE,  }, 
    { "BLINK", 	 CMD_BLINK,  }, 
    { "TEST", 	 CMD_TEST,  }, 
    { "INIT", 	 CMD_INIT,  }, 
    { "RUN", 	 CMD_RUN,  }, 
    { "SEND", 	 CMD_SEND,  }, 
    { "FADE", 	 CMD_FADE,  }, 
    { "ID", 	 CMD_ID,  }, 
    { "BEEP", 	 CMD_BEEP,  }, 
    { "SOUND", 	 CMD_SOUND,  }, 
    { "NOTE", 	 CMD_NOTE,  }, 
    { "PAUSE", 	 CMD_PAUSE,  }, 
};

#define CMD_TBL_LEN (sizeof (cmd_tbl) / sizeof (cmd_tbl [0]))

/********** Command functions ***********/void cmd_LIST(char *argstr_buf);
void cmd_ERASE(char *argstr_buf);
void cmd_MOVE(char *argstr_buf);
void cmd_BLINK(char *argstr_buf);
void cmd_TEST(char *argstr_buf);
void cmd_INIT(char *argstr_buf);
void cmd_RUN(char *argstr_buf);
void cmd_SEND(char *argstr_buf);
void cmd_FADE(char *argstr_buf);
void cmd_ID(char *argstr_buf);
void cmd_BEEP(char *argstr_buf);
void cmd_SOUND(char *argstr_buf);
void cmd_NOTE(char *argstr_buf);
void cmd_PAUSE(char *argstr_buf);
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

    case CMD_ERASE:
      cmd_ERASE(argstr_buf);
    break;

    case CMD_MOVE:
      cmd_MOVE(argstr_buf);
    break;

    case CMD_BLINK:
      cmd_BLINK(argstr_buf);
    break;

    case CMD_TEST:
      cmd_TEST(argstr_buf);
    break;

    case CMD_INIT:
      cmd_INIT(argstr_buf);
    break;

    case CMD_RUN:
      cmd_RUN(argstr_buf);
    break;

    case CMD_SEND:
      cmd_SEND(argstr_buf);
    break;

    case CMD_FADE:
      cmd_FADE(argstr_buf);
    break;

    case CMD_ID:
      cmd_ID(argstr_buf);
    break;

    case CMD_BEEP:
      cmd_BEEP(argstr_buf);
    break;

    case CMD_SOUND:
      cmd_SOUND(argstr_buf);
    break;

    case CMD_NOTE:
      cmd_NOTE(argstr_buf);
    break;

    case CMD_PAUSE:
      cmd_PAUSE(argstr_buf);
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
   * CMD_ERASE
   * @brief 
   * @param Arguments string from ERASE command
   * @param None
   * @retval None
   */
void cmd_ERASE(char *argstr_buf)

{
  
  // add code here --------
  
  
  
}
  
  
  /**
   * CMD_MOVE
   * @brief 
   * @param Arguments string from MOVE command
   * @param None
   * @retval None
   */
void cmd_MOVE(char *argstr_buf)

{
  
  // add code here --------
  
  
  
}
  
  
  /**
   * CMD_BLINK
   * @brief 
   * @param Arguments string from BLINK command
   * @param None
   * @retval None
   */
void cmd_BLINK(char *argstr_buf)

{
  
  // add code here --------
  
  
  
}
  
  
  /**
   * CMD_TEST
   * @brief 
   * @param Arguments string from TEST command
   * @param None
   * @retval None
   */
void cmd_TEST(char *argstr_buf)

{
  
  // add code here --------
  
  
  
}
  
  
  /**
   * CMD_INIT
   * @brief 
   * @param Arguments string from INIT command
   * @param None
   * @retval None
   */
void cmd_INIT(char *argstr_buf)

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
   * CMD_SEND
   * @brief 
   * @param Arguments string from SEND command
   * @param None
   * @retval None
   */
void cmd_SEND(char *argstr_buf)

{
  
  // add code here --------
  
  
  
}
  
  
  /**
   * CMD_FADE
   * @brief 
   * @param Arguments string from FADE command
   * @param None
   * @retval None
   */
void cmd_FADE(char *argstr_buf)

{
  
  // add code here --------
  
  
  
}
  
  
  /**
   * CMD_ID
   * @brief 
   * @param Arguments string from ID command
   * @param None
   * @retval None
   */
void cmd_ID(char *argstr_buf)

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
  
  
  /**
   * CMD_SOUND
   * @brief 
   * @param Arguments string from SOUND command
   * @param None
   * @retval None
   */
void cmd_SOUND(char *argstr_buf)

{
  
  // add code here --------
  
  
  
}
  
  
  /**
   * CMD_NOTE
   * @brief 
   * @param Arguments string from NOTE command
   * @param None
   * @retval None
   */
void cmd_NOTE(char *argstr_buf)

{
  
  // add code here --------
  
  
  
}
  
  
  /**
   * CMD_PAUSE
   * @brief 
   * @param Arguments string from PAUSE command
   * @param None
   * @retval None
   */
void cmd_PAUSE(char *argstr_buf)

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



