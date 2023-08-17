#ifndef BIGINT128_H
#define BIGINT128_H

class BigInt128 {
private:
    unsigned long long low;
    unsigned long long high;

public:
    BigInt128();
    BigInt128(unsigned long long value);
    BigInt128(unsigned long long high, unsigned long long low);

    BigInt128 operator+(const BigInt128& other) const;
    BigInt128 operator-(const BigInt128& other) const;
    BigInt128 operator*(const BigInt128& other) const;
    BigInt128 operator/(const BigInt128& other) const;
    BigInt128 operator%(const BigInt128& other) const;

    // Convert to string for display
    char* to_string(char* buffer, unsigned int size) const;
};

// BigInt128 implementation

BigInt128::BigInt128() : low(0), high(0) {}

BigInt128::BigInt128(unsigned long long value) : low(value), high(0) {}

BigInt128::BigInt128(unsigned long long high, unsigned long long low) : low(low), high(high) {}

BigInt128 BigInt128::operator+(const BigInt128& other) const {
    BigInt128 result;
    unsigned long long carry = 0;

    result.low = low + other.low;
    if (result.low < low) {
        carry = 1;
    }

    result.high = high + other.high + carry;

    return result;
}

BigInt128 BigInt128::operator-(const BigInt128& other) const {
    BigInt128 result;
    unsigned long long borrow = 0;

    result.low = low - other.low;
    if (result.low > low) {
        borrow = 1;
    }

    result.high = high - other.high - borrow;

    return result;
}

BigInt128 BigInt128::operator*(const BigInt128& other) const {
    BigInt128 result;

    unsigned long long a = high;
    unsigned long long b = low;
    unsigned long long c = other.high;
    unsigned long long d = other.low;

    // Basic multiplication algorithm (ignoring carry)
    unsigned long long ac = a * c;
    unsigned long long ad = a * d;
    unsigned long long bc = b * c;
    unsigned long long bd = b * d;

    result.high = ac + (ad >> 64) + (bc >> 64);
    result.low = (ad << 64) + (bd & 0xFFFFFFFFFFFFFFFFULL);

    return result;
}

BigInt128 BigInt128::operator/(const BigInt128& other) const {
    if (other == BigInt128(0)) {
        // Handle division by zero
        // Return a special value or throw an exception
    }

    BigInt128 quotient;
    BigInt128 remainder = *this;

    while (remainder >= other) {
        quotient = quotient + BigInt128(1);
        remainder = remainder - other;
    }

    return quotient;
}

BigInt128 BigInt128::operator%(const BigInt128& other) const {
    if (other == BigInt128(0)) {
        // Handle division by zero
        // Return a special value or throw an exception
    }

    BigInt128 remainder = *this;

    while (remainder >= other) {
        remainder = remainder - other;
    }

    return remainder;
}

char* BigInt128::to_string(char* buffer, unsigned int size) const {
    const unsigned int buffer_size = 33; // 32 hex digits + null terminator
    if (size < buffer_size) {
        return nullptr; // Insufficient buffer size
    }

    char temp[buffer_size];
    unsigned long long temp_high = high;
    unsigned long long temp_low = low;

    for (int i = buffer_size - 2; i >= 0; --i) {
        temp[i] = "0123456789ABCDEF"[temp_low & 0xF];
        temp_low >>= 4;
    }
    temp[buffer_size - 1] = '\0';

    snprintf(buffer, size, "%016llx%016s", temp_high, temp);

    return buffer;
}

#endif // BIGINT128_H
