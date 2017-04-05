m=input()
n=input()
l=0
r=1
while r**m<n: 
	r*=2
while l<r:
	o=(l+r)//2+1
	x=o**m
	if x<=n:
		l=o
	else:
		r=o-1
print l
