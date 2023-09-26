#include "filesdialog1.h"
#include "filedialog2.h"
#include "filesdialog3.h"
#include "filesdialog4.h"


#include <QApplication>
#include <vector>
#include <functional>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::vector< std::unique_ptr<QWidget> > widgets;
//    widgets.emplace_back(new FilesDialog1());
//    widgets.emplace_back(new FileDialog2());
//    widgets.emplace_back(new FilesDialog3());
    widgets.emplace_back(new FilesDialog4());

    for(auto& w : widgets)
        w->show();

    return a.exec();
}
