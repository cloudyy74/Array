#pragma once

#include <cstddef>
#include <cstdint>
#include <stdexcept>

namespace containers {
    
    template<typename T, std::size_t N>
    class my_array {
    public:
        const T& at(std::size_t index) const {
            if (index >= N) {
                throw std::out_of_range("Array index out of range.");
            }
            return array_[index];
        }
        
        T& at(std::size_t index) {
            if (index >= N) {
                throw std::out_of_range("Array index out of range.");
            }
            return array_[index];
        }

        const T& operator[](std::size_t index) const {
            return array_[index];
        }

        T& operator[](std::size_t index) {
            return array_[index];
        }

        bool empty() const {
            return N == 0;
        }

        std::size_t size() const {
            return N;
        }

        void fill(const T& value) {
            for (std::size_t i = 0; i < N; ++i) {
                array_[i] = value;
            }
        }
    private:
        T array_[N]{};
    };

    bool get_bit(uint8_t byte, std::size_t pos) {
        return (bool) (byte & (1 << pos));
    }

    void set_bit(uint8_t& byte, std::size_t pos, bool value) {
        if (value == false) {
            byte &= ~(1 << pos);
        }
        else {
            byte ^= (1 << pos);
        }
    }

    class bit_ref {
    public:
        bit_ref(uint8_t& byte, std::size_t bit_index) : byte_(byte), bit_index_(bit_index) {};

        bit_ref& operator=(bool value) {
            set_bit(byte_, bit_index_, value);
            return *this;
        }

        bit_ref& operator=(bit_ref& value) {
            if (this == &value) {
                return *this;
            }
            set_bit(byte_, bit_index_, value);
            return *this;
        }

        operator bool() {
            return get_bit(byte_, bit_index_);
        }
    private:
        uint8_t& byte_;
        std::size_t bit_index_;
    };
    
    template<std::size_t N>
    class my_array<bool, N> {
    public:
        bool at(std::size_t index) const {
            if (index >= N) {
                throw std::out_of_range("Array index out of range.");
            }
            return get_bit(array_[index / 8], index % 8);
        }

        bit_ref at(std::size_t index) {
            if (index >= N) {
                throw std::out_of_range("Array index out of range.");
            }
            return bit_ref(array_[index / 8], index % 8);
        }

        bool operator[](std::size_t index) const {
            return get_bit(array_[index / 8], index % 8);
        }

        bit_ref operator[](std::size_t index) {
            return bit_ref(array_[index / 8], index % 8);
        }

        bool empty() const {
            return N == 0;
        }

        std::size_t size() const {
            return N;
        }

        void fill(bool value) {
            int8_t new_value = (value) ? ~0 : 0;
            for (std::size_t i = 0; i < (N + 7) / 8; ++i) {
                array_[i] = new_value;
            }
        }
    private:
        uint8_t array_[(N + 7) / 8]{};
    };  
}
 