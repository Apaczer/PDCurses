/************************************************************************ 
 * This file is part of PDCurses. PDCurses is public domain software;	*
 * you may use it for any purpose. This software is provided AS IS with	*
 * NO WARRANTY whatsoever.						*
 *									*
 * If you use PDCurses in an application, an acknowledgement would be	*
 * appreciated, but is not mandatory. If you make corrections or	*
 * enhancements to PDCurses, please forward them to the current		*
 * maintainer for the benefit of other users.				*
 *									*
 * No distribution of modified PDCurses code may be made under the name	*
 * "PDCurses", except by the current maintainer. (Although PDCurses is	*
 * public domain, the name is a trademark.)				*
 *									*
 * See the file maintain.er for details of the current maintainer.	*
 ************************************************************************/

#define	CURSES_LIBRARY 1
#define	INCLUDE_WINDOWS_H
#include <curses.h>

#ifdef PDCDEBUG
const char *rcsid_PDCsetsc =
	"$Id: pdcsetsc.c,v 1.13 2006/02/22 06:09:47 wmcbrine Exp $";
#endif

extern HANDLE hConOut;

/*man-start*********************************************************************

  PDC_set_80x25()	- force a known screen state: 80x25 text mode.

  PDCurses Description:
	This is a private PDCurses function.

	Forces the appropriate 80x25 alpha mode given the display adapter.

  PDCurses Return Value:
	This function returns OK upon success otherwise ERR is returned.

  PDCurses Errors:
	No errors are defined for this routine.

  Portability:
	PDCurses  int PDC_set_80x25(void);

**man-end**********************************************************************/

int PDC_set_80x25(void)
{
	PDC_LOG(("PDC_set_80x25() - called\n"));

	return OK;
}

/*man-start*********************************************************************

  PDC_set_cursor_mode()	- Set the cursor start and stop scan lines.

  PDCurses Description:
	Sets the cursor type to begin in scan line startrow and end in
	scan line endrow.  Both values should be 0-31.

  PDCurses Return Value:
	This function returns OK on success and ERR on error.

  PDCurses Errors:
	No errors are defined for this function.

  Portability:
	PDCurses  int PDC_set_cursor_mode(int startrow, int endrow);

**man-end**********************************************************************/

int PDC_set_cursor_mode(int startrow, int endrow)
{
	PDC_LOG(("PDC_set_cursor_mode() - called: startrow %d endrow %d\n",
		startrow, endrow));

	return OK;
}

/*man-start*********************************************************************

  PDC_set_font()	- sets the current font size

  PDCurses Description:
	This is a private PDCurses function.

	This routine sets the current font size, if the adapter allows
	such a change.

  PDCurses Return Value:
	This function returns OK upon success otherwise ERR is returned.

  PDCurses Errors:
	It is an error to attempt to change the font size on a "bogus"
	adapter.  The reason for this is that we have a known video
	adapter identity problem.  e.g. Two adapters report the same
	identifying characteristics.

  Portability:
	PDCurses  int PDC_set_font(int size);

**man-end**********************************************************************/

int PDC_set_font(int size)
{
	PDC_LOG(("PDC_set_font() - called\n"));

	return OK;
}

/*man-start*********************************************************************

  PDC_set_rows()	- sets the physical number of rows on screen

  PDCurses Description:
	This is a private PDCurses function.

	This routine attempts to set the number of rows on the physical
	screen to the passed value.

  PDCurses Return Value:
	This function returns OK upon success otherwise ERR is returned.

  PDCurses Errors:
	It is an error to attempt to change the screen size on a "bogus"
	adapter.  The reason for this is that we have a known video
	adapter identity problem.  e.g. Two adapters report the same
	identifying characteristics.

  Portability:
	PDCurses  int PDC_set_rows(int rows);

**man-end**********************************************************************/

int PDC_set_rows(int rows)
{
	PDC_LOG(("PDC_set_rows() - called\n"));

	return OK;
}

/*man-start*********************************************************************

  PDC_set_scrn_mode()	- Set BIOS Video Mode

  PDCurses Description:
 	Sets the BIOS Video Mode Number ONLY if it is different from
 	the current video mode.  This routine is for DOS systems only.

  PDCurses Return Value:
 	This function returns OK on success and ERR on error.

  PDCurses Errors:
 	No errors are defined for this function.

  Portability:
 	PDCurses	int PDC_set_scrn_mode( int new_mode );

**man-end**********************************************************************/

int PDC_set_scrn_mode(int new_mode)
{
	PDC_LOG(("PDC_set_scrn_mode() - called\n"));

	return OK;
}

int PDC_curs_set(int visibility)
{
	CONSOLE_CURSOR_INFO cci;
	int ret_vis;

	PDC_LOG(("PDC_curs_set() - called: visibility=%d\n", visibility));

	ret_vis = SP->visibility;

	if (GetConsoleCursorInfo(hConOut,&cci) == FALSE)
		return ERR;

	switch(visibility)
	{
	case 0:				/* invisible */
		cci.bVisible = FALSE;
		break;
	case 2:				/* highly visible */
		cci.bVisible = TRUE;
		cci.dwSize = 95;
		break;
	default:			/* normal visibility */
		cci.bVisible = TRUE;
		cci.dwSize = 25;
		break;
	}

	if (SetConsoleCursorInfo(hConOut,&cci) == FALSE)
		return ERR;

	SP->visibility = visibility;
	return ret_vis;
}

/*man-start*********************************************************************

  PDC_set_title()	- Set window title

  PDCurses Description:
	Sets the title of the window in which the curses program is 
	running. This function may not do anything on some platforms.

  Portability:
	PDCurses  void PDC_set_title(char *title);

**man-end**********************************************************************/

void PDC_set_title(char *title)
{
	PDC_LOG(("PDC_set_title() - called:<%s>\n", title));

	SetConsoleTitle(title);
	return;
}
