#ifndef PROJECT_SOFT_BODY_FACTORY_H
#define PROJECT_SOFT_BODY_FACTORY_H

#include <memory>

class ControlBox;

class ControlBoxFactory {
public:
    ControlBoxFactory();
    ~ControlBoxFactory();

    std::shared_ptr<ControlBox> CreateControlBox();
private:
};


#endif //PROJECT_SOFT_BODY_FACTORY_H
