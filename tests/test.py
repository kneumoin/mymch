import os, sys
from subprocess import Popen, PIPE

build_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))

tests = {'feb': '0 1 1 2 3 5 8 13 21 34 55 89 144 233 ',
	'rand': '',
	'hello': 'Hello World!',
	'sieve': '2357111317192329313741434753596167717379',}

failed = False

for test in tests:
	program_path = os.path.join(build_dir, 'programs', test + '.bf')
	exe = os.path.join(build_dir, 'mymch')
	p = Popen([exe, program_path], stdout = PIPE, stderr = PIPE)
	out, status = p.communicate()
	if not tests[test] and not status:
		ok = True
	else:
		ok = out == tests[test]
	status = p.wait()

	if ok:
		print "%s:\tPASS" % test
	else:
		print "%s:\tFAILED got:%r expect:%r" % (test, out, tests[test])
		failed = True

if failed:
	sys.exit(1)
sys.exit(0)
