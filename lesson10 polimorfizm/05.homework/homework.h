#pragma once

#include <iostream>
#include <limits>
#include <vector>

class IStatistics {
public:
	virtual ~IStatistics() {}

	virtual void update(double next) = 0;
	virtual double eval() const = 0;
	virtual const char * name() const = 0;
};

class Min : public IStatistics {
public:
    Min() : m_min{std::numeric_limits<double>::max()} {
    }

    void update(double next) override {
        if (next < m_min) {
            m_min = next;
        }
    }

    double eval() const override {
        return m_min;
    }

    const char * name() const override {
        return "min";
    }

private:
    double m_min;
};

class Max : public IStatistics {
public:
    Max() : m_min{std::numeric_limits<double>::min()} {
    }

    void update(double next) override {
        if (next > m_min) {
            m_min = next;
        }
    }

    double eval() const override {
        return m_min;
    }

    const char * name() const override {
        return "max";
    }

private:
    double m_min;
};



class Mean : public IStatistics {
public:
//    Mean() : m_mean{std::numeric_limits<double>::max()} {
//    }

    void update(double next) override {
        summ += next;
        ++quantity;
    }

    double eval() const override {
        double temp;
        temp = summ/quantity;
        return temp;
    }

    const char * name() const override {
        return "mean";
    }

private:
   // double m_mean;
    double summ = 0;
    double quantity = 0;
};


class Std : public IStatistics {
public:
//    Std() : m_mean{std::numeric_limits<double>::max()} {
//    }

    void update(double next) override {
        m_mean.push_back(next);
    }

    double eval() const override {
        double summ = 0;
        double quantity = 0;
        for (double v : m_mean)
        {
            summ  += v;
            ++quantity;
        }
        double mid = summ/quantity;
        double temp = 0;
        for (double v : m_mean)
        {
            temp += std::pow((v - mid), 2);
        }
        return std::sqrt(temp/quantity);;
    }

    const char * name() const override {
        return "std";
    }

private:
    std::vector<double> m_mean;

};













