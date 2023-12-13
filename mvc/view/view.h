#pragma once

#include <memory>

namespace View{
    template <typename T>
    struct ViewCRTP{
        std::shared_ptr<T> model;
        ViewCRTP(T * model);
        ViewCRTP(std::shared_ptr<T> & model);
        ~ViewCRTP();
        void setModel(std::shared_ptr<T> & model);
        std::shared_ptr<T> getModel();
    };
};

#include "view.inl"

