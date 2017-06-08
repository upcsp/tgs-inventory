#include <QApplication>
#include "connection.h"
#include "tableeditor.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    if (!createConnection())
        return 1;

    TableEditor editor("tgs");
    editor.resize(1100, 500);
    editor.show();
    return app.exec();
}
