#include "view.h"

template <typename T>
View::ViewCRTP<T>::ViewCRTP(T * model):model(model){}

template <typename T>
View::ViewCRTP<T>::ViewCRTP(std::shared_ptr<T> & model):model(model){}

template <typename T>
View::ViewCRTP<T>::~ViewCRTP(){}

template <typename T>
inline void View::ViewCRTP<T>::setModel(std::shared_ptr<T> & model){
    this->model = model;
}

template <typename T>
inline std::shared_ptr<T> View::ViewCRTP<T>::getModel(){
    return this->model;
}
