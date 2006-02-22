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
#include <curses.h>

/* undefine any macros for functions defined in this module */
#undef addstr
#undef addnstr
#undef waddstr
#undef waddnstr
#undef mvaddstr
#undef mvaddnstr
#undef mvwaddstr
#undef mvwaddnstr

/* undefine any macros for functions called by this module if in debug mode */
#ifdef PDCDEBUG
# undef move
# undef wmove
# undef addch
# undef waddch
#endif

#ifdef PDCDEBUG
const char *rcsid_addstr =
	"$Id: addstr.c,v 1.17 2006/02/22 06:09:47 wmcbrine Exp $";
#endif

/*man-start*********************************************************************

  Name:                                                        addstr

  Synopsis:
	int addstr(const char *str);
	int addnstr(const char *str, int n);
	int waddstr(WINDOW *win, const char *str);
	int waddnstr(WINDOW *win, const char *str, int n);
	int mvaddstr(int y, int x, const char *str);
	int mvaddnstr(int y, int x, const char *str, int n);
	int mvwaddstr(WINDOW *, int y, int x, const char *str);
	int mvwaddnstr(WINDOW *, int y, int x, const char *str, int n);

  X/Open Description:
	These routines write all the characters of the null-terminated 
	string str on the given window.  The functionality is equivalent 
	to calling waddch() once for each character in the string.  The 
	four routines with n as the last argument write at most n 
	characters.  If n is negative, then the entire string will be 
	added.

	NOTE: addstr(), addnstr(), mvaddstr(), mvaddnstr(), mvwaddstr(), 
	and mvwaddnstr() are implemented as macros.

  PDCurses Description:
	The *raw*() routines output 8 bit values.  These contrast to
	their normal counterparts which output 7 bit values and convert
	control character to the ^X notation.

	str is a standard 8 bit character string WITHOUT embedded 
	attributes.

  X/Open Return Value:
	All functions return OK on success and ERR on error.

  X/Open Errors:
	No errors are defined for this function.

  Portability				     X/Open    BSD    SYS V
					     Dec '88
	addstr					Y	Y	Y
	waddstr					Y	Y	Y
	mvaddstr				Y	Y	Y
	mvwaddstr				Y	Y	Y
	addnstr					-	-      4.0
	waddnstr				-	-      4.0
	mvaddnstr				-	-      4.0
	mvwaddnstr				-	-      4.0

**man-end**********************************************************************/

int addstr(const char *str)
{
	PDC_LOG(("addstr() - called: string=\"%s\"\n", str));

	return waddnstr(stdscr, str, -1);
}

int addnstr(const char *str, int n)
{
	PDC_LOG(("addnstr() - called: string=\"%s\" n %d \n", str, n));

	return waddnstr(stdscr, str, n);
}

int waddstr(WINDOW *win, const char *str)
{
	PDC_LOG(("waddstr() - called: string=\"%s\"\n", str));

	return waddnstr(win, str, -1);
}

int waddnstr(WINDOW *win, const char *str, int n)
{
	int i, ic;

	PDC_LOG(("waddnstr() - called: string=\"%s\" n %d \n", str, n));

	if (win == (WINDOW *)NULL)
		return ERR;

	for (ic = 0; *str && (ic < n || n < 0); ic++)
	{
		/* make negative chars positive - PJK */
		if ((i = *str++) < 0)
			i += 256;

		if (waddch(win, (chtype)i) == ERR)
			return ERR;
	}

	return OK;
}

int mvaddstr(int y, int x, const char *str)
{
	PDC_LOG(("mvaddstr() - called: y %d x %d string=\"%s\"\n", y, x, str));

	if (move(y, x) == ERR)
		return ERR;

	return waddnstr(stdscr, str, -1);
}

int mvaddnstr(int y, int x, const char *str, int n)
{
	PDC_LOG(("mvaddnstr() - called: y %d x %d string=\"%s\" n %d \n",
		y, x, str, n));

	if (move(y, x) == ERR)
		return ERR;

	return waddnstr(stdscr, str, n);
}

int mvwaddstr(WINDOW *win, int y, int x, const char *str)
{
	PDC_LOG(("mvwaddstr() - called: string=\"%s\"\n", str));

	if (wmove(win, y, x) == ERR)
		return ERR;

	return waddnstr(win, str, -1);
}

int mvwaddnstr(WINDOW *win, int y, int x,
			 const char *str, int n)
{
	PDC_LOG(("mvwaddnstr() - called: y %d x %d string=\"%s\" n %d \n",
		y, x, str, n));

	if (wmove(win, y, x) == ERR)
		return ERR;

	return waddnstr(win, str, n);
}
