#include <iostream>
#include <iomanip>
#include <cmath>
#include <complex>
#include <vector>
#include <chrono>

using namespace std;
;
// coefficient representaion of polynomials
class Coefficient {
public:
    Coefficient();
    Coefficient(vector<complex<double>>& data, int size);
    ~Coefficient();

    complex<double>& operator[](int index);
    Coefficient operator+(Coefficient& other) const;
    Coefficient operator-(Coefficient& other) const;
    Coefficient operator*(Coefficient& other) const;
    complex<double> operator()(complex<double> value) const;
    friend ostream& operator<<(ostream& os, Coefficient& A);
    int length() const;
    Coefficient doubling() const;

private:
    int size;
    vector<complex<double>> data;
};

Coefficient::Coefficient() {}

Coefficient::Coefficient(vector<complex<double>>& data, int size) : data(data), size(size) {}

Coefficient::~Coefficient() {}

// get the value of a_i
complex<double>& Coefficient::operator[](int index) {
    return this->data[index];
}

Coefficient Coefficient::operator+(Coefficient& other) const {
    vector<complex<double>> sum(this->size);
    for (int i = 0; i < this->size; i++) {
        sum[i] = this->data[i] + other.data[i];
    }
    return Coefficient(sum, this->size);
}

Coefficient Coefficient::operator-(Coefficient& other) const {
    vector<complex<double>> sum(this->size);
    for (int i = 0; i < this->size; i++) {
        sum[i] = this->data[i] - other.data[i];
    }
    return Coefficient(sum, this->size);
}

Coefficient Coefficient::operator*(Coefficient& other) const {
    int prod_size = this->size * 2;
    vector<complex<double>> prod(prod_size, complex < double>(0.0));
    for (int i = 0; i < prod_size; i++) {
        for (int j = 0; j < this->size; j++) {
            if (i - j >= 0 && i - j < this->size) {
                prod[i] += this->data[j] * other.data[i - j];
            }
        }
    }
    return Coefficient(prod, prod_size);
}

// get the value of A(x_0)
complex<double> Coefficient::operator()(complex<double> value) const {
    complex<double> sum = 0;
    for (int i = this->size - 1; i >= 0; i--) {
        sum *= value;
        sum += this->data[i];
    }
    return sum;
}

int Coefficient::length() const {
    return this->size;
}

Coefficient Coefficient::doubling() const {
    vector<complex<double>> temp(this->data);
    temp.insert(temp.end(), this->size, complex<double>(0.0));
    return Coefficient(temp, this->size * 2);
}

ostream& operator<<(ostream& os, Coefficient& A) {
    os << '[' << fixed << setprecision(2);
    for (int i = 0; i < A.length(); i++) {
        os << noshowpos << A[i].real() << showpos << A[i].imag() << "i, ";
    }
    os << "\b\b]";
    return os;
}

// point-value representation of polynomials
class PointValue {
public:
    PointValue();
    PointValue(vector<pair<complex<double>, complex<double>>>& points, int size);
    ~PointValue();

    int length() const;
    PointValue operator+(PointValue& other) const;
    PointValue operator-(PointValue& other) const;
    PointValue operator*(PointValue& other) const;
    pair<complex<double>, complex<double>>& operator[](int index);
    friend ostream& operator<<(ostream& os, PointValue& y);

private:
    vector<pair<complex<double>, complex<double>>> points;
    int size;
};

PointValue::PointValue() {}

PointValue::PointValue(vector<pair<complex<double>, complex<double>>>& points, int size) : points(points), size(size) {}

PointValue::~PointValue() {}

int PointValue::length() const {
    return this->size;
}

PointValue PointValue::operator+(PointValue& other) const {
    vector<pair<complex<double>, complex<double>>> sum(this->size);
    for (int i = 0; i < this->size; i++) {
        pair<complex<double>, complex<double>> value;
        value.first = this->points[i].first;
        value.second = this->points[i].second + other.points[i].second;
        sum[i] = value;
    }

    return PointValue(sum, this->size);
}

PointValue PointValue::operator-(PointValue& other) const {
    vector<pair<complex<double>, complex<double>>> sum(this->size);
    for (int i = 0; i < this->size; i++) {
        pair<complex<double>, complex<double>> value;
        value.first = this->points[i].first;
        value.second = this->points[i].second - other.points[i].second;
        sum[i] = value;
    }

    return PointValue(sum, this->size);
}

PointValue PointValue::operator*(PointValue& other) const {
    vector<pair<complex<double>, complex<double>>> prod(this->size);
    for (int i = 0; i < this->size; i++) {
        pair<complex<double>, complex<double>> value;
        value.first = this->points[i].first;
        value.second = this->points[i].second * other.points[i].second;
        prod[i] = value;
    }

    return PointValue(prod, this->size);
}

// get the pair of i^{th} point
pair<complex<double>, complex<double>>& PointValue::operator[](int index) {
    return this->points[index];
}

ostream& operator<<(ostream& os, PointValue& y) {
    os << '{' << fixed << setprecision(2);
    for (int i = 0; i < y.length(); i++) {
        os << '(' << noshowpos << y[i].first.real();
        os << showpos << y[i].first.imag() << "i, ";
        os << noshowpos << y[i].second.real();
        os << showpos << y[i].second.imag() << "i), ";
    }
    os << "\b\b}";
    return os;
}

