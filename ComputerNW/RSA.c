#include <stdio.h>
#include <math.h>

double min(double x, double y) {
    return (x < y ? x : y);
}

double max(double x, double y) {
    return (x > y ? x : y);
}

double gcd(double a, double b) {
    if (a == b)
        return a;
    else
        return gcd(min(a, b), max(a, b) - min(a, b));
}

long double modular_exponentiation(long double base, long double exponent, long double modulus) {
    long double result = 1;
    while (exponent > 0) {
        if ((int)(fmodl(exponent, 2)) == 1) {
            result = fmodl((result * base), modulus);
        }
        base = fmodl((base * base), modulus);
        exponent /= 2;
    }
    return result;
}

int main() {
    long double prime1, prime2, phi, modulus, public_key, private_key, message, encrypted_message, decrypted_message;

    do {
        printf("\nEnter prime numbers P and Q : ");
        scanf("%Lf %Lf", &prime1, &prime2);
    } while (prime1 == prime2);

    modulus = prime1 * prime2;
    phi = (prime1 - 1) * (prime2 - 1);

    do {
        printf("\nEnter prime value of public key : ");
        scanf("%Lf", &public_key);
    } while ((gcd(public_key, phi) != 1) && public_key > phi);

    for (private_key = 1; private_key < phi; ++private_key) {
        if (fmod((public_key * private_key), phi) == 1)
            break;
    }
    printf("\nPrivate key within main = %Lf", private_key);
    printf("\nEnter the message : ");
        scanf("%Lf", &message);
    encrypted_message = modular_exponentiation(message, public_key, modulus);
    decrypted_message = modular_exponentiation(encrypted_message, private_key, modulus);
    printf("\nOriginal message : %Lf", message);
    printf("\nEncrypted message : %Lf", encrypted_message);
    printf("\nDecrypted message : %Lf", decrypted_message);
}
