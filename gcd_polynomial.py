#! /usr/bin/env python3
from sys import stdin
from fractions import Fraction
import functools

def normalize(poly):
    while poly and poly[-1] == 0:
        poly.pop()
    if poly == []:
        poly.append(0)


def poly_div(num, den):
    num = num[:]
    normalize(num)
    den = den[:]
    normalize(den)

    if len(num) >= len(den):
        shift = len(num) - len(den)
        den = [0] * shift + den
    else:
        return [0], num

    quot = []
    divisor = Fraction(den[-1])
    for i in range(shift + 1):
        mult = num[-1] / divisor
        quot = [mult] + quot
        if mult != 0:
            d = [mult * u for u in den]
            num = [u - v for u, v in zip(num, d)]
        num.pop()
        den.pop(0)

    normalize(num)
    return quot, num

def ggtPoly(X):
    X[-1] = X[-1].strip()
    P = [Fraction(elem) for elem in X[0].split()]
    Q = [Fraction(elem) for elem in X[1].split()]
    degP = len(P)
    degQ = len(Q)
    r = 1

    while r != [0]:
        if degP < degQ:
            q, r = poly_div(Q, P)
            P = Q
            Q = r
        else:
            q, r = poly_div(P, Q)
            P = Q
            Q = r

    for i in range(0,len(P)):
        P[i] = P[i]/P[-1]


for line in stdin:
    X = [str(elem) for elem in line.split(" , ")]
    ggtPoly(X)