PointValue FFT_no_doubling_recursive(Coefficient& A) {
    int n = A.length();
    if (n == 1) {
        vector<pair<complex<double>, complex<double>>> temp(1);
        temp[0] = pair<complex<double>, complex<double>>(complex<double>(1.0, 0.0), A(complex<double>(1.0, 0.0)));
        return PointValue(temp, 1);
    }
 
    complex<double> w_n = exp(2.0 * 4.0 * atan(1) / n * complex<double>(0.0, 1.0));
    complex<double> w(1.0, 0.0);

    vector<complex<double>> part_even;
    vector<complex<double>> part_odd;

    for (int i = 0; i < n; i += 2) {
        part_even.push_back(A[i]);
    }
    for (int i = 1; i < n; i += 2) {
        part_odd.push_back(A[i]);
    }

    Coefficient even(part_even, n / 2);
    Coefficient odd(part_odd, n / 2);

    PointValue y_even = FFT_no_doubling_recursive(even);
    PointValue y_odd = FFT_no_doubling_recursive(odd);

    // A(w_n^k) = A_{even}((w_n^k)^2) + w_n^k A_{odd}((w_n^k)^2)
    // A(w_n^k) = A_{even}(w_{n/2}^k) + w_n^k A_{odd}(w_{n/2}^k)
    // A(w_n^{k+n/2}) = A_{even}(w_{n/2}^k) - w_n^k A_{odd}(w_{n/2}^k)
    vector<pair<complex<double>, complex<double>>> y(n);
    for (int k = 0; k < n / 2; k++) {
        y[k].first = w;
        y[k].second = y_even[k].second + w * y_odd[k].second;
        y[k + n / 2].first = -w;
        y[k + n / 2].second = y_even[k].second - w * y_odd[k].second;
        w *= w_n;
    }
    return PointValue(y, n);
}

Coefficient FFT_inv_recursive(PointValue& y) {
    int n = y.length();
    if (n == 1) {
        vector<complex<double>> temp(1);
        temp[0] = y[0].second;
        return Coefficient(temp, 1);
    }

    complex<double> w_n = exp(-2.0 * 4.0 * atan(1) / n * complex<double>(0.0, 1.0));
    complex<double> w(1.0, 0.0);

    vector<pair<complex<double>, complex<double>>> part_even;
    vector<pair<complex<double>, complex<double>>> part_odd;

    for (int i = 0; i < n; i += 2) {
        part_even.push_back(y[i]);
    }
    for (int i = 1; i < n; i += 2) {
        part_odd.push_back(y[i]);
    }

    PointValue even(part_even, n / 2);
    PointValue odd(part_odd, n / 2);

    Coefficient A_even = FFT_inv_recursive(even);
    Coefficient A_odd = FFT_inv_recursive(odd);

    // A(w_n^k) = A_{even}((w_n^k)^2) + w_n^k A_{odd}((w_n^k)^2)
    // A(w_n^k) = A_{even}(w_{n/2}^k) + w_n^k A_{odd}(w_{n/2}^k)
    // A(w_n^{k+n/2}) = A_{even}(w_{n/2}^k) - w_n^k A_{odd}(w_{n/2}^k)
    vector<complex<double>> A(n);
    for (int k = 0; k < n / 2; k++) {
        A[k] = A_even[k] + w * A_odd[k];
        A[k + n / 2] = A_even[k] - w * A_odd[k];
        w *= w_n;
    }
    return Coefficient(A, n);
}

PointValue FFT(Coefficient& A) {
    auto temp = A.doubling();
    auto pointSet = FFT_no_doubling_recursive(temp);
	return pointSet; 
}

Coefficient FFT_inv(PointValue& y) {
    int n = y.length();
    auto temp = FFT_inv_recursive(y);
    for (int i = 0; i < n; i++) {
        temp[i] /= n;
    }
    return temp;
}

int main()
{
    const int size = 4096;
    vector<complex<double>> one(size);
    for (int i = 0; i < size; i++) {
        one[i] = complex<double>((double)1, 0.0);
    }
    Coefficient A(one, size);
    Coefficient B(one, size);
    // PointValue A_ = FFT(A);
    // PointValue B_ = FFT(B);
    // cout << "Polynomial A in coefficient representation: " << A << endl;
    // cout << "Polynomial A in point value representation: " << A_ << endl;
    // cout << endl;
    // cout << "Polynomial B in coefficient representation: " << B << endl;
    // cout << "Polynomial B in point value representation: " << B_ << endl;
    // cout << endl;

    // Coefficient C = A + B;
    // PointValue C_ = A_ + B_;
    // cout << "A + B = " << C << " or " << C_ << endl;
    // cout << endl;

    // Coefficient D = A * B;
    // PointValue D_ = A_ * B_;
    // cout << "A * B = " << D << " or " << D_ << endl;
    // cout << endl;

    // Coefficient A__ = FFT_inv_recursive(C_);
    // Coefficient B__ = FFT_inv_recursive(D_);
    // cout << "FFT inverse: A = " << A << " and B = " << B << endl;
    
    auto start = chrono::high_resolution_clock::now();
	auto C = A * B;
	auto end = chrono::high_resolution_clock::now();
	double duration = (double)chrono::duration_cast<chrono::microseconds>(end - start).count();			
	cout << "Directly: "<< duration << " microseconds" << endl;


    start = chrono::high_resolution_clock::now();
	auto A_ = FFT(A);
    auto B_ = FFT(B);
    auto C_ = A_ * B_;
    auto C__ = FFT_inv(C_);
	end = chrono::high_resolution_clock::now();
	duration = (double)chrono::duration_cast<chrono::microseconds>(end - start).count();
	cout << "FFT: " <<duration << " microseconds" << endl;
	
    cout << C.length() << endl;
    cout << C__.length() << endl;
    //auto D = C - C__;
    //cout << D << endl;

    return 0;
}
