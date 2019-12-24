import numpy
import sys
import subprocess

def rand_gen(l, n ):
    return numpy.random.choice(l, n)

def hill_climb(l, n):
    opts = []
    print("here")
    for i in range(n):
        p_min = 30.0
        min_opt = ""
        trys = numpy.random.choice(l, 5, replace= False) 
        for t in trys:
           p = eval_opt(opts+[t])

           print(p)
           if p < p_min:
               p_min = p
               min_opt = t
        opts.append(min_opt)
    return opts

def approx_hill_climb(l, n):
    opts = []
    p_min = 30.0
    min_opt = ""
    for i in range(n):
        # select using model
        opts.append(min_opt)
    return opts

def eval_opt(opts):
    print(opts)
    f = open("opt.txt", "w")
    f.write(" ".join(opts))
    f.close()
    out = subprocess.check_output(['./eval.sh'],universal_newlines = True)
    return float(out.split(" ")[0])


if __name__ == '__main__':
    l = sys.stdin.read().split()
    n = int(sys.argv[1])
    if len(sys.argv) < 3 or sys.argv[2] == "random":
        print("random")
        indices = rand_gen(len(l), n)
        print(" ".join([l[i] for i in indices]))
    elif sys.argv[2] == "hill":
        print("hill")
        print(" ".join(hill_climb(l, n)))
    else:
        print("method not found")



    
