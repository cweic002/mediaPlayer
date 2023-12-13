#pragma once

#include <memory>

namespace Controller{
    template <typename T>
    struct ControllerCRTP{
        std::shared_ptr<T> model;
        ControllerCRTP(T * model);
        ControllerCRTP(std::shared_ptr<T> & model);
        virtual ~ControllerCRTP();
        void setModel(std::shared_ptr<T> & model);
        std::shared_ptr<T> getModel();
    };
};

#include "controller.inl"

