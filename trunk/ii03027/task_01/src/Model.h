#pragma once

class Model {
public:
    virtual ~Model() = default;
    
    virtual double step(double u) = 0;
    
    virtual void reset() = 0;
};