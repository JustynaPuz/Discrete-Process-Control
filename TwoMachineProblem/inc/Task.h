//
// Created by Justyna on 11.03.2024.
//

#ifndef SINGLE_TASK_H
#define SINGLE_TASK_H

class Task {
    double p_j, r_j,q_j;
    int index;

public:
    Task(double p_j,double r_j, double q_j, int index) {
        this->p_j = p_j;
        this->q_j= q_j;
        this->r_j = r_j;
        this->index = index;
    }

    double getR() {return r_j;}
    double getR() const {return r_j;}
    double getQ() {return  q_j;}
    double getQ() const {return  q_j;}
    double getP() {return p_j;}
    void setP(double p) {this->p_j=p;}
    int getIndex() {return index;}

};

#endif //SINGLE_TASK_H
