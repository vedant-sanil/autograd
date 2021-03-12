#ifndef HEADER_FLAG
#define HEADER_FLAG

class Tensor {

    public:
        Tensor(double (&data)[row],bool requires_grad=false, bool is_leaf=true, bool is_parameter=false);
}
#endif