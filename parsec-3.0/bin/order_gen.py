import numpy
import sys
def rand_gen(l, n ):
    return numpy.random.choice(l, n)

if __name__ == '__main__':
    l = sys.stdin.read().split()
    indices = rand_gen(len(l), int(sys.argv[1]))
    print(" ".join([l[i] for i in indices]))
