#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QDebug>
#include <QRandomGenerator>
#include <QTimer>
#include "tictactoe.h"

void initializeBoardGUI(QGridLayout* gridLayout) {
    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            QPushButton* button = qobject_cast<QPushButton*>(gridLayout->itemAtPosition(row, col)->widget());
            if (button) {
                button->setText("");
                button->setEnabled(true);
            }
        }
    }
}

void disableAllButtons(QGridLayout* gridLayout) {
    for (int i = 0; i < gridLayout->count(); ++i) {
        auto item = gridLayout->itemAt(i);
        if (item) {
            auto button = qobject_cast<QPushButton*>(item->widget());
            if (button) {
                button->setEnabled(false);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Tic-Tac-Toe");

    QGridLayout *gridLayout = new QGridLayout;

    // Initialize the Tic-Tac-Toe board and determine the starting player
    initializeBoard();
    int playersign = QRandomGenerator::global()->generate() % 2;
    char player = playersign ? 'X' : 'O';
    char aiPlayer = !playersign ? 'X' : 'O';
    char currentPlayer = player;

    qDebug() << "player = " << player << " ai = " << aiPlayer;
    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            QPushButton *button = new QPushButton("", &mainWindow);
            button->setFixedSize(100, 100);
            gridLayout->addWidget(button, row, col);

            QObject::connect(button, &QPushButton::clicked, [=, &currentPlayer, &gridLayout]() {
                if (button->text().isEmpty()) {
                    // Map the button click to the Tic-Tac-Toe board coordinates
                    const char currentPlayerCr = currentPlayer;
                    int boardRow = row;
                    int boardCol = col;

                    board[boardRow][boardCol] = currentPlayerCr;
                    
                    button->setText(QString(currentPlayerCr));
                    button->setEnabled(false);

                    currentPlayer = currentPlayer == player ? aiPlayer : player;

                    if (checkWin(currentPlayerCr)) {
                        qDebug() << currentPlayerCr  << "wins!";
                        disableAllButtons(gridLayout);
                        initializeBoard();
                        QTimer::singleShot(5000, [=]() {
                            initializeBoardGUI(gridLayout);
                        }); 
                    } else if (isBoardFull()) {
                        qDebug() << "It's a tie!";
                        disableAllButtons(gridLayout);
                        initializeBoard();
                        QTimer::singleShot(5000, [=]() {
                            initializeBoardGUI(gridLayout);
                        }); 
                    } else {
                        // If it's the AI's turn, make the AI move
                        if (currentPlayer == aiPlayer) {
                            int ai_row = 0 , ai_col = 0;
                            makeAIMove(player, aiPlayer, &ai_row, &ai_col);
                            auto *but = gridLayout->itemAtPosition(ai_row, ai_col);
                            qDebug() << "ai player move " << ai_col << ", " << ai_row;
                            QMetaObject::invokeMethod(qobject_cast<QObject*>(but->widget()), "clicked", Qt::AutoConnection);
                        }
                    }
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
