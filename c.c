/*#include "./c.h"*/
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>
#include <X11/extensions/Xfixes.h>

extern void GoCallback(char* out, int out_len);

bool GetSelection(
	Display *display, Window window, const char *bufname, const char *fmtname)
{
	char *result;
	unsigned long ressize, restail;
	int resbits;

	Atom bufid = XInternAtom(display, bufname, False),
		fmtid = XInternAtom(display, fmtname, False),
		propid = XInternAtom(display, "XSEL_DATA", False),
		incrid = XInternAtom(display, "INCR", False);

	XEvent event;

	XConvertSelection(display, bufid, fmtid, propid, window, CurrentTime);
	do {
		XNextEvent(display, &event);
	} while (event.type != SelectionNotify || event.xselection.selection != bufid);

	if (event.xselection.property)
	{
		XGetWindowProperty(display, window, propid, 0, LONG_MAX/4, False, AnyPropertyType,
			&fmtid, &resbits, &ressize, &restail, (unsigned char**)&result);

			if (fmtid == incrid) {
			//printf("Buffer is too large and INCR reading is not implemented yet.\n");
			// https://stackoverflow.com/questions/27378318/c-get-string-from-clipboard-on-linux/44992938#44992938
			} else {
				GoCallback(result, ressize);
			}

		XFree(result);
		return true;
	}
	else // request failed, e.g. owner can't convert to the target format
		return false;
}
bool WatchClipboard()
{
	const char* bufname = "CLIPBOARD";
	Display *display = XOpenDisplay(NULL);
	unsigned long color = BlackPixel(display, DefaultScreen(display));
	Window window = XCreateSimpleWindow(display, DefaultRootWindow(display), 0,0, 1,1, 0, color, color);


	int event_base, error_base;
	XEvent event;
	Atom bufid = XInternAtom(display, bufname, False);

	if (! XFixesQueryExtension(display, &event_base, &error_base) ) {
		return false;
	}
	XFixesSelectSelectionInput(display, DefaultRootWindow(display), bufid, XFixesSetSelectionOwnerNotifyMask);

	while (true) {
		XNextEvent(display, &event);

		if (event.type == event_base + XFixesSelectionNotify &&
			((XFixesSelectionNotifyEvent*)&event)->selection == bufid)
		{
			if(!GetSelection(display, window, bufname, "UTF8_STRING")) {
				GetSelection(display, window, bufname, "STRING");
			}
		}
	}
	XDestroyWindow(display, window);
	XCloseDisplay(display);
	return true;
}
