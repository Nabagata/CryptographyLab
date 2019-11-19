import argparse
import itertools


def initialize_K(key):
    K = []
    key = itertools.cycle(key)
    for i in xrange(256):
        K.append(key.next())
    return K


def initialize_S(K):
    S = range(256)
    j = 0
    for i in xrange(256):
        j = (j + S[i] + K[i]) % 256
        S[i], S[j] = S[j], S[i]

    return S


def get_X(S, length, print_x=False):
    i = 0
    j = 0

    for x in xrange(length):
        i = (i + 1) % 256
        j = (j + S[i]) % 256
        S[i], S[j] = S[j], S[i]
        m = (S[i] + S[j]) % 256
        X = S[m]
        if print_x:
            print X
        yield X


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Implements RC4 encryption.')
    parser.add_argument('-k', '--key', type=str, default='12345', help='The key used for encryption.')
    parser.add_argument('-m', '--message', type=str, required=True, help='The message to be encrypted.')
    parser.add_argument('-x', dest='x', action='store_true', help='Whether or not to print out the X values.')
    parser.set_defaults(x=False)

    args = parser.parse_args()

    key = [ord(k) - ord('0') for k in args.key]

    K = initialize_K(key)
    S = initialize_S(K)

    X = get_X(S, len(args.message), args.x)

    ciphertext = []
    for char in args.message:
        ciphertext.append(chr(ord(char) ^ X.next()))

    print ''.join(ciphertext)