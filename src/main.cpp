#include <iostream>
#include <X11/Xlib.h>
#include <X11/Xatom.h>

void move_window_to_workspace(Display* display, Window window, int workspace) {
    Atom net_wm_desktop = XInternAtom(display, "_NET_WM_DESKTOP", False);

    XEvent event = {0};
    event.xclient.type = ClientMessage;
    event.xclient.message_type = net_wm_desktop;
    event.xclient.display = display;
    event.xclient.window = window;
    event.xclient.format = 32;
    event.xclient.data.l[0] = workspace;
    event.xclient.data.l[1] = CurrentTime;

    XSendEvent(display, DefaultRootWindow(display), False, SubstructureRedirectMask | SubstructureNotifyMask, &event);
}

int get_current_workspace(Display* display) {
    Atom net_current_desktop = XInternAtom(display, "_NET_CURRENT_DESKTOP", True);
    Atom actual_type;
    int actual_format;
    unsigned long nitems, bytes_after;
    unsigned char* data = nullptr;

    if (XGetWindowProperty(display, DefaultRootWindow(display), net_current_desktop, 0, 1, False, XA_CARDINAL,
                           &actual_type, &actual_format, &nitems, &bytes_after, &data) == Success) {
        if (data) {
            int current_workspace = static_cast<int>(*reinterpret_cast<unsigned long*>(data));
            XFree(data);
            return current_workspace;
        }
    }
    return -1; // Error
}

int get_number_of_workspaces(Display* display) {
    Atom net_number_of_desktops = XInternAtom(display, "_NET_NUMBER_OF_DESKTOPS", True);
    Atom actual_type;
    int actual_format;
    unsigned long nitems, bytes_after;
    unsigned char* data = nullptr;

    if (XGetWindowProperty(display, DefaultRootWindow(display), net_number_of_desktops, 0, 1, False, XA_CARDINAL,
                           &actual_type, &actual_format, &nitems, &bytes_after, &data) == Success) {
        if (data) {
            int number_of_workspaces = static_cast<int>(*reinterpret_cast<unsigned long*>(data));
            XFree(data);
            return number_of_workspaces;
        }
    }
    return -1; // Error
}

void move_window_to_workspace(Display* display, Window window, bool next){
    int current_workspace = get_current_workspace(display);
    int num_workspaces = get_number_of_workspaces(display);
    int next_workspace;
    if(next){
        next_workspace = (current_workspace + 1) % num_workspaces;
    }else{
        next_workspace = (current_workspace - 1) % num_workspaces;
    }

    move_window_to_workspace(display, window, next_workspace);
}

Window get_window_under_cursor(Display* display) {
    int root_x, root_y, win_x, win_y;
    unsigned int mask;
    Window root_window = DefaultRootWindow(display);
    Window root_return, child_return;

    XQueryPointer(display, root_window, &root_return, &child_return, &root_x, &root_y, &win_x, &win_y, &mask);

    if (child_return == None) {
        return root_return;
    } else {
        return child_return;
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <direction (next|prev)>" << std::endl;
        return 1;
    }

    std::string direction = argv[1];

    Display* display = XOpenDisplay(nullptr);
    if (!display) {
        std::cerr << "Cannot open display" << std::endl;
        return 1;
    }

    Window window = get_window_under_cursor(display);
    if (window == None) {
        std::cerr << "No window under cursor" << std::endl;
        XCloseDisplay(display);
        return 1;
    }

    if (direction == "next") {
        move_window_to_workspace(display, window, true);
    } else if (direction == "prev") {
        move_window_to_workspace(display, window, false);
    } else {
        std::cerr << "Unknown direction: " << direction << std::endl;
        return 1;
    }

    XCloseDisplay(display);
    return 0;
}
