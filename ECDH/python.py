#!/bin/python


def p(res):
	bs = res.to_bytes(10, byteorder='big')
	for b in reversed(bs):
		print('0x{:02x}'.format(b), end = ' ')
	print('')

# a 4DD25E754270071AC1DD
# b 0AC9DA69B0E46B48AFAF

a = 0x4DD25E754270071AC1DD
b = 0x0AC9DA69B0E46B48AFAF
prim = 0x62CE5177412ACA899CF5
result = 0;
for x in range(79,-1,-1):
	result = result * 2;
	bit = (b & (0x1 << x)) >> x
	if bit:
		result = result + a
	p(result)
	if result > prim:
		result = result - prim
	if result > prim:
		resutl = result - prim

	# print(bit, end = ' ')


	# shiftl(out);
	# 	printHex(out);
	# 	if(getbit(b, i))
	# 		add(out, out, a);
	# 	if(geprime(out))
	# 		sub(out, out, prime);
	# 	if(geprime(out))
	# 		sub(out, out, prime);
	# 	assert(cmp(out, prime) < 0);