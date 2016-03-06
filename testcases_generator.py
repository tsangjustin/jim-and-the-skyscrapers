import sys
import random

f = open('testcases_gen.txt', 'wb')

sys.stdout = f

NUM_CASES = 15
MAX_TEST_CASES = 300000
MAX_HEIGHT = 1000000

for i in range (0, NUM_CASES):
	num_buildings = random.randrange(1, MAX_TEST_CASES)
	print num_buildings
	currline = ''
	for j in range(0, num_buildings):
		if j == num_buildings-1:
			currline += str(random.randrange(1, MAX_HEIGHT))
		else:
			currline += str(random.randrange(1, MAX_HEIGHT)) + ' '
	print currline
	print ''