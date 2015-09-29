#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QFrame>
#include <QMouseEvent>

class Board : public QFrame
{
    Q_OBJECT
public:
    Board(QWidget *parent = 0);

public slots:
     void start();
     void clear();
     void update_arrays();

private:
     enum {width_count = 43, height_count = 31};
     enum {DEAD, ALIVE};
     enum {board_height = 450, board_width = 630};
     enum {outer_border = 15, inner_border = 13};
     short old_cells[width_count][height_count], new_cells[width_count][height_count];
     bool is_changed;
     bool is_game_on;
     QTimer *timer;
     void update_view();
     void clear_arrays();
     int count_neighbours(int i, int j);
     void stop_game();

     void mousePressEvent(QMouseEvent *event);
     void paintEvent(QPaintEvent *event);
};

#endif // BOARD_H
