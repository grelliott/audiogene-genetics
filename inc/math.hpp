/*
 * Copyright 2020 Grant Elliott <grant@grantelliott.ca>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

//TODO look at c++20 module
#pragma once

#include <chrono>
//#include <concepts>
#include <random>
#include <type_traits>
#include <utility>
#include <vector>

namespace audiogene {

class Math {
    // would be ideal to have this instantiated here and not need the callers to need a Math object
    mutable std::default_random_engine _rng;

 public:
    Math() {
        _rng.seed(std::chrono::system_clock::now().time_since_epoch().count());
    }

    bool flipCoin() const {
        std::uniform_int_distribution<int> d(0, 1);
        return d(_rng) == 0;
    }

    bool didEventOccur(const double probability) const {
        std::uniform_real_distribution<double> d(0.0, 1.0);
        return d(_rng) >= probability;
    }

    // TODO(grant) look into C++20 concepts for some of these
    // see https://youtu.be/ImLFlLjSveM?t=2350
    // eg these could be changed to remove this templating boilerplate
    // or adjusted to expand/constrain their accepted types
    template<
        typename T,
        typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
    >
    T similarity(const T ideal, const T actual, const T min, const T max) const {
        return 1 - std::abs(ideal - actual) / max - min;
    }

    template<
        typename T,
        typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
    >
    bool inRange(T current, T min, T max) const {
        return (current >= min && current <= max);
    }

    template<
        typename T,
        typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
    >
    T clip(T desired, T min, T max) const {
        if (desired < min) return min;
        if (desired > max) return max;
        return desired;
    }

    template<
        typename T,
        typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
    >
    T stddev(const T min, const T max) const {
        return (max - min) / 6;
    }

    template<
        typename T,
        typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
    >
    T normalDistribution(const T mean, const T stddev) const {
        std::normal_distribution<T> d(mean, stddev);
        return d(_rng);
    }

    // these could be comparable
    // ie equality_comparable
    // also may not need to define the vector, but instead maybe a container that has orderable elements
    // maybe it should return a pair of Ts?
    template<
        typename T
    >
    std::pair<int, int> uniquePair(const std::vector<T>& container) const {
        std::uniform_int_distribution<int> choose(0, std::distance(container.begin(), container.end() - 1));
        int first = choose(_rng);
        int second;
        do {
            second = choose(_rng);
        } while (second == first);
        return std::make_pair(first, second);
    }
};

}  // namespace audiogene
