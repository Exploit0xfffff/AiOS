#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    Display *display;
    Window root, window;
    XEvent event;

    // Open a connection to the X server
    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    // Get the root window of the default screen
    root = DefaultRootWindow(display);

    // Create a simple window
    window = XCreateSimpleWindow(display, root, 100, 100, 400, 300, 1,
                                 BlackPixel(display, DefaultScreen(display)),
                                 WhitePixel(display, DefaultScreen(display)));

    // Select events to monitor
    XSelectInput(display, window, ExposureMask | KeyPressMask);

    // Map the window on the screen
    XMapWindow(display, window);

    // Event loop
    while (1) {
        XNextEvent(display, &event);
        if (event.type == Expose) {
            // Handle Expose events
            // Redraw or update window contents here
        }
        if (event.type == KeyPress) {
            // Handle KeyPress events
            break; // Exit on any key press
        }
    }

    // Clean up and close the connection to X server
    XDestroyWindow(display, window);
    XCloseDisplay(display);

    return 0;
}
