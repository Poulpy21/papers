
#ifndef WAVELET_H
#define WAVELET_H

#include "interval.hpp"

template <typename T>
class Wavelet {
    
    public:
        virtual ~Wavelet();
    
        virtual T operator()(T x) const = 0;
        virtual T operator()(unsigned int j, int k, T x) const = 0;

        Interval<T> support() const;
        
        void plot(Gnuplot &gp, unsigned int nPoints, unsigned int j, int k) const;

    protected:
        explicit Wavelet(const Interval<T> &support);
        Wavelet(const Wavelet<T> &other);
        
        Interval<T> _support;
};
        
template <typename T>
Wavelet<T>::Wavelet(const Interval<T> &support) : _support(support) {
}

template <typename T>
Wavelet<T>::Wavelet(const Wavelet<T> &other) : _support(other.support()) {
}

template <typename T>
Wavelet<T>::~Wavelet() {
}

template <typename T>
Interval<T> Wavelet<T>::support() const {
    return _support;
}
        
template <typename T>
void Wavelet<T>::plot(Gnuplot &gp, unsigned int nPoints, unsigned int j = 0u, int k = 0) const {
    
    std::vector<std::tuple<T,T>> pts;
    
    T dx = this->support().length()/(nPoints - 1u);
    for (unsigned int i = 0; i < nPoints; i++) {
        T x = this->support().inf + i*dx;
        pts.push_back(std::make_tuple(x, this->operator()(j,k,x)));
    }
    
    gp << "set xr [" << this->support().inf << ":" << this->support().sup <<  "]\n";
    gp << "set yr [0:1]\n";
    gp << "set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 1.5\n";
    gp << "plot '-' with linespoints ls 1 title 'wavelet'\n";
    gp.send1d(pts);
}   

#endif /* end of include guard: WAVELET_H */