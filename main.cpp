#include "videoPlayerApp.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[]) {
    if (!g_thread_supported())
        g_thread_init(NULL);
    gst_init(&argc, &argv);
    QApplication app(argc, argv);
    QtVideo window;
    window.show();
    return app.exec();
}
