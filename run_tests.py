from os import listdir, path
import subprocess
from subprocess import Popen, PIPE, STDOUT

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'


def compile_and_execute(code):
    with open('test.s', 'w') as f:
        p = Popen('compile', stdout=f, stdin=PIPE, stderr=STDOUT)
        p.communicate(code)
    subprocess.call(['gcc', 'test.s', 'runtime.c'])
    return subprocess.check_output('a.out')


def run():
    files = listdir('test')
    no_tests = 0
    failed = 0
    for fi in files:
        with open(path.join('test',fi), 'r') as f:
            tests = f.read().rstrip().split('\n\n')
            no_tests += len(tests)
            for test in tests:
                lines = test.split("\n")
                code = "\n".join(lines[:-1])
                expected = lines[-1]
                got = compile_and_execute(code)
                if expected != got:
                    failed += 1
                    print "\n%sFAILED%s %s" % (bcolors.FAIL, bcolors.ENDC, code)
                    print "Expected %s%s%s" % (bcolors.OKGREEN,expected, bcolors.ENDC)
                    print "Got %s%s%s\n" % (bcolors.FAIL, got, bcolors.ENDC)
                else:
                    print "%sPASSED%s %s" % (bcolors.OKGREEN, bcolors.ENDC, code)
    print ""
    print "Failed %d tests" % failed
    print "Passed %d tests" % (no_tests - failed)

    color = bcolors.OKGREEN
    if failed > 0:
        color = bcolors.FAIL
    print "Ran %s%d%s tests" % (color, no_tests, bcolors.ENDC)
        
    

if __name__ == '__main__':
    run()