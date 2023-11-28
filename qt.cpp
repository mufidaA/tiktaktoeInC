#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QDebug>
#include <QRandomGenerator>  

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Tic-Tac-Toe");

    QGridLayout *gridLayout = new QGridLayout;

    bool isPlayerX = QRandomGenerator::global()->generate() % 2 == 0;

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            QPushButton *button = new QPushButton("", &mainWindow);
            button->setFixedSize(100, 100);
            gridLayout->addWidget(button, row, col);

            QObject::connect(button, &QPushButton::clicked, [=, &isPlayerX]() {
                if (button->text().isEmpty()) {
                    qDebug() << "Clicked at:" << row + 1 << col + 1;
                    button->setText(isPlayerX ? "X" : "O");
                    button->setEnabled(false);
                    isPlayerX = !isPlayerX;  // Toggle the player for the next move
                }
            });
        }
    }

   
    QWidget *centralWidget = new QWidget(&mainWindow);
    centralWidget->setLayout(gridLayout);
    mainWindow.setCentralWidget(centralWidget);

    mainWindow.show();

    return app.exec();
}
