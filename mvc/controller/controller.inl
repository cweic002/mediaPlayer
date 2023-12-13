#include "controller.h"

template <typename T>
Controller::ControllerCRTP<T>::ControllerCRTP(T * model):model(model){}

template <typename T>
Controller::ControllerCRTP<T>::ControllerCRTP(std::shared_ptr<T> & model):model(model){}

template <typename T>
Controller::ControllerCRTP<T>::~ControllerCRTP(){}

template <typename T>
inline void Controller::ControllerCRTP<T>::setModel(std::shared_ptr<T> & model){
    this->model = model;
}

template <typename T>
inline std::shared_ptr<T> Controller::ControllerCRTP<T>::getModel(){
    return this->model;
}