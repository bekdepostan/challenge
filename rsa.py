import math

def egcd(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = egcd(b % a, a)
        return (g, x - (b // a) * y, y)

def modinv(a, m):
    g, x, y = egcd(a, m)
    if g != 1:
        raise Exception('modular inverse does not exist')
    else:
        return x % m

if __name__ == "__main__":

    # p and q are two prime number (for security purposes, the integers p and q should be chosen at random, and should be of similar bit-length)
    p = 9648423029010515676590551740010426534945737639235739800643989352039852507298491399561035009163427050370107570733633350911691280297777160200625281665378483
    q = 11874843837980297032092405848653656852760910154543380907650040190704283358909208578251063047732443992230647903887510065547947313543299303261986053486569407

    # c is the ciphered message (ciphered with the public key)
    c = 83208298995174604174773590298203639360540024871256126892889661345742403314929861939100492666605647316646576486526217457006376842280869728581726746401583705899941768214138742259689334840735\
633553053887641847651173776251820293087212885670180367406807406765923638973161375817392737747832762751690104423869019034

    # Totient
    t = (p - 1) * (q - 1)

    # modulo
    e = 65537

    # n is used as the modulus for both the public and private keys
    n = p * q

    # the public key is (n, e)
    # the private key is (n, d)

    d = modinv(e, t)

    print 'ciphered message is ' +  str(c)

    print 'Computing ' + str(c) + ' ^ ' + str(d) + ' mod ' + str(n)

    m = pow(c, d, n)

    print 'orginal message (int)' + str(m)
    
    # Wikipedia example for factoring
    # m = 65
    # print 'orginal message ' + str(m)

    # c = pow(m, e, n)
    # print 'ciphered message ' +  str(c)

    # m = pow(c, d, n)
    # print 'deciphered message = ' + str(m)
