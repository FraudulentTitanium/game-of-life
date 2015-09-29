#include "board.h"
#include <QTimer>
#include <QPainter>
#include <iostream>
#include <QRect>

Board::Board(QWidget *parent)  : QFrame(parent)
{
    is_game_on = false;
    clear_arrays();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_arrays()));

}

void Board::start(){
    timer->start(1000);
    is_game_on = true;
}
void Board::clear(){
    clear_arrays();
    timer->stop();
    is_game_on = false;
    repaint();
}

void Board::mousePressEvent(QMouseEvent *event)
{
    if (is_game_on == false) {
        if(event->y() < board_height && event->x() < board_width){
        int i = event->x()/outer_border+1, j = event->y()/outer_border+1;
        old_cells[i][j] = old_cells[i][j] == DEAD?ALIVE:DEAD;
        repaint();
        }
    }
}

void Board::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QColor alive_col(255, 230, 91, 255);
    QColor dead_col(255, 255, 255, 50);

    for (int i = 0; i < width_count-2; ++i){
        for (int j = 0; j < height_count-2; ++j){
            QRect *r1 = new QRect(i*outer_border, j*outer_border,inner_border, inner_border);
            if(old_cells[i+1][j+1] == ALIVE)
                painter.fillRect(*r1, alive_col);
            else
                painter.fillRect(*r1, dead_col);
        }
    }
}

void Board::clear_arrays(){
    for(int i = 1; i < width_count-1; ++i){
        for(int j = 1; j < height_count-1; ++j){
            old_cells[i][j] = new_cells[i][j] = DEAD;
        }
    }
}

int Board::count_neighbours(int i, int j){
    int counter=0;

    if(old_cells[i-1][j-1]==ALIVE) ++counter;
    if(old_cells[i-1][j]==ALIVE) ++counter;
    if(old_cells[i-1][j+1]==ALIVE) ++counter;
    if(old_cells[i][j-1]==ALIVE) ++counter;
    if(old_cells[i][j+1]==ALIVE) ++counter;
    if(old_cells[i+1][j-1]==ALIVE) ++counter;
    if(old_cells[i+1][j]==ALIVE) ++counter;
    if(old_cells[i+1][j+1]==ALIVE) ++counter;

    return counter;
}

void Board::update_arrays(){
    is_changed = false;
    int num_of_neighbours;
    for(int i = 1; i < width_count-1; ++i){
        for(int j = 1; j < height_count-1; ++j){
            num_of_neighbours = count_neighbours(i, j);

            if(old_cells[i][j] == DEAD ){
                if( num_of_neighbours == 3){
                    new_cells[i][j] = ALIVE;
                    is_changed = true;
                }
                else{
                    new_cells[i][j] = DEAD;
                }
            }
            else if(old_cells[i][j] == ALIVE){
                if (num_of_neighbours == 2 || num_of_neighbours==3){
                new_cells[i][j] = ALIVE;
                }
                else{
                new_cells[i][j] = DEAD;
                is_changed = true;
                }
            }
        }
    }

    if(is_changed == false) stop_game();

    for(int i = 1; i < width_count-1; ++i){
        for(int j = 1; j < height_count-1; ++j){
            old_cells[i][j]=new_cells[i][j];
        }
    }

    repaint();
}

void Board::stop_game(){
    timer->stop();
    is_game_on = false;
}
